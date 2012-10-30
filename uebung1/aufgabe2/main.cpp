/* 
 * File:   main.cpp
 * Author: richard
 *
 * Created on October 30, 2012, 3:19 PM
 */

#include <iostream>
#include <cstdlib>
#include "Heap.h"

using namespace std;

/**
 * Main method for program execution.
 * @return 0 if no error occurred.
 */
int main() {
    unsigned heapSize = 10;
    double array[] = {2, 9, 3, 6, 1, 4, 5, 7, 0, 8};

    Heap heap(heapSize);
    for (unsigned i = 0; i < heapSize; i++) {
        heap.push(array[i]);
    }
    heap.sort();

    return 0;
}