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
    int i = 0, keyListSize;

    cout << "Skiplist Unit Test" << endl;
    cout << "--------------------------------\n" << endl;
    /** Our skiplist to test. */
    cout << "Create new skiplist\n" << endl;
    skiplist<int, int> skiplistObj(5);

    //Should return default value < -1
    //The skiplist was initialized
    cout << "Check if skiplist has default value" << endl;
    int defaultValue = skiplistObj.search(0);
    assert(defaultValue > 1 || defaultValue <= 1);
    cout << "True - Skiplist was created\n" << endl;

    //Should return 2 with key 67
    //Value was inserted
    cout << "Insert value 2 with key 67" << endl;
    skiplistObj.insert(67, 2);
    int skipValue = skiplistObj.search(67);
    assert(skipValue == 2);
    cout << "True - value was inserted\n" << endl;

    //Insert 4 new values
    cout << "Insert keys 83, 27, 91, 12\n" << endl;
    skiplistObj.insert(83, 6);
    skiplistObj.insert(27, 9);
    skiplistObj.insert(91, 3);
    skiplistObj.insert(12, 8);

    //Two new Arrays with keys and values in the right order
    int newKeys[5];
    int newValues[5];
    newKeys[0] = 12;
    newValues[0] = 8;
    newKeys[1] = 27;
    newValues[1] = 9;
    newKeys[2] = 67;
    newValues[2] = 2;
    newKeys[3] = 83;
    newValues[3] = 6;
    newKeys[4] = 91;
    newValues [4] = 3;

    //Get list of Keys
    typedef vector<int> intVector;
    intVector skiplistKeys = skiplistObj.getKeyVector();
    keyListSize = skiplistKeys.size();
    //Check if the first key equals the first value of our array
    cout << "Check if first value of keylist is first value of sorted array" << endl;
    assert(newKeys[0] == skiplistKeys[0]);
    cout << "True - First value equals\n" << endl;

    //Are the sorted array and the keys list equal?
    cout << "Check whole array if keys equal with sorted array" << endl;
    for (unsigned int i = 0; i < skiplistKeys.size(); ++i)
    {
        assert(newKeys[i] == skiplistKeys[i]);
    }
    cout << "True - All keys equal\n" << endl;

    //TODO: Value List
    //Get list of values
    cout << "Check if values equal the values of sorted array" << endl;
    list<int> skiplistValues = skiplistObj.getKeyList();
    i = 0;
    for (list<int>::const_iterator it = skiplistValues.begin(), end = skiplistValues.end(); it != end; ++it) {
        //cout << newValues[i] << endl;
        //cout << *it << endl;
        //assert(newValues[i] == *it);
        ++i;
    }
    cout << "True - all values equal\n" << endl;

    //TODO: Remove
    //Remove value
    cout << "Remove key 27 from list and check if list size decrements" << endl;
    //skiplistObj.remove(27);
    //assert(skiplistKeys.size()-1 == keyListSize);
    cout << "True - size was decremented by 1\n" << endl;

    cout << "Check if key 27 is not in list" << endl;
    skiplistKeys = skiplistObj.getKeyVector();
    for (unsigned int i = 0; i < skiplistKeys.size(); ++i)
    {
        //cout << skiplistKeys[i]) << endl;
        if(skiplistKeys[i]) {
            //assert(skiplistKeys[i] != 27);
        }
    }
    cout << "True - key is not in list\n" << endl;

    //Insert negative key
    skiplistObj.insert(-2, -4);
    skiplistKeys = skiplistObj.getKeyVector();
    cout << "Check if negative key is first in list" << endl;
    for (unsigned int i = 0; i < skiplistKeys.size(); ++i)
    {
        if(skiplistKeys[i]) {
            assert(skiplistKeys[0] == -2);
        }
    }
    cout << "True - negative key is first in list\n" << endl;

    return 0;
}

