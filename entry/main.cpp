#include "room.h"
#include "../tests/test.cpp"
#include <iostream>
#include "bst.h"

int main(){
    std::cout<<"compiled"<<std::endl;
    testSetObstacle();
    std::cout<< " " << std::endl;
    testSetEnemy();
    std::cout<< " " << std::endl;
    testCanTravel();
    std::cout<< " " << std::endl;
    testWalkingDistance();
    std::cout<< " " << std::endl;
    testMakeRoomSmall();
    std::cout<< " " << std::endl;
    testMakeRoomLarge();
    std::cout<< " " << std::endl;
    testMakeRoomConnected();
    std::cout<< " " << std::endl;
    
    djsTestAddElements();
    std::cout<< " " << std::endl;
    djsTestUnion();
    std::cout<< " " << std::endl;
    djsTestSize();
    std::cout<< " " << std::endl;
    testSolveRoom();
    testSolveRoomSmall();
    testSolveRoomLarge();
    
    std::cout<< " " << std::endl;

    testBSTDatasetSmall();
    testBSTDatasetBig();
    testAddEnemies();
    Room r;
    r.makeRoom(22,22);
    BST tree = BST("../src/large_twitch_features.csv", 1000);
    r.addEnemies(&tree);
    cs225::PNG* unsolved = r.drawRoom();
    unsolved->writeToFile("unsolved.png");
    std::cout<<"Walking Weight = 0, 43x43, green.png"<<std::endl;
    cs225::PNG* solved = r.drawRoomSolution(0);
    solved->writeToFile("green.png");
    std::cout<<"Walking Weight = 10, 43x43, yellow.png"<<std::endl;
    r.setWalkingDistance(10);
    cs225::PNG* solved2 = r.drawRoomSolution(50);
    solved2->writeToFile("yellow.png");
    r.setWalkingDistance(10);
    std::cout<<"Walking Weight = 20, 43x43, red.png"<<std::endl;
    cs225::PNG* solved1 = r.drawRoomSolution(125);
    solved1->writeToFile("red.png");
}
