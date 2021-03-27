//
// Created by Sijia Huo on 3/6/18.
//


#include "student_information_tests.h"
#include <iostream>
#include "catch.h"
#include "../src/student_information.h"


TEST_CASE("import_right_student_inform_from_file_student") {
    StudentInformation students_book;
    SectionInformation section_list;
    std::string path = "/Users/hsj/Desktop/test-file.txt";
    students_book.ImportInformationFromFile(path, section_list);
    REQUIRE(students_book.GetTotalStudentSize() == 15);
}

TEST_CASE("import_right_student_inform_from_file_gradebook") {
    StudentInformation students_book;
    SectionInformation section_list;
    std::string path = "/Users/hsj/Desktop/test-file.txt";
    students_book.ImportInformationFromFile(path, section_list);
    REQUIRE(section_list.GetTotalNumberOfSessions() == 6);
}

TEST_CASE("to_lower_word_test") {

    std::string before_formate = "UpperLower";
    ToLowerWord(before_formate);
    REQUIRE(before_formate == "upperlower");
}

TEST_CASE("find_student_name_test") {
    StudentInformation students_book;
    SectionInformation section_list;
    std::string path = "/Users/hsj/Desktop/test-file.txt";
    students_book.ImportInformationFromFile(path, section_list);
    REQUIRE(students_book.FindStudentName(2) == "student_c");
    REQUIRE(students_book.FindStudentName(4) == "student_e");
}
