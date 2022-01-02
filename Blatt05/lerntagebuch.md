# Lerntagebuch Blatt05 Ring Buffer (Finn Watermann / Mattis Fieseler / Ben-Lukas Horn)

## Initialisieren des Ringpuffers (1P)

Die Funktion `ring_buffer *init_buffer(const size_t n, void (*f)(void *p))` soll mit Hilfe von `malloc()` einen neuen Ringpuffer anlegen sowie ein Array mit Platz für `n` void-Pointer allozieren und das Array in elems einhängen. Der Pointer auf die Callback-Funktion f wird in der Struktur im Pointer `free_callback` gespeichert.

Die Funktion `free_callback()` wird aufgerufen, um ein Element des Puffers freizugeben.

## Lesen des ersten Elements (1P)

Die Funktion `void *read_buffer(ring_buffer *cb)` soll das erste (älteste) Element aus dem Ringpuffer `cb` zurückliefern oder `NULL`, wenn der Puffer leer ist.

Falls ein Element gelesen wurde, steht der interne Startzeiger `head` anschließend auf dem nächsten Element, der count wird dekrementiert. Der gelesene Datensatz wird nicht freigegeben.
## Schreiben in den Ringpuffer (1P)

Die Funktion `void write_buffer(ring_buffer *cb, void *data)` soll den Datensatz `data` in den Puffer hängen.

Wenn der Puffer voll ist, soll der älteste Eintrag durch den neuen Datensatz ersetzt werden. Der ersetzte Datensatz soll mittels des Funktionspointers `free_callback` freigegeben werden.
## Freigeben des Puffers (1P)

Die Funktion `int free_buffer(ring_buffer *cb)` soll den Ringpuffer freigeben. Die Datensätze sollen dabei ebenfalls freigegeben werden (mittels des Funktionspointers `free_callback`).

Der Rückgabewert entspricht der Anzahl der ursprünglich gespeicherten Datensätze.
## Testfälle (1P)

Schreiben Sie eine Testsuite, in der Sie die implementierten Funktionalitäten ansprechen und sinnvoll testen: Ringpuffer anlegen, Daten eintragen und lesen, Ringpuffer löschen; sinnvolle `free_callback()`-Funktion definieren und mitgeben …

Schauen Sie sich dazu [GoogleTest](https://github.com/google/googletest) an. Das Framework ist bereits auf dem Raspi installiert.

Denken Sie daran, dass Ihr Makefile das Ausführen der Tests erlauben soll, bauen Sie also passende Targets ein.

Wann immer Sie das Gefühl haben, eine Debug-Ausgabe zu brauchen: Schreiben Sie stattdessen einfach einen Testfall.

Sie können die Tests auch in einem anderen Framework formulieren, dann muss Ihr Makefile ein Target aufweisen, welches das von Ihnen verwendete Framework lokal für den ausführenden User installiert.

## Unsere Erfahrungen
Wir haben den Ringbuffer wie beschrieben programmiert.
Für die Tests haben wir mittels cpp die Testfälle geschrieben und ausführen lassen.