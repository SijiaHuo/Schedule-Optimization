//
// Created by hsj on 5/2/18.
//

#include "section_information_test.h"
#include <iostream>
#include "catch.h"
#include "../src/student_information.h"
#include "../src/section_information.h"


TEST_CASE("add_section_to_list_test") {

    StudentInformation students_book;
    SectionInformation section_list;
    std::string path = "/Users/hsj/Desktop/test-file.txt";
    students_book.ImportInformationFromFile(path, section_list);
    section_list.AddSessionToList("section_x");
    //Check the size of the newly added list
    REQUIRE(section_list.GetTotalNumberOfSessions() == 7);
}

TEST_CASE("find_section_time_test") {

    StudentInformation students_book;
    SectionInformation section_list;
    std::string path = "/Users/hsj/Desktop/test-file.txt";
    students_book.ImportInformationFromFile(path, section_list);
    REQUIRE(section_list.FindSessionTime(3, 3) == "section2");
    REQUIRE(section_list.FindSessionTime(2, 3) == "section1");
}

TEST_CASE("get_index_test") {

    StudentInformation students_book;
    SectionInformation section_list;
    std::string path = "/Users/hsj/Desktop/test-file.txt";
    students_book.ImportInformationFromFile(path, section_list);
    REQUIRE(section_list.GetIndexOfCertainSession("section2") == 1);
    REQUIRE(section_list.GetIndexOfCertainSession("section4") == 2);
}