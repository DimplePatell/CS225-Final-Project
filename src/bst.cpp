#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include "bst.h"

//bst contructor
//takes in a csv datafile by name and an integer representing the size of the bst wanted
//creates a bst of the top num_enemies number of twitch streamers
BST::BST(std::string file_name, int num_enemies) {

    std::string lines;
    std::ifstream file(file_name);
    std::vector<int> gamers;
    if (file.is_open()) {
        while (std::getline(file, lines)) {
            std::stringstream ss(lines);
            std::string str;
            std::vector<std::string> row;
            while (std::getline(ss, str, ',')) {
                row.push_back(str);
                
            }
            if (std::stoi(row[0]) >= 0) {
                gamers.push_back(std::stoi(row[0]));
                //inserts the number of streams for each twitch gamer
            }  
        }
    }
    
    file.close();
    sort(gamers.rbegin(), gamers.rend());
    gamers.erase(gamers.begin() + num_enemies, gamers.end());
    //sorts it from most to least to get the top gamers of size num_enemies
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
    std::shuffle(gamers.begin(), gamers.end(), e);
    //randomly sorts the gamers vector for a more efficient bst contruction
    
    for (int i = 0; i < num_enemies; i++) {
        insert(gamers[i]);
        //inserts into the bst
    }
}
struct BST::Node* BST::getRoot(){
    return root;
}

//returns a vector representing either a pre, in, or post order traversal of the bst depending on the parameter passed in 0, 1, and 2, respectively
//used to make the implementation of Room::addEnemies more randomlized
std::vector<int> BST::getAllNodes(int c){
    if (c == 0) {
        allNodes_one.clear();
        preOrder(root);
        return allNodes_one;
    } else if (c == 1) {
        allNodes_two.clear();
        inOrder(root);
        return allNodes_two;
    } else {
        allNodes_three.clear();
        postOrder(root);
    }
    return allNodes_three;
}

//inserts a key into the bst (stores each gamer/enemy)
void BST::insert(const int & key) {
    Node* n = new Node(key);
    if (root == NULL) {
        root = n;
        return;
    }
    Node* back = NULL;
    Node* temp = root;
    while (temp != NULL) {
        if (temp->key > key) {
            back = temp;
            temp = temp->left;
        } else if (temp->key < key) {
            back = temp;
            temp = temp->right;
        }
    }
    if (back->key > key) {
        back->left = n;
    } else {
        back->right = n;
    }
}

//preorder traversal of the bst
void BST::preOrder(Node* n) {
    if (n == NULL) {
        return;
    }
    allNodes_one.push_back(n->key);
    preOrder(n->left);
    preOrder(n->right);
}

//inorder traversal of the bst
void BST::inOrder(Node* n) {
    if (n == NULL) {
        return;
    }
    inOrder(n->left);
    allNodes_two.push_back(n->key);
    inOrder(n->right);
}

//postorder traversal of the bst
void BST::postOrder(Node* n) {
    if (n == NULL) {
        return;
    }
    postOrder(n->left);
    postOrder(n->right);
    allNodes_three.push_back(n->key);
}
