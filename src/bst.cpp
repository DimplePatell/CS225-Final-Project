#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include "bst.h"

BST::BST() {

    std::string lines;
    std::ifstream file;
    file.open("large_twitch_features.csv");
    std::vector<std::vector<int>> gamers;
    
    while (std::getline(file, lines)) {
        std::stringstream ss(lines);
        std::string str;
        
        std::vector<std::string> row;
       
        while (std::getline(ss, str, ',')) {
            row.push_back(str);
            
        }
        std::vector<int> temp;
        if (std::stoi(row[0]) >= 0 && std::stoi(row[5]) >= 0) {
            temp.push_back(std::stoi(row[0]));
            temp.push_back(std::stoi(row[5]));
            gamers.push_back(temp);
        }  
    }
    
    sort(gamers.begin(), gamers.end());
    //gamers.erase(gamers.begin(), gamers.end()); //should be 1000, for testing purposes only
    for (std::vector<int> i : gamers) {
        insert(i[0], i[1]);
    }
}
struct BST::Node* BST::getRoot(){
    return root;
}
std::vector<int> BST::getAllNodes(){
    return allNodes;
}
bool BST::greater(std::vector<int>& A, std::vector<int>& B)
{
    if (A[0] < B[0])
        return true; //no swap
    //swap
    return false;
}


int BST::find(const int& key) {
    return find(root, key)->value;
}

struct BST::Node* & BST::find(Node* & subtree, const int& key) {
   
    if (subtree != NULL) {
        if (key < subtree->key) {
            return find(subtree->left, key);
        } else if (key > subtree->key) {
            return find(subtree->right, key);
        }
    }
    return subtree;
}

void BST::insert(const int & key, const int & value) {
    if (find(root, key) == NULL) {
        find(root, key) = new Node(key, value);
    }
}

// void BST::insert(Node*& node, const int & key, const int & value) {
//     insert(root, key);
// }

void BST::preOrder(Node* n) {
    allNodes.clear();
    if (n == NULL) {
        return;
    }
    allNodes.push_back(n->key);
    preOrder(n->left);
    preOrder(n->right);
}

void BST::inOrder(Node* n) {
    allNodes.clear();
    if (n == NULL) {
        return;
    }
    preOrder(n->left);
    allNodes.push_back(n->key);
    preOrder(n->right);
}

void BST::postOrder(Node* n) {
    allNodes.clear();
    if (n == NULL) {
        return;
    }
    preOrder(n->left);
    preOrder(n->right);
    allNodes.push_back(n->key);
}
