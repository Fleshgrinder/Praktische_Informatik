# Praktische Informatik
Zusammenfassung des theoretischen Stoffs in __Praktische Informatik__.

## Heap
Ein __Heap__ ist eine baumartige Datenstruktur. Es wird zwischen _Max-Heap_ und _Min-Heap_ unterschieden. In der Praxis werden Heap-Datenstrukturen verwendet zum Sortieren ([Heapsort](https://de.wikipedia.org/wiki/Heapsort)) und zum wiederholten bestimmen des Minimums / Maximums von Elementen.

### Max-Heap
Beim __Max-Heap__ befindet sich der wertemäßig größte Knoten an der Wurzel. Daraus folgt, dass Knoten B ein Kind von Knoten A ist gdw. der Wert von A ≧ dem Wert von B ist.

![Max-Heap](https://i1.wp.com/a248.e.akamai.net/assets.github.com/images/gravatars/gravatar-org-420.png?ssl=1)

Knoten B ist Kind von Knoten A → `key(A) >= key(B)`

### Min-Heap
Beim __Min-Heap__ befindet sich der wertmäßig kleinste Knoten an der Wurzel. Daraus folgt, dass Knoten B ein Kind von Knosten A ist gdw. der Wert von A ≦ dem Wert von B ist.

![Min-Heap](https://i1.wp.com/a248.e.akamai.net/assets.github.com/images/gravatars/gravatar-org-420.png?ssl=1)

Knoten B ist Kind von Knoten A → `key(A) <= key(B)`

### Typische Heap Operationen und Komplexität
* `find_max()` / `top()` in _O(1)_ (konstante Komplexität)
* `delete_max()` / `pop()` in _O(log n)_
* `insert()` / `push()` in _O(log n)_
* `merge()` in _O(n)_

### Implementierung via Array
* Erstes (größtes / kleinstes) Element ist die Wurzel
* Nächsten zwei Elemente sind die Kinder der Wurzel
* Nächsten vier Elemente sind die Kinder auf der nächsten Ebene
* usw.

#### Links / Rechts / Elternknoten
Bewegungen im Baum können leicht in Array-Indizes umgerechnet werden:

```JavaScript
var data = [];

function left_index(index) {
  return 2 * index + 1;
}

function right_index(index) {
  return 2 * index + 2;
}

function parent_index(index) {
  return (index - 1) / 2;
}
```

#### Einfügen
1. Element an Array anfügen
2. Element mit Eleternelement vergleichen und Tauschen falls die Heap-Eigenschaft verletzt ist
3. Nach oben wandern und Schritt 2 wiederholen bis die Heap-Eigenschaft nicht mehr verletzt wird

```JavaScript
function swap(index1, index2) {
  var tmp = data[index1];
  data[index1] = data[index2];
  data[index2] = data[index1];
}

function push(value) {
  var current_index = data.length;

  // Append value to the array.
  data.push(value);

  while (current_index != 0) {
    var parent_index = parent_index(current_index);

    // Max-Heap
    if (data[parent_index] < value) {
      swap(current_index, parent_index);
    }

    // Min-Heap
    if (data[parent_index] > value) {
      swap(current_index, parent_index);
    }

    current_index = parent_index;
  }
}
```

#### Löschen
1. Letztes Element an die Wurzel setzen und vom Ende entfernen
2. Element mit größtem oder kleinstem Kind vergleichen und Tauschen fall die Heap-Eigenschaft verletzt ist
3. Nach unten wandern und Schritt 2 wiederholen bis die Heap-Eigenschaft nicht mehr verletzt wird

```JavaScript
function children(index) {
  if (data.length <= left_index(index)) return 0;
  if (data.length > right_index(index)) return 2;
  return 1;
}

function pop() {
  var current_index = 0;

  data[current_index] = data[data.length - 1];

  do {
    var childs = children(current_index);
    if (childs == 0) break;

    var max_index = left_index(index);
    if (childs == 2 && data[max_index] < data[max_index + 1]) max_index++;

    // Max-Heap
    if (data[index] < data[max_index]) {
      swap(index, max_index);
      index = max_index;
    } else break;

    // Min-Heap
    if (data[index] > data[max_index]) {
      swap(index, max_index);
      index = max_index;
    } else break;
  } while (true);
}
```

### Heap in der C++ STL
Die [C++ Standard Template Library (STL)](https://de.wikipedia.org/wiki/Standard_Template_Library) enthält den Header [Algorithm](http://www.cplusplus.com/reference/algorithm/) der auch eine Heap-Implementierung besitzt. Folgende Funktionen stehen zur Verfügung:
* [`make_heap()`](http://www.cplusplus.com/reference/algorithm/make_heap/) … Heap in-place erstellen
* [`push_heap()`](http://www.cplusplus.com/reference/algorithm/push_heap/) … Element hinzufügen
* [`pop_heap()`](http://www.cplusplus.com/reference/algorithm/pop_heap/) … Element entfernen

### Priority Queue
_Priority Queues_ sind in C++ sogenannte [__Container Adaptor__](http://www.cplusplus.com/reference/stl/). In der C++-Implementierung ist das erste Element im Container immer das größte Element und wird mit einem Heap implementiert. Container Adaptors sind Klassen die einen Container beinhalten und spezielle Zugriffsmethoden bereitstellen (in anderen Programmiersprachen (z. B. Java) würde dies als Interface implementiert werden).

![Container Adaptor](https://i1.wp.com/a248.e.akamai.net/assets.github.com/images/gravatars/gravatar-org-420.png?ssl=1)

```Cpp
template<
  class T
  class Container = vector<T>,
  class Compare = less<typename Container::value_type>
>
class priority_queue;
```

Die Klasse [`priority_queue`](http://www.cplusplus.com/reference/queue/priority_queue/) hat somit drei Template-Parameter:
* `T` … Elementdatentyp
* `Container` … Containerklasse zum Speichern der Elemente. Die Klasse muss `front()`, `push_back()` und `pop_back()` implementieren
* `Compare` … Vergleichsklasse die den Operator `(a, b)` implementiert der `true` oder `false` zurückgibt

## Binärbaum
In einem _Binärbaum_ besitzt jeder Knoten maximal zwei Kindknoten. Kinder des linken Teilbaumes besitzen kleinere (oder gleiche) Schlüssel und Kinder des rechten Teilbaumes haben größere Schlüssel als der Knoten selbst.

![Binärbaum](https://upload.wikimedia.org/wikipedia/commons/thumb/a/ae/Binary-tree.svg/500px-Binary-tree.svg.png)

### Höhe
* 0 … ohne Elemente
* 1 … mit einem Element
* 1 + die Höhe des höchstens Unterbaumes bei mehr als einem Element

```JavaScript
function height(node) {
  if (node == null) return 0;
  return 1 + Math.max(height(node.left), height(node.right));
}
```

### Komplexität
* O(Höhe) … Suchen, Einfügen, Löschen
* O(log n) … bei einem vollständigen Binärbaum
* O(log n) … bei einem durchschnittlichen Binärbaum
* O(n) … bei einem degenerierten Binärbaum

Binärbäume degenerieren aufgrund der Reihenfolge in der Elemente hinzugefügt werden. Ein Binärbaum wird als degeneriert bezeichnet wenn es sich optisch um keinen Baum sondern vielmehr um eine Liste handelt.

```
C
 \
  D
   \
    F
     \
      G
       \
        J
         \
          ⋮
```

### Gewichtung
Jeder Knoten in einem Binärbaum besitzt ein Gewicht. Dieses errechnet sich aus der Höhe des rechten Teilbaumes minus der Höhe des linken Teilbaumes.

```JavaScript
function node_weight(node) {
  if (!node == null) return false;
  return height(node.right) - height(node.left);
}
```

![Binärbaum-Gewichtung](https://i1.wp.com/a248.e.akamai.net/assets.github.com/images/gravatars/gravatar-org-420.png?ssl=1)

### Funktionen
```Cpp
class BinaryTree {
public:
  /**
   * Constructor
   */
  BinaryTree() : root(0) { /* Do nothing */ }

  /**
   * Public insert method
   */
  void insert(double data) {
    if (!root) {
      root = new Node(data);
    }
    else {
      this.insert(root, data);
    }
  }

  /**
   * Public print method
   */
  void print() const {
    this.print(root);
  }
private:
  /**
   * Inline class node structure
   */
  struct Node {
    // Constructor
    Node(double data) : data(data), left(0), right(0) { /* Do nothing */ }
    double data;
    // Pointer to the left and right child nodes
    Node *left, *right;
  }

  /**
   * The root node of this binary tree instance
   */
  Node *root;

  /**
   * Print each node to the console
   */
  void print(Node *node) const {
    if (!node) return;
    this.print(node->left);
    printf("%.2f (%d)\n", node->data, height(node));
    this.print(node->right);
  }

  /**
   * Get the height of this node
   */
  unsigned height(Node *node) const {
    if (!node) return 0;
    return 1 + max(height(node->left), height(node->right));
  }

  /**
   * Insert new element
   */
  void insert(Node* &node, double data) {
    if (!node) node = new Node(data);
    if (data < node->data) {
      this.insert(node->left, data);
    }
    else if (data > node->data) {
      this.insert(node->right, data);
    }
  }
};
```
