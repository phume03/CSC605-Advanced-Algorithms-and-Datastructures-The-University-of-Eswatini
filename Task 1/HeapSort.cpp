/****** 
 * Author: Phumelela Mdluli
 * Program: Heap Sort
 * Date: 25 October 2025
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
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include "dsexceptions.h"
#include <vector>
using namespace std;

#ifndef HEAP_SORT_H
#define HEAP_SORT_H

/**
 * Internal method for heapsort.
 * i is the index of an item in the heap.
 * Returns the index of the left child.
 */
inline int leftChild( int i ) {
    return (2 * i ) + 1;
}

/**
 * Internal method for heapsort that is used in
 * deleteMax and buildHeap.
 * i is the position from which to percolate down.
 * n is the logical size of the binary heap.
 */
template <typename Comparable>
void percDown( vector<Comparable> & a, int i, int n ) {
    int child;
    Comparable tmp;

    for( tmp = std::move( a[ i ] ); leftChild( i ) < n; i = child ) {
        child = leftChild( i );
        if( child != n - 1 && a[ child ] < a[ child + 1 ] )
            ++child;
        if( tmp < a[ child ] )
            a[ i ] = std::move( a[ child ] );
        else
            break;
    }
    a[ i ] = std::move( tmp );
}       

/**
 * buildMaxHeap.
 */
template <typename Comparable>
void buildMaxHeap( vector<Comparable> & a ) {
    for ( int i = (a.size( ) / 2) - 1; i >= 0; --i ) { /* buildMaxHeap */
        percDown(a, i, a.size( ) );
    }
    return;
}
template <typename Comparable>
void heapsort( vector<Comparable> & a ) {
    for ( int j = a.size( ) - 1; j > 0; --j ) { /* deleteMax */
        std::swap( a[ 0 ], a[ j ]); 
        percDown(a, 0, j );        
    }

    return;
}

#endif

int main(void) {
    double tempRandValue;
    int N; // number of random numbers
    int peek = 10; // peek only first 10 values
    srand(time(NULL)); // random number gen seed

    // get user-input
    cout<<"\n *** Running... ***\n";
    cout <<"\nPlease enter a positive integer, N (* N = 1,000 | 10,000 | 100,000 and 0 < N < 100,001): ";
    cin >> N;
    if (N > 100000 || N < 0) N=5; //set default value for N
    if (peek > N) peek = N;

    vector<long> a( N ); // vector array

    for (int i=0; i<N; i++) {
        //generate random values
        tempRandValue = rand()%100000 + 1; // generate random values as big as the greatest array-size possible, from 1:: disregards input size
        a[i] = (long) tempRandValue;
    }//end-for-loop
    buildMaxHeap( a );  

    cout<<"\n *** C++ Max-Heap Heapsort ***";
    cout<<"\n N =\t"<<N;
    cout<<"\n Y (unsorted):";
    for (int b=0; b<peek; b++) {
    cout <<"\t"<<a[b];
    }
    cout<<"... \n";

    // sort array and time
    chrono::time_point <chrono::high_resolution_clock> start_time = chrono::high_resolution_clock::now();
    heapsort( a );
    chrono::time_point <chrono::high_resolution_clock> end_time = chrono::high_resolution_clock::now();

    cout<<" X (sorted):";
    for (int b=0; b<peek; b++) {
        cout <<"\t"<<a[b];
    }
    cout<<"... \n";
    int64_t elapsed_time = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
    cout<<"Sorting Time: "<<elapsed_time<<" microseconds";

    cout <<"\n\n Done!\n";
    return 0;
}//end-main