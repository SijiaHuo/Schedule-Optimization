//
// Created by hsj on 5/2/18.
//

#include "adjacency_matrix_test.h"
#include <iostream>
#include "catch.h"
#include "../src/student_information.h"
#include "../src/section_information.h"
#include "../src/adjacency_matrix.h"

TEST_CASE("import_matrix_from_file_test") {

    StudentInformation students_book;
    SectionInformation section_list;
    std::string path = "/Users/hsj/Desktop/test-file.txt";
    students_book.ImportInformationFromFile(path, section_list);
    AdjacencyMatrix adj_mtx(students_book, section_list, 3);
    adj_mtx.ImportMatrixFromFile(path, section_list);

    //Test whether the edge is added to the right place
    REQUIRE(adj_mtx.EdgeConditionInMatrix(1, 0) == 0);
    REQUIRE(adj_mtx.EdgeConditionInMatrix(0, 1) == 1);
}


TEST_CASE("matching_for_single_student_test") {

    StudentInformation students_book;
    SectionInformation section_list;
    std::string path = "/Users/hsj/Desktop/test-file.txt";
    students_book.ImportInformationFromFile(path, section_list);
    AdjacencyMatrix adj_mtx(students_book, section_list, 3);
    adj_mtx.ImportMatrixFromFile(path, section_list);
    //In our example, all student get matched
    REQUIRE(adj_mtx.BipartiteMatchingSingleStudent(0));
    REQUIRE(adj_mtx.BipartiteMatchingSingleStudent(3));
}