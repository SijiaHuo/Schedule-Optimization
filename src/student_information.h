//
// Created by hsj on 4/19/18.
//

#ifndef UNTITLED_STUDENT_INFORMATION_H
#define UNTITLED_STUDENT_INFORMATION_H

#include <string>
#include <map>
#include "section_information.h"

class StudentInformation {
    
private:
    std::map<int, std::string> student_book_;
    int next_new_student_number_ = 0;
    
public:
    
    StudentInformation() = default;
    
    void ImportInformationFromFile(std::string path, SectionInformation &information);
    
    void AddStudentToBook(int number, std::string name);
    
    std::string FindStudentName(int number);
    
    long GetTotalStudentSize();
    
    
};

//General helper function to solve case sensitive issue
void ToLowerWord(std::string &input_string);


#endif //UNTITLED_STUDENT_INFORMATION_H

