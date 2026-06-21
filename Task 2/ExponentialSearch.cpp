/****** 
 * Author: Phumelela Mdluli
 * Program: Exponential Search
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
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include <cmath>
#include <vector>

using namespace std;

#ifndef EXPONENTIAL_SEARCH_H
#define EXPONENTIAL_SEARCH_H

/**
 * Exponential Search method
 */
template <typename Comparable>
bool exponentialSearch(vector <Comparable> & A, Comparable K) {

  if (A.size() == 0) {
    return false; // NOT FOUND
  }

  int bound = 1; 
  while (bound < A.size() && A[ bound ] < K ) {
    bound = bound * 2;
  }

  int left = bound / 2;
  int right = min(bound, (int) A.size() - 1);

  // had initially used the system binary_search algorithm
  while (left <= right) {
      int midVal = round((left + right)/2); 
      
      if (K > A[midVal]) {
          left = midVal + 1;
      } else if (K < A[midVal]) {
          right = midVal - 1;
      } else {
          return true;
      }
  }
  return false; // NOT FOUND 
}

#endif

int main(void) {
    double tempRandValue;
    int N; // number of random numbers
    long K; // search key
    bool found;
    int peek = 10; // peek only first 10 values
    srand(time(NULL)); // random number gen seed

    //get user-input
    cout<<"\n *** Running... ***\n";
    cout <<"\nPlease enter a positive integer, N (* N = 1,000 | 10,000 | 100,000 and 0 < N < 100,001) for array size: ";
    cin >> N;
    if (N > 100000 || N < 0) N=5; //set default value for N
    if (peek > N) peek = N;

    vector<long> a( N ); // vector array

    for (int i=0; i<N; i++) {
        //generate random values
        tempRandValue = rand()%100000 + 1; // generate random values as big as the greatest array-size possible, from 1:: disregards input size
        a[i] = (long) tempRandValue;
    }//end-for-loop

    // sort the array
    sort(a.begin(), a.end());

    cout<<"\n *** C++ Exponential Search ***";
    cout<<"\n N =\t"<<N;
    cout<<"\n Y (sorted):";
    for (int b=0; b<peek; b++) {
      cout <<"\t"<<a[b];
    }

    cout<<"... \n";
    cout <<"\nPlease enter a positive integer, K to search for in A: ";
    cin >> K;
    if (K > 100000 || K < 0) {
        K = (long) rand()%100000 + 1; //set default value for K
        cout<<"\n K was not valid, random K = "<<K<<" was chosen.";
    } else {
        cout<<"\n K =\t"<<K;
    }

    // search array and time
    std::chrono::time_point <chrono::high_resolution_clock> start_time = chrono::high_resolution_clock::now();
    found = exponentialSearch( a, K );
    std::chrono::time_point <chrono::high_resolution_clock> end_time = chrono::high_resolution_clock::now();

    cout<<"... \n";
    int64_t elapsed_time = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
    if (found) {
        cout<<" Found in "<<elapsed_time<<" microseconds";
    } else {
        cout<<" K was not Found";
        cout<<"\n Search time was "<<elapsed_time<<" microseconds";
    }

    //  ---------- DONE FOR ASSIGNMENT -- RESEARCH A Repeat --
    cout<<"... \n";
    int repeats = 100000;
    // search, repeat, and time
    start_time = chrono::high_resolution_clock::now();
    for (int i=0; i<repeats; i++) {
        // randomly select K in a for each repeat
        double index = rand() % N; // 0 to N - 1
        K = a[ ( int ) index ];
        // not printed out as large datasets would make the CMD unreadable
        // cout<<"\n K =\t"<<K;
        exponentialSearch( a, K );
    }//end-for-loop
    end_time = chrono::high_resolution_clock::now();
    cout<<"... \n";
    elapsed_time = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
    cout<<"\n Experiment was repeated "<<repeats<<" times";
    cout<<"\n Search time was "<<elapsed_time<<" microseconds";    

    cout <<"\n\n Done!\n";
    return 0;
}//end-main