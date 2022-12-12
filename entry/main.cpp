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
    
//     Room r;
//     r.makeRoom(10,10);
//     std::cout << "made room" << std::endl;
//     BST tree = BST();
//     std::cout << "made bst" << std::endl;
//     r.addEnemies(&tree);
//     std::cout << "added enemies" << std::endl;
//     cs225::PNG* unsolved = r.drawRoom();
//     unsolved->writeToFile("unsolved.png");
//     std::cout << "drew room" << std::endl;
     
}
