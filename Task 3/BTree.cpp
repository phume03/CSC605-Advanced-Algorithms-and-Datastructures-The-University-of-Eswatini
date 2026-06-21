/****** 
 * Author: Phumelela Mdluli
 * Program: B Tree
 * Date: 9 November 2025
 *
 * Copyright 2025 Live System User <liveuser@localhost-live>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *    
******/

#include "dsexceptions.h"
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <cmath>
#include <vector>

using namespace std;

#ifndef NODE_H
#define NODE_H

// BTree Node
template <typename Comparable>
class Node {
public:
    static const int MINIMUM_DEGREE = 2;   // t is the minimum degree of the B-tree, here t>=2
    static const int ORDER = 4; // m (order) is the maximum number of children any node can have 
    vector<Comparable> keys; // a list of the keys, sorted in ascending order
    vector<Node*> children; // a list of the children
    bool isLeaf;    // flag for node being a leaf node or not, default is true
    
    Node(bool leaf = true) {
        isLeaf = leaf;
        keys.reserve(ORDER - 1);
        children.reserve(ORDER);
    }
    
    ~Node() { // I typically do not implement destructors in my code
        for (Node* child : children) {
            delete child;
        }
    }
    
    bool is_full() const {
        return keys.size() == ORDER - 1;
    }
    
    bool has_min_keys() const {
        return keys.size() >= MINIMUM_DEGREE;
    }
}; // end node declaration
#endif

#ifndef B_TREE_H
#define B_TREE_H

// B Tree Implementation
template <typename Comparable>
class BTree {
private:
    Node<Comparable>* root;
    static const int MIN_KEYS = (Node<Comparable>::ORDER - 1) / 2;

public:
    BTree() {
        root = nullptr; 
        /**
         * same as the member initializer technique below, apparently member initializer is more efficient 
         * BTree () : root (nullptr) {}
         * 
         */
    }
    
    ~BTree() { // BTree destructor
        makeEmpty();
    }
    
    void makeEmpty() {
        makeEmpty(root);
    }

    void makeEmpty(Node<Comparable>* &T) {
        if (T != nullptr) {
            delete T;
            T = nullptr;
        }
    } 
    
    bool isEmpty() const {
        return (root == nullptr);
    }    

    // Insertion helpers p494 Cormen et. al.
    void splitChild(int index, Node<Comparable>* T) {
        Node<Comparable>* fullChild = T->children[index];
        Node<Comparable>* newChild = new Node<Comparable>(fullChild->isLeaf);
        
        // Middle key moves up to parent
        Comparable middleKey = fullChild->keys[MIN_KEYS];
        
        // Split keys: right half goes to new child
        for (int i = MIN_KEYS + 1; i < Node<Comparable>::ORDER - 1; ++i) {
            newChild->keys.push_back(fullChild->keys[i]);
        }
        fullChild->keys.resize(MIN_KEYS);
        
        // Split children if not leaf
        if (!fullChild->isLeaf) {
            for (int i = MIN_KEYS + 1; i < Node<Comparable>::ORDER; ++i) {
                newChild->children.push_back(fullChild->children[i]);
            }
            fullChild->children.resize(MIN_KEYS + 1);
        }
        
        // Insert middle key and new child into parent
        T->keys.insert(T->keys.begin() + index, middleKey);
        T->children.insert(T->children.begin() + index + 1, newChild);
        // no disk reads or writes
        return;
    }

    // p496 Cormen et. al.
    void insertNonFull(const Comparable &x, Node<Comparable>* T) {
        int i = T->keys.size() - 1;
        
        if (T->isLeaf) {
            // Insert into leaf
            T->keys.push_back(x); // Temporary placeholder
            while (i >= 0 && x < T->keys[i]) {
                T->keys[i + 1] = T->keys[i];
                i--;
            }
            T->keys[i + 1] = x;
        } else {
            // Find child to insert into
            while (i >= 0 && x < T->keys[i]) {
                i--;
            }
            i++;
            
            // Split child if full
            if (T->children[i]->is_full()) {
                splitChild(i, T);
                if (x > T->keys[i]) {
                    i++;
                }
            }
            insertNonFull(x, T->children[i]);
        }
        return;
    }

    // Insertion p495 Cormen et. al.
    void insert(const Comparable &x) {
        if (root == nullptr) {
            root = new Node<Comparable>(true);
            root->keys.push_back(x);
            return;
        }

        if (root->is_full()) {
            Node<Comparable>* newRoot = new Node<Comparable>(false);
            newRoot->children.push_back(root);
            splitChild(0, newRoot);
            root = newRoot;
        }

        // done either way, removed from if statement for simplicity
        insertNonFull(x, root);
        print();
    }

    // Search helper
    bool searchRecursive(const Comparable &x, Node<Comparable>* T) const {
        if (T == nullptr) return false;
        
        int i = 0;
        while (i < T->keys.size() && x > T->keys[i]) {
            i++;
        }
        
        if (i < T->keys.size() && x == T->keys[i]) {
            return true;
        }
        
        if (T->isLeaf) {
            return false;
        }
        // from Cormen et. al. remember there are no disk read or write operations
        return searchRecursive(x, T->children[i]);
    }    
    
    // p492 Cormen et. al.
    bool search(const Comparable &x) {
        return searchRecursive(x, root);
    }    

    // Deletion helpers
    int findKeyIndex(const Comparable &x, Node<Comparable>* T) {
        int idx = 0;
        while (idx < T->keys.size() && T->keys[idx] < x) {
            idx++;
        }
        return idx;
    }

    void removeFromLeaf(int idx, Node<Comparable>* T) {
        T->keys.erase(T->keys.begin() + idx);
    }

    Comparable getPredecessor(int idx, Node<Comparable>* T) {
        // Go to left child, then rightmost key
        Node<Comparable>* current = T->children[idx];
        while (!current->isLeaf) {
            current = current->children.back();
        }
        return current->keys.back();
    }

    Comparable getSuccessor(int idx, Node<Comparable>* T) {
        // Go to right child, then leftmost key
        Node<Comparable>* current = T->children[idx + 1];
        while (!current->isLeaf) {
            current = current->children[0];
        }
        return current->keys[0];
    }
    
    void mergeChildren(int idx, Node<Comparable>* T) {
        Node<Comparable>* child = T->children[idx];
        Node<Comparable>* rightSibling = T->children[idx + 1];
        
        // Move key from parent to child
        child->keys.push_back(T->keys[idx]);
        
        // Copy keys from right sibling
        for (Comparable key : rightSibling->keys) {
            child->keys.push_back(key);
        }
        
        // Copy children from right sibling if not leaf
        if (!child->isLeaf) {
            for (Node<Comparable>* grandchild : rightSibling->children) {
                child->children.push_back(grandchild);
            }
        }
        
        // Remove key and child from parent
        T->keys.erase(T->keys.begin() + idx);
        T->children.erase(T->children.begin() + idx + 1);
        
        // Delete the merged right sibling
        rightSibling->children.clear(); // Prevent double deletion
        delete rightSibling;
    }

    void removeFromNonLeaf(int idx, Node<Comparable>* T) {
        Comparable key = T->keys[idx];
        
        // Case 2a: Left child has at least min_keys + 1 keys
        if (T->children[idx]->keys.size() > MIN_KEYS) {
            Comparable predecessor = getPredecessor(idx, T);
            T->keys[idx] = predecessor;
            removeRecursive(predecessor, T->children[idx]);
        }
        // Case 2b: Right child has at least min_keys + 1 keys  
        else if (T->children[idx + 1]->keys.size() > MIN_KEYS) {
            Comparable successor = getSuccessor(idx, T);
            T->keys[idx] = successor;
            removeRecursive(successor, T->children[idx + 1]);
        }
        // Case 2c: Both children have min_keys, merge them
        else {
            mergeChildren(idx, T);
            removeRecursive(key, T->children[idx]);
        }
    }

    void borrowFromLeft(int idx, Node<Comparable>* T) {
        Node<Comparable>* child = T->children[idx];
        Node<Comparable>* leftSibling = T->children[idx - 1];
        
        // Move key from parent to child
        child->keys.insert(child->keys.begin(), T->keys[idx - 1]);
        
        // Move key from left sibling to parent
        if (!leftSibling->isLeaf) {
            child->children.insert(child->children.begin(), leftSibling->children.back());
            leftSibling->children.pop_back();
        }
        
        T->keys[idx - 1] = leftSibling->keys.back();
        leftSibling->keys.pop_back();
    }
    
    void borrowFromRight(int idx, Node<Comparable>* T) {
        Node<Comparable>* child = T->children[idx];
        Node<Comparable>* rightSibling = T->children[idx + 1];
        
        // Move key from parent to child
        child->keys.push_back(T->keys[idx]);
        
        // Move key from right sibling to parent
        if (!rightSibling->isLeaf) {
            child->children.push_back(rightSibling->children[0]);
            rightSibling->children.erase(rightSibling->children.begin());
        }
        
        T->keys[idx] = rightSibling->keys[0];
        rightSibling->keys.erase(rightSibling->keys.begin());
    }
     
    void fillChild(int idx, Node<Comparable>* T) {
        // Borrow from left sibling if possible
        if (idx != 0 && T->children[idx - 1]->keys.size() > MIN_KEYS) {
            borrowFromLeft(idx, T);
        }
        // Borrow from right sibling if possible
        else if (idx != T->keys.size() && T->children[idx + 1]->keys.size() > MIN_KEYS) {
            borrowFromRight(idx, T);
        }
        // Merge with sibling
        else {
            if (idx != T->keys.size()) {
                mergeChildren(idx, T);
            } else {
                mergeChildren(idx - 1, T);
            }
        }
    }    
     
    void removeRecursive(const Comparable &x, Node<Comparable>* T) {
        int idx = findKeyIndex(x, T);
        
        if (idx < T->keys.size() && T->keys[idx] == x) {
            // Key found in this node
            if (T->isLeaf) {
                removeFromLeaf(idx, T);
            } else {
                removeFromNonLeaf(idx, T);
            }
        } else {
            // Key not in this node, recurse to appropriate child
            if (T->isLeaf) {
                return; // Key not found
            }
            
            bool lastChild = (idx == T->children.size() - 1);
            
            // Ensure child has at least min_keys + 1 keys
            if (T->children[idx]->keys.size() <= MIN_KEYS) {
                fillChild(idx, T);
            }
            
            // Update idx after potential merge
            if (lastChild && idx > T->keys.size()) {
                removeRecursive(x, T->children[idx - 1]);
            } else {
                removeRecursive(x, T->children[idx]);
            }
        }
    }

    // Deletion
    bool remove(const Comparable &x) {
        if (!search(x)) return false;
        
        removeRecursive(x, root);
        
        // If root becomes empty
        if (root->keys.empty() && !root->isLeaf) {
            Node<Comparable>* oldRoot = root;
            root = root->children[0];
            oldRoot->children.clear(); // Prevent double deletion
            delete oldRoot;
        }
        print();
        return true;
    }
 
    void printRecursive(Node<Comparable>* T, int depth) const {
        if (T == nullptr) return;
        
        string indent(depth * 2, ' ');
        cout << indent << "[";
        for (int i = 0; i < T->keys.size(); ++i) {
            cout << T->keys[i];
            if (i < T->keys.size() - 1)
                cout << ", ";
        }
        cout << "]" << endl;
        
        if (!T->isLeaf) {
            for (Node<Comparable>* child : T->children) {
                printRecursive(child, depth + 1);
            }
        }
    }

    void print() const {
        cout<<"\n Printing current tree state: \n";
        printRecursive(root, 0);
    }
}; // end B Tree Class

#endif

int main( ) {
    double tempRandValue;
    int N; // number of random numbers
    srand(time(NULL)); // random number gen seed

    //get user-input
    cout<<"\n *** Running C++ B (Balanced) Tree Insertion ***";
    cout <<"\n For this assignment, it was requested that the BTree demonstrate the input of 10-15 values.";
    N = 12;
    if (N > 15 || N < 10) N=10; //set default value for N

    BTree<long> T; // AVL Tree as classed
    
    std::chrono::time_point <chrono::high_resolution_clock> start_time = chrono::high_resolution_clock::now();
    for (int i=0; i<N; i++) {
        //generate random values
        tempRandValue = rand()%100000 + 1; // generate random values as big as the greatest size possible, from 1:: disregards input size
        T.insert( (long) tempRandValue );
    }//end-for-loop
    std::chrono::time_point <chrono::high_resolution_clock> end_time = chrono::high_resolution_clock::now();

    cout<<"... \n";
    int64_t elapsed_time = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
    cout<<"\n "<<N<<" balanced insertions were performed in "<<elapsed_time<<" microseconds";
    long R;
    cout <<"\nPlease enter a value to remove: ";
    cin >> R;
    T.remove( R );
    cout <<"\nPlease enter another value to remove: ";
    cin >> R;
    T.remove( R );

    cout <<"\n\n Done!\n";
    return 0;
}