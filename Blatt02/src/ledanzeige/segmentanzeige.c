#include "ledanzeige/segmentanzeige.h"
#include "ledanzeige/TM1637_intern.h"
#include "ledanzeige/TM1637.h"

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