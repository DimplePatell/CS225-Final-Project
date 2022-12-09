#include "room.h"
#include "../tests/test.cpp"
#include <iostream>

int main(){
    std::cout<<"compiled"<<std::endl;
    testSetObstacle();
    testCanTravel();
    testMakeRoomSmall();
    testMakeRoomLarge();
    testMakeRoomConnected();
    
    testSolveRoom();
    
    djsTestAddElements();
    djsTestUnion();
    djsTestSize();

}
