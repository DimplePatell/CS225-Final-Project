#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include "utils.h"
#include "bst.cpp"

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
    //BST(const BST& other);
    //~BST();
    bool greater(std::vector<int>& A, std::vector<int>& B);
    //const BST& operator=(const BST& rhs);
    //void clear();
    //int height() const;
    void insert(const int& key, const int& value);
    //void remove(const int& key);
    int find(const int& key);
    //void printFunctionOrder(std::ostream& out = std::cout) const;
    //void print(std::ostream& out = std::cout, bool order = true) const;
    //void setOutput(std::ostream& newOut);
    //std::vector<int> getInorderTraversal() const;
    //std::vector<int> getPreorderTraversal() const;
    //std::vector<std::string> getFunctionOrder() const;

  private:
    Node* root;
    void insert(Node*& node, const int& key, const int& value);
    //void remove(Node*& node, const int& key);
    struct BST::Node* &  find(Node*& node, const int& key);
    //int height(const Node* subRoot) const;
    //void swap(Node*& first, Node*& second);
    //Node* copy(const Node* subRoot);
    //void clear(Node* subRoot);
    //void getInorderTraversal(const Node* subRoot, std::vector<int>& traversal) const;
    //void getPreorderTraversal(const Node* subRoot, std::vector<int>& traversal) const;
};

