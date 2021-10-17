#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

double toRadians(double degree) {
    return degree * (PI / 180.0);
}

int main() {
    int i = 0;
    printf("Aufgabe 2\n");
    printf("--FOR-SCHLEIFE--\n\n");

    for(i = 0; i <= 360; i += 10) {
        printf("Winkel: %u Grad => Sinus-Funktionswert: %.3f\n", i, sin(toRadians(i)));
    }

    printf("\n--WHILE-SCHLEIFE--\n\n");

    i = 0;
    while(i <= 360) {
        printf("Winkel: %u Grad => Sinus-Funktionswert: %.3f\n", i, sin(toRadians(i)));
        i += 10;
    }

    return EXIT_SUCCESS;
}