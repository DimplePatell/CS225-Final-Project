#include "room.h"
#include <iostream>
#include <vector>
#include <utility>
#include <iostream>
#include <string>
#include <stack>


void testMakeRoomSmall();
void testMakeRoomLarge();
void testMakeRoomConnected();
void testCanTravel();
void testSetObstacle();
void assert_room_tree(Room& room, int width, int height);
void assert_connected(Room & room, int width, int height);
std::pair<int, int> assert_room_helper(Room & room, int width, int height);
void DFS(Room & room, std::vector<std::vector<int> > * visited, int x, int y, int width, int height, int * calls);

void djsTestAddElements();
void djsTestUnion();
void djsTestSize();

void djsAddElements() {
    DisjointSets djs;
	djs.addelements(5);
    if (3 == djs.find(3)) {
        std::cout << "djs added elements correctly" << std::endl;
    }
}

void djsTestUnion() {
    DisjointSets djs;
	djs.addelements(4);
	djs.setunion(1, 2);
    if (djs.find(2) == djs.find(1)) {
        std::cout << "djs set union correctly" << std::endl;
    }
}

void djsTestSize() {
    DisjointSets djs;
	djs.addelements(8);
	djs.setunion(1, 7);
	djs.setunion(2, 6);
	djs.setunion(3, 5);
	djs.setunion(2, 3);
    if (4 == disjSets.size(3)) {
        std::cout << "djs check size correctly" << std::endl;
    }
}

void testMakeRoomSmall(){
    Room room;
    room.makeRoom(3, 3);
    room.printRoom();
    assert_room_tree(room, 3, 3);
    std::cout<<"test make room small passed"<<std::endl;
}
void testMakeRoomLarge(){
    Room room;
    room.makeRoom(75, 75);
    //room.printRoom();
    assert_room_tree(room, 75, 75);
    std::cout<<"test make room large passed"<<std::endl;
}
void testMakeRoomConnected(){
    Room room;
    room.makeRoom(15, 15);
    assert_connected(room, 15, 15);
    std::cout<<"test make room connected passed"<<std::endl;
}
void testCanTravel(){
    Room room;
    room = *room.roomHelper(3,3, true);
    room.setObstacle(1, 1, false);
    room.setObstacle(2,1, false);
    if(room.canTravel(1, 1, 0)){
        std::cout<<"can travel, right, true succesful"<<std::endl;
    }
    else{
        std::cout<<"can travel, right, true failed"<<std::endl;
        return;
    }
    room.setObstacle(1,2, false);
    if(room.canTravel(1, 1, 1)){
        std::cout<<"can travel, up, true succesful"<<std::endl;
    }
    else{
        std::cout<<"can travel, up, true failed"<<std::endl;
        return;
    }
    room.setObstacle(0,1, false);
    if(room.canTravel(1, 1, 2)){
        std::cout<<"can travel, left, true succesful"<<std::endl;
    }
    else{
        std::cout<<"can travel, left, true failed"<<std::endl;
        return;
    }
    room.setObstacle(1,0, false);
    if(room.canTravel(1, 1, 3)){
        std::cout<<"can travel, down, true succesful"<<std::endl;
    }
    else{
        std::cout<<"can travel, down, true failed"<<std::endl;
        return;
    }
    room.setObstacle(1,2, true);
    if(room.canTravel(1, 1, 0)){
        std::cout<<"can travel false succesful"<<std::endl;
    }
    else{
        std::cout<<"can travel false failed"<<std::endl;
        return;
    }
    std::cout<<"all travel tests passed"<<std::endl;
}
void testSetObstacle(){
    Room room;
    room = *room.roomHelper(3,3, false);
    std::vector<int> edge;
    room.setObstacle(1,1, true);
    if(room.getObstacle(1,1) == 'o'){
        std::cout<<"obstacle set successful"<<std::endl;
        edge = room.getEdgesHelper(1,1);
        if(edge[0] == -1 && edge[1] == -1 && edge[2] == -1 && edge[3] == -1){
            std::cout<< "edges correct" << std::endl;
        }
        else{
            std::cout<< "edges failed" << std::endl;
            return;
        }
    }
    else{
        std::cout<< "obstacle failed" << std::endl;
        return;
    }
    Room room2;
    room2 = *room2.roomHelper(3,3, true);
    room2.setObstacle(1,1, false);
    if(room2.getObstacle(1,1) != 'o'){
        std::cout<<"obstacle remove successful"<<std::endl;
        edge = room2.getEdgesHelper(1,1);
        if(edge[0] == 0 && edge[1] == 0 && edge[2] == 0 && edge[3] == 0){
            std::cout<< "edges correct" << std::endl;
        }
        else{
            std::cout<< "edges failed" << std::endl;
            return;
        }
    }
    else{
        std::cout<< "obstacle failed" << std::endl;
        return;
    }
    std::cout<< "all set obstacle tests passed" << std::endl;
}
void DFS(Room & room, std::vector<std::vector<int> > * visited, int x, int y, int width, int height, int * calls){
    std::stack< std::pair<int, int> > s;
    s.push(std::make_pair(x, y));

    while (!s.empty()) {
        x = s.top().first;
        y = s.top().second;
        s.pop();
        (*calls)++;
        if ((*visited)[x][y] != 0)
            continue;
        (*visited)[x][y] = 1;

        if (x < width-1 && room.canTravel(x, y, 0))
            s.push(std::make_pair(x+1, y));
        if (y < height-1 && room.canTravel(x, y, 1))
            s.push(std::make_pair(x, y+1));
        if (x > 0 && room.canTravel(x, y, 2))
            s.push(std::make_pair(x-1, y));
        if (y > 0 && room.canTravel(x, y, 3))
            s.push(std::make_pair(x, y-1));
    }
}

std::pair<int, int> assert_room_helper(Room & room, int width, int height){
    std::vector<std::vector<int> > visited;
    for (int i = 0; i < width; i++)
        visited.push_back(std::vector<int>(height));

    int components = 0;
    int calls = 0;

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (visited[i][j] == 0) {
                DFS(room, &visited, i, j, width, height, &calls);
                components++;
            }
        }
    }

    return std::make_pair(components, calls);
}

void assert_connected(Room & room, int width, int height){
    std::pair<int, int> checks = assert_room_helper(room, width, height);
    int components = checks.first;
    int calls = checks.second;
    if (components != 1)
        std::cout<<"fail room is not connected"<<std::endl;
}

void assert_room_tree(Room & room, int width, int height){
    std::pair<int, int> checks = assert_room_helper(room, width, height);
    int components = checks.first;
    int calls = checks.second;
    if (components != 1)
        std::cout<<"fail room is not connected"<<std::endl;
}
