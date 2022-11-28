/* Your code here! */
#include "room.h"
#include "disjointsets.cpp"
#include <queue>
#include <iostream>
/*#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"*/
    Room::Room(){
        width = 0;
        height = 0;
    }
    Room* Room::roomHelper(int w,int h, bool ob){
        width = w;
        height = h;
        if(ob){
            v = std::vector<std::vector<char>>(width, std::vector<char>(height, 'o'));
            edges = std::vector<std::vector<std::vector<int>>>(width, std::vector<std::vector<int>>(height, std::vector<int>(4, -1)));
        }
        else{
            v = std::vector<std::vector<char>>(width, std::vector<char>(height, 'n'));
            edges = std::vector<std::vector<std::vector<int>>>(width, std::vector<std::vector<int>>(height, std::vector<int>(4, 0)));
        }
        return this;
    }
    std::vector<int> Room::getEdgesHelper(int x, int y){
        std::vector<int> edge =std::vector<int>(4,-1);
        if(x-1 >= 0){
          edge[0] = edges[x-1][y][0];  
        }
        if(y-1 >= 0){
            edge[1] = edges[x][y-1][1];
        }
        if(x+1 < width){
           edge[2] = edges[x+1][y][2]; 
        }
        if(y+1 < height){
            edge[3] = edges[x][y+1][3];
        } 
        return edge;
    }
    char Room::getObstacle(int x, int y){
        return v[x][y];
    }
    void Room::makeRoom(int new_width, int new_height){
        width = new_width * 2 - 1;
        height = new_height *2 - 1;
        edges = std::vector<std::vector<std::vector<int>>>(width, std::vector<std::vector<int>>(height, std::vector<int>(4, -1)));
        if(!v.empty()){ v.clear();}
        v = std::vector<std::vector<char>>(width, std::vector<char>(height, 'o'));
        for(int i = 0; i<width; i=i+2){
            for(int j =0; j<width;j=j+2){
                v[i][j] = 'n';
            }
            
        }
        std::cout<<"n"<<std::endl;
        DisjointSets set;
        set.addelements(new_width * new_height);
        int x;
        int y;
        int dir;
        while(set.size(0) != (new_width * new_height)){
            x = rand()%new_width;
            y = rand()%new_height;
            dir = rand()%4;
            if(dir == 0 && 2*(x+1)<(width + 1)/2 && v[2*x +1][2*y] == 'o' && set.find(y*new_width + x) != set.find(y*new_width + (x +1))){
                set.setunion(y*new_width + x, y*new_width + x +1);
                setObstacle(2*x+1, 2*y, false);
 
            }
            if(dir == 1 && 2*(y+1)<height && v[2*x][2*y+1] == 'o' && set.find(y*new_width + x) != set.find((y+1)*new_width + x)){
                set.setunion(y*new_width + x, (y+1)*new_width + x);
                setObstacle(2*x, 2*y+1, false);
            }
            if(dir == 2 && x>0 && v[2*x-1][2*y] == 'o' && set.find(y*new_width + x) != set.find(y*new_width + x -1)){
                set.setunion(y*new_width + x, y*new_width + x -1);
                setObstacle(2*x-1, 2*y, false);
 
            }
            if(dir == 3 && y>0 && v[2*x][2*y-1] == 'o' && set.find(y*new_width + x) != set.find((y-1)*new_width + x)){
                set.setunion(y*new_width + x, (y-1)*new_width + x);
                setObstacle(2*x, 2*y-1, false);
 
            }
        }
    }
    
    bool Room::canTravel(int x, int y, int dir) const{
        if(x< 0 || y< 0 || 2*x >= width || 2*y >= height || v[2*x][2*y] == 'o' ){
            return false;
        }
        switch(dir) {
            case 0: 
                if(v[2*x+1][2*y] != 'o'){
                    return true;
                }
                break;
            case 1: 
                if(v[2*x][2*y+1] != 'o'){
                    return true;
                }
                break;
            case 2: 
                if(x > 0 && v[2*x-1][2*y] != 'o'){
                    return true;
                }
                break;
            case 3: 
                if(y > 0 && v[2*x][2*y-1] != 'o'){
                    return true;
                }
                break;
        }
        return false;
    }
    void Room::setObstacle(int x, int y, bool exists){
        if(x >= 0 && x<width && y >= 0 && y<height){
            if(exists){
                v[x][y] = 'o';
                if(x-1 >= 0){
                    edges[x-1][y][0] = -1;
                }
                if(y-1 >=0){
                    edges[x][y-1][1] = -1;  
                }
                if(x+1 < width){
                edges[x+1][y][2] = -1;  
                }
                if(y+1 < height){
                    edges[x][y+1][3] = -1;
                }
            }
            else{
                v[x][y] = 'n';
                if(x-1 >= 0){
                    edges[x-1][y][0] = 0;
                }
                if(y-1 >=0){
                    edges[x][y-1][1] = 0;  
                }
                if(x+1 < width){
                    edges[x+1][y][2] = 0;  
                }
                if(y+1 < height){
                    edges[x][y+1][3] = 0;
                } 
            }
        }
    }
    void Room::printRoom(){
        for(int x=0; x < width; x++){
            for(int y=0; y <height; y++){
                if(v[x][y] == 'o'){
                    std::cout<<"O";
                }
                else{
                    std::cout<<"X";
                }
            }
            std::cout<<std::endl;
        }
    }