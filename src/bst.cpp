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
    int c = 0;
    for (std::vector<int> i : gamers) {
        if (c == 1000) {
            break;
        }
        insert(i[0], i[1]);
        c++;
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


// int BST::find(const int& key) {
//     return find(root, key)->value;
// }

struct BST::Node* & BST::find(Node* & subtree, const int& key) {
    if (subtree == NULL || subtree->key == key) {
        return subtree;
    }
    if (key < subtree->key) {
        return find(subtree->left, key);
    }
    return find(subtree->right, key);
}

void BST::insert(const int & key, const int & value) {
    if (find(root, key) == NULL) {
        find(root, key) = new Node(key, value);
    } else {
        root = putIn(root, key, value);
    }
}

struct BST::Node* BST::putIn(Node*& node, const int & key, const int & value) {
    if (node == null)  {
        return new Node(key, value);
    }
    if (key < node->key) {
        node.left = putIn(node.left, key, value);
    } else
        node.right = putIn(node.right, key, value);
    }
    return node;
}

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
