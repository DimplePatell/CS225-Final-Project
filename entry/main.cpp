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
    Room r;
    r.makeRoom(10,10);
    BST tree = BST();
    std::cout<<"hi"<<std::endl;
    r.addEnemies(&tree);
    std::cout<<"hey"<<std::endl;
    cs225::PNG* unsolved = r.drawRoom();
    unsolved->writeToFile("unsolved.png");
     
}
