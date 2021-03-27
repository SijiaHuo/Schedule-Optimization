//
// Created by hsj on 4/19/18.
//

#include "adjacency_matrix.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#define CHOICE_NUM 3

/*
 * A constructor to build empty variable to hold the edges and vertices
 * Use the student/section information to determine the dimension
 * of the matrix
 */
AdjacencyMatrix::AdjacencyMatrix(StudentInformation student_information,
                                 SectionInformation section_information,
                                 int seat_number) {
    
    number_of_sections = (int) section_information.GetTotalNumberOfSessions();
    number_of_students = (int) student_information.GetTotalStudentSize();
    capacity = seat_number; //Assign variable
    number_of_total_section_vertex = seat_number * number_of_sections; //Total seats
    
    //Create a blank adjacency matrix
    adjacency_matrix_ = std::vector<std::vector<int> >
    ((u_int64_t) number_of_students,
     std::vector<int>((u_int64_t) number_of_total_section_vertex, 0));
    
    //Create a blank session_visited_by_current_student
    session_visited_by_current_student = std::vector<bool>
    ((u_int64_t) number_of_total_section_vertex, false);
    
    //Create a blank matching_result_vector
    matching_result_vector = std::vector<int>
    ((u_int64_t) number_of_total_section_vertex, -1);
    
}

/*
 * Filling in the adjacency matrix according to the import file
 */
void AdjacencyMatrix::ImportMatrixFromFile(std::string path,
                                           SectionInformation information) {
    
    //Open the file according to the path
    std::ifstream survey_file(path);
    
    //Check the validity of the path
    if (!survey_file) {
        std::cout << "invalid file path" << std::endl;
        return;
    }
    
    std::string current_line;
    std::vector<std::string> current_line_vector;
    int current_student_index = 0;
    
    while (getline(survey_file, current_line)) {
        
        //extract the information, split by white space
        std::istringstream iss(current_line);
        
        //split the words of each line
        //This chunk is adapted from stack overflow
        //https://stackoverflow.com/questions/236129/the-most-elegant-way-to-iterate-the-words-of-a-string?
        //utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa
        
        do {
            std::string substring;
            iss >> substring;
            current_line_vector.push_back(substring);
        } while (iss);
        
        //convert the sessions to lower case, check to see the index of session
        
        for (auto i = 1; i < CHOICE_NUM + 1; i++) {
            ToLowerWord(current_line_vector.at(i));
            long session_starting_node_index =
            information.GetIndexOfCertainSession(current_line_vector.at(i)) * capacity;
            
            //Add edges to the adjacent matrix if should
            for (auto j = session_starting_node_index;
                 j < session_starting_node_index + capacity; j++) {
                adjacency_matrix_[current_student_index][j] = 1;
            }
        }
        
        //Clean the vector for the next iteration
        current_line_vector.clear();
        current_student_index++;
    }
}


/*
 * The following two parts of bipartite matching are adapted from the GeeksforGeeks at
 * https://www.geeksforgeeks.org/maximum-bipartite-matching/
 * The function is to find a seat for student, if there's no seat available, find the
 * person that occupies the potential seat, try to find another feasible seat for that person
 * return true if the student can get matched, false otherwise
 */
bool AdjacencyMatrix::BipartiteMatchingSingleStudent(int current_student_index) {
    // Try every job one by one
    for (int i = 0; i < number_of_total_section_vertex; i++) {
        // If student i can take session j and the seat is not occupied
        if (adjacency_matrix_[current_student_index][i] && !session_visited_by_current_student[i]) {
            session_visited_by_current_student[i] = true; // Mark i as occupied
            
            // If session 'i' is not assigned OR
            // previously assigned student for the session
            // has an alternate feasible choice.
            // Since i is marked as occupied in the above line, matchR[v]
            // in the following recursive call will not get job 'i' again
            if (matching_result_vector[i] == -1 ||
                BipartiteMatchingSingleStudent(matching_result_vector[i])) {
                matching_result_vector[i] = current_student_index;
                return true;
            }
        }
    }
    return false;
}

/*
 * Loop over the list for all students in the dictionary.
 * Print out all the possible matching accordingly.
 */
int AdjacencyMatrix::BipartiteMatchingEntireSystem(StudentInformation students,
                                                   SectionInformation sections, int capacity) {
    
    int current_max_matching = 0; // Count the maximum matching so far
    
    for (auto i = 0; i < number_of_students; i++) {
        
        // Mark all sessions as not seen for next applicant.
        
        std::fill(session_visited_by_current_student.begin(),
                  session_visited_by_current_student.end(), false);
        
        // Find if the applicant 'u' can get a job
        if (BipartiteMatchingSingleStudent(i)) {
            current_max_matching++;
        } else {
            //record the student who's unable to find the session
            std::string unmatched_student_name = students.FindStudentName(i);
            unmatched_students.push_back(unmatched_student_name);
        }
    }
    
    //Check the available seats
    for (int i = 0; i < matching_result_vector.size(); i++) {
        if (matching_result_vector[i] == -1) {
            std::string available_session_name = sections.FindSessionTime(i, capacity);
            available_sessions.push_back(available_session_name);
        }
    }
    
    //Print out the maximum matching results
    std::cout << current_max_matching << " students get matched successfully!" << std::endl;
    std::cout << "The matching results are as following:" << std::endl;
    
    //Print out the pairs that can get matched
    for (int i = 0; i < matching_result_vector.size(); i++) {
        std::cout << sections.FindSessionTime(i, capacity) << ": ";
        std::cout << students.FindStudentName(matching_result_vector[i]) << std::endl;
    }
    
    return current_max_matching;
}

/*
 * Return a vector containing at most twenty matchings in the system.
 * Each matching is wrapped in a string.
 * This function is used for testing and displaying results in the application
 */
std::vector<std::string> AdjacencyMatrix::ListOfMatching(StudentInformation students,
                                                         SectionInformation sections,
                                                         int capacity) {
    
    std::vector<std::string> result_vector;
    std::string matching_pair;
    u_long output_size;
    if (matching_result_vector.size() <= 20) {
        output_size = matching_result_vector.size();
    } else {
        output_size = 20; //Only output 20 matching regardingly
    }
    
    //Use the index to find the real string information of the student and the section
    //Conjunct the information together as a string.
    for (int i = 0; i < output_size; i++) {
        matching_pair = sections.FindSessionTime(i, capacity)
        + ":\n " + students.FindStudentName(matching_result_vector[i]);
        result_vector.push_back(matching_pair);
    }
    return result_vector;
}

/*
 * Query function to show the information inside the adjacency matrix
 */
int AdjacencyMatrix::EdgeConditionInMatrix(int i, int j) {
    return adjacency_matrix_[i][j];
}

