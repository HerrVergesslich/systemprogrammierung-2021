# Lerntagebuch Blatt02 (LED-Segmentanzeige von Finn Watermann / Mattis Fieseler / Ben-Lukas Horn)

## Datentypen (1P)

In der Datei [segmentanzeige.h](./include/ledanzeige/segmentanzeige.h) soll ein vorzeichenloser Datentyp `byte` implementiert werden, dazu ein Aufzählungstyp `segment` für die einzelnen Segmente in der Anzeige, noch ein Aufzählungstyp `dot` für den Dezimalpunkt der Anzeige und noch einen Aufzählungstyp `brightness` für die unterschiedlichen Helligkeitsstufen der Anzeige. 

Für die Aufzählungstypen haben wir Enums verwendet, da in der Aufgabe Aufzählungstypen gefordert werden. Dazu kommt noch ein `unsigned char`, da dieser nicht den negativen Zahlenbereich darstellen kann und bis 255 hoch geht. 

Das Enum `segment` enthält vier Konstanten mit den Zahlen 0 bis 3 für die einzelnen Segmente

    typedef enum{
        SEG1 = 0,
        SEG2 = 1,
        SEG3 = 2,
        SEG4 = 3
    }segment;

Das Enum `dot` enthält zwei Konstanten mit 0 und 1 um festzulegen ob der Dezimalpunkt aktiviert ist oder nicht.

    typedef enum {
        OFF = 0,
        ON = 1
    }dot;

Das Enum `brightness` enthält drei Konstanten mit den Zahlen 0, 1 und 7 um die Helligkeit zu regulieren.

    typedef enum {
        DARK = 0,
        MEDIUM = 1,
        BRIGHT = 7
    }brightness;


## Funktionen (2P)

Als nächsten Schritt soll die Datei [segmentanzeige.c](./src/ledanzeige/segmentanzeige.c) mithilfe der Funktion byte_wr_data implementiert werden. Wenn man sich an die in der Aufgabe gegebenen Anleitung hält, sieht das am Ende etwa so aus

    void TM1637_write_byte(byte wr_data){
        int i;
        for(i=0; i < 8; i ++) {
            digitalWrite(PIN_CLOCK, LOW);
            delayMicroseconds(DELAY_TIMER); 
            if((wr_data & (1 << i)) > 0) {
                digitalWrite(PIN_DATA, HIGH);
            } else {
                digitalWrite(PIN_DATA, LOW);
            }
            delayMicroseconds(DELAY_TIMER);
            digitalWrite(PIN_CLOCK, HIGH);
            delayMicroseconds(DELAY_TIMER);
        }
        TM1637_ack();
    }

Die Bits müssen alle einzeln übertragen werden, wird der Code innerhalb der For-Schleife acht Mal ausgeführt, heißt für jeden Bit. Zu Anfang soll der Clock Pin auf LOW gesetzt werden. Danach wird ein Delay eingefügt, damit die Spannung im Pin sich wieder stabilisieren kann.  
Dieser Delay muss nach jedem Aufruf von  `digitalWrite()` eingesetzt werden. In dem If Block prüfen wir mittels Bit-Shifting ob ein bit in dem Segment Beleuchtet werden soll oder nicht. Sollte bei der UND Verknüpfung ein Wert größer Null rauskommen, wird der Teil der Anzeige Beleuchtet. Danach wird wieder der Delay eingesetzt und er Clock-Pin wieder auf HIGH gesetzt, danach wieder der Delay.
Die Datenübertragung wird nach der For-Schleife mit `TM1637_ack()` beendet.


## LED-Demo (1P)

Es soll eine kleine Demonstration der LED-Segmentanzeige implementiert werden.
Unsere LED-Segmentanzeige zählt bis 999 hoch und springt dann wieder auf Null und fängt von vorne an. Dafür haben wir in der Datei [main.c](./src/ledanzeige/main.c) die Methode `LED_DEMO()` implementiert. 

    void LED_Demo(){
        float i;
        TM1637_setup();
        while(1) {
            TM1637_display_number((float)i);
            printf("Showing: %f\n", i);
            i += 0.1f;
            if(i > 999) {
                i = 0;
            }
        }
    }

Wir haben eine unendliche While-Schleife implementiert die immer wieder `TM1637_display_number()` aufruft und die Variable `i` die am Anfang deklariert wurde dort als Parameter mitgibt.
danach wird auf der Console die Zahl ausgegeben die angezeigt wird. Dann wird die Variable `i` in 0.1er Schritten hochgezählt. Sollte `i` größer als 999 werden, wird die Variable auf null zurückgesetzt. 
## Make (1P)

Schreiben Sie ein Makefile für Ihr Programm entsprechend den Regeln für das Praktikum.


## Unsere Erfahrungen
Wir haben die Codeschnippsel aus der Aufgabenstellung in die entsprechenden Dateien kopiert und auf den Pi geschrieben.
Wir hatten allerdings Probleme den Import der Header Dateien zu finden. Als wir dann das -i durch das -I getauscht hatten, hat es funktioniert.
Für die Demo Aufgabe haben wir eine Zahlenfolge von 0 bis 999 anzeigen lassen.