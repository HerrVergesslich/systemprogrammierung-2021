#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "betterTypes.h"

int bitStuff(uint8 input, int8 bit) {
    int value = 0;

    if(bit >= 0 && bit < 8) {
        printf("Input: %hu\n", input);
        value = (input) & (1<<(bit));
        printf("Wert: %d\n", value);
        input = (input) ^ (1<<(bit));
        printf("Input-Edit: %hu\n", input);
        return value == (1<<(bit));
    } else {
        printf("Es gibt 8 Bits! Bitte Bit 0-7 auswaehlen.");
        return 0;
    }

    return 0;
}

int main() {
    int16 eingabe = 0;
    int16 bitstelle = 0;

    printf("Zahl (0-255): ");
    scanf("%i", &eingabe);

    printf("Bitstelle: (0-7): ");
    scanf("%i", &bitstelle);
    printf("\n");
    
    printf("\n%hu hat an der %hdten Stelle eine: %i", eingabe, bitstelle, bitStuff((uint8) eingabe, (int8) bitstelle));
    return EXIT_SUCCESS;
}