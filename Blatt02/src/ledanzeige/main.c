
#include "ledanzeige/TM1637.h"

#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include <time.h>

/**
 * Eine Funktion, um die 7-Segmentanzeige zu demonstrien.
 * Es wird eine aufsteigende Zahl angezeigt, die, wenn sie 999.9 err
 */
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

/**
 * Eine Funktion, die die 7-Segmentanzeige nach Hilfe schreien lässt.
 * Es wird abwechselnd "SEND" und "HELP" angezeigt.
 */
void sendHelp() {
    int a = 0;
    TM1637_setup();
    while(1) {
        if(a == 0) {
            TM1637_display_text("send");
            a = 1;
        } else if(a == 1) {
            TM1637_display_text("help");
            a = 0;
        }
        delay(1000);
    }    
}

/**
 * Die Hauptfunktion des Programms. 
 * Sie wird beim Start des Programs aufgerufen.
 */
int main(){
    /* LED_Demo(); */
    sendHelp();
    return 0;
}