/* 
 * File:   test.cpp
 * Author: Richard Fussenegger
 * Author: Markus Deutschl
 *
 * Created on November 19, 2012, 10:50 PM
 */

#include <iostream>
#include <list>
#include <vector>
#include "skiplist.h"

using namespace std;

int main() {
    /** Iterator and random key variable. */
    int i = 0, randKey;

    /** Our skiplist to test. */
    skiplist<int, int> skiplistObj(5);

    // Fill something into our skiplist.
    cout << endl << "Inserting keys and values into our skiplist:" << endl;
    for (; i < 10; ++i) {
        randKey = rand() % 100;
        skiplistObj.insert(randKey, i);
        cout << "Inserted key " << randKey << " with value " << i << "." << endl;
    }

    // Show me!
    cout << endl << "Using the print method of our skiplist:" << endl;
    skiplistObj.print();

    // Use the list.
    cout << endl << "Iterating over our key list:" << endl;
    list<int> skiplistKeyList = skiplistObj.getKeyList();
    list<int>::const_iterator listIterator;
    for (listIterator = skiplistKeyList.begin(); listIterator != skiplistKeyList.end(); ++listIterator) {
        cout << *listIterator << endl;
    }

    // Use the vector.
    cout << endl << "Iterating over our key vector:" << endl;
    vector<int> skiplistKeyVector = skiplistObj.getKeyVector();
    vector<int>::const_iterator vectorIterator;
    for (vectorIterator = skiplistKeyVector.begin(); vectorIterator != skiplistKeyVector.end(); ++vectorIterator) {
        cout << *vectorIterator << endl;
    }
    

    return 0;
}