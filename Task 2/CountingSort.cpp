/****** 
 * Author: Phumelela Mdluli
 * Program: Counting Sort
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

#ifndef COUNTING_SORT_H
#define COUNTING_SORT_H

template <typename Comparable>
void countingsort(vector <Comparable> & A, vector <Comparable> & B, int N) {
  
  vector<Comparable> C( N );

  for (int i=0; i<C.size(); i++) {
    C[i] = 0;
  }
  
  for (int j=1; j<A.size(); j++) {
    C[A[j]] = C[A[j]] + 1;
  }

  // C[i] now contains the number of elements equal to i
  for (int i=1; i<N; i++) {
    C[i] = C[i] + C[i-1];
  }
    

  // C[i] now contains the number of elements less than or equal to i
  for (int j=A.size()-1; j>0; j--) {
    B [ C [ A[ j ] ] ] = A[ j ];
    C[A[j]] = C[A[j]] - 1;
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

    vector<long> a( N ); // vector array:: initial array
    vector<long> b( N ); // vector array:: output array

    for (int i=0; i<N; i++) {
        //generate random values
        tempRandValue = rand()%100000 + 1; // generate random values as big as the greatest array-size possible, from 1:: disregards input size
        // the above was altered, noting large time values, the results are the same (timewise)
        a[i] = (long) tempRandValue;
    }//end-for-loop  

    cout<<"\n *** C++ Counting Sort ***";
    cout<<"\n N =\t"<<N;
    cout<<"\n Y (unsorted):";
    for (int i=0; i<peek; i++) {
    cout <<"\t"<<a[i];
    }
    cout<<"... \n";

    // sort array and time
    chrono::time_point <chrono::high_resolution_clock> start_time = chrono::high_resolution_clock::now();
    countingsort( a, b, 100001 );
    chrono::time_point <chrono::high_resolution_clock> end_time = chrono::high_resolution_clock::now();

    cout<<" X (sorted):";
    for (int j=0; j<peek; j++) {
        cout <<"\t"<<b[j];
    }
    cout<<"... \n";
    int64_t elapsed_time = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
    cout<<"Sorting Time: "<<elapsed_time<<" microseconds";

    cout <<"\n\n Done!\n";
    return 0;
}//end-main