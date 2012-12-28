/* 
 * File:   main.cpp
 * Author: Richard Fussenegger <rfussenegger.mmt-m2012@fh-salzburg.ac.at>
 * Author: Markus Deutschl <mdeutschl.mmt-m2012@fh-salzburg.ac.at>
 * Author: Elisabeth Lang <elang.mmt-m2012@fh-salzburg.ac.at>
 * Created on December 28, 2012, 9:24 PM
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include "CacheInspector.h"

using namespace std;

/**
 * Print a nice separator on the console.
 */
void printSeparator() {
    for (int i = 0; i < 80; i++) {
        cout << "-";
    }
    cout << endl;
}

/**
 * Main method including tests of our CircularBuffer.
 *
 * @return
 *   Always returns EXIT_SUCCESS.
 */
int main() {
    return EXIT_SUCCESS;
}
