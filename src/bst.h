#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
//#include "utils.h"



class BST
{
  private:
  //each value in the bst is a node with a key and can access its left and right nodes
    struct Node {
        int key;
        Node* left;
        Node* right;

        Node(const int& newKey)
            : key(newKey), left(NULL), right(NULL)
        {
        }
    };

  public:
    //bst contructor
    //takes in a csv datafile by name and an integer representing the size of the bst wanted
    //creates a bst of the top num_enemies number of twitch streamers
    BST(std::string file_name, int num_enemies);
  
    //inserts a key into the bst (stores each gamer/enemy)
    void insert(const int& key);
    
    //preorder traversal of the bst
    void preOrder(Node* n);
  
    //inorder traversal of the bst
    void inOrder(Node* n);
  
    //postorder traversal of the bst
    void postOrder(Node* n);
  
    //returns the root
    Node* getRoot();
    
    //returns a vector representing either a pre, in, or post order traversal of the bst depending on the parameter passed in 0, 1, and 2, respectively
    //used to make the implementation of Room::addEnemies more randomlized
    std::vector<int> getAllNodes(int c);

  private:
    Node* root = NULL;
  
    //vector that stores the preorder traversal for the bst
    std::vector<int> allNodes_one;
  
    //vector that stores the preorder traversal for the bst
    std::vector<int> allNodes_two;
  
    //vector that stores the preorder traversal for the bst
    std::vector<int> allNodes_three;
};
