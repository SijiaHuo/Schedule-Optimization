#include "ofApp.h"
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "student_information.h"
#include "section_information.h"
#include "adjacency_matrix.h"
#include "events_time.h"

//--------------------------------------------------------------
void ofApp::setup() {
    
    //Add background music
    background_music.load("background.mp3");
    background_music.play();
    background_music.setLoop(true);
    
    //Set up gui to be used when displaying results
    //This part of code is inspired by a tutorial video on youtube
    //https://www.youtube.com/watch?v=PxpnVhpfm2s
    
    gui.setup();
    gui.add(scale.set("scale", 0, 0, 255));
    gui.add(red.set("red", 0, 0, 255));
    gui.add(green.set("green", 0, 0, 255));
    gui.add(blue.set("blue", 0, 0, 255));
    gui.add(alpha.set("alpha", 0, 0, 255));
    
    fbo.allocate(1290, 720);
    fbo.begin();
    ofClear(255);
    fbo.end();
    
    //The font type is adapted from the openframeworks example
    // in the folder downloaded with the zip file named "fontsExample"
    
    ofTrueTypeFont::setGlobalDpi(72);
    
    verdana30.load("verdana.ttf", 30, true, true);
    verdana30.setLineHeight(26.0f);
    verdana30.setLetterSpacing(1.037);
    
    verdana30A.load("verdana.ttf", 30, false);
    verdana30A.setLineHeight(22.0f);
    verdana30A.setLetterSpacing(1.037);
    
    verdana18.load("verdana.ttf", 18, true, true);
    verdana18.setLineHeight(22.0f);
    verdana18.setLetterSpacing(1.037);
    
    verdana18A.load("verdana.ttf", 18, false);
    verdana18A.setLineHeight(26.0f);
    verdana18A.setLetterSpacing(1.037);
    
    bFirst = true;
    typeStr = "Please Type Your Input To The Box";
}

//--------------------------------------------------------------
void ofApp::update() {
    
}

//--------------------------------------------------------------
void ofApp::draw() {
    
    if (state == WELCOME) {
        
        ofBackground(54, 54, 54, 255);
        ofSetColor(225);
        
        verdana30.drawString("Welcome To The Art Of Optimization", 30, 35);
        ofSetColor(245, 58, 135);
        
        verdana18.drawString(
                             "(m) If you are interested in matching, "
                             "please first type in m and a space in the box", 30,
                             80);
        
        ofSetColor(245, 58, 135);
        
        verdana18.drawString(
                             "(m) For matching, then please type the capacity "
                             "of each option in the box", 30,
                             110);
        
        ofSetColor(245, 58, 135);
        
        verdana18.drawString(
                             "(m) Press LEFT Arrow to import the file that "
                             "you want to conduct the matching analysis", 30,
                             140);
        
        ofSetColor(255, 128, 0);
        
        verdana18.drawString(
                             "(s) If you are interested in scheduling, "
                             "please first type in s and a space in the box", 30,
                             170);
        
        ofSetColor(255, 128, 0);
        
        verdana18.drawString(
                             "(s) For scheduling, then type a list of "
                             "schedules, Use dash to split hour and minute", 30,
                             200);
        
        ofSetColor(255, 128, 0);
        
        verdana18.drawString("(s) Use comma to split starting "
                             "time and ending time, use semicolon "
                             "to split each event",
                             30, 230);
        ofSetColor(102, 204, 0);
        
        verdana18A.drawString("*(m) Matching: Press UP"
                              " Arrow After Inputing To See"
                              " Results", 30, 270);
        ofSetColor(102, 204, 0);
        
        verdana18A.drawString("*(s) Scheduling: Press DOWN Arrow "
                              "After Inputing To See Results", 30, 300);
        ofSetColor(245, 58, 135);
        
        
        ofSetColor(225);
        verdana30.drawString(typeStr, 30, 360);
        
        ofSetColor(225);
        verdana18A.drawString("Please Check Carefully "
                              "Before Continuing", 630, 420);
        
        
        ofDrawRectangle(100, 400, 500, 200);
        ofSetColor(54, 54, 54);
        verdana18A.drawString(typeStr, 116, 420);
        
        ofSetColor(29, 29, 29);
        ofDrawLine(30, 320, ofGetWidth() - 4, 320);
        
    } else if (state == MATCHING) {
        
        //Draw the gui bar as well as the instruction sentences
        //The following three lines are also from the youtube video
        //mentioned above.
        
        ofBackground(255, 255, 255, 255);
        fbo.draw(0, 0);
        gui.draw();
        
        int number_of_matchings = display_matchings.size();
        
        verdana18A.drawString("There are in total of " +
                              to_string(number_of_matchings) +
                              " fitted matching(s) found", 100, 180);
        verdana18A.drawString("One pair of matching will show up after "
                              "clicking mouse once", 100, 210);
        verdana18A.drawString(
                              "Please select the color and the transparency of the "
                              "visualization before clicking the mouse", 100, 240);
        verdana18A.drawString("Pressing Tab to save the "
                              "result to a file", 100, 270);
        verdana18A.drawString("Pressing RIGHT arrow to go back "
                              "to the welcome page", 100, 300);
        
        //If the key of save is pressed, an additional line will be displayed
        if (file_saved) {
            verdana18A.drawString("You have successfully "
                                  "saved the file!", 100, 330);
        }
    } else {
        
        //For scheduling part
        
        ofBackground(255, 255, 255, 255);
        fbo.draw(0, 0);
        gui.draw();
        
        int number_of_scheduling = display_scheduling.size();
        
        verdana18A.drawString("There are in total of " +
                              to_string(number_of_scheduling) +
                              " event(s) scheduled", 100, 180);
        verdana18A.drawString("The time of one scheduled event will "
                              "show up after clicking mouse once "
                              "(in order)", 100, 210);
        verdana18A.drawString(
                              "Please select the color and the transparency "
                              "of the visualization before clicking the mouse", 100,
                              240);
        verdana18A.drawString("Pressing RIGHT arrow to go back "
                              "to the welcome page", 100, 270);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    
    //The string input part is also learned from the given example "FontExample" in
    //the default folder when downloading. The fbo part is adapted from youtube video
    //which was already mentioned above.
    //The code was only adapted from the given examples, but have done adjustments
    //according to my own need.
    
    if (key == OF_KEY_DEL || key == OF_KEY_BACKSPACE) {
        typeStr = typeStr.substr(0, typeStr.length() - 1);
    } else if (key == OF_KEY_RETURN) {
        typeStr += "\n";
    } else if (key == '_') {
        typeStr += "_";
    } else if (key == OF_KEY_UP) {
        state = MATCHING;
        
        //Clean the previous results for another round of matching
        display_matchings.clear();
        
        //Clean the previous board
        fbo.begin();
        ofClear(255, 255, 255, 0);
        fbo.end();
        output_string_index = 0;
        MatchingStudent();
        
    } else if (key == OF_KEY_RIGHT) {
        
        state = WELCOME;
        
        //Cancel the previous saving notice for a new round matching
        file_saved = false;
        
    } else if (key == OF_KEY_DOWN) {
        
        state = SCHEDULING;
        fbo.begin();
        ofClear(255, 255, 255, 0);
        fbo.end();
        
        //clean the original string for a new round a scheduling
        output_string_index = 0;
        display_scheduling.clear();
        display_scheduling = ScheduleTime();
        
    } else if (key == OF_KEY_LEFT) {
        
        //The following three lines use the library ofxFileDialog
        //Along with the library, an example is attached.
        //The three lines adapted from the example given
        //The library is downloaded from the
        // https://forum.openframeworks.cc/t/ofxfiledialog-create-an-open-file-dialog/3922/2
        
        dialogSettings s;
        s.allowMultipleSelection = true;
        files = openDialog(s);
        
    } else if (key == OF_KEY_TAB) {
        SaveMatchingToFile();
        
    } else {
        if (bFirst) {
            typeStr.clear();
            bFirst = false;
        }
        
        //Append the string according to the key pressed
        ofAppendUTF8(typeStr, key);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    
    //fbo part are adapted from the youtube tutorial video mentioned above
    
    ofSetColor(red, green, blue, alpha);
    
    fbo.begin();
    ofPushStyle();
    ofDrawCircle(mouseX, mouseY, scale);
    ofSetColor(54, 54, 54);
    
    if (state == SCHEDULING) {
        if ((output_string_index >= display_scheduling.size()) ||
            (display_scheduling.empty())) {
            verdana18A.drawString("No more results",
                                  mouseX - 63, mouseY - 5);
        } else {
            
            verdana18A.drawString("The #" +
                                  to_string(output_string_index + 1) +
                                  " event:", mouseX - 60, mouseY - 20);
            verdana18A.drawString(display_scheduling.at(output_string_index),
                                  mouseX - 60, mouseY);
        }
        
    } else if (state == MATCHING) {
        if ((output_string_index >= display_matchings.size()) ||
            (display_matchings.empty())) {
            verdana18A.drawString("No more results",
                                  mouseX - 63, mouseY - 5);
        } else {
            verdana18A.drawString(display_matchings.at(output_string_index),
                                  mouseX - 60, mouseY - 15);
        }
    }
    
    output_string_index++;
    ofPopStyle();
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
    
}

//--------------------------------------------------------------
/*
 * The function wraps the matching functions.
 * It provides optimal matching based on the file path
 * and the capacity given
 */
void ofApp::MatchingStudent() {
    
    //To avoid wrong pressing
    if (files.empty()) {
        return;
    }
    
    //Get the file path from the file uploaded
    std::string path = files[0];
    
    //Make a copy of the input value
    std::string input_string;
    input_string.assign(typeStr);
    
    //Split the type indicator and the real value
    std::istringstream input_stream(input_string);
    std::string input_type_indicator;
    std::string class_capacity_string;
    input_stream >> input_type_indicator;
    input_stream >> class_capacity_string;
    
    //Check input indicator, avoid run key pressing
    if (input_type_indicator.compare("m") != 0) {
        //If wrong key pressed, assign empty vector the
        // result vector and return
        display_matchings = vector<string>();
        return;
    }
    
    //Assign the integer to the capacity, catch error if
    //the string is not a valid integer
    int class_capacity;
    
    try {
        class_capacity = stoi(class_capacity_string);
    }
    catch (std::invalid_argument &e) {
        display_matchings = vector<string>();
        return;
    }
    
    //Start matching
    StudentInformation students_book;
    SectionInformation section_list;
    students_book.ImportInformationFromFile(path, section_list);
    AdjacencyMatrix adj_mtx(students_book,
                            section_list, class_capacity);
    adj_mtx.ImportMatrixFromFile(path, section_list);
    adj_mtx.BipartiteMatchingEntireSystem(students_book,
                                          section_list, class_capacity);
    display_matchings = adj_mtx.ListOfMatching(students_book,
                                               section_list, class_capacity);
}

//--------------------------------------------------------------
/*
 * The function wraps up the scheduling functions.
 * It will return a vector of string for displaying on the screen.
 * The strings are the chose events to be taken.
 */
vector <string> ofApp::ScheduleTime() {
    
    //Make a copy of the input string
    std::string input_string;
    input_string.assign(typeStr);
    
    //Split the type indicator and the real value
    std::istringstream input_stream(input_string);
    std::string input_type_indicator;
    std::string schedule_information;
    
    input_stream >> input_type_indicator;
    input_stream >> schedule_information;
    
    //Check input indicator, avoid run key pressing
    if (input_type_indicator.compare("s") != 0) {
        //If wrong key pressed, assign empty vector the result vector and return
        return vector<string>();
    }
    
    //Use the functions declared under the EventTime class
    EventTime input_time(schedule_information);
    input_time.SortEvents();
    input_time.PrintEventList();
    return input_time.EventChoosing();
}

//--------------------------------------------------------------
/*
 * The function saves the output of matching to the local file based on the
 * path I defined in the function. The function return true
 * if the saving succeed,
 * false otherwise.
 */
bool ofApp::SaveMatchingToFile() {
    
    //Save file to a self-defined path for testing
    std::ofstream savefile(
                           "/Users/hsj/Documents/CS126/of_v0.9.8_osx_release/apps/myApps"
                           "/final_project_sijia_huo/matching.txt");
    if (!savefile) {
        return false;
    }
    
    //Print the result strings to the file.
    if (display_matchings.empty()) {
        return false;
        
    } else {
        for (auto result : display_matchings) {
            savefile << result << std::endl;
        }
    }
    
    //Close the file and return
    savefile.close();
    file_saved = true;
    return true;
}


