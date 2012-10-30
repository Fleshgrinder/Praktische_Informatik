Aufgabenstellung
================

Der AVL-Baum aus der Vorlesung hat ein Problem. Was ist die Komplexität? Wie beheben wir das Problem?

Lösung
======

Das Problem ist die `insert`-Methode, da hier die `height`-Methode für jeden Knoten der beiden Kindteilbäume rekursiv aufgerufen.
Was bedeutet, dass bei Aufruf der Wurzel z. B. alle Knoten durchgegangen werden.

```cpp
                                                                            //       #
void insert(AvlNode* &node, double d) {                                     // T0    1
    if (!node) node = new AvlNode(d);                                       // T1    1
    if (d < node->data) {                                                   // T2    1
        this->insert(node->left, d);                                        // T3    log(n)
        if (this->height(node->left) - this->height(node->right) == 2) {    // T4    ????????????????????????
            if (d < node->left->data) rotateRight(node);                    // T5    1
            else rotateLeftRight(node);                                     // T6    1
        }                                                                   //
    } else if (d > node->data) {                                            //
        this->insert(node->right, d);                                       //
        if (this->height(node->right) - this->height(node->left) == 2) {    //
            if (d > node->right->data) rotateLeft(node);                    //
            else rotateRightLeft(node);                                     //
        }                                                                   //
    }                                                                       //
}                                                                           //
```

