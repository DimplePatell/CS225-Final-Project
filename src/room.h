/* Your code here! */

#pragma once
#include <vector>
#include "../lib/cs225/PNG.h"

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
        std::vector<int> solveRoom();
//         PNG* drawRoom() const;
    private:
        int width;
        int height;
        std::vector<std::vector<char>> v;
        //"e" = enemy
        //"o" = obstacle
        //otherwise empty
        std::vector<std::vector<std::vector<int>>> edges;
    
        std::vector<bool> wallRight;
        std::vector<bool> wallDown;
};
