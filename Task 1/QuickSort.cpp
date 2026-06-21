/****** 
 * Author: Phumelela Mdluli
 * Program: Quick Sort
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
#include <vector>

using namespace std;

#ifndef QUICK_SORT_H
#define QUICK_SORT_H

/**
 * My own implementation of Quick Sort swapping
 * following Gilles Brassard -- kind of, he does not have a separate method
 */
void qSwap( vector <long> & a, int index_i, int index_j ) {
    if (index_i < 0 || index_j < 0 || index_i >= a.size() || index_j >= a.size()) {
        throw std::out_of_range("Index out of bounds");
    }    
    auto tempElement = a[index_i];
    a[index_i] = a[index_j];
    a[index_j] = tempElement;
    return;
}

/**
 * My own implementation of Quick Sort partitioning
 * following Gilles Brassard
 * returns not the pivot element but the pivot point
 */
int qPartition( vector <long> & a, int left, int right ) {
    // Check if indices are within bounds
    if (left < 0 || right < 0 || left >= a.size() || right >= a.size()) {
        throw std::out_of_range("Index out of bounds");
    }     
    // partition method for smalling and larging leftmost and rightmost elements, respectively
    // 25836   7333    63116   72916   99725   56460   14203   22000   33351   64852
    // left                            center                                  right
    auto k = left, l = right;
    auto pivot = a[left];  

    // left-scan
    while (a[k] <= pivot && k < right) {
        k++;
    }

    // right-scan
    while (a[l] > pivot) {
        l--;
    }

    while (k < l) {
        qSwap(a, k, l);

        // left-scan
        while (a[k] <= pivot) {
            k++;
        }

        // right-scan
        while (a[l] > pivot) {
            l--;
        }
    }
    qSwap(a, left, l);
    return l;
}

/**
 * My own implementation of the Quick Sort algorithm
 * following Gilles Brassard.
 */
void quicksort( vector<long> & a, int left, int right ) {

    if (left < right) {
        int pivot = qPartition(a, left, right); // return pivot position which will be a perfectly sorted element
        quicksort(a, left, pivot-1); // re-run with small elements
        quicksort(a, pivot+1, right); // re-run with large elements
    }
    return;
}

#endif


int main(void) {
  double tempRandValue;
  int N; // number of random numbers
  int peek = 10; // peek only first 10 values
  srand(time(NULL)); // random number gen seed

  //get user-input
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

  cout<<"\n *** C++ Quick Sort ***";
  cout<<"\n N =\t"<<N;
  cout<<"\n Y (unsorted):";
  for (int b=0; b<peek; b++) {
  cout <<"\t"<<a[b];
  }
  cout<<"... \n";

  // sort array and time
  std::chrono::time_point <chrono::high_resolution_clock> start_time = chrono::high_resolution_clock::now();
  quicksort ( a, 0, N-1 );
  std::chrono::time_point <chrono::high_resolution_clock> end_time = chrono::high_resolution_clock::now();

  cout<<" X (sorted):";
  for (int b=0; b<peek; b++) {
  cout <<"\t"<<a[b];
  }
  cout<<"... \n";
  int64_t elapsed_time = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
  cout<<"Sorting Time: "<<elapsed_time<<" microseconds";

  cout <<"\n\n Done!\n";
}//end-main