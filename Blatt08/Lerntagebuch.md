# Lerntagebuch Blatt08 (LED-Segmentanzeige von Finn Watermann / Mattis Fieseler / Ben-Lukas Horn)

## Smartpointer in C++

In C++ können u.a. auch Operatoren überladen werden, die zum Umgang mit Pointern dienen. Dadurch lassen sich “Smartpointer” realisieren, die im Umgang den aus Java bekannten Referenzen ähneln und die die typischen Pointer-Probleme1 in C/C++ vermeiden können.

Ein Smartpointer soll entsprechend folgende Eigenschaften haben:

    - Verwendung soll analog zu normalen Pointern sein (Operatoren * und -> überladen)
    - Smartpointer sollen für beliebige Klassen nutzbar sein (Template-Klasse)
    - Smartpointer haben niemals einen undefinierten Wert: entweder sie zeigen auf ein Objekt oder auf nullptr2
    - Dereferenzierung von nicht existierenden Objekten (d.h. der Smartpointer zeigt intern auf nullptr) führt nicht zum Programmabsturz, sondern zu einer Exception
    - Kopieren von Smartpointern führt dazu, dass sich mehrere Smartpointer das verwiesene Objekt teilen
    - Smartpointer löschen sich selbst (und das verwiesene Objekt, falls kein anderer Smartpointer mehr darauf zeigt), wenn die Smartpointer ungültig werden (bei Verlassen des Scopes bzw. bei explizitem Aufruf von delete)
    - Es gibt keine verwitweten Objekte mehr: Wenn mehrere Smartpointer auf das selbe Objekt zeigen, darf erst der letzte Smartpointer das Objekt aus dem Heap löschen
    - Smartpointer funktionieren nur für mit new erzeugte Objekte

Es gibt in der C++-Standardbibliothek bereits verschiedene Smartpointer-Klassen. Um diese sicher benutzen zu können, benötigen Sie ein Grundverständnis der in C++11 hinzugekommenen Move-Semantik. => Themen in “Move-Semantik und Rvalue-Referenzen” und “Smartpointer”. Auf diesem Übungsblatt sollen Sie durch die eigenständige Implementierung der Smartpointer sowohl ein Grundverständnis für die prinzipielle Arbeitsweise erwerben als auch Ihre C++-Template-Kenntnisse vertiefen.

## Hilfsklassen (1P)
### Hilfsklasse für den Referenzen-Zähler

Für die Smartpointer brauchen Sie einen Zähler, der mitzählt, wie oft auf das Objekt gezeigt wird. Nutzen Sie dafür die Klasse RefCounter. Sie finden die Schnittstelle als Vorgabe im Header `smartpointer/RefCounter.h`. Implementieren Sie die Klasse in `smartpointer/RefCounter.cpp`.

### Hilfsklasse für Exceptions

Bei der Dereferenzierung eines “leeren” Smartpointers, dessen interner Objektzeiger pObj ein nullptr ist, soll eine Exception ausgelöst werden. Implementieren Sie dafür die Klasse NullPointerException als “echte” Exception (`std::runtime_error`).

Implementieren Sie diese Klasse direkt im Header `smartpointer/NullPointerException.h`.

## Smartpointer in C++ (2P)

Implementieren Sie nun die Smartpointer mit dem Klassen-Template smartpointer/SmartPointer. Da es sich um ein Klassen-Template handelt, müssen Sie Ihre Implementierung direkt im Header vornehmen.

Betrachten Sie die vorgegebene Testsuite wieder als Ergänzung der Aufgabenstellung (“ausführbare Spezifikation”).

Sie sollen sich in dieser Aufgabe u.a. mit der Arbeitsweise von Smartpointern beschäftigen. Nutzen Sie für Ihre Lösung keine existierenden Smartpointer-Implementierungen!

## Standard-Idiome in C++ (2P)

Gerade im Zusammenhang mit Smartpointern werden in C++ häufig die Idiome “RAII” (Resource Acquisition Is Initialisation) und “PIMPL” (Pointer to Implementation) verwendet.

Recherchieren Sie, was diese Idiome bedeuten und wie sie umgesetzt und genutzt werden. Erläutern Sie im Lerntagebuch anhand selbst implementierter Beispiele die Funktionsweise. Wo werden diese Idiome angewendet und warum?

## Unsere Erfahrungen