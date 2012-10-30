/* 
 * File:   Btree.h
 * Author: Richard Fussenegger
 *
 * Created on October 30, 2012, 5:20 PM
 */

#include <stdio.h>

using namespace std;

class Btree {
public:
    Btree() : root(0) {}
    void insert(double d) {
        if (!this->root) this->root = new Node(d);
        else this->insert(this->root, d);
    }
    unsigned height() {
        return this->height(this->root);
    }
    void print() const {
        print(this->root);
    }
private:
    struct Node {
        Node(double d) : data(d), left(0), right(0) {}
        double data;
        Node *left, *right;
    };
    void print(Node *node) const {
        if (!node) return;
        print(node->left);
        printf("%.2f (%d)\n", node->data, this->height(node));
        print(node->right);
    }
    unsigned height(Node *node) const {
        if (!node) return 0;
        return 1 + max(this->height(node->left), this->height(node->right));
    }
    void insert(Node* &node, double d) {
        if (!node) node = new Node(d);
        if (d < node->data) this->insert(node->left, d);
        else if (d > node->data) this->insert(node->right, d);
    }
    Node *root;
};