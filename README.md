
# Welcome to the Application "The Art Of Optimization" (CS 126 Final Project)

# Sijia Huo

# 1. Introduction And Overview

The openFramework application named " The Art Of Optimization" is a decision-making app aimed to help users to get the optimal solution when dealing with problems with constraints. In this project, two types of optimization methods is implemented. The optimization methods that have be implemented are as below:

1. Schedule the events which may conflict with each other. Suppose there're ten potential events to be done during one day, but some of the events happen during the same time. The algorithm  applies Greedy Algorithm to reach the goal of finishing as many events as possible.

1. Match the users/applicants with the objects. Suppose each user/applicant is able to choose 3 objects that he/she is willing to attend, and each object has a fixed size of capacity (e.g. 3 person per object), the best result is that all the applicants can finally get into one of the objects they once selected, which reaches perfect matching in graph theory. However, sometime since some objects are much popular than others, the perfect matching cannot reached. The application appies a revised version of DFS (Depth First Search) to find the maximum matching in the corresponding "graph". By finding the maximum matching, the maximum number of students can get into the objects they chose. 

All of the algorithms were leaned either from CS374 or from MATH412 (graph theory). The idea behind is applying the graph-related algorithms to solve the real-world problem and to build a user-friendly application.


# 2. A Quick Guide Of Building The Application

The application takes the advantage of the open frameworks platform. To build the application, please follow the following steps:

1. Download all the files inside the src, ofxFileDialog/src folder along with the data folder under the bin folder on the github page.
1. Build a new open frameworks program using the openframeworks project generator.
1. Paste the files in the src folder and the data folder to the corresponding location in your newly established project. Then paste the ofxFileDialog/src to the project folder for later use. 
1. When importing files, remember adding them to the target of the project.
1. Run the project.


# 3. A Quick Guide Of Using The Application

The program can basically be splitted into three parts. The welcome part, the scheduling part, and the matching part. Each part has some screen shots of demos in the "graphs" folder. To see the visualization of the outputs, please check the graphs.

The usage of each part is illustrated as below:

1. Welcome: In the welcome page, the details of the manipulation are already displayed. To do the matching, please input "m " in the text box first to indicate your usage (this is to avoid the mispressing of the key, e.g., you want to go schduling but you mispress the up-arrow, this can avoid the crash of the program.) Then, press left arrow to selete the file to analyze if you want to analyze the matching of a txt file. You should also imput the capacity of the object the textbox if you wish to do matching. If you are interested in scheduling, please first press "s ", then input a list of time schdules. Use "-" to split hour and minute, use "," to split begin time and end time, use ";" to split the events. Notice that the time of events are for 24 hour period, not for 12. After inputting to the textbox, press up-arrow if do matching and down-arrow if do scheduling.

1. Matching: In the window of matching, please first set the transparency, the color and the size of circle you want to embed the results in. Click mouse once to see part of the results. If no more new results, the notice will be displayed. You can make the window a kind of "art" if you choose the color/ scale/ transparency carefully. Press "Tab" key if you wish to save the results to local (especially the result is large), press right key to go back to the welcome page.

1. Scheduling: In the window of scheduling, please first set the transparency, the color and the size of circle you want to embed the scheduled event. Click mouse once to see one event scheduled. If no more other events scheduled, the notice will be displayed. You can make the window a kind of "art" if you choose the color/ scale/ transparency carefully. Press right key to go back to the welcome page.

To see how to create "art" in the result windows, please see the demo graphs. 


# 4. More Details About The Implementation: Algorithms In Details

The details of the two implemented methods are listed below:


1. Scheduling: By proving that there's no better solution, we can reach the conclusion that applying the greedy algorithm of finding the event that ends first and recursively find the other events that have no time conflict with the already chosen one can give the best answer. The algorithm is implemented by first sorting the events according to the ending time, and recursively add new events to the schedule plan. The return of the algorithm is a list of events (in ascending order) that is scheduled for the user. More details about the interface is explained in the next section.

1. Matching: The problem is converted into a maximum matching problem of a bipartite graph to solve. The details about the conversion is shown in "bipartite_graph.png" under the "graphs" folder. In the "bipartite_graph.png", we assume each student can only pick one favorite session they prefer, and each session has a capacity of 2 ( 2 available seats for each section). We now have 4 sections, that's to say, in a good situation, we will have two 2-people section and one 1-people section. Therefore, for the vertex 1-5, they each represents a student and for 6-15, they each represents a seat in a session. We have 8 seats available in total. For the edges, since student 0 likes section A, he connects himself to node 6 and 7 which both represents section 1. In this graph, the maximum matching is 4 (not the perfect matching), which means two students need to choose their seats between section 3 and 4 even though these two sections were not chosen by any student before. The situation can get more complexed if more students or sections are added. The more objects are there in the system, the harder the matching process will be. The maxmimum matching algorithm is implemented by revising the DFS search. Each student first search whether the options they have chosen are availble, if yes, then we've done; if not, we will first find which student the seat was occupied by, and to see whether that student has can choose other seats in his/her preference list. By recursively go through the student's list, we finally reach the maximum matching.

# 5. More Details About The Implementation: Interface , Library And Visualization

The application takes advantage of the Open Frameworks to interact with users and display results. The details of the two optimization methods are as below:

1. Greedy Algorithm for Scheduling: The users will first input "s " to indicate that they wish to do the scheduling. Then they need to input the time of events inside the text box and press the key of down arrow. The result will be displayed in a new page.
1. Matching for Bipartite Graph: The user will first input "m " to indicate that they wish to do the matching. Then they need to press left arrow to select the file they wish to upload to conduct the analysis. Finally they need to input the capacity of the chosing objects (e.g. the capacity of each class), and press key of up arrow. The result will be displayed in a new page.

The way of displaying the results is quite interesting. A part of the result will display each time after the user clicking the mouse once. The result will display in order, if no more result are availble, the text of "no more results" will be displayed on the screen. The user can arbitarily move between the window of "welcome", "scheduling" and "matching" and can retype the inputs at anytime. More details about coloring can be found in ReadMe.

To fulfill the ideas, three (actually four) libraries are applied. 
1. ofFbo along with ofxGui to visualize the results in a artistic way. (More details can be seen in the sceenshots of demos in the "graphs" folder )
ofFbo: http://openframeworks.cc/documentation/gl/ofFbo/
ofxGui: http://openframeworks.cc/documentation/ofxGui/
1. ofxFileDialog to upload the file from local. The library avoids typing in the path of the file.
ofxFileDialog: https://forum.openframeworks.cc/t/ofxfiledialog-create-an-open-file-dialog/3922/2
1. ofSoundPlayer to make background music.
ofSoundPlayer: http://openframeworks.cc/documentation/sound/ofSoundPlayer/



