Aufgabenstellung
================

Schreiben Sie ein kleines Programm, mit welchem *n* Zufallszahlen in einen binären Suchbaum eingefügt werden können. Bestimmen Sie die Höhe des resultierenden Baumes. Wiederholen Sie diesen Test für *n = 10000, 20000, 30000, …* und vergleichen Sie mit einem ausbalanzierten (AVL-)Baum.

Lösung
======

```bash
$ make
g++ -Wall -g -o aufgabe3 ./main.cpp
$ make test
./aufgabe3
AVL-Tree height for n = 10000 => 16
B-Tree height for n = 10000 => 31
AVL-Tree height for n = 20000 => 18
B-Tree height for n = 20000 => 34
AVL-Tree height for n = 30000 => 19
B-Tree height for n = 30000 => 37
AVL-Tree height for n = 40000 => 20
B-Tree height for n = 40000 => 42
Finally finished =)
$ make clean
rm -f aufgabe3
```