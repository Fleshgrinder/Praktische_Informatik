/* 
 * File:   AvlTree.h
 * Author: Richard Fussenegger
 *
 * Created on October 30, 2012, 6:19 PM
 */

#include <stdio.h>

using namespace std;

class AvlTree {
public:

    AvlTree() : root(0) {
    }

    void insert(double d) {
        if (!this->root) this->root = new AvlNode(d);
        else this->insert(this->root, d);
    }

    unsigned height() {
        return this->height(this->root);
    }

    void print() const {
        print(this->root);
    }
private:

    struct AvlNode {

        AvlNode(double d) : data(d), left(0), right(0) {
        }
        double data;
        AvlNode *left, *right;
    };

    unsigned height(AvlNode *node) const {
        if (!node) return 0;
        return 1 + max(this->height(node->left), this->height(node->right));
    }

    void print(AvlNode *node) const {
        if (!node) return;
        print(node->left);
        printf("%.2f (%d)\n", node->data, this->height(node));
        print(node->right);
    }

    void rotateRight(AvlNode* &node) {
        AvlNode *tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;
        node = tmp;
    }

    void rotateRightLeft(AvlNode* &node) {
        this->rotateRight(node->right);
        this->rotateLeft(node);
    }

    void rotateLeft(AvlNode* &node) {
        AvlNode *tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;
        node = tmp;
    }

    void rotateLeftRight(AvlNode* &node) {
        this->rotateLeft(node->left);
        this->rotateRight(node);
    }

    void insert(AvlNode* &node, double d) {
        if (!node) node = new AvlNode(d);
        if (d < node->data) {
            this->insert(node->left, d);
            if (this->height(node->left) - this->height(node->right) == 2) {
                if (d < node->left->data) rotateRight(node);
                else rotateLeftRight(node);
            }
        } else if (d > node->data) {
            this->insert(node->right, d);
            if (this->height(node->right) - this->height(node->left) == 2) {
                if (d > node->right->data) rotateLeft(node);
                else rotateRightLeft(node);
            }
        }
    }
    AvlNode *root;
};