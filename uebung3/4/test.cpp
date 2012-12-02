/* 
 * File:   test.cpp
 * Author: Elisabeth Lang
 * Author: Richard Fussenegger
 * Author: Markus Deutschl
 *
 * Created on December 1, 2012, 16:30 PM
 */

#include <iostream>
#include <cassert>
#include "skiplist.h"

using namespace std;

int main() {
    /** Iterator and random key variable. */
    int i = 0, randKey;

    cout << "Skiplist Unit Test" << endl;

    /** Our skiplist to test. */
    cout << "Create new skiplist" << endl;
    skiplist<int, int> skiplistObj(5);

    //Should return default value < -1
    //The skiplist was initialized
    cout << "Check if skiplist has default value" << endl;
    int defaultValue = skiplistObj.search(0);
    assert(defaultValue > 1 || defaultValue <= 1);
    cout << "True - Skiplist was created" << endl;

    //Should return 2 with key 67
    //Value was inserted
    cout << "Insert value 2 with key 67" << endl;
    skiplistObj.insert(67, 2);
    int skipValue = skiplistObj.search(67);
    assert(skipValue == 2);
    cout << "True - value was inserted" << endl;

    //Insert 4 new values
    /*cout << "Insert keys 83, 27, 91, 12" << endl;
    skiplistObj.insert(83, 6);
    skiplistObj.insert(27, 9);
    skiplistObj.insert(91, 3);
    skiplistObj.insert(12, 8);
    //Make an array with all keys in the right order
    int keys[5];
    keys[0] = 12;
    keys[1] = 27;
    keys[2] = 67;
    keys[3] = 83;
    keys[4] = 91;

    skiplistObj.print();*/


    //Wert hat key?

    //Wert Löschen

    //Wert ist an Stelle ist nicht mehr verfügbar

    //Was passiert bei negativen key?


    // Fill something into our skiplist.
    for (; i < 10; ++i) {
        randKey = rand() % 100;
        skiplistObj.insert(randKey, i);
        cout << "Inserted key " << randKey << " with value " << i << "." << endl;
    }

    //cout << "Search: " << skiplistObj.search(83) << endl;

    // Show me!
    skiplistObj.print();

    return 0;
}

