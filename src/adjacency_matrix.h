//
// Created by hsj on 4/19/18.
//

#ifndef UNTITLED_ADJACENCY_MATRIX_H
#define UNTITLED_ADJACENCY_MATRIX_H

#include <vector>
#include "student_information.h"
#include "section_information.h"

class AdjacencyMatrix {
    
private:
    std::vector<std::vector<int>> adjacency_matrix_;
    std::vector<bool> session_visited_by_current_student;
    int number_of_students = 0;
    int number_of_sections = 0;
    int number_of_total_section_vertex = 0;
    int capacity = 0;
    
    //Three vectors to store the results
    
    std::vector<int> matching_result_vector;
    std::vector<std::string> unmatched_students;
    std::vector<std::string> available_sessions;
    
public:
    
    explicit AdjacencyMatrix(StudentInformation student_information,
                             SectionInformation section_information,
                             int seat_number);
    
    void ImportMatrixFromFile(std::string path, SectionInformation information);
    
    bool BipartiteMatchingSingleStudent(int current_student_index);
    
    int BipartiteMatchingEntireSystem(StudentInformation students,
                                      SectionInformation sections, int capacity);
    
    std::vector<std::pair<std::string, std::string>> GetMatchingVector();
    
    std::vector<std::string> ListOfMatching(StudentInformation students,
                                            SectionInformation sections,
                                            int capacity);
    
    int EdgeConditionInMatrix(int i, int j);
};


#endif //UNTITLED_ADJACENCY_MATRIX_H

