/****** 
 * Author: Phumelela Mdluli
 * Program: AVL Tree
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
#include <time.h>
#include <chrono>
#include <cmath>
#include <vector>

using namespace std;

#ifndef BINARY_NODE_H
#define BINARY_NODE_H

// Standard Binary Node
// ******************PROPERTIES*********************
// element       --> Item to be store, typically a key reference
// left          --> Reference to the left child of the current node
// right         --> Reference to the right child of the current node
// height        --> The height of the node (or distance from leaf to the current node)
//                   All new nodes in a tree have a height of zero (0) because they are leafs
template <typename Comparable>
class Node {
    public:
        Comparable element;
        Node *left;
        Node *right;
        int height;

        Node( const Comparable & key, Node *ltChild, Node *rtChild, int h = 0 ) {
            element = key;
            left = ltChild;
            right = rtChild;
            height = h;
        }
}; // end node declaration

#endif

#ifndef AVL_TREE_H
#define AVL_TREE_H

// AVL Tree Implementation
// void insert( x )       --> Insert x | required
// void remove( x )       --> Remove x | required
// Comparable findMin( )  --> Return smallest item of a subtree | helper
// boolean isEmpty( )     --> Return true if empty; else false | helper
// void makeEmpty( )      --> Remove all elements | helper
// void printTree( )      --> Print implements printing in preorder, inorder, and postorder | required
template <typename Comparable>
class AvlTree {
  public:
    Node <Comparable> *root;
    static const int ALLOWED_IMBALANCE = 1;

    void makeEmpty( ) {
        return makeEmpty( root );
    }

    void makeEmpty( Node <Comparable> * & T ) {
        if( T != nullptr ) {
            makeEmpty( T->left );
            makeEmpty( T->right );
            delete T;
        }
        T = nullptr;
        return;
    } 
    
    bool isEmpty( ) {
        return ( root == nullptr );
    }    

    AvlTree( ) {
        root = nullptr;
        makeEmpty( );
    }   

    int height( Node <Comparable> *T ) {
        if ( T == nullptr ) {
            return 0; // zero or -1 ? A leaf with a null subtree or child has height 0 not -1!!!!
        } else {
            return T->height;
        }
    }

    void printTree( ) {
        if( isEmpty( ) ) {
            cout << "\n The Tree is Empty.";
        } else {
            cout<<"\n Pre-Order: \t";
            printTreePreOrder( root );
            cout<<"\n In-Order: \t";
            printTreeInOrder( root );
            cout<<"\n Post-Order: \t";
            printTreePostOrder( root );
            cout<<"\n";
        }
        return;
    }

    /***
     * Preorder traversal (recursive) of the nodes of the T is: 
     *      the root n of T, 
     *      the nodes of the left subtree T1, 
     *      the nodes of the right subtree T2 
     * 
     ***/
    void printTreePreOrder( Node <Comparable> *T ) {
        if( T != nullptr ) {
            cout<<" "<<T->element;
            printTreePreOrder( T->left );
            printTreePreOrder( T->right );
        }
        return;
    } 
    
    /***
     * Inorder traversal (recursive) of the nodes of the T is: 
     *      the nodes of the left subtree T1,
     *      the root n of T, 
     *      the nodes of the right subtree T2 
     * 
     ***/
    void printTreeInOrder( Node <Comparable> *T ) {
        if( T != nullptr ) {
            printTreeInOrder( T->left );
            cout<<" "<<T->element;
            printTreeInOrder( T->right );
        }
        return;
    } 
    
    /***
     * Postorder traversal (recursive) of the nodes of the T is:
     *      the nodes of the left subtree T1, 
     *      the nodes of the right subtree T2,
     *      the root n of T  
     * 
     ***/
    void printTreePostOrder( Node <Comparable> *T ) {
        if( T != nullptr ) {
            printTreePostOrder( T->left );
            printTreePostOrder( T->right );
            cout<<" "<<T->element;            
        }
        return;
    }
    
    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( Node<Comparable> * & k2 ) {
        Node <Comparable> *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), height( k2 ) ) + 1;
        k2 = k1;
        return;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild( Node<Comparable> * & k1 ) {
        Node <Comparable> *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), height( k1 ) ) + 1;
        k1 = k2;
        return;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild( Node<Comparable> * & k3 ) {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
        return;
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild( Node<Comparable> * & k1 ) {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
        return;
    }

    /***
     *  Balance the binary tree, checking where the change was just made
     *  and assuming T is balanced or within one of being balanced
     */
    void balance( Node<Comparable> * & T ) {
        if( T == nullptr ) {
            return;
        }
        
        if( ( height(T->left) - height(T->right) ) > ALLOWED_IMBALANCE ) { 
            // check for left-subtree imbalance, use height because if T is a leaf there will be an error, the height function solves this for us by returning 0
            
            if( height( T->left->left ) >= height( T->left->right ) ) { 
                rotateWithLeftChild( T );
            } else {
                doubleWithLeftChild( T );
            }
        } else if( ( height(T->right) - height(T->left) ) > ALLOWED_IMBALANCE ) { // check for right-subtree imbalance
            if( height( T->right->right ) >= height( T->right->left ) ) {
                rotateWithRightChild( T );
            } else {
                doubleWithRightChild( T );
            }
        } else {
            T->height = max( height( T->left ), height( T->right ) ) + 1;
        }
        return;
    }

    /**
     * Insert x into the tree as with a binary tree; duplicates (x == T->element) are ignored.
     */
    void insert( const Comparable & x ) {
        insert( x, root );
        printTree( );
        return;
    }

    void insert( const Comparable & x, Node <Comparable> * & T ) {
        if( T == nullptr ) {
            T = new Node <Comparable> ( x, nullptr, nullptr );
        } else if( x < T->element ) {
            insert( x, T->left );
        } else if( x > T->element ) {
            insert( x, T->right );
        } else {
            // removed as printout would be too large on the screen...
            // cout<<"\n That element is a duplicate!";
            // cout<<"\n AVL Tree unchanged.";
        }

        balance( T );
        return;
    }

    /**
     * Helper functions to delete
     */
    const Comparable & findMin( ) {
        if( isEmpty( ) ) {
            throw UnderflowException{ };
        }

        return findMin( root )->element;
    }

    Node<Comparable> * findMin( Node <Comparable> *T ) {
        if( T == nullptr ) {
            return nullptr;
        }

        if( T->left == nullptr ) {
            return T;
        }
        return findMin( T->left );
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */    
    void remove( const Comparable & x ) {
        remove( x, root );
        printTree( );
    }    

    void remove( const Comparable & x, Node <Comparable> * & T ) {
        if( T == nullptr ) {
            cout<<"\n That element does not exist!";
            cout<<"\n AVL Tree unchanged.";
            return;   // Item not found; do nothing
        }

        if ( x < T->element ) {
            remove( x, T->left );
        } else if ( x > T->element ) {
            remove( x, T->right );
        } else if ( T->left != nullptr && T->right != nullptr ) { // Two children
            T->element = findMin( T->right )->element;
            remove( T->element, T->right );
        } else {
            // searched and found node x to be removed
            Node <Comparable> *oldNode = T;
            if (T->left != nullptr) {
                T = T->left;
            } else {
                T = T->right;
            }
            delete oldNode;
        }
        
        balance( T );
        return;
    }
}; // end AVL Tree Class

#endif

int main( ) {
    double tempRandValue;
    int N; // number of random numbers
    srand(time(NULL)); // random number gen seed

    //get user-input
    cout<<"\n *** Running C++ AVL Tree Insertion ***";
    cout <<"\nPlease enter a positive integer, N (* N = 1,000 | 10,000 | 100,000 and 0 < N < 100,001) for array size: ";
    cin >> N;
    if (N > 100000 || N < 0) N=5; //set default value for N

    AvlTree<long> T; // AVL Tree as classed
    
    std::chrono::time_point <chrono::high_resolution_clock> start_time = chrono::high_resolution_clock::now();
    for (int i=0; i<N; i++) {
        //generate random values
        tempRandValue = rand()%100000 + 1; // generate random values as big as the greatest size possible, from 1:: disregards input size
        T.insert( (long) tempRandValue );
    }//end-for-loop
    std::chrono::time_point <chrono::high_resolution_clock> end_time = chrono::high_resolution_clock::now();

    cout<<"... \n";
    int64_t elapsed_time = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
    cout<<"\n "<<N<<" AVL insertions were performed in "<<elapsed_time<<" microseconds";
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