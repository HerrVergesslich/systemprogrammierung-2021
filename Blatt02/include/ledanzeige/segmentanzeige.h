#ifndef SEGMENTANZEIGE_H
#define SEGMENTANZEIGE_H

typedef unsigned char byte;
typedef signed char int8;
typedef int int16;
typedef unsigned int uint16;
typedef long int int32;
typedef unsigned long int uint32;

typedef enum{
    SEG1 = 0,
    SEG2 = 1,
    SEG3 = 2,
    SEG4 = 3
}segment;

typedef enum {
    OFF = 0,
    ON = 1
}dot;

typedef enum {
    DARK = 0,
    MEDIUM = 1,
    BRIGHT = 7
}brightness;

#endif