#include "room.h"
#include "test.cpp"
#include <iostream>

int main(){
    std::cout<<"compiled"<<std::endl;
    testSetObstacle();
    testCanTravel();
    testMakeRoomSmall();
    testMakeRoomLarge();
    testMakeRoomConnected();

}