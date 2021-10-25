#include "../../include/ledanzeige/segmentanzeige.h"
#include "../../include/ledanzeige/TM1637_intern.h"
#include "../../include/ledanzeige/TM1637.h"

#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>

void TM1637_write_byte(byte wr_data){
    digitalWrite(PIN_CLOCK, LOW);
    delayMicroseconds(DELAY_TIMER);
    digitalWrite(PIN_DATA, LOW);
    delayMicroseconds(DELAY_TIMER);
    digitalWrite(PIN_CLOCK, HIGH);
    delayMicroseconds(DELAY_TIMER);
    TM1637_ack();
}

void LED_Demo(){
    TM1637_setup();
    for(int i = 0; i<20; i++){
        TM1637_display_number(i);
        delayMicroseconds(1000);
    }
}