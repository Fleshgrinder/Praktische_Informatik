/* 
 * File:   main.cpp
 * Author: Richard Fussenegger
 *
 * Created on October 30, 2012, 1:17 PM
 */

#include <cstdlib>
#include <sstream>
#include "Heap.h"
#include "Custom.h"

using namespace std;

/*
 * 
 */
int main() {
    Heap<Custom> heap(5);

    for (unsigned i = 0; i < 5; i++) {
        heap.push(Custom("Custom" + static_cast<ostringstream*>(&(ostringstream() << i))->str()));
    }

    heap.print();

    return 0;
}

