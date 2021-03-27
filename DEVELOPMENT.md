
# Log of Development (Finalized)

# Sijia Huo

# 1.Week One

1. The hardest part is to choose the methods  to implement. There're four methods in my original list, but I cannot decided which one to choose. It's not hard to simply implement the algorithm for a graph theory, but I should first transform the file regarding the real-world problem to the vertex and nodes. So I have to choose to convert them.  Another problem is to visualize the results and to do the interface thing. I still have no idea how to do this.

1. My solution towards the problem is to self-construct the txt file and read in them line by line. Finally split each string according to my needs. I input the file twice, one is to determine the dimension of my adjacency matrix to store my information, another is to really upload the data to the matrix. I now use the command line to the input, but I will do some interface during the next week.


# 2. Week Two

1. I begin to implement the user interface, but I still have no clue how to convert the command line into the interface. Also, since I have more than one method implement, I have to create multiple windows regardingly, but I have to find a way to realize the design.

1. My solution towards the problem is to sate multiple states regarding different windows. My current solution of converting the command line into user input is by creating a textbox to ask the user to input the path of the file.

# 3. Week Three (Last Week)

1. The biggest problem of the last week is that I have only implemented one method so far but in my original proposal, I planned to implement at least two. I tried to load the boost graph library to implement the vertex colouring algorithm, but the libarary cannot be loaded successfully. I went to the office hour on Sunday but the TA couldn't load the library either. Another problem in my program is that my visualization is kind of stupid, and if the results are too large, I have no way to output the results to a text file. My way of uploading the file is also stupid (simply type in the path of the file). Finally, I have to deal with the situation of mistype the inputs. If the user mistype the inputs, the programs breaks once the function gets the invalid inputs. I have to write codes dealing with this situation as well.

1. For the problem of uploading the library, the TA who couldn't offer me the help suggested me to use the ofX series of library which are much easier to handle. I then implement another algorithm that does not need the graph library and use the external library to do the visualization and interface. In order to show my heavy use of library, I applied four at once:  

ofFbo: http://openframeworks.cc/documentation/gl/ofFbo/
ofxGui: http://openframeworks.cc/documentation/ofxGui/
ofxFileDialog: https://forum.openframeworks.cc/t/ofxfiledialog-create-an-open-file-dialog/3922/2
ofSoundPlayer: http://openframeworks.cc/documentation/sound/ofSoundPlayer/

I used the mouse-clicking way to display results (see the screen shots of demos in the "graphs" folder), and user can select the color they want the text to be, which makes it a kind of "art".  My app now can select the file from local computer. I have dealed with all bugs and wrong input errors. I also add background music regardingly. 
