#include <stdio.h>

int main() {
    
    const char str[12] = "8901";
    const char *p = str;

    int i = 0;

    while(*p++);
    i = p-str-1;

    printf("I: %d", i);
    return 0;
}