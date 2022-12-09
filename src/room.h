/* Your code here! */

#pragma once
#include <vector>
#include "../lib/cs225/PNG.h"
#include "bst.h"

using namespace std;
using namespace cs225;


class Room {
    public:
        Room();
        void makeRoom(int width, int height);
        bool canTravel(int x, int y, int dir) const;
        void setObstacle(int x, int y, bool exists);
        Room* roomHelper(int w,int h, bool ob);
        std::vector<int> getEdgesHelper(int x, int y);
        char getObstacle(int x, int y);
        int minDistance(std::vector<int> dist, std::vector<bool> visited) const;
        std::vector<int> solveRoom() const;
        void printSolution(vector<int> dist, int n) const;
        PNG* drawRoom() const;
        PNG* drawRoomSolution() const;
        void addEnemies(BST* enemies);
        void setEnemy(int x, int y, bool exists, int difficulty);
        void setWalkingDistance(int walk);
    private:
        int width;
        int height;
        std::vector<std::vector<char>> v;
        //"e" = enemy
        //"o" = obstacle
        //otherwise empty
        std::vector<std::vector<std::vector<int>>> edges;
        double getColor(int difficulty) const;
};
