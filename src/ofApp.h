#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxFileDialog.h"
#include <string>
#include <vector>


class ofApp : public ofBaseApp {
    
    enum AppState {
        WELCOME,
        SCHEDULING,
        MATCHING
    };
    
public:
    void setup();
    
    void update();
    
    void draw();
    
    void keyPressed(int key);
    
    void keyReleased(int key);
    
    void mouseMoved(int x, int y);
    
    void mouseDragged(int x, int y, int button);
    
    void mousePressed(int x, int y, int button);
    
    void mouseReleased(int x, int y, int button);
    
    void mouseEntered(int x, int y);
    
    void mouseExited(int x, int y);
    
    void windowResized(int w, int h);
    
    void dragEvent(ofDragInfo dragInfo);
    
    void gotMessage(ofMessage msg);
    
    //Function for methods
    void MatchingStudent();
    
    vector <string> ScheduleTime();
    
    bool SaveMatchingToFile();
    
    //Music Adding
    ofSoundPlayer background_music;
    
    //Assign states
    AppState state = WELCOME;
    
    //input string management
    bool bFirst;
    string typeStr;
    
    ofTrueTypeFont verdana18;
    ofTrueTypeFont verdana30;
    
    ofTrueTypeFont verdana18A;
    ofTrueTypeFont verdana30A;
    
    //For upload local files
    std::vector<string> files;
    
    
    //The following two variables tracing the index of the output
    int output_string_index = 0;
    vector <string> display_matchings;
    vector <string> display_scheduling;
    
    //Trace the status of saving files
    bool file_saved = false;
    
    //For the visualization of the results
    ofFbo fbo;
    ofxPanel gui;
    ofParameter<int> scale;
    ofParameter<int> red;
    ofParameter<int> green;
    ofParameter<int> blue;
    ofParameter<int> alpha;
    
};

