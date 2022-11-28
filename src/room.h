/* Your code here! */
#pragma once
#include <vector>
//#include "cs225/PNG.h"
class Room {
    public:
        Room();
        void makeRoom(int width, int height);
        bool canTravel(int x, int y, int dir) const;
        void setObstacle(int x, int y, bool exists);
        Room* roomHelper(int w,int h, bool ob);
        std::vector<int> getEdgesHelper(int x, int y);
        char getObstacle(int x, int y);
        void printRoom();
       // std::vector<int> solveRoom();
        //cs225::PNG* drawRoom() const;
    private:
        int width;
        int height;
        std::vector<std::vector<char>> v;
        //"e" = enemy
        //"o" = obstacle
        //otherwise empty
        std::vector<std::vector<std::vector<int>>> edges;
};
