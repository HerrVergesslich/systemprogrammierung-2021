#ifndef SEGMENTANZEIGE_H
#define SEGMENTANZEIGE_H

/** Definiere unsigned char als byte */
typedef unsigned char byte;

/** Definiere signed char als int8 */
typedef signed char int8;

/** Definiere signed int als int16 */
typedef int int16;

/** Definiere unsigned int als uint16 */
typedef unsigned int uint16;

/** Definiere long int als int32 */
typedef long int int32;

/** Definiere unsigned long int als uint32 */
typedef unsigned long int uint32;

/** Enum als Repräsentation der Segmentanzeigen-Stellen */
typedef enum{
    SEG1 = 0,
    SEG2 = 1,
    SEG3 = 2,
    SEG4 = 3
}segment;

/** Enum als Repräsentation des Zustands des decimal-dots */
typedef enum {
    OFF = 0,
    ON = 1
}dot;

/** Enum als Repräsentation der Anzeigenhelligkeit */
typedef enum {
    DARK = 0,
    MEDIUM = 2,
    BRIGHT = 7
}brightness;

#endif