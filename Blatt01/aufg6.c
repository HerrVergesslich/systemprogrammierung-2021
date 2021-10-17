#include <stdio.h>
#include <stdlib.h>
#include "betterTypes.h"
#define ANIMALCOUNT 10

enum viech
{
    MAMMAL,
    FISH,
    BIRD,
    AMPHIBIAN,
    REPTILES
};
typedef struct animal
{
    enum viech species;
    uint8 name[32];
    int16 age;
    double food_weight;
} animal;

animal zoo[ANIMALCOUNT];
animal elephant = {MAMMAL, "Tim", 6, 5.5};
animal ape = {MAMMAL, "Finn", 69, 7.3};
animal cockato = {BIRD, "Mattis", 3, 1.2};
animal python = {REPTILES, "Luca", 2, 2.4};
animal toad = {AMPHIBIAN, "Niklas", 1, 0.5};
animal crocodile = {REPTILES, "Manuel", 200, 400};
animal dolphin = {MAMMAL, "Kevin", 1, 12.36};
animal salamander = {REPTILES, "Jason", 4, 20.35};
animal giraffe = {MAMMAL, "Dennis", 9, 7.8};
animal sloth = {MAMMAL, "Marck", 1500, 69.420};

double calculate_average_age()
{
    int i, total;
    for (i = 0; i < ANIMALCOUNT; i++)
    {
        total += zoo[i].age;
    }
    return (double)total / ANIMALCOUNT;
}

int main()
{

    zoo[0] = elephant;
    zoo[1] = ape;
    zoo[2] = cockato;
    zoo[3] = python;
    zoo[4] = toad;
    zoo[5] = crocodile;
    zoo[6] = dolphin;
    zoo[7] = salamander;
    zoo[8] = giraffe;
    zoo[9] = sloth;
    printf("%f", calculate_average_age());
    return EXIT_SUCCESS;
}
