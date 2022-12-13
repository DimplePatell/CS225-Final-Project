# CS225-Final-Project
In the terminal, run the following commands:
mkdir build
cd build
cmake ..
Code should compile.  Then run make and ./main this will run the tests.

Locations of Important Function/ Files:
Entry- Main executable
Lib- CS225 library functions for png
Src- room files, bst files, and disjoint sets files
Tests- contains all test functions which are then run through main
Pres- contains the presentation and written report

The enemies are colored by difficulty. The following is the progression of colors from most to least difficult: Red, Purple, Magenta, Pink, Orange, Yellow-Orange, Yellow, Blue, Cyan, Green.

Tests and asssociated png files (where necessary):

Room Helper Tests:
    The following tests make sure our helper functions run as intended.  
    testSetObstacle()
    testSetEnemy()
    testCanTravel()
    testWalkingDistance()
Disjoint Sets Tests:
    The following tests make sure the disjoint sets code used to make a room works properly
    djsTestAddElements()
    djsTestUnion()
    djsTestSize()
Make Room Tests:
    These tests make sure that Make Room is working properly and have a visual component as well
    testMakeRoomSmall() - "unsolvedsmall.png"
    testMakeRoomLarge() - "unsolvedlarge.png"
    testMakeRoomConnected()
Solve Room Tests:
    testSolveRoom() - "unsolved.png", "solved.png"
    testSolveRoomSmall()- "unsolved1.png", "solved1.png"
    testSolveRoomLarge()- "unsolved2.png", "solved2.png"

After running tests Main runs 3 instances to see our code in action.  These can be seen in the following files:
1 - Walking Weight = 0, 10x10, green.png"
2- Walking Weight = 50, 10x10, yellow.png"
3- Walking Weight = 100, 10x10, red.png"
You should see the same 10 x10 room solved 3 times with different walking weights.