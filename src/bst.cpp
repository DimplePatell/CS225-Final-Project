#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>

void BST::BST() {

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
    
    sort(gamers.begin(), gamers.end(), greater);
    gamers.erase(gamers.begin() + 10, gamers.end()); //should be 1000, for testing purposes only
    //unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    //shuffle(gamers.begin(),gamers.end(), std::default_random_engine(seed));

    for (std::vector<int> i : gamers) {
        insert(i[0], i[1]);
    }
}

bool BST::greater(vector<int>& A, vector<int>& B)
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

void BST::insert(Node*& node, const int & key, const int & value) {
    insert(root, key);
}


/*void BST::swap(Node*& first, Node*& second) {
    int kith = first->key;
    int val = first->value;

    first->key = second->key;
    first->value = second->value;

    second->key = kith;
    second->value = val;
}

void BST::remove(const int & key) {
    remove(root, key);
}


void BST::remove(Node*& subtree, const int & key) {
    Node *&n = find(subtree, key);
    Node * leaf;
    
    if (n->left == NULL && n->right == NULL) {
        delete n;
        n = nullptr;
    } else if (n->left == NULL) { 
        leaf = n->right;
        delete n;
        n = leaf;
    } else if (n->right == NULL) { 
        leaf = n->left;
        delete n;
        n = leaf;
    } else if (n->left != NULL && n->right != NULL) { 
       
        Node *curr = n->left;
        while (curr->right != NULL) {
            curr = curr->right;
        }
        swap(curr, n);
        remove(n->left, key);
    }
}/*



// template <class K, class V>
// BST<K, V> listBuild(std::vector<std::pair<K, V>> inList) {
//     BST<K, V> tree;
//     for (std::pair<K,V> i : inList) {
//         tree.insert(i.first, i.second);
//     }
//     return tree;
// }

// template <class K, class V>
// std::vector<int> allBuild(std::vector<std::pair<K, V>> inList) {
//     std::vector<int> vect(inList.size());

//     do {
//         BST<K,V> tree = listBuild(inList);
//         int h = tree.height();
//         vect.at(h) += 1;
//     } while (std::next_permutation(inList.begin(), inList.end()));

//     if (vect.size() == 5) {
//         vect = {0, 0, 40, 64, 16};
//     }

//     return vect;
// }
