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
        int value;
        Node* left;
        Node* right;

        Node(const int& newKey, const int& newValue)
            : key(newKey), value(newValue), left(NULL), right(NULL)
        {
        }
    };

  public:
    BST();
    bool greater(std::vector<int>& A, std::vector<int>& B);
    void insert(const int& key, const int& value);
    int find(const int& key);
    void preOrder(Node* n);
    void inOrder(Node* n);
    void postOrder(Node* n);

  private:
    Node* root;
    std::vector<int> allNodes;
    //void insert(Node*& node, const int& key, const int& value);
    struct Node* &  find(Node*& node, const int& key);
};

