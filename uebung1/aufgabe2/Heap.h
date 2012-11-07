#include <algorithm>
#include <assert.h>
#include <iostream>

using namespace std;

class Heap {
public:

    Heap(unsigned n) : elements(0), size(n), data(new double[n]) {}

    virtual ~Heap() {
        delete [] data;
    }

    bool empty() const {
        return elements;
    }

    double top() const {
        assert(elements > 0);
        return data[0];
    }

    void push(double d) {
        assert(elements < size);

        data[elements++] = d;
        unsigned idx = elements - 1;
        while (idx != 0) {
            unsigned pidx = parent_index(idx);
            if (data[pidx] < d)
                swap(data[idx], data[pidx]);
            else break;
            idx = pidx;
        }
    }

    double pop() {
        assert(elements > 0);

        // get highest value from root before it's gone.
        double value = data[0];

        data[0] = data[--elements];
        unsigned idx = 0;

        do {
            unsigned childs = children(idx);
            if (childs == 0) break;

            unsigned max_idx = left_index(idx);
            if (childs == 2) {
                if (data[max_idx] < data[max_idx + 1])
                    max_idx++;
            }

            if (data[idx] < data[max_idx]) {
                swap(data[idx], data[max_idx]);
                idx = max_idx;
            } else break;
        } while (true);

        return value;
    }

    void sortAsc() {
        int size = this->elements;
        double* sorted = new double[size];
        for (int i = size - 1; i >= 0; i--) {
            sorted[i] = this->pop();
        }
        this->print(sorted, size);
        delete [] sorted;
    }

    void sortDesc() {
        int size = this->elements;
        double* sorted = new double[size];
        for (int i = 0; i < size; i++) {
            sorted[i] = this->pop();
        }
        this->print(sorted, size);
        delete [] sorted;
    }

    void print() const {
        for (unsigned i = 0; i < elements; i++) {
            cout << data[i] << "-";
        }
        cout << endl;
    }

    void print(double* array, unsigned size) const {
        for (unsigned i = 0; i < size; i++) {
            cout << array[i] << "-";
        }
        cout << endl;
    }
private:
    unsigned elements;
    unsigned size;
    double *data;

    unsigned left_index(unsigned idx) const {
        return 2 * idx + 1;
    }

    unsigned right_index(unsigned idx) const {
        return 2 * idx + 2;
    }

    unsigned parent_index(unsigned idx) const {
        return (idx - 1) / 2;
    }

    unsigned children(unsigned idx) const {
        if (elements <= left_index(idx)) return 0;
        else if (elements > right_index(idx)) return 2;
        else return 1;
    }
};