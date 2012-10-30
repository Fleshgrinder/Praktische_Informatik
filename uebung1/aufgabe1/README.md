Aufgabenstellung
================

Erweitern Sie den *Heap* aus der Vorlesung mit Hilfe von einem oder mehreren Template-Parametern so, dass beliebige Datentypen verwendet werden können. Testen Sie mit zwei Datentypen wobei ein Datentyp eine eigene Klasse sein soll. Welche Anforderungen werden an den Datentyp gestellt?

Lösung
======

```bash
$ make
g++ -Wall -g -o aufgabe1 ./main.cpp
$ make test
./aufgabe1
Custom4
Custom3
Custom1
Custom0
Custom2
$ make clean
rm -f aufgabe1
```