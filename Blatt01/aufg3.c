#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    long i = 0;
    long j = 0;
    long eingabe = 0;

    /*Lese Benutzereingabe*/
    scanf("%ld", &eingabe);

    if(eingabe < 0) {
        printf("Die Eingabe muss groesser gleich 0 sein. Technisch bedingt, kleiner als 2.147.483.647");
        return EXIT_FAILURE;
    }

    printf("1. Ausgabe:\n\n");

    for(i = 0; i < eingabe; i ++) {
        printf("*");
    }

    printf("\n\n2. Ausgabe:\n\n");

    for(i = 0; i < eingabe; i ++) {
        for(j = 0; j < i+1; j ++) {
            printf("*");
        }
        printf("\n");
    }

    printf("\n\n3. Ausgabe:\n\n");

    if(eingabe % 2 == 0) {
        printf("Um Aufgabe 3 auszufuehren, muss die eingegebene Zahl ungerade sein!");
        return EXIT_FAILURE;
    }

    i = 1;
    while(i <= eingabe) {
        
        /*Spacer*/
        for(j = 0; j < (eingabe / 2) - i/2; j ++) {
            printf(" ");
        }

        for(j = 0; j < i; j ++)  {
            printf("*");
        }
        printf("\n");
        i += 2;
    }
    i = 0;
    j = 0;
    while(i <= (eingabe/6.0)){
        while(j<eingabe){
            if(eingabe-j-1 > floor(eingabe/2.0)-(eingabe/5.0) && eingabe-j < ((eingabe/2.0)+(eingabe/5.0))){
                printf("*");
            }else{
                printf(" ");
            }
            j++;
        }
        printf("\n");
        i++;
        j=0;
    }

    return EXIT_SUCCESS;
}