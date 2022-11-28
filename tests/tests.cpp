#include "room.h"
#include <iostream>
#include <vector>


//testMakeRoomSmall
//testMakeRoomLarge
//testMakeRoomConnected
void testCanTravel();
void testSetObstacle();

void testCanTravel(){
    Room * room = room->roomHelper(3,3, true);
    room->setObstacle(1, 1, false);
    room->setObstacle(1,2, false);
    if(room->canTravel(1, 1, 0)){
        std::cout<<"can travel, right, true succesful"<<std::endl;
    }
    else{
        std::cout<<"can travel, right, true failed"<<std::endl;
        return;
    }
    room->setObstacle(2,1, false);
    if(room->canTravel(1, 1, 1)){
        std::cout<<"can travel, up, true succesful"<<std::endl;
    }
    else{
        std::cout<<"can travel, up, true failed"<<std::endl;
        return;
    }
    room->setObstacle(1,0, false);
    if(room->canTravel(1, 1, 2)){
        std::cout<<"can travel, left, true succesful"<<std::endl;
    }
    else{
        std::cout<<"can travel, left, true failed"<<std::endl;
        return;
    }
    room->setObstacle(0,1, false);
    if(room->canTravel(1, 1, 3)){
        std::cout<<"can travel, down, true succesful"<<std::endl;
    }
    else{
        std::cout<<"can travel, down, true failed"<<std::endl;
        return;
    }
    room->setObstacle(1,2, true);
    if(room->canTravel(1, 1, 0)){
        std::cout<<"can travel false succesful"<<std::endl;
    }
    else{
        std::cout<<"can travel false failed"<<std::endl;
        return;
    }
    std::cout<<"all tests passed"<<std::endl
}
void testSetObstacle(){
    Room room = room->roomHelper(3,3, false);
    std::vector<int> edge;
    room->setObstacle(1,1, true);
    if(room->getObstacle(1,1) == 'o'){
        std::cout<<"obstacle set successful"<<std::endl;
        edge = room->getEdgesHelper(1,1);
        if(edge[0] == -1 && edge[1] == -1 && edge[2] == -1 && edge[3] == -1){
            set::cout<< "edges correct" << std::endl;
        }
        else{
            set::cout<< "edges failed" << std::endl;
            return;
        }
    }
    else{
        set::cout<< "obstacle failed" << std::endl;
        return;
    }
    Room room2 = room2->roomHelper(3,3, true);
    room2->setObstacle(1,1, false);
    if(room2->getObstacle(1,1) == 'o'){
        std::cout<<"obstacle remove successful"<<std::endl;
        edge = room2->getEdgesHelper(1,1)
        if(edge[0] == -1 && edge[1] == -1 && edge[2] == -1 && edge[3] == -1){
            set::cout<< "edges correct" << std::endl;
        }
        else{
            set::cout<< "edges failed" << std::endl;
            return;
        }
    }
    else{
        set::cout<< "obstacle failed" << std::endl;
        return;
    }
    std::cout<< "all set obstacle tests passed" << std::endl;
}