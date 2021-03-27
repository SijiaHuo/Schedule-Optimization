//
// Created by hsj on 4/19/18.
//

#include "student_information.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define CHOICE_NUM 3

/*
 * Collect the student information and section information
 * from the file. Construct the object for the student and
 * the section at the same time.
 */
void StudentInformation::ImportInformationFromFile
(std::string path, SectionInformation &information) {
    
    //Open the file according to the path
    std::ifstream survey_file(path);
    
    //Check the validity of the path
    if (!survey_file) {
        std::cout << "invalid file path" << std::endl;
        return;
    }
    
    std::string current_line;
    std::vector<std::string> current_line_vector;
    
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
        
        std::string current_student_name = current_line_vector.at(0);
        
        //Change all words to lower case to avoid case-redundancy
        ToLowerWord(current_student_name);
        
        //Add the name to the map of students
        AddStudentToBook(next_new_student_number_, current_student_name);
        next_new_student_number_ += 1;
        
        //convert the sessions to lower case, check to see whether exist in the vector
        //If not, insert to the list
        
        for (auto i = 1; i < CHOICE_NUM + 1; i++) {
            ToLowerWord(current_line_vector.at(i));
            information.AddSessionToList(current_line_vector.at(i));
        }
        
        //Clean the vector for next iteration
        current_line_vector.clear();
    }
    
}

/*
 * Convert the string to all lower cases to avoid case sensitivity
 */
void ToLowerWord(std::string &input_string) {
    std::transform(input_string.begin(), input_string.end(),
                   input_string.begin(), ::tolower);
}

/*
 * Insert the student and its corresponding index to the hash table
 * So that later can match the index of vertex with the student's name
 */
void StudentInformation::AddStudentToBook(int number, std::string name) {
    student_book_[number] = name;
}

/*
 * Look up the student's name given the index of the "vertex" in the bipartite graph
 * The function is used to display the results in the application
 */
std::string StudentInformation::FindStudentName(int number) {
    auto student_number = student_book_.find(number);
    if (student_number == student_book_.end()) {
        std::cout << "The name of student is not found!" << std::endl;
        return "";
    }
    return student_number->second;
}

/*
 * Query function to get the number of students enrolled.
 * The function is used for testing the constructor.
 */
long StudentInformation::GetTotalStudentSize() {
    return student_book_.size();
}

