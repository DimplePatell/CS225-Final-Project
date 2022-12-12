#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
//#include "utils.h"



class BST
{
  private:
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
    BST(std::string file_name, int num_enemies);
    void insert(const int& key);
    void preOrder(Node* n);
    void inOrder(Node* n);
    void postOrder(Node* n);
    Node* getRoot();
    std::vector<int> getAllNodes(int c);

  private:
    Node* root = NULL;
    std::vector<int> allNodes_one;
    std::vector<int> allNodes_two;
    std::vector<int> allNodes_three;
};
