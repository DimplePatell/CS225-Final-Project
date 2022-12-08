#include "room.h"
#include "disjointsets.h"
#include <queue>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
using namespace cs225;

#include "../lib/cs225/HSLAPixel.h"
#include "../lib/cs225/PNG.h"
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
        if(x< 0 || y< 0 || x >= width || y >= height || v[x][y] == 'o' ){
            return false;
        }
        switch(dir) {
            case 0: 
                if(v[x+1][y] != 'o'){
                    return true;
                }
                break;
            case 1: 
                if(v[x][y+1] != 'o'){
                    return true;
                }
                break;
            case 2: 
                if(x > 0 && v[x-1][y] != 'o'){
                    return true;
                }
                break;
            case 3: 
                if(y > 0 && v[x][y-1] != 'o'){
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

    std::vector<int> Room::solveRoom() {
        vector<int> lastRow;
        map<int, int> steps;
        vector<bool> visited;
 
        for (int i = 0; i < (width * height); ++i) {
        visited.push_back(false);
    }
        queue<int> q1;
        q1.push(0);
        visited.at(0) = true;
 
        while (!q1.empty()) {
        int elem = q1.front();
        q1.pop();
        int x_pos = elem % width;
        int y_pos = elem / width;
        if (y_pos == (height - 1)) {  
            lastRow.push_back(elem);
        }
        if (canTravel(x_pos, y_pos, 0) && !visited.at(elem+1)) {
            steps.insert(pair<int,int> (elem + 1, elem));
            visited.at(elem + 1) = true;
            q1.push(elem + 1);
        }
        if (canTravel(x_pos, y_pos, 1) && !visited.at(elem + width)) {
            steps.insert(pair<int,int> (elem + width, elem));
            visited.at(elem + width) = true;
            q1.push(elem + width);
        }
        if (canTravel(x_pos, y_pos, 2) && !visited.at(elem - 1)) {
            steps.insert(pair<int,int> (elem - 1, elem));
            visited.at(elem - 1) = true;
            q1.push(elem - 1);
        }
        if (canTravel(x_pos, y_pos, 3) && !visited.at(elem - width)) {
            steps.insert(pair<int,int> (elem - width, elem));
            visited.at(elem - width) = true;
            q1.push(elem - width);
        }
    }
    vector<int> vec;
    int end = width - 1;
    while (lastRow.at(end) == lastRow.at(end - 1)) {
        end -= end;
    }
    int start = lastRow.at(end);
    while (start != 0) {
        int prev = steps[start];
        if (start == (prev + 1)) {
            vec.push_back(0);
        } else if (start == (prev + width)) {
            vec.push_back(1);
        } else if (start == (prev - 1)) {
            vec.push_back(2);
        } else if (start == (prev - width)) {
            vec.push_back(3);
        }
        start = prev;
    }
    reverse(vec.begin(), vec.end());
    return vec;
}
void Room::setEnemy(int x, int y, bool exists, int difficulty){
        if(x >= 0 && x<width && y >= 0 && y<height){
            if(exists){
                v[x][y] = 'e';
                if(x-1 >= 0){
                    edges[x-1][y][0] += difficulty;
                }
                if(y-1 >=0){
                    edges[x][y-1][1] += difficulty;  
                }
                if(x+1 < width){
                    edges[x+1][y][2] += difficulty;  
                }
                if(y+1 < height){
                    edges[x][y+1][3] += difficulty;
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
void Room::setWalkingDistance(int walk){
    if(walk <=0){
        return;
    }
    for(int x=0; x < (int)edges.size(); x++){
       for(int y=0; y < (int)edges[0].size(); y++){
            for(int d=0; d<4; d++){
                if(edges[x][y][d] != -1){
                    edges[x][y][d] += walk;
                }
            }
        } 
    }
}
    cs225::PNG* Room::drawRoom() const{
        cs225::PNG* pic = new cs225::PNG(width * 10 + 1, height * 10 + 1);
        for(unsigned i = 0; i < pic->width(); i++) {
            pic->getPixel(i, 0) = cs225::HSLAPixel(0, 0, 0);
            pic->getPixel(i, pic->height()-1) = cs225::HSLAPixel(0, 0, 0);
        }
        for(unsigned i = 0; i < pic->height(); i++) {
            pic->getPixel(0, i) = cs225::HSLAPixel(0, 0, 0);
            pic->getPixel(pic->width()-1, i) = cs225::HSLAPixel(0, 0, 0);
        }
        for(int x = 0; x < width; x++) {
            for(int y = 0; y < height; y++) {
                if(v[x][y]=='o') {
                    for(int k=0; k < 6; k++){
                       pic->getPixel(x * 10, y * 10 + k + 2) = cs225::HSLAPixel(0, 0, 0); 
                       pic->getPixel(x * 10 + 9, y * 10 + k + 2) = cs225::HSLAPixel(0, 0, 0);
                       pic->getPixel(x * 10 + k + 2, y * 10) = cs225::HSLAPixel(0, 0, 0);
                       pic->getPixel(x * 10 + k + 2, y * 10 + 9) = cs225::HSLAPixel(0, 0, 0);
                    }
                    pic->getPixel(x * 10 + 1, y * 10 + 1) = cs225::HSLAPixel(0, 0, 0); 
                    pic->getPixel(x * 10 + 8, y * 10 + 1) = cs225::HSLAPixel(0, 0, 0);
                    pic->getPixel(x * 10 + 8, y * 10 + 8) = cs225::HSLAPixel(0, 0, 0);
                    pic->getPixel(x * 10 + 1, y * 10 + 8) = cs225::HSLAPixel(0, 0, 0);
                }
                else if(v[x][y] == 'e'){
                    int difficulty = 90;//change
                    double d = getColor(difficulty);
                    pic->getPixel(x * 10 + 3, y * 10 + 2) = cs225::HSLAPixel(d, 1, 0.5); 
                    pic->getPixel(x * 10 + 4, y * 10 + 2) = cs225::HSLAPixel(d, 1, 0.5);
                    pic->getPixel(x * 10 + 5, y * 10 + 2) = cs225::HSLAPixel(d, 1, 0.5);
                    pic->getPixel(x * 10 + 6, y * 10 + 2) = cs225::HSLAPixel(d, 1, 0.5);
                    pic->getPixel(x * 10 + 2, y * 10 + 3) = cs225::HSLAPixel(d, 1, 0.5); 
                    pic->getPixel(x * 10 + 4, y * 10 + 3) = cs225::HSLAPixel(d, 1, 0.5);
                    pic->getPixel(x * 10 + 5, y * 10 + 3) = cs225::HSLAPixel(d, 1, 0.5);
                    pic->getPixel(x * 10 + 7, y * 10 + 3) = cs225::HSLAPixel(d, 1, 0.5);
                    pic->getPixel(x * 10 + 2, y * 10 + 4) = cs225::HSLAPixel(d, 1, 0.5); 
                    pic->getPixel(x * 10 + 4, y * 10 + 4) = cs225::HSLAPixel(d, 1, 0.5);
                    pic->getPixel(x * 10 + 5, y * 10 + 4) = cs225::HSLAPixel(d, 1, 0.5);
                    pic->getPixel(x * 10 + 7, y * 10 + 4) = cs225::HSLAPixel(d, 1, 0.5);
                    pic->getPixel(x * 10 + 2, y * 10 + 5) = cs225::HSLAPixel(d, 1, 0.5);
                    pic->getPixel(x * 10 + 3, y * 10 + 5) = cs225::HSLAPixel(d, 1, 0.5);
                    pic->getPixel(x * 10 + 4, y * 10 + 5) = cs225::HSLAPixel(d, 1, 0.5); 
                    pic->getPixel(x * 10 + 5, y * 10 + 5) = cs225::HSLAPixel(d, 1, 0.5);
                    pic->getPixel(x * 10 + 6, y * 10 + 5) = cs225::HSLAPixel(d, 1, 0.5);
                    pic->getPixel(x * 10 + 7, y * 10 + 5) = cs225::HSLAPixel(d, 1, 0.5);
                    pic->getPixel(x * 10 + 2, y * 10 + 6) = cs225::HSLAPixel(d, 1, 0.5);
                    pic->getPixel(x * 10 + 3, y * 10 + 6) = cs225::HSLAPixel(d, 1, 0.5);
                    pic->getPixel(x * 10 + 4, y * 10 + 6) = cs225::HSLAPixel(d, 1, 0.5); 
                    pic->getPixel(x * 10 + 5, y * 10 + 6) = cs225::HSLAPixel(d, 1, 0.5);
                    pic->getPixel(x * 10 + 6, y * 10 + 6) = cs225::HSLAPixel(d, 1, 0.5);
                    pic->getPixel(x * 10 + 7, y * 10 + 6) = cs225::HSLAPixel(d, 1, 0.5);
                    pic->getPixel(x * 10 + 2, y * 10 + 7) = cs225::HSLAPixel(d, 1, 0.5); 
                    pic->getPixel(x * 10 + 4, y * 10 + 7) = cs225::HSLAPixel(d, 1, 0.5);
                    pic->getPixel(x * 10 + 5, y * 10 + 7) = cs225::HSLAPixel(d, 1, 0.5);
                    pic->getPixel(x * 10 + 7, y * 10 + 7) = cs225::HSLAPixel(d, 1, 0.5);
                    for(int k = 0; k < 10; k++){
                        pic->getPixel(x * 10, y * 10 + k) = cs225::HSLAPixel(d, 1, 0.5);
                        pic->getPixel(x * 10 + 9, y * 10 + k) = cs225::HSLAPixel(d, 1, 0.5);
                        pic->getPixel(x * 10 + k, y * 10) = cs225::HSLAPixel(d, 1, 0.5);
                        pic->getPixel(x * 10 + k, y * 10 + 9) = cs225::HSLAPixel(d, 1, 0.5);
                    }
                }
                
            }
        }
        return pic;
    }
    double Room::getColor(int difficulty) const{
        if(difficulty <=10){
            return 125;
        }
        if(difficulty <=20){
            return 175;
        }
        if(difficulty <=30){
            return 200;
        }
        if(difficulty <=40){
            return 55;
        }
        if(difficulty <=50){
            return 35;
        }
        if(difficulty <=60){
            return 20;
        }
        if(difficulty <=70){
            return 330;
        }
        if(difficulty <=80){
            return 295;
        }
        if(difficulty <=90){
            return 275;
        }
        return 0;
    }