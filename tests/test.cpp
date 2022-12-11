#include "room.h"
#include "disjointsets.h"
#include <iostream>
#include <vector>
#include <utility>
#include <iostream>
#include <string>
#include <stack>
#include "roomreader.h"
#include <catch2/catch_test_macros.hpp>


void testMakeRoomSmall();
void testMakeRoomLarge();
void testMakeRoomConnected();
void testCanTravel();
void testSetObstacle();
void assert_room_tree(Room& room, int width, int height);
void assert_connected(Room & room, int width, int height);
std::pair<int, int> assert_room_helper(Room & room, int width, int height);
void DFS(Room & room, std::vector<std::vector<int> > * visited, int x, int y, int width, int height, int * calls);
void copyRoom(const RoomReader & source, Room * dest);
PNG read_solution(const string & filename, int width, int height);
PNG read_unsolved(const string & filename, int width, int height);
#define READ_SOLUTION_ROOM(func, width, height)  \
    RoomReader(READ_SOLUTION_PNG(func, width, height))
#define READ_SOLUTION_PNG(func, width, height)  \
    read_solution(string("../tests/soln_") + func + string(".png"), width, height)

//void djsTestAddElements();
//void djsTestUnion();
//void djsTestSize();

void djsTestAddElements() {
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
    if (4 == djs.size(3)) {
        std::cout << "djs check size correctly" << std::endl;
    }
}

void testMakeRoomSmall(){
    Room room;
    room.makeRoom(3, 3);
    //room.drawRoom();
    assert_room_tree(room, 3, 3);
    std::cout<<"test make room small passed"<<std::endl;
}
void testMakeRoomLarge(){
    Room room;
    room.makeRoom(75, 75);
    //room.drawRoom();
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
void testSetEnemy(){
    Room room;
    room = *room.roomHelper(3,3, false);
    std::vector<int> edge;
    room.setEnemy(1,1, true, 50);
    if(room.getObstacle(1,1) == 'e'){
        std::cout<<"enemy set successful"<<std::endl;
        edge = room.getEdgesHelper(1,1);
        if(edge[0] == 50 && edge[1] == 50 && edge[2] == 50 && edge[3] == 50){
            std::cout<< "edges correct" << std::endl;
        }
        else{
            std::cout<< "edges failed" << std::endl;
            return;
        }
    }
    else{
        std::cout<< "set enemy failed" << std::endl;
        return;
    }
    std::cout<< "all set enemy tests passed" << std::endl;
}
void testWalkingDistance(){
    std::vector<int> edge;
    Room room;
    room = *room.roomHelper(3,3, false);
    room.setWalkingDistance(3);
    edge = room.getEdgesHelper(1,1);
    if(edge[0] == 3 && edge[1] == 3 && edge[2] == 3 && edge[3] == 3){
        std::cout<< "edges correct" << std::endl;
    }
    else{
        std::cout<< "test walking distance failed" << std::endl;
    }
    std::cout<< "test walking distance passed" << std::endl;
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

PNG read_solution(const string & filename, int width, int height)
{
      PNG output;
      output.readFromFile(filename);
      return output;
}

/*void helpSolveRoom(const RoomReader & soln)
{
    Room room;
    copyRoom(soln, &room);
    vector<vector<int>> solution = room.solveRoom();

    cout << "first 10 steps in solution:" << endl;
    for (size_t i = 0; i < solution.size() && i < soln.getSolutionSize() && i < 10; i++)
        cout << "step " << i << ": actual=" << solution[i] << ", expected=" << soln.getSolutionAt(i) << endl;

    if(soln.getSolutionSize() == solution.size()){
        cout<<"check size works"<<endl;
    }

    for (size_t i = 0; i < solution.size(); i++)
        if (solution[i] != soln.getSolutionAt(i)){
            cout<<"Solution is incorrect"<<endl;
            return;
        }
            
}*/

void copyRoom(const RoomReader & source, Room * dest)
{
    dest->makeRoom(source.getWidth(), source.getHeight());
    for (int x = 0; x < source.getWidth(); x++)
    {
        for (int y = 0; y < source.getHeight(); y++)
        {
            if (x < source.getWidth() - 1)
                dest->setObstacle(x, y, source.isWall(x, y, RoomReader::RIGHTWALL));
            if (y < source.getHeight() - 1)
                dest->setObstacle(x, y, source.isWall(x, y, RoomReader::DOWNWALL));
        }
    }
}

void testSolveRoom() {
    Room room;
    room = *room.roomHelper(3,3, false);
    room.setObstacle(0,1, true);
    room.setObstacle(1,0, false);
    room.setObstacle(1, 1, false);
    room.setObstacle(1,2, true);
    room.setObstacle(2,1, false);

    // n o n
    // n n o
    // n n n
    room.setWalkingDistance(3);
}
void testSolveRoom2() {
    Room room;
    room.makeRoom(3,3);
    room.setWalkingDistance(3);
    cs225::PNG* unsolved = room.drawRoom();
    unsolved->writeToFile("unsolved1.png");
    int difficulty = 90;
    cs225::PNG* solved = room.drawRoomSolution(difficulty);
    solved->writeToFile("solved.png");
}

void testSolveRoom3() {
    Room room;
    room.makeRoom(5,5);
    room.setWalkingDistance(2);
    cs225::PNG* unsolved = room.drawRoom();
    unsolved->writeToFile("unsolved2.png");

    // std::vector<std::vector<int>> answr = room.solveRoom();
    int difficulty = 90;
    cs225::PNG* solved = room.drawRoomSolution(difficulty);
    solved->writeToFile("solved2.png");
}


