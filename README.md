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
  data[index2] = tmp;
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
    } else break;

    // Min-Heap
    if (data[parent_index] > value) {
      swap(current_index, parent_index);
    } else break;

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

    var max_index = left_index(current_index);
    if (childs == 2 && data[max_index] < data[max_index + 1]) max_index++;

    // Max-Heap
    if (data[current_index] < data[max_index]) {
      swap(current_index, max_index);
      current_index = max_index;
    } else break;

    // Min-Heap
    if (data[current_index] > data[max_index]) {
      swap(current_index, max_index);
      current_index = max_index;
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

### Formelsammlung
| Deutsch          | Englisch             | Formel
| ---------------- | -------------------- | ----
| Cachegröße       | Cache size           | geg.
| Cachezeilengröße | Cache line size      | geg.
| Adresstyp        | Address type         | geg.
| Assoziativität   | Associativity(level) | geg.
| Cachezeilen      | Cache lines          | Cachegröße ÷ Cachezeilengröße
| Offset           | Offset               | log₂(Cachezeilengröße)
| Index            | Index                | log₂(Cachezeilen ÷ Assoziativität)
| Tag              | Tag                  | Adresstyp − Index − Offset

### Fully associative cache
Cache ist in __cache lines__ organisiert, es werden immer ganze __cache lines__ transferiert. Ein 4 MB L2 Cache hat also Platz für 65.536 __cache lines__. Für jede __cache line__ gibt es einen __tag__ der bestimmt welches Datum in einer __cache line__ gespeicher ist.

```
given:
	size = 256 B
	cache line size = 64 B
	address type = 16 bit

calculate:
	cache lines = 256 B / 64 B = 4 count
	offset = log2(4) = 2^2 = 2 bit
	tag = 16 bit - 2 bit = 14 bit

15                0
|---------------|--|
|               |  |
|---------------|--|
       tag       offset

|--------------------------------|--------------------------------|--------------------------------|--------------------------------|
| cache line (64 B)              | cache line (64 B)              | cache line (64 B)              | cache line (64 B)              |
|--------------------------------|--------------------------------|--------------------------------|--------------------------------|
```

### Direct mapped cache
Große voll assoziative Caches sind nicht praktikabel, da alle __tags__ abgesucht werden müssen, das ist einfach zu langsam. __Direct mapped__ ist eine Caching-Variante die das Problem durch Unterteilung in Untergruppen (sogenannte __sets__) versucht zu lösen.

```
given:
	size = 256 B
	cache line size = 64 B
	address type = 16 bit

calculate:
	cache lines = 256 B / 64 B = 4 count
	offset = log2(4) = 2^2 = 2 bit
	index = log2(4 / 1) = 2^2 = 2 bit
	tag = 16 - 2 - 2 = 12 bit

   15                      4 3  2 1  0
   |------------------------|----|----|
   |                        |    |    |
   |------------------------|----|----|
    tag                     index offset

index
      |--------------------------------|
  00  | cache line (64 B)              |
      |--------------------------------|
  01  | cache line (64 B)              |
	    |--------------------------------|
  10  | cache line (64 B)              |
      |--------------------------------|
  11  | cache line (64 B)              |
      |--------------------------------|
```

### Set associative cache
Eine praktikable Mischung beider Varianten ist ein __set associative__ Cache. In jedem __set__ gibt es eine vorbestimmt Anzahl an __tags__ die durchsucht werden müssen.

```
given:
	size = 256 B
	cache line size = 32 B
	address type = 16 bit
	associativity level = 2

calculate:
	cache lines = 256 B / 32 B = 8 count
	offset = log2(8) = 2^3 = 3 bit
	index = log2(8 / 2) = 2^2 = 2 bit
	tag = 16 - 2 - 3 = 11 bit

   15                    5 4  3 2    0
   |----------------------|----|------|
   |                      |    |      |
   |----------------------|----|------|
    tag                   index offset

index
      |--------------------------------|--------------------------------|
  00  | cache line (64 B)              | cache line (64 B)              |
      |--------------------------------|--------------------------------|
  01  | cache line (64 B)              | cache line (64 B)              |
      |--------------------------------|--------------------------------|
  10  | cache line (64 B)              | cache line (64 B)              |
      |--------------------------------|--------------------------------|
  11  | cache line (64 B)              | cache line (64 B)              |
      |--------------------------------|--------------------------------|
```
![github-icon](https://github.com/favicon.ico) [ Übung 3 Aufgabe 6](https://github.com/Fleshgrinder/Praktische_Informatik/tree/master/uebung3/6)

### Instruction Trace
Der _Instruction Trace_ gibt an was im Cache passiert. Wir zählen ausschließlich Hits und Misses und die Daten selbst sind uns egal.

_Beispiel Trace:_
```
L 0000000000000100,16
L 0000000000001001,8
```

* _L_ … Load-Anweisung, was für Anweisungen wir erhalten spielt keine Rolle für die Hits und Misses
* _0000000000000100_ … Adresse die geladen werden soll, muss in Tag[, Index], Offset unterteilt werden
* _16_ … gibt an wieviel Bytes aus dem Cache gelesen werden sollen

### Hit/Miss-Rate berechnen
> TODO

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

### Warum Refactoring?
* Verbessert das Design der Software
* Code wird leichter verständlich
* Hilft Bugs zu entdecken
* Kann das Programm schneller machen

### Wann Refactoring?
* Rule of Three:
	1. Code wird erstellt
	2. Code wird dupliziert (Autsch!)
	3. Refactoring!
* Wenn eine neue Funktion dazukommt
* Wenn ein Fehler behoben wird
* Während Code Reviews

### Wann kein Refactoring?
* Wenn Klassen Datenbankdesign wiederspiegeln und die Daten in der Datenbank nur schwer migriert werden können
* Wenn sich dadurch die Schnittstellen (Interfaces) des Programms ändern würden
* Wenn das Programm so schlecht ist, dass ein Neuanfang sich rentiert

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
#### Methode extrahieren / Extract Method [[ref](http://www.refactoring.com/catalog/extractMethod.html)]
_Ein Codefragment kann zusammengefasst werden._

__Setze die Fragmente in eine Methode, deren Namen den Zweck kennzeichnet.__

```Java
void printOwing() {
	printBanner();
 
	//print details
	System.out.println ("name:	" + _name);
	System.out.println ("amount	" + getOutstanding());
}
```

__↓__

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

#### Verschiebe Methode / Move Method [[ref](http://www.refactoring.com/catalog/moveMethod.html)]
_Eine Methode wird von einer anderen Klasse mehr verwendet als von der definierenden Klasse._

__Erzeuge eine Methode mit ähnlichem Rumpf in der Klasse, die die Eigenschaft am meisten nutzt. Delegiere in der alten Methode an die neue Implementierung, oder lösche sie.__

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

#### Ersetze temporäre Variable durch Abfrage / Replace Temp with Query [[ref](http://www.refactoring.com/catalog/replaceTempWithQuery.html)]
_Stelle den Ausdruck in eine Abfrage-Methode. Ersetze die temporäre Variable durch Aufrufe der Methode._

__Eine temporäre Variable speichert das Ergebnis eines Ausdrucks.__

Warum?
* Die Berechnung kommt u. U. in mehreren Methoden vor → Code-Duplikation
* Einführung einer Abfrage-Methode beseitigt Duplikation
* Lokale Variablen provozieren lange Methoden → Variable nur innerhalb der Methode zugreifbar

```Java
double basePrice = _quantity * _itemPrice;
if (basePrice > 1000)
	return basePrice * 0.95;
else
	return basePrice * 0.98;
```

__↓__

```Java
	if (basePrice() > 1000)
		return basePrice() * 0.95;
	else
		return basePrice() * 0.98;
 
// ....
 
double basePrice() {
	return _quantity * _itemPrice;
}
```

#### Ersetzte Typ-spezifischen Code durch Unterklassen / Replace Type Code with Subclasses [[ref](http://www.refactoring.com/catalog/replaceTypeCodeWithSubclasses.html)]
_Ein unveränderlicher Programmcode bestimmt das Verhalten einer Klasse._

__Ersetze den Typ-spezifischen Code durch eine Unterklasse.__

![Replace Type Code with Subclasses](https://raw.github.com/Fleshgrinder/Praktische_Informatik/master/summary/replace-type-code-with-subclasses.gif)

#### Ersetze Fallunterscheidungen durch Polymorphie / Replace Conditional with Polymorphism [[ref](http://www.refactoring.com/catalog/replaceConditionalWithPolymorphism.html)]
_Eine Fallunterscheidung führt abhängig vom Typ eines Objektes unterschiedliches Verhalten aus._

__Lege jeden Zweig der Fallunterscheidung in eine Methode einer Unterklasse. Die Methode der Oberklasse wird abstrakt und die neuen Methoden überschreiben die abstrakte Methode.__

```Java
double getSpeed() {
	switch (_type) {
	case EUROPEAN:
		return getBaseSpeed();
	case AFRICAN:
		return getBaseSpeed() - getLoadFactor() * _numberOfCoconuts;
	case NORWEIGIAN_BLUE:
		return (_isNailed) ? 0 : getBaseSpeed(_voltage);
	}
	throw new RuntimeException ("Should be unreachable");
}
```

__↓__

![Replace Conditional with Polymorphism](https://raw.github.com/Fleshgrinder/Praktische_Informatik/master/summary/replace-conditional-with-polymorphism.gif)

### Anzeichen für schlechten Code / Code Smells
_Das ist nur ein Auszug der Code Smells, es gibt noch weitere:_

* Code-Duplizierung (duplicated code)
	* Code-Duplizierung ist der am weitesten verbreitete smell:
		* Explizit → identischer Code
		* Subtil → Strukturen oder Prozessschritte die nach außen hin anders, grundsätzlich jedoch gleich sind 
* Lange Methode (long method)
	* Je länger eine Methode ist, desto unverständlicher ist sie. Besser ist es mehrere kurze Methoden mit sprechenden Namen zu erstellen, sprechende Methodennamen erübrigen oft das lesen vom Methodenkörper.
* Große Klasse (large class)
	* Wenn eine Klasse zu viel erledigen will hat sie meist zu viele Instanzvariablen. Hat eine Klasse zu viele Instanzvariablen ist duplizierter Code nicht weit entfernt. Eine Klasse mit zu viel Code ist ein Nährboden für duplizierten Code und Chaos.
* Schrotkugeln herausoperieren (shotgun surgery)
	* Sehr viele Änderungen an Klassen ziehen viele kleine Änderungen in anderen Klassen nach sich. Erstrecken sich diese Änderungen über sehr viele Klassen, können wichtige Änderungen leicht übersehen werden.
* Neid (feature envy)
	* Wenn eine Methode zur Ausführung etliche Methoden einer anderen Klasse benötigt. Es gibt Heuristiken zur Auswertung dieses smells. Anders ausgedrückt: Eine Methode interessiert sich mehr für die Eigenschaften – insbesondere die Daten – einer anderen Klasse als für jene ihrer eigenen Klasse.
* Case-Anweisungen (switch statements)
	* Polymorphismus macht Switch-Case-Anweisungen weitgehend überflüssig und erledigt das damit zusammenhängende Problem des duplizierten Codes.
* Parallele Vererbungshierarchien (parallel inheritance hierarchies)
	* Zu jeder Unterklasse in der einen Hierarchie gibt es immer auch eine Unterklasse in einer anderen Hierarchie.
* Faule Klasse (lazy class)
	* Eine Klasse leistet zu wenig, um ihre Existenz zu rechtfertigen.

## Design Patterns
_Auch hier haben wir nur einen Bruchteil durchgenommen von denen die es gibt._

### Creational Pattern: Factory
Es wird ein Interface für die Erstellung von Objekten definiert, die Entscheidung darüber, welche Klasse instanziiert wird, wird aber der Subklasse überlassen. 

#### Anwendbarkeit
* Eine Klasse kann nicht vorhersehen, welche Art von Objekten erstellt werden müssen.
* Eine Klasse möchte, dass Subklassen die zu erstellenden Objekte spezifizieren.
* Klassen delegieren Verantwortung an eine von mehreren Helfer-Subklassen, und man möchte das Wissen darüber, welche Helfer-Subklasse delegiert wird, lokalisieren.

#### Auswirkungen
* Ein möglicher Nachteil von factory methods ist, dass Anwender die creator-Klasse erweitern (subclassen) müssen, um ein konkretes Produktobjekt zu erzeugen.
* Factory methods geben einer Subklasse Einhängepunkte (hooks) um eine erweiterte Version eines Objektes zu liefern.

#### UML Diagramm

![Factory Pattern](https://raw.github.com/Fleshgrinder/Praktische_Informatik/master/summary/factory-pattern.jpg)

#### Implementierung (Theorie)
* __Product__ – Definiert ein Interface für Objekte
* __ConcreteProduct__ – Implementiert das Product-Interface
* __Creator__
	* Deklariert die Factory-Methode, welche ein Objekt des Typs Product zurück gibt. 
	* Kann eine Standardimplementierung der Factory-Methode definieren, welche ein Standard-ConreteProduct zurück liefert. 

#### Implementierung (Praxis)
```Java
package factory;
 
public interface Product {
	// add useful methods
}
```

```Java
package factory;
 
// Visibility set to PACKAGE SCOPED --> client has to use the interface
class ConcreteProduct implements Product {
	// implement useful methods
}
```

```Java
package factory;
 
public interface Creator {
	public Product create();
}
```

```Java
package factory;
 
public class ConcreteCreator implements Creator {
	public Product create() {
		return new ConcreteProduct();
	}
}
```

```Java
package demo;
 
import factory.*;
 
public class HowToUseFactory {
	public static void main(String[] args) {
		// Create a new factory that can create products.
		Creator factory = new ConcreteCreator();
 
		// Let the factory create a product
		Product awesome = factory.create();	
	}
}
```

#### C++-Beispiel aus dem Unterricht
##### Das Problem
Die `DocumentManager`-Klasse führt eine Liste aller offener Dokumente, das Erzeugen eines Dokuments foll auch in der Verantwortung des Managers liegen.

```Cpp
class DocumentManager {
public:
	Document *newDocument();
	virtual Document* CreateDocument() = 0; // Factory method, type unknown!
private:
	std::list<Document *> listOfDocuments;
};
```

Verwendung:
```Cpp
Document* DocumentManager::newDocument() {
	Document *p = CreateDocument();
	listOfDocuments.push_back(p);
	return p;
}
```

Verwendung mit konkretem Typ:
```Cpp
Document *GraphicDocumentManager::CreateDocument() {
	return new GraphicDocument;
}
```

_Neues Problem:_ wir wollen ein Dokument aus einer Datei erzeugen, der folgende Code ist jedoch kein valider C++-Code.
```Cpp
Class Read(const char *filename);

Document *DocumentManager::OpenDocument(const char *filename) {
	Class theClass = Read(filename);
	Document *p = new theClass;
	p->read(filename);
	return p;
}
```
Beim Instanzieren von Objekten (`new`) muss in C++ _immer_ der konkrete Typ einer Klasse angegeben werden. C++ besitzt keinen Typ `Class` (oder `Object`) von dem alle ableiten.

##### Die Lösung
Wir erstellen eine abstrakte Klasse `Shape` von der konkrete Implementierungen (z. B. `Circle` oder `Rectangle`) ableiten:
```Cpp
class Shape {
public:
	virtual void draw() const = 0;
	virtual void rotate(double angle) = 0;
	virtual void zoom(double zoomFactor) = 0;
};
```

Die Klasse `Drawing` verwaltet eine Sammlung von `Shape`-Objekten:
```Cpp
class Drawing {
public:
	void save(std::ofstream &output);
	void load(std::ifstream &input);
private:
	// Some container of shapes
};
```

Das Speichern einer Zeichnung ist einfach:
```Cpp
void Drawing::Save(std::ofstream &output) {
	for (each element in drawing) {
		(current element)->save(output);
	}
}
```

Das Laden stellt die größere Herausforderung dar, da nicht bekannt ist um was für einen Typ es sich handelt:
```Cpp
const int LINE = 1, CIRCLE = 2, ...

void Drawing::Load(std::ifstream &input) {
	while (input) {
		int shapeType;
		input >> shapeType; // Read object (shape) type.
		Shape *currentObject;
		switch (shapeType) {
			case LINE:
				currentObject = new Line;
				break;
			case CIRCLE:
				currentObject = new Circle;
				break;
			...
		}
		currentObject->read(input);
		// Add object (shape) to container.
	}
}
```

Diese Implementierung ist jedoch schlecht und stinkt! Wir haben ein `switch` über verschiedene Typen, alls `Shape`-Unterklassen müssen in `Drawing` bekannt sein und das Ganze ist nur schwer erweiterbar (eindeutiger, neuer Typ wird benötigt und die `Load`-Methode muss erweitert werden). Das `switch` soll verschwinden und dafür erstellen wir eine Factory-Klasse die zu einer ID einen Pointer auf eine Funktion speichert, die das gewünschte Objekt zurückliefert.
```Cpp
|----------|----------|
| LINE     |          |  ---------->  Shape *CreateLine() { return new Line; }
|----------|----------|
| CIRCLE   |          |  ---------->  Shape *CreateCircle() { return new Circle; }
|----------|----------|
|          |          |
```

Die Implementierung könnte aussehen wie folgt:
```Cpp
class ShapeFactory {
public:
	typedef Shape* (*CreateShapeCallback) ();
	/**
	 * @return true if the registration was successful
	 */
	bool registerShape(int shapeId, CreateShapeCallback createFn);
	/**
	 * @return true if shapeId was registered before
	 */
	bool unregisterShape(int shapeId);
	Shape *createShape(int shapeId);
private:
	typedef std::map<int, CreateShapeCallback> CallbackMap;
	CallbackMap callbacks;
};
```

Um nun eine konkrete `Shape`-Implementierung unserer `ShapeFactory` hinzuzufügen könnten wir etwas wie das folgende machen:
```Cpp
namespace {
	Shape *CreateLine() {
		return new Line;
	}
	const int LINE = 1;
	const bool registered = ShapeFactory.registerShape(LINE, CreateLine);
}
```

Die Implementierung der `ShapeFactory`-Methoden könnte wie folgt aussehen:
```Cpp
bool ShapeFactory::registerShape(int shapeId, CreateShapeCallback createFn) {
	return callbacks.insert(CallbackMap::value_type(shapeId, createFn)).second;
}

bool ShapeFactory::unregisterShape(int shapeId) {
	return callbacks.erase(shapeId) == 1;
}

Shape *ShapeFactory::createShape(int shapeId) {
	CallbackMap::const_iterator it = callbacks.find(shapeId);
	// Do we know the shape with this ID?
	if (it == callbacks.end()) {
		throw std::runtime_error(Unknown Shape ID);
	}
	// Invoke the creation function.
	return (it->second)();
}
```

Nun schauen wir uns nochmals das Laden einer Zeichnung an.
```Cpp
void Drawing::Load(std::ifstream &input) {
	while (!input.eof()) {
		int shapeId;
		input >> shapeId;
		Shape *currentShape = ShapeFactory.createShape(shapeId);
		currentShape->load(input);
		listOfShapes.push_back(currentShape);
	}
}
```

###### Zusammenfassung
Neue von `Shape` abgeleitete Klassen können einfach integriert werden. Bestehende Klassen müssen nicht abgeändert werden, die neu hinzugekommene Klasse kann selbst alle nötigen Methoden und Aufrufe implementieren. Trotzdem bleiben ein paar Probleme offen:
* Die Typ-Identifikatoren müssen irgendwie zentral verwaltet werden (`LINE = 1, CIRCLE = 2, ...`)
* Die `ShapeFactory`-Klasse ist speziell nur für `Shape`-Klassen (und deren Unterklassen)
* Es muss auch sichergestellt werden, dass es nur eine `ShapeFactory`-Instanz gibt

Um diese Probleme zu lösen müssen wir weitere Verallgemeinerungen der `ShapeFactory` vornehmen. Wir erstellen also eine ganz allgemeine `ObjectFactory` mit folgenden Elementen:
* __AbstractObject__ … abstrakte Basisklasse der erzeugten Objekte
* __IdentifierType__ … identifiziert den Typ des zu erzeugenden Objektes
* __ObjectCreator__ … Funktion zum erzeugen eines Objektes
* __ConcreteObject__ … ein erzeugtes Objekt

```Cpp
template <
	class AbstractObject,
	typename IdentifierType,
	typename ObjectCreator
> class ObjectFactory {
public:
	bool register(const IdentifierType &id, ObjectCreator creator) {
		return callbacks.insert(CallbackMap::value_type(id, creator)).second;
	}
	bool unregister(const IdentifierType &id) {
		return callbacks.erase(id) == 1;
	}
	AbstractObject *createObject(const IdentifierType &id) {
		typename CallbackMap::const_iterator it = callbacks.find(id);
		if (it != callbacks.end()) {
			return (it->second)();
		}
		// ERROR!?!
	}
private:
	typedef std::map<IdentifierType, ObjectCreator> CallbackMap;
	CallbackMap callbacks;
};
```

Was soll jedoch passieren wenn eine ID nicht bekannt ist und kein Objekt erzeugt werden kann? Dafür gibt es keine allgemeingültige Antwort, möglich oder sinnvoll wäre:
* 0 (`null`-Pointer) zurückgeben?
* Exception werfen?
* Programm beenden?
* Eine dynamische Bibliothek (`dll`, `so`) laden und erneut versuchen?

### Policies
Das Verhalten kann in sogenannte _Policies_ ausgelagert werden. Die Factory soll alle genannten Fehlerbehandlungen ermöglichen und ein vernünftiges Standardverhalten bereitstellen. Dazu erstellen wir eine `FactoryError`-Policy die eine Methode implementiert: `AbstractObject *unknownType(IdentifierType id)`
_Policies_ und _Policy Classes_ erlauben es einzelne Aspekte einer Klasse flexibel zu gestalten. Eigenständig bieten diese Klassen nichts sinnvolles an und werden nur in anderen Klassen (sogenannten _Host Classes_) verwendet und integriert. Realisiert werden Policies durch eine Kombination von Templates und Mehrfachvererbung (multiple inheritance). Eine Klasse die Policies implementiert, ist eine Template-Klasse mit vielen Template-Parametern; jeder Template-Parameter entspricht einer Policy. Beim Zerlegen einer Klasse in Policies muss darüber nachgedacht werden, welche Entscheidungen auf mehr als eine Art gelöst werden könnten und ob diese als Policy ausgelagert werden können oder sollen.

#### Beispiele aus der C++ STL
```Cpp
// std::priority_queue
template <
	class T,
	class Container = vector<T>,
	class Compare = less<typename Container::value_type>
> class priority_queue;

// std::list
template <
	class T,
	class Allocator = allocator<T>
> class list;
```

#### `class` Vs. `typename`
In C++ kann es aufgrund der falschen Verwendung der Schlüsselwörter zu unentscheidbaren Problemen kommen.

Wir hier `T::A` mit `aObj` multipliziert?
```Cpp
template <Class T> class Demonstration {
	void method() {
		T::A *aObj;
```

Durch Verwendung von `typename` kann dieses Problem umgangen werden:
```Cpp
template <Class T> class Demonstration {
	void method() {
		typename T::A *aObj;
```

#### Generische Factory mit Policy erweitern
```Cpp
/**
 * Default Factory Error Policy
 */
template <class IdentifierType, class ObjectType> class DefaultFactoryError {
public:
	class Exception : public std::exception {
	public:
		Exception(const IdentifierType &id) : unknownId(id) {}
		virtual const char *what() {
			return "Unknown object type passed to Factory.";
		}
		const IdentifierType &getId() {
			return unknownId;
		}
	}
protected:
	static ObjectType *unknownType(const IdentifierType &id) {
		throw Exception(id);
	}
};
```

```Cpp
template <
	class AbstractObject,
	typename IdentifierType,
	typename ObjectCreator,
	template <typename, class> class FactoryErrorPolicy = DefaultFactoryError
> ObjectFactory : public FactoryErrorPolicy<IdentifierType, AbstractObject> {
public:
	bool register(const IdentifierType &id, ObjectCreator creator) {
		return callbacks.insert(CallbackMap::value_type(id, creator)).second;
	}
	bool unregister(const IdentifierType &id) {
		return callbacks.erase(id) == 1;
	}
	AbstractObject *createObject(const IdentifierType &id) {
		typename CallbackMap::const_iterator it = callbacks.find(id);
		if (it != callbacks.end()) return (it->second)();
		return unknownType(id);
	}
private:
	typedef std::map<IdentifierType, ObjectCreator> CallbackMap;
	CallbackMap callbacks;
};
```

```Cpp
/**
 * Usage example
 */
ObjectFactory<Shape, int> myShapeFactory;
myShapeFactory.register(POLYGON, createPolygon);
Shape *shape1 = myShapeFactory.createObject(POLYGON);
try {
	Shape *shape2 = myShapeFactory.createObject(666);
} catch (DefaultFactoryError<int, Shape>::Exception &e) {
	std::cerr << e.what() << std::endl;
}
```

## Creational Pattern: Singleton
Das __Creational Pattern__ _Singleton_ stellt sicher …
* … es von einer Klasse nur eine Instanz gibt.
* … es auf diese eine Instanz nur einen global Zugriffspunkt gibt.

```Cpp
class Singleton {
public:
	static Singleton &Instance();
	// Other methods
private:
	Singleton(); // disable
	Singleton(const Singleton &); // disable
	Singleton& operator=(const Singleton &); // disable
	~Singleton();
};
```

Einfachste Implementierung in C++ ist _Meyers Singleton_:
```Cpp
Singleton &Singleton::Instance() {
	static Singleton obj;
	return obj;
}
```
`obj` wird initialisiert wenn `Instance()` zum ersten Mal aufgerufen wird.

