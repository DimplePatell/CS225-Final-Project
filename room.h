/* Your code here! */
#pragma once
#include <vector>
//#include "cs225/PNG.h"
class Room {
    public:
        Room();
        void makeRoom(int width, int height);
        bool canTravel(int x, int y, int dir) const;
        void setObstacle(int x, int y, int dir, bool exists);
        std::vector<int> solveRoom();
        cs225::PNG* drawRoom() const;
    private:
        int width;
        int height;
        std::vector<std::vector<char>> v;
        //"e" = enemy
        //"o" = obstacle
        //otherwise empty
};
