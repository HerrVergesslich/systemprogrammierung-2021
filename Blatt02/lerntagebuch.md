# Lerntagebuch Blatt02

## Datentypen (1P)

Definieren Sie in der Datei ledanzeige/segmentanzeige.h folgende Strukturen:

## Funktionen (2P)

Implementieren Sie in der Datei ledanzeige/segmentanzeige.c die Funktion void TM1637_write_byte(byte wr_data), mit der wie nachfolgend beschrieben ein Byte wr_data an die LED-Segmentanzeige übertragen wird.

## LED-Demo (1P)

Schreiben Sie ein Programm zur Demonstration der LED-Segmentanzeige-Funktionen: Lassen Sie beispielsweise mit zeitlichem Abstand bestimmte Zahlen anzeigen.

## Make (1P)

Schreiben Sie ein Makefile für Ihr Programm entsprechend den Regeln für das Praktikum.


## Unsere Erfahrungen
Wir haben die Codeschnippsel aus der Aufgabenstellung in die entsprechenden Dateien kopiert und auf den Pi geschrieben.
Wir hatten allerdings Probleme den Import der Header Dateien zu finden. Als wir dann das -i durch das -I getauscht hatten, hat es funktioniert.
Für die Demo Aufgabe haben wir eine Zahlenfolge von 0 bis 999 anzeigen lassen.