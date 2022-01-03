# Lerntagebuch Blatt08 (LED-Segmentanzeige von Finn Watermann / Mattis Fieseler / Ben-Lukas Horn)

## Hilfsklassen (1P)
### Hilfsklasse für den Referenzen-Zähler
Die Datei `RefCounter.cpp` beinhaltet den Referenz-Zähler in unserem Programm. Diese included die header-Datei `RefCounter.h` der Default Konstruktor aus der header-Datei wird überladen und die zuvor deklarierte Variable `n` wird auf 0 gesetzt.
Die Datei implementiert Methoden zum Hochzählen von n (`inc()`), zum Runterzählen (`dec()`) , zum Abfragen ob der Counter (n) 0 ist und um den aktuellen Zählerstand zurückzugeben(`getRefCount()`).   
### Hilfsklasse für Exceptions
Die header-Datei `NullPointerException.h` implemtiert eine eigene Exception für den SmartPointer.
Die erbt von `runtime_error` um als quasi "offizielle" Exception zu gelten.
Sollte keine Exception Message bei der Initalisierung der Exception mitgegeben werden, so lautet die Message "NullPointerException". Andernfalls wird die übergebene Nachricht als Exception Message ausgeben bei Eintreten jener Exception. 
## Smartpointer in C++ (2P)
 Hier soll ein eigener SmartPointer implementiert werden. Dieser soll folgende Anforderungen erfüllen:
+ Operatoren "*" und "->" sollen überladen werden
+ nutzbar für beliebige Klassen
+ zeigen entweder auf ein Objekt oder auf nullptr
+ eigene Exception für Nullpointer
+ Kopien des SmartPointers teilen sich das verwiesene Objekt
+ Das Löschen passiert automatisch
+ Kein SmartPointer ohne Wert: erst der Letzte Pointer auf verwiesenes Objekt darf jenes löschen
+ Funktionieren nur mit Objekten die mit `new ` erzeugt wurden

Die header-Datei "SmartPointerImpl.h" definiert jene Methoden die zuvor in einer weiteren header-Datei "SmartPointer.h" deklariert wurden:
+ Das private Attribut `pObj` ist ein generischer Typ `T` um den Typen auf den der Pointer zeigt variabel zu lassen
+ Das private Attribut `rc` ist ein Pointer der auf einen Referenz-Counter zeigt um die Pointer auf ein jeweiliges Objekt zu zählen
+ Es gibt einen Konstruktor mit einem Parameter vom Typ `T` dieser hat als Default-Wert einen NullPointer (`nullptr`). Innerhalb des Konstruktors wird das private Attribut `pObj` auf den Parameter `p` gebogen. Sollte dieser kein NullPointer mehr sein wird der RefCounter initialisiert (`rc`) und incrementiert.
+ Der Copy-Konstruktor hat ebenfalls ein Parameter, dieser ist jedoch eine Referenz auf einen anderen SmartPointer und konstant, um sicherzustellen, dass die Referenz nicht verändert wird. Sollte der eigene Pointer ungleich dem Parameter `p` sein, wird unser eigenes Objekt auf das Objekt von `p` gesetzt, sowie unser Referenz-Counter auch auf den von `p` gesetzt und incrementiert wird. 
+ Die delete Methode ist virtuell (abstrakt) und löscht den SmartPointer. Sollte Referenz-Counter kein NullPointer sein wird dieser decrementiert. Sollte der Counter dann 0 oder kleiner sein wird das Object und der Referenz-Counter ebenfalls gelöscht.
+ Der Operator `->` gibt den Pointer `pObj` zurück sollte dieser kein NullPointer sein. Andernfalls kommt die NullPointerException aus der Hilfsklasse zum Einsatz
+ Der Operator `*` gibt eine Referenz auf `pObj` zurück sollte dieser kein NullPointer sein. Andernfalls kommt die NullPointerException aus der Hilfsklasse zum Einsatz    
+ Der Operator `=` erwartet ein Objekt vom gleichen Typ wie `pObj` (`T`) zum Weiterarbeiten wird ein konstanter Pointer auf dieses Objekt verwendet.
Sollte unser `pObj` gleich dem Parameter `p` sein passiert nichts.
Sollte unser Referenz-Counter kein NullPointer mehr sein, wird dieser decrementiert. Wenn dieser anschließend null sein sollte wird das Objekt auf das wir zeigen und unser Referenz-Counter gelöscht.
Sollte der Parameter `p` ein NullPointer sein wird unser Objekt und unser Referenz-Counter zum NullPointer gemacht. Andernfalls zeigen wir dann auf dieses Objekt `p` und der Counter wird initialisiert und incrementiert.
+ Der Operator `=` kann ebenfalls mit einem anderen SmartPointer verwendet werden. Zum Weiterarbeiten wird eine konstante Referenz auf diesen SmartPointer verwendet (`p`). Intern passiert hier so gut wie das Gleiche wie als würde man den Oberator mit einenm Objekt vom Typ `T` verwenden. Zeigen wir auf das gleiche Objekt wie der Pointer den wir reinbekommen.
+ Die Methode `getRefCounter()` gibt einen Pointer auf unseren Referenz-Counter zurück
+ Die Methode `getObject()` gibt einen Pointer auf unser `pObj` zurück
+ Der Operator `==` kann verwendet werden um zu überprüfen ob wir und ein anderer SmartPointer auf das gleiche Objekt zeigen und damit quasi gleich sind
+ Der Operator `!=` kann verwendet werden um zu überprüfen ob wir und ein anderer Pointer nicht auf das gleiche Objekt zeigen und damit ungleich sind
+ Sollte unser Pointer in einem Boolschen Kontext verwendet werden, gibt er `true` zurück wenn das Objekt auf das wir zeigen kein NullPointer ist
 

## Standard-Idiome in C++ (2P)
### RAII 
Das Idiom RAII ("Resource Acquisition Is Initialisation") wird verwendet um Ressourcen eines Programmes dynamisch zu verwalten.
Dabei sind die Ressourcen die ein Objekt benutzt solange nicht für andere freigegeben bis dieses Objekt nicht mehr existiert bzw. gelöscht wurde.
Vorraussetzung dafür ist das die Klasse des Objekts einen Dekonstruktor besitzt die die benutzten Ressourcen wieder freigibt.

Ein Beispiel: 
```
class RAII{
    private:
        std::vector<std:string> str;
    public:
        RAII(std::vector<std:string> str){
            this->str = str;
        } 

        ~RAII(){
            delete [] str; 
        }
}
```

Hier haben wir in der Klasse `RAII` ein string array das nach dem löschen eines Objektes der Klasse auch wieder entfernt werden muss und somit der Speicher wieder freigeben werden muss. Dies wird ermöglicht indem im Dekonstruktor der Klasse das Array ebenfalls gelöscht wird.

```
void func(void){
    std::vector<string> test = {"hallo","hier","ein","test"};
    RAII testObj = new RAII(test);
    delete testObj;
}
```

Wenn wir ein Objekt vom Typ `RAII` erstellen wird Speicher für unser privates Array freigeben. Dieser kann dann mittels des Dekonstruktors der Klasse wieder freigegeben werden.

## Unsere Erfahrungen