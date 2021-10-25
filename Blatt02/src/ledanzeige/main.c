#include "ledanzeige/TM1637.h"

#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include <time.h>

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

int main(){
    LED_Demo();
    return 0;
}