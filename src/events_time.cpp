//
// Created by hsj on 4/27/18.
//

#include "events_time.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>


/*
 * Construct the EventTime object from the input_string
 * Split the string, construct the Event struct and
 * push the object to vector
 */
EventTime::EventTime(std::string input_string) {
    
    //Split the input string by comma
    
    std::stringstream ss(input_string);
    std::vector<std::string> time_string_vector;
    
    while (ss.good()) {
        std::string substr;
        getline(ss, substr, ';');
        time_string_vector.push_back(substr);
    }
    
    //Convert the string vector to the pair vector
    for (auto event:time_string_vector) {
        
        //Split the starting time and the end time
        std::stringstream one_event_stream(event);
        std::string starting_time;
        std::string ending_time;
        
        getline(one_event_stream, starting_time, ',');
        getline(one_event_stream, ending_time, ',');
        
        //Split the time by "-" on starting time and end time
        std::pair<int, int> new_event_begin = SplitTimeToHourMinute(starting_time);
        std::pair<int, int> new_event_end = SplitTimeToHourMinute(ending_time);
        
        struct Event eve;
        eve.event_time_start = new_event_begin;
        eve.event_time_end = new_event_end;
        event_time_list_.push_back(eve);
        
    }
}

/*
 * Split the string of time into a pair of hour and minute
 */
std::pair<int, int> EventTime::SplitTimeToHourMinute(std::string const input_hour) {
    
    //Split the time by "-" on starting time and end time
    std::stringstream starting_stream(input_hour);
    std::string hour_time;
    std::string minute_time;
    getline(starting_stream, hour_time, '-');
    getline(starting_stream, minute_time, '-');
    
    //form pair for the time
    std::pair<int, int> new_event;
    new_event = std::make_pair(std::stoi(hour_time), std::stoi(minute_time));
    return new_event;
};

/*
 * Compare two events to determine which event finishes earlier
 * Return true if event_a finishes earlier, false otherwise
 */
bool FinishEarlier(Event event_a, Event event_b) {
    
    if (event_a.event_time_end.first < event_b.event_time_end.first) {
        return true;
    } else if ((event_a.event_time_end.first == event_b.event_time_end.first)
               && (event_a.event_time_end.second < event_b.event_time_end.second)) {
        return true;
    } else {
        return false;
    }
}

/*
 * Sort a list of events (inside the EventTime object) according the finish time
 */
void EventTime::SortEvents() {
    std::sort(event_time_list_.begin(), event_time_list_.end(), FinishEarlier);
}

/*
 * Print out all the time stored in the event list
 * The function is used for testing and checking correctness
 */
void EventTime::PrintEventList() {
    for (Event event:event_time_list_) {
        std::cout << event.event_time_start.first << ":" << event.event_time_start.second << " to ";
        std::cout << event.event_time_end.first << ":" << event.event_time_end.second << std::endl;
        
    }
}

/*
 * Check whether the undecided_event time conflicts with the taken_event.
 * Return true if no conflict, false if have conflict.
 */
bool EventTime::NoConflict(Event taken_event, Event undecided_event) {
    
    /*undecided_event end time should be earlier than the start
     * time of the taken_event
     */
    
    if (undecided_event.event_time_start.first > taken_event.event_time_end.first) {
        return true;
    } else if ((undecided_event.event_time_start.first == taken_event.event_time_end.first)
               && (undecided_event.event_time_start.second >= taken_event.event_time_end.second)) {
        return true;
    } else {
        return false;
    }
}

/*
 * Wrapping up function to choose the optimal list of events with no conflict
 */
std::vector<std::string> EventTime::EventChoosing() {
    
    std::vector<std::string> result;
    
    //The first event after sorting should be included
    bool have_selected_first_event = false;
    Event current_last_event;
    
    
    //Lopp over the event list
    for (Event event: event_time_list_) {
        if (!have_selected_first_event) {
            result.push_back(TurnEventToString(event));
            current_last_event = event;
            have_selected_first_event = true;
        } else {
            
            //Check whether have conflict
            if (NoConflict(current_last_event, event)) {
                result.push_back(TurnEventToString(event));
                current_last_event = event;
            }
        }
    }
    
    return result;
}

/*
 * Turn a event object to a string to help display the result
 * in the application
 */

std::string TurnEventToString(Event event) {
    
    std::string result;
    
    //Connect the starting time (hour and minute)
    result += std::to_string(event.event_time_start.first) + ":";
    if (event.event_time_start.second == 0) {
        result += "00 to "; //Turn 0 to 00 for displaying
    } else {
        result += std::to_string(event.event_time_start.second) + " to ";
    }
    //Connect the ending time (hour and minute)
    result += std::to_string(event.event_time_end.first) + ":";
    if (event.event_time_end.second == 0) {
        result += "00"; //Turn 0 to 00 for displaying
    } else {
        result += std::to_string(event.event_time_end.second);
    }
    
    return result;
}

/*
 * Query function to return the event struct
 * at the given index of the vector
 */
Event EventTime::TimeOfOneSlot(int index) {
    return event_time_list_.at(index);
}


