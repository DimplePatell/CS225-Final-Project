#pragma once
#include <vector>
#include "../lib/cs225/PNG.h"
#include <map>
#include "bst.h"


using namespace std;
using namespace cs225;


class Room {
    public:
        Room();
        int getWidth();
        int getHeight();
        void makeRoom(int width, int height);
        bool canTravel(int x, int y, int dir) const;
        void setObstacle(int x, int y, bool exists);
        Room* roomHelper(int w,int h, bool ob);
        std::vector<int> getEdgesHelper(int x, int y);
        char getObstacle(int x, int y);
        vector<vector<int>> solveRoom();
        //void printSolution(vector<int> dist, int n) const;
        pair<int,int> minDistance(vector<vector<int>> dist, vector<vector<bool>> visited) const;
        PNG* drawRoom() const;
        PNG* drawRoomSolution(int difficulty);
        //void addEnemies(BST* enemies);
        void setEnemy(int x, int y, bool exists, int difficulty);
        void setWalkingDistance(int walk);
        void addEnemies(BST* enemies);
        std::vector<std::vector<int>> getSolved();
    private:
        int width;
        int height;
        std::vector<std::vector<char>> v;
        //"e" = enemy
        //"o" = obstacle
        //otherwise empty
        std::vector<std::vector<std::vector<int>>> edges;
        double getColor(int difficulty) const;
        std::map<std::vector<int>, int> enemy_difficulties;
        std::vector<std::vector<int>> solved;
};
