/* 
 * File:   Custom.h
 * Author: Richard Fussenegger
 *
 * Created on October 30, 2012, 2:35 PM
 */

#include <string>

using namespace std;

class Custom {
private:
    string value;
public:
    /*
     * Empty default constructor.
     */
    Custom() {}

    /*
     * Constructor
     */
    Custom(string s) : value(s){}

    virtual ~Custom(){}

    /*
     * Get value.
     */
    string getValue() {
        return value;
    }

    /*
     * Set value.
     */
    void setValue(string value) {
        this->value = value;
    }

    /*
     * Lesser then comparison.
     */
    friend bool operator< (Custom &obj1, Custom &obj2) {
        return obj1.getValue().compare(obj2.getValue()) < 0;
    }

    /*
     * Stream operator.
     */
    friend ostream& operator<< (ostream &stream, Custom &custom) {
        return stream << custom.getValue();
    }
};