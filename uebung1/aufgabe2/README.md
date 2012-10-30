Aufgabenstellung
================

Wie funktioniert *heap sort*. Implementieren Sie *heap sort* mit Hilfe der bekannten Datenstrukturen. Argumentieren Sie warum der Algorithmus *worst-case* Komplexität *O(n log n)* besitzt.

Lösung
======

```bash
$ make
g++ -Wall -g -o aufgabe2 ./main.cpp
$ make test
./aufgabe2
9-8-5-6-7-3-4-2-0-1-
8-7-5-6-1-3-4-2-0-
7-6-5-2-1-3-4-0-
6-2-5-0-1-3-4-
5-2-4-0-1-3-
4-2-3-0-1-
3-2-1-0-
2-0-1-
1-0-
0-
$ make clean
rm -f aufgabe2
```

Um einen neuen Knoten hinzuzufügen benötigen wir maximal *log(n)*-Schritte da ein Baum mit *n* Knoten die Tiefe *d ≤ log(n)* hat.
Beim Sortieren wird nochmals jeder Knoten betrachtet, daraus folgt die Zeitkomplexität von *O(n · log(n))*.