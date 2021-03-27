//
// Created by hsj on 5/2/18.
//

#include "events_time_test.h"
#include <iostream>
#include "catch.h"
#include "../src/events_time.h"

TEST_CASE("import_event_test") {

    EventTime test_schedule("5:50,6:50;4:20,6:00;7:00,8:00;7:00,7:50");
    Event first_event = test_schedule.TimeOfOneSlot(0);

    //Test whether the input is correct
    REQUIRE(first_event.event_time_start.first == 5);
    REQUIRE(first_event.event_time_start.second == 50);
    REQUIRE(first_event.event_time_end.first == 6);
    REQUIRE(first_event.event_time_end.second == 50);
}

TEST_CASE("sort_event_test") {

    EventTime test_schedule("5:50,6:50;4:20,6:00;7:00,8:00;7:00,7:50");
    test_schedule.SortEvents();
    Event first_event = test_schedule.TimeOfOneSlot(0);

    REQUIRE(first_event.event_time_start.first == 4);
    REQUIRE(first_event.event_time_start.second == 20);
    REQUIRE(first_event.event_time_end.first == 6);
    REQUIRE(first_event.event_time_end.second == 0);
}

TEST_CASE("no_conflict_test") {

    EventTime test_schedule("5:50,6:50;4:20,6:00;7:00,8:00;7:00,7:50");
    test_schedule.SortEvents();
    Event first_event = test_schedule.TimeOfOneSlot(0);
    Event second_event = test_schedule.TimeOfOneSlot(1);
    Event third_event = test_schedule.TimeOfOneSlot(2);

    REQUIRE(!test_schedule.NoConflict(first_event, second_event));
    REQUIRE(test_schedule.NoConflict(second_event, third_event));

}

TEST_CASE("turn_event_to_string_test") {

    EventTime test_schedule("5:50,6:50;4:20,6:00;7:00,8:00;7:00,7:50");
    test_schedule.SortEvents();
    Event second_event = test_schedule.TimeOfOneSlot(1);
    Event third_event = test_schedule.TimeOfOneSlot(2);

    REQUIRE(TurnEventToString(second_event) == "5:50 to 6:50");
    REQUIRE(TurnEventToString(third_event) == "7:00 to 7:50");

}

