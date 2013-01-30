# Praktische Informatik
Zusammenfassung des theoretischen Stoffs in __Praktische Informatik__.

## Heap
Ein __Heap__ ist eine baumartige Datenstruktur. Es wird zwischen _Max-Heap_ und _Min-Heap_ unterschieden. In der Praxis werden Heap-Datenstrukturen verwendet zum Sortieren ([Heapsort](https://de.wikipedia.org/wiki/Heapsort)) und zum wiederholten bestimmen des Minimums / Maximums von Elementen.

### Max-Heap
Beim __Max-Heap__ befindet sich der wertemäßig größte Knoten an der Wurzel. Daraus folgt, dass Knoten B ein Kind von Knoten A ist gdw. der Wert von A ≧ dem Wert von B ist.

![Max-Heap](https://raw.github.com/Fleshgrinder/Praktische_Informatik/master/summary/max-heap.png)

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

![Container Adaptor](https://raw.github.com/Fleshgrinder/Praktische_Informatik/master/summary/container-adaptor.png)

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

![Binärbaum 2](https://raw.github.com/Fleshgrinder/Praktische_Informatik/master/summary/binary-tree.png)

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

![Binärbaum Höhe](https://raw.github.com/Fleshgrinder/Praktische_Informatik/master/summary/binary-tree-height.png)

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

![Binärbaum-Gewichtung](https://raw.github.com/Fleshgrinder/Praktische_Informatik/master/summary/binary-tree-weight.png)

* −1 … linkslastig
* 0 … ausbalanciert
* 1 … rechtslastig

### Implementierung
```Cpp
/*
* File: Btree.h
* Author: Richard Fussenegger
*
* Created on October 30, 2012, 5:20 PM
*/

#include <stdio.h>

using namespace std;

class Btree {
public:

    Btree() : root(0) {}

    ~Btree() {
        delete this->root;
    }

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
        ~Node() {
            delete this->left;
            delete this->right;
        }
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
```
![github-icon](https://github.com/favicon.ico) [ Btree.h](https://github.com/Fleshgrinder/Praktische_Informatik/blob/master/uebung1/aufgabe3/Btree.h)

## AVL-Bäume
[__AVL-Bäume__](https://de.wikipedia.org/wiki/AVL-Baum) sind Binärbäume die sicherstellen, dass es zu keiner Degenerierung kommt. Es gibt verschiedene Varianten von AVL-Bäumen, z. B. [Red-Black Baum](https://de.wikipedia.org/wiki/Rot-Schwarz-Baum), [2-3-4-Baum](https://de.wikipedia.org/wiki/2-3-4-Baum), uvm.. Damit ein Binärbaum balanziert ist, darf sich die Höhe eines Knotens ausschließlich 0, 1, oder −1 betragen. Bei einem AVL-Baum bleibt das Suchen gleich wie beim Binärbaum. Einfüge- und Löschoperationen ändern sich jedoch, da sichergestellt werden muss, dass der Binärbaum zu jeder Zeit ausbalanciert ist.

### Einfügen
1. Neuer Knoten wird wie in einem normalen Binärbaum eingefügt.
2. Nun muss die Balance kontrolliert werden, es wird zwischen zwei Fällen unterschieden:
  1. Wenn das neue Blatt die Höhe des rechten Teilbaumes eines Knotens erhöht, der bereits rechtslasting war.
  2. Wenn das neue Blatt die Höhe des linken Teilbaumes eines Knotens erhöht, der bereits linkslastig war.

### Ausbalancieren
Ausbalancieren ist in konstanter Zeit möglich – also O(1) – und das Gewicht des Knotens wird auf 0 zurückgesetzt.

Eine Visualisierung des Ausbalancierens könnt ihr euch auf folgender Website ansehen (JavaScript wird benötigt): http://www.cs.usfca.edu/~galles/visualization/AVLtree.html

### Änderungen in der Implmentierung
Lediglich die `insert()`-Methode muss angepasst werden und Methoden für das Ausbalancieren müssen implementiert werden.

```Cpp
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
    delete [] node;
}
```
![github-icon](https://github.com/favicon.ico) [ Gesamter Code: AvlTree.h](https://github.com/Fleshgrinder/Praktische_Informatik/blob/master/uebung1/aufgabe3/AvlTree.h)

## Speicherhierarchie
* _Massenspeicher:_ langsam, billig, nicht flüchtig [TB]
* _Hauptspeicher:_ flüchtig [GB]
* _Cache:_ flüchtig [KB]
* _Register:_ schnell, teuer, flüchtig [B]

| Level         | Zugriffszeit      | Typische Größe | Technologie |
| ------------- | -----------------:| --------------:| ----------- |
| Register      | 1 Zyklus (1 ns)   | <1 KB          | CMOS        |
| L1 Cache      | ~5 Zyklen         | ~32 KB         | SRAM        |
| L2 Cache      | ~20 Zyklen        | ~256 KB        | SRAM        |
| L3 Cache      | ~50 Zyklen        | <3 MB          | SRAM        |
| Hauptspeicher | ~300 Zyklen       | GB             | DRAM        |
| Festplatte    | 10.000.000 Zyklen | TB             | Magnetisch  |

Caching ist ein Verfahren, das Daten zwischenspeichert um sie bei wiederholtem Zugriff schneller liefern zu können. Caching ist für den Benutzer transparent, allerdings beeinflusst die Datenorganisation die Ausführungsgeschwindigkeit erheblich.

### Wichtige Konzepte und Begriffe
#### Caching
* __Spatial Locality__: weitere Zugriffe in der Nähe wahrscheinlich
* __Temporal Locality__: weitere Zugriffe in naher Zukunft wahrscheinlich
* __Cache Hit / Miss__: benötigtes Datum kann im Cache gefunden werden / oder nicht
* __Latency__: Zeit um das Datum eines Blocks ( __cache line__ ) zu holen; __bandwidth__ bestimmt die Dauer des weiteren Ladevorgangs

##### Fragen zu Caches
* Wo wird ein Block im Cache gespeichert?
  * __direct mapped__, __fully associative__, __set associative__
* Wir wird ein Block im Cache gefunden?
  * __cache tag__
* Welcher Block wird bei einem __cache miss__ ersetzt?
  * __random__, __least-recently used__ (LRU), __first in / first out__ (FIFO)
* Was passiert bei einem Schreibzugriff?
  * __write back__, __write through__

#### Virtual Memory
* Adressraum wird in Blöcke gleicher Größe unterteilt: __pages__
* Zugriffe auf Blöcke, die nicht im physikalischen Speicher sind, erzeugen __page faults__, die vom Betriebssystem behandelt werden können
* Memory Management Unit (MMU)

![MMU](https://i1.wp.com/a248.e.akamai.net/assets.github.com/images/gravatars/gravatar-org-420.png?ssl=1)

##### Fragen zu Virtual Memory
* Wo kann eine __page__ in den Hauptspeicher geladen werden?
* Wie wird eine __page__ im Hauptspeicher gefunden?
  * __page table__
  * __Translation lookaside buffer__ (TLB): Cache zur Adressumwandlung
* Welcher Block soll ersetzt werden wenn der Hauptspeicher voll ist?
* Was passiert wenn ein Block beschrieben wird?

#### Virtuelle Adressen / Paging
Virtuelle Adressräume sind in Seiten (__pages__) eingeteilt und physikalischer Speicher in __page frames__. Typische Seitengröße ist 4 KB, typische Adressräume sind 4 GB (x86) bzw. 256 TB (x64).

![Virtuelle Adressen](https://i1.wp.com/a248.e.akamai.net/assets.github.com/images/gravatars/gravatar-org-420.png?ssl=1)

##### Fragen zu virutellen Adressen / Paging
* Was passiert bei Zugriff auf eine Seite, die nicht im Speicher ist?
* Was passiert bei Zugriff auf eine Seite ohne entsprechende Berechtigung (write, execute)?
* Wie kann das Betriebssystem mehr Speicher anbieten als physikalisch vorhanden ist?

![Paging](https://i1.wp.com/a248.e.akamai.net/assets.github.com/images/gravatars/gravatar-org-420.png?ssl=1)

##### Mehrstufige Seitentabellen
Jeder Prozess besitzt sein eigenes __page directory__. Das Betriebssystem kümmert sich bei Prozesswechsel, dass Register neu geladen werden.

##### Page Faults / Seitenfehler
Wenn beim Zugriff auf eine Seite ein Fehler auftritt kann das Betriebssystem eingreifen um den Zugriff abzulehnen oder Paging einzuleiten (die Seite einlagern). Dazu muss das Betriebssystem wenig benutzte physikalische Speicher-Frames suchen, den Inhalt gegebenenfalls sichern, die Seite in den Frame laden, Abbildungstabelle anpassen und den Befehl nochmals ausführen.

##### Demand Paging
Beim starten eines Prozesses ist unklar wieviel Seiten geladen werden sollen, um diesem Problem entgegen zu setzen, werden die Seiten reserviert sobald das Progamm diese anfordert (virtuell und physikalisch).

##### Working Set
Das _Working Set_ ist die Menge der Seiten, die ein Prozess zu einem bestimmten Zeitpunkt benötigt. Pass das Set in den Speicher ist alles ok. Sollte der verfügbare Speicher jedoch kleiner sein, führt dies zu sehr vielen __page faults__.

###### Thrashing
Das System ist nur noch am ein- und auslagern von Seiten.

#### Shared Pages
Prozesse können sich Seiten teilen (z. B. Programmcode) aber auch Daten sind möglich:
  1. Page auf read-only setzen
  2. Bei Schreibzugriff: page kopieren, jeder Prozess erhält eine eigene Kopie, auf read-write setzen; diese Strategie nennt sich copy-on-write (COW)
  3. Vorteil: pages die nie beschrieben werden, müssen nie kopiert werden

![Shared Pages](https://i1.wp.com/a248.e.akamai.net/assets.github.com/images/gravatars/gravatar-org-420.png?ssl=1)

### Fully associative cache
Cache ist in __cache lines__ organisiert, es werden immer ganze __cache lines__ transferiert. Ein 4 MB L2 Cache hat also Platz für 65.536 __cache lines__. Für jede __cache line__ gibt es einen __tag__ der bestimmt welches Datum in einer __cache line__ gespeicher ist.

```
32-bit address = 2^5 offset

|---------------------------|-----|
|            27bit          | 5bit|
|---------------------------|-----|
              tag            offset

4 MB / 64 B = 65536 cache lines

                                    64 Bytes Cache Lines
    0 |---------------------------|---------
      |             tag           |  line
      |---------------------------|---------
      |             tag           |  line
      |---------------------------|---------
      ⋮                           ⋮

      ⋮                           ⋮
      |---------------------------|---------
      |             tag           |  line
      |---------------------------|---------
      |             tag           |  line
65535 |---------------------------|---------
```

### Direct mapped cache
Große voll assoziative Caches sind nicht praktikabel, da alle __tags__ abgesucht werden müssen, das ist einfach zu langsam. __Direct mapped__ ist eine Caching-Variante die das Problem durch Unterteilung in Untergruppen (sogenannte __sets__) versucht zu lösen.

```
32-bit address = 2^5 offset

|-----------|----------------|-----|
|   11bit   |      16bit     | 5bit|
|-----------|----------------|-----|
     tag           index      offset


                                    64 Bytes Cache Lines
    0 |---------------------------|---------
      |             tag           |  line
      |---------------------------|---------
      |             tag           |  line
      |---------------------------|---------
      ⋮                           ⋮

      ⋮                           ⋮
      |---------------------------|---------
      |             tag           |  line
      |---------------------------|---------
      |             tag           |  line
65535 |---------------------------|---------
```

### Set associative cache
Eine praktikable Mischung beider Varianten ist ein __set associative__ Cache. In jedem __set__ gibt es eine vorbestimmt Anzahl an __tags__ die durchsucht werden müssen.

```
offset:       64bit = 2^6 = 6bit
cache lines:  256 KB / 64 B = 4096
index:        4096 / 8 = 512 = 2^9 = 9bit
tag:          64 - 6 - 9 = 49bit

|-------------------------------------------------|---------|------|
|                      49bit                      |   9bit  | 6bit |
|-------------------------------------------------|---------|------|
                        tag                          index   offset

Aussehen:
                           8-fach assoziativ -->
  0 |------|------|---     |------------|------------|---
    | set0 | set1 |        |    set0    |    set1    |   
    |------|------|---     |------------|------------|---
    | set0 | set1 |        |    set0    |    set1    |   
    |------|------|---     |------------|------------|---
    |      |      |        |            |            |   


    |      |      |        |            |            |   
    |------|------|---     |------------|------------|---
    | set0 | set1 |        |    set0    |    set1    |   
511 |------|------|---     |------------|------------|---
      18bit   18bit            64Bytes      64Bytes
```
![github-icon](https://github.com/favicon.ico) [ Übung 3 Aufgabe 6](https://github.com/Fleshgrinder/Praktische_Informatik/tree/master/uebung3/6)

### Rechenbeispiel
* 32-bit Adressraum
* 2-fach assoziativ
* 32 KB großer Cache
* 32 Byte Cache Lines
* Berechne:
  * tag bits
  * offset bits
  * cache indices
  * cache lines im cache
  * Wie sieht der Cache aus?

```
offset:       32-bit address = 2^5 = 5bit
cache lines:  32 KB / 32 B = 1024
index:        1024 / 2 = 512 = 2^9 = 9bit
tag:          32 - 5 - 9 = 18bit

|------------------|---------|-----|
| 18bit            | 9bit    | 5bit|
|------------------|---------|-----|
 tag                index     offset

Aussehen:
                           2-fach assoziativ
  0 |------|------|---     |------------|------------|
    | set0 | set1 |        |    set0    |    set1    |   
    |------|------|---     |------------|------------|
    | set0 | set1 |        |    set0    |    set1    |   
    |------|------|---     |------------|------------|
    |      |      |        |            |            |   


    |      |      |        |            |            |   
    |------|------|---     |------------|------------|
    | set0 | set1 |        |    set0    |    set1    |   
511 |------|------|---     |------------|------------|
     18bit  18bit             64Bytes      64Bytes
```

### Instruction Trace
_Brauchen wir das?_

## Interprozesskommunikation
Dient zum Austausch von Daten zwischen Prozessen. Normalerweise sind Prozesse durch die virtuellen Adressräume strikt getrennt.

Möglichkeiten zum Datenaustausch:
* via Dateisystem (langsam)
* Sockets
* Shared Memory
* Semaphoren
* Memory Mapped Files
* Unix Domain Sockets
* Pipes
* …

### Shared Memory
API um Speicherseiten zwischen Prozessen zu teilen: `shmget()`, `shmat()`, `shmdt()`, `CreateFileMapping()` (Windows), `MapViewOfFile()` (Windows)
Kommandozeilentools: `ipcs`, `ipcrm`

### Memory Mapped Files
Bindet Dateien in den Speicher ein: `mmap()`, `munmap()`, `CreateFileMapping()` (Windows)

## Refactoring
_Refactoring_ bedeutet die interne Struktur einer Software zu optimieren und zu verbessern ohne das externe Verhalten zu verändern. Refactoring wird dazu eingesetzt, um das Design einer Software zu optimieren und den stetigen Zerfall von Software entgegen zu wirken.

### Prinzipien
* Wenn eine Funktion einem Programm nicht hinzugefügt werden kann, weil das Design der Software dies nicht zulässt. Dann wird zuerst das Design geändert bis dies möglich ist und erst dann wird die Funktion hinzugefügt.
* Bevor mit Refactoring begonnen werden kann, sollte es eine solide Basis an Tests für die Software geben.
* Refactoring verändert das Programm in kleinen Schritten.
* Wenn Code stinkt muss Refactoring angewendet werden!

### Exkurs: Tests
* Tests sollen …
  * schnell ablaufen (wenige Sekunden)
  * ein eindeutiges Ergebnis liefern (Ja / Nein, Korrekt / Fehler)
  * einfach aufzurufen sein
  * automatisch ablaufen
  * Codeteile separat prüfen (Unit Tests)
  * bereits während der Entwicklung berücksichtigt werden
  * Randbedingungen mit erfassen, z. B.:
    * was passiert bei Eingabe einer leeren Zeichenkette?
    * was passiert wenn das erste / letzte Element gelöscht wird?
  * eine größtmögliche Überdeckung (test coverage) aufweisen; besser einige wenige (wichtige) Tests als viele Kleine
  * Unit Tests sind auch grundlage für Laufzeitoptimierung:
    * Optimierung ähnlich zu Refactoring; Ziel ist die Verbesserung der Performance
    * Optimierungen ändern die interne Struktur und die Ausführungszeit
* _Unit Tests:_ überprüfen einen kleinen Codeteil
* _Functional Tests:_ überprüfen ob das Programm im Gesamten das macht was es soll
* Es existieren Frameworks und Werkzeuge um Tests zu organisieren (z. B. JUnit für Java)
* _Black Box Tests:_
  * Testfälle basieren auf Spezifikation
  * Testfälle können ohne Entwickler erstellt werden
  * Interna unbekannt
* _White Box Tests:_
  * Testfälle basieren auf Struktur (des Codes)
  * Testfälle werden vom Entwickler erstellt
  * Testüberdeckung wird anhand des Codes ermittelt
  * Ziel ist alle Anweisungen, Bedingungen und Pfade mindestens einmal ausgeführt zu haben
  * Analyse des Kontrollflussgraphen zur Überprüfung
  * Verschiedene Anforderungen an Überdeckung:
    * C0 … Anweisungsüberdeckung / Statement Coverage
      * Testfälle werden so gewählt, dass alle Anweisungen (Statements) zumindest einmal ausgeführt werden
    * C1 … Zweigüberdeckung / Branch Coverage
      * Testfälle werden so gewählt, dass alle Kanten des Kontrollflussgraphen einmal ausgeführt werden
    * …

![Kontrollflussgraph](https://raw.github.com/Fleshgrinder/Praktische_Informatik/master/summary/kontrollflussgraph.png)

### Fortsetzung: Refactoring
Vorgehen:
1. Testfälle vorhanden? Falls nicht, erstellen!
2. Kleine Änderungen vornehmen – Refactoringkatalog beachten
3. Testen
4. Ziel erreicht oder ab Schritt 2 Prozedere wiederholen

### Refactoringkatalog (Auswahl)
#### Methode extrahieren / Extract Method [ref](http://www.refactoring.com/catalog/extractMethod.html)
__Ein Codefragment kann zusammengefasst werden.__

_Setze die Fragmente in eine Methode, deren Namen den Zweck kennzeichnet._

```Java
void printOwing() {
  printBanner();
 
	//print details
	System.out.println ("name:	" + _name);
	System.out.println ("amount	" + getOutstanding());
}
```

_↓_

```Java
void printOwing() {
  printBanner();
	printDetails(getOutstanding());
}
 
void printDetails (double outstanding) {
	System.out.println ("name:	" + _name);
	System.out.println ("amount	" + outstanding);
}
```

#### Verschiebe Methode / Move Method [ref](https://forum.itm09.at/wiki/Software_Design/Refactoring_Katalog#cite_note-9)
__Eine Methode wird von einer anderen Klasse mehr verwendet als von der definierenden Klasse.__

_Erzeuge eine Methode mit ähnlichem Rumpf in der Klasse, die die Eigenschaft am meisten nutzt. Delegiere in der alten Methode an die neue Implementierung, oder lösche sie._

![Move Method](https://raw.github.com/Fleshgrinder/Praktische_Informatik/master/summary/move-method.gif)

```Java
class Project {
  Person[] participants;
}
 
class Person {
	int id;
	boolean participate(Project p) {
		for(int i=0; i<p.participants.length; i++) {
			if (p.participants[i].id == id) return(true);
		}
		return(false);
	}   
}
 
... if (x.participate(p)) ...
 
 
Nach der Verschiebung folgt:
	class Project {
	Person[] participants;
	boolean participate(Person x) {
		for(int i=0; i<participants.length; i++) {
			if (participants[i].id == x.id) return(true);
		}
		return(false);
	}   
}
 
class Person {
	int id;
}
 
... if (p.participate(x)) ...
```
