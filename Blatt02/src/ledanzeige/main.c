#include "ledanzeige/TM1637.h"

#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>

void LED_Demo(){
    int i;
    TM1637_setup();
    for(i=0; i<20; i++){
        TM1637_display_number(i);
        delayMicroseconds(1000);
    }
}

int main(){
    LED_Demo();
    return 0;
}