//
// Created by hsj on 4/27/18.
//

#ifndef FINALPROJECTMATCHING_EVENTS_TIME_H
#define FINALPROJECTMATCHING_EVENTS_TIME_H


#include <vector>
#include <string>
#include <utility>


struct Event {
    std::pair<int, int> event_time_start;
    std::pair<int, int> event_time_end;
};

class EventTime {
    
private:
    
    std::vector<Event> event_time_list_;
    
public:
    
    explicit EventTime(std::string input_string);
    
    std::pair<int, int> SplitTimeToHourMinute(std::string input_hour);
    
    void SortEvents();
    
    void PrintEventList();
    
    bool NoConflict(Event taken_event, Event undecided_event);
    
    std::vector<std::string> EventChoosing();
    
    Event TimeOfOneSlot(int index);
};

// Other helper function regarding the Event struct
bool FinishEarlier(Event event_a, Event event_b);

std::string TurnEventToString(Event event);


#endif //FINALPROJECTMATCHING_EVENTS_TIME_H


