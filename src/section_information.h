//
// Created by hsj on 4/19/18.
//

#ifndef UNTITLED_SECTION_INFORMATION_H
#define UNTITLED_SECTION_INFORMATION_H

#include <string>
#include <vector>

class SectionInformation {
    
private:
    std::vector<std::string> section_list_;
    
public:
    SectionInformation() = default;
    
    void AddSessionToList(std::string name);
    
    std::string FindSessionTime(int number, int class_capacity);
    
    long GetIndexOfCertainSession(std::string session_time);
    
    long GetTotalNumberOfSessions();
    
};


#endif //UNTITLED_SECTION_INFORMATION_H

