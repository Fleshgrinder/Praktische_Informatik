# Praktische Informatik
Zusammenfassung des theoretischen Stoffs in __Praktische Informatik__.

## Heap
Ein __Heap__ ist eine baumartige Datenstruktur. Es wird zwischen _Max-Heap_ und _Min-Heap_ unterschieden.

### Max-Heap
Beim __Max-Heap__ befindet sich der wertemäßig größte Knoten an der Wurzel. Daraus folgt, dass Knoten B ein Kind von Knoten A ist gdw. der Wert von A ≧ dem Wert von B ist.

![Max-Heap](https://i1.wp.com/a248.e.akamai.net/assets.github.com/images/gravatars/gravatar-org-420.png?ssl=1)

Knoten B ist Kind von Knoten A → `key(A) >= key(B)`

### Min-Heap
Beim __Min-Heap__ befindet sich der wertmäßig kleinste Knoten an der Wurzel. Daraus folgt, dass Knoten B ein Kind von Knosten A ist gdw. der Wert von A ≦ dem Wert von B ist.

![Min-Heap](https://i1.wp.com/a248.e.akamai.net/assets.github.com/images/gravatars/gravatar-org-420.png?ssl=1)

Knoten B ist Kind von Knoten A → `key(A) <= key(B)`

### Typische Heap Operationen
* `find_max()` / `top()` in _O(1)_
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

function left(i) {
  return data[2 * i + 1];
}

function right(i) {
  return data[2 * i + 2];
}

function parent(i) {
  return data[(i - 1) / 2];
}
```

#### Einfügen
+ Element an Array anfügen
+ Element mit Eleternelement vergleichen und Tauschen falls die Heap-Eigenschaft verletzt ist
+ Nach oben wandern und Schritt 2 wiederholen bis die Heap-Eigenschaft nicht mehr verletzt wird

```JavaScript
function swap(index1, index2) {
  var tmp = data[index1];
  data[index1] = data[index2];
  data[index2] = data[index1];
}

function push(value) {
  var current_index = data.length;
  var parent_index = null;

  // Append value to the array.
  data.push(value);

  while (current_index != 0) {
    parent_index = parent(current_index);

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
