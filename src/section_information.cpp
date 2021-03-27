//
// Created by hsj on 4/19/18.
//

#include "section_information.h"
#include <iostream>

/*
 * This function checks whether the object course is inside the list.
 * If not, add the object to the list
 */
void SectionInformation::AddSessionToList(std::string name) {
    
    //Check whether the session is already in the list (case insensitive)
    if (std::find(section_list_.begin(), section_list_.end(), name) !=
        section_list_.end()) {
        return;
        
    } else {
        section_list_.push_back(name);
    }
    
}

/*
 * Find the time of the object (session) according to the index of the matrix
 * and the capacity of the class. For instance, the index 0-2 in the second dimension
 * of the matrix should corresponds to the first object (session) in the list
 */
std::string SectionInformation::FindSessionTime(int location_in_matrix,
                                                int class_capacity) {
    
    //Find the index of the object (session) in the section_list_
    
    u_long index_of_the_class;
    
    if (((location_in_matrix + 1) % class_capacity) == 0) {
        index_of_the_class = (location_in_matrix + 1) / class_capacity - 1;
    } else {
        index_of_the_class = (location_in_matrix + 1) / class_capacity;
    }
    
    //Find the time of the session in the list, according to the index of the list
    
    return section_list_.at(index_of_the_class);
}

/*
 * Given the string of session_time, the function returns the index
 * of such object(session) in the section_list_.
 */
long SectionInformation::GetIndexOfCertainSession(std::string session_time) {
    
    
    auto matched_session = std::find(section_list_.begin(),
                                     section_list_.end(), session_time);
    
    if (matched_session == section_list_.end()) {
        std::cout << "Invalid time period" << std::endl;
        return -1;
    }
    return std::distance(section_list_.begin(), matched_session);
}

/*
 * Query function to get the number of sessions in the list
 */

long SectionInformation::GetTotalNumberOfSessions() {
    return section_list_.size();
}

