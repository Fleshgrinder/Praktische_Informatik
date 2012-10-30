Aufgabenstellung
================

Der AVL-Baum aus der Vorlesung hat ein Problem. Was ist die Komplexität? Wie beheben wir das Problem?

Lösung
======

Das Problem ist die `insert`-Methode, da hier die `height`-Methode für jeden Knoten der beiden Kindteilbäume rekursiv aufgerufen wird.
Was bedeutet, dass bei Aufruf der Wurzel z. B. alle Knoten durchgegangen werden.

```cpp
                                                                            //       #
void insert(AvlNode* &node, double d) {                                     // T0    1
    if (!node) node = new AvlNode(d);                                       // T1    1
    if (d < node->data) {                                                   // T2    1
        this->insert(node->left, d);                                        // T3    log(n)
        if (this->height(node->left) - this->height(node->right) == 2) {    // T4    log(n)^2
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

![Formel](https://raw.github.com/Fleshgrinder/Praktische_Informatik/master/uebung1/aufgabe7/formel.png)

Nach herauskürzen aller Konstanten bleibt der Logarithmus von *n* zum Quadrat übrig.

Unser Lösungsvorschlag ist, die Höhe als weiteres Attribut zu `Node` hinzuzufügen.
Beim Einfügen und Rotieren können wir die Höhe dann aktualisieren.