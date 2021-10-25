#include <stdio.h>
#include <stdlib.h>
#include "betterTypes.h"
#define ANIMALCOUNT 10

typedef enum{
    MAMMAL = 10,
    FISH = 4,
    BIRD = 1,
    AMPHIBIAN = 2,
    REPTILES = 0
}viech;

typedef struct{
    viech species;
    uint8 name[32];
    int16 age;
    double food_weight;
}animal;

    animal zoo[ANIMALCOUNT];  
    animal elephant = {MAMMAL,"Tim",6,5.5};
    animal ape = {MAMMAL,"Finn",69,7.3};
    animal cockato = {BIRD,"Mattis",3,1.2};
    animal python = {REPTILES,"Luca",2,2.4};
    animal toad = {AMPHIBIAN,"Niklas",1,0.5};
    animal crocodile = {REPTILES,"Manuel",200,400};
    animal pufferfish = {FISH,"Kevin",1,12.36};
    animal salamander = {REPTILES,"Jason",4,20.35};
    animal giraffe = {MAMMAL,"Dennis",9,7.8};
    animal sloth = {MAMMAL,"Marck",1500,69.420};

double calculate_average_age(){
    int i,total;
    for(i=0;i<ANIMALCOUNT;i++){
        total += zoo[i].age;
    }    
    return (double)total/ANIMALCOUNT; 
}

void more_food(){
    int i;
    for(i = 0;i<ANIMALCOUNT;i++){
            printf("\nOld food weight from %s : %f" ,zoo[i].name,zoo[i].food_weight);
            zoo[i].food_weight = zoo[i].food_weight + (zoo[i].food_weight*(zoo[i].species/100.0));              
            printf("\nNew food weight from %s : %f" ,zoo[i].name,zoo[i].food_weight);
            }
    }
    
char* getSpeciesName(viech sp){
    switch(sp){ 
        case MAMMAL: return "Mammal";
        case BIRD: return "Bird";
        case FISH: return "Fish";
        case AMPHIBIAN: return "Amphibian";
        case REPTILES: return "Reptile";
    }
}

void print_animal(animal an){
    int i;
    printf("\n%-10s||%-10s||%-10s||%-10s","name","species","age","food_weight");
    printf("\n");
    for(i = 0;i<=46;i++){
        if(i == 10 || i == 11 || i == 22 || i == 23 || i == 34 || i == 35){
            printf("|");
        }
        else{
            printf("#");
        }
    }
    printf("\n%-10s||%-10s||%-10i||%-10.3f",an.name,getSpeciesName(an.species),an.age,an.food_weight);
}

void print_zoo(){
    int i;
    int j;
    print_animal(zoo[0]);
    for(i = 1;i<ANIMALCOUNT;i++){
        printf("\n");
        for(j = 0;j<=46;j++){
            if(j == 10 || j == 11 || j == 22 || j == 23 || j == 34 || j == 35){
                printf("|");
            }
            else{
                printf("-");
            }
        }
        printf("\n%-10s||%-10s||%-10i||%-10.3f",zoo[i].name,getSpeciesName(zoo[i].species),zoo[i].age,zoo[i].food_weight);
    }
}

int main(){
    zoo[0] = elephant;
    zoo[1] = ape;
    zoo[2] = cockato;
    zoo[3] = python;
    zoo[4] = toad;
    zoo[5] = crocodile;
    zoo[6] = pufferfish;
    zoo[7] = salamander;
    zoo[8] = giraffe;
    zoo[9] = sloth;
    printf("%f",calculate_average_age());
    more_food();
    print_zoo();
    return EXIT_SUCCESS;
}
