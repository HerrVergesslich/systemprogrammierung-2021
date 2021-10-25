#include "ledanzeige/TM1637.h"
#include "ledanzeige/TM1637_intern.h"

#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>

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