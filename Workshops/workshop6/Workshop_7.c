/*--------------------------------------------------------------------------------------------------------------------------*/
// Code Quest Workshop 6
// codequest_w6.c
/*--------------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
/*--------------------------------------------------------------------------------------------------------------------------*/
#define STAT_LOW 0.15 // regular stat min-max
#define STAT_HIGH 0.5
#define HP_LOW 0.5 // HP min-max
#define HP_HIGH 2.0
#define LV_LOW 3 // level min-max
#define LV_HIGH 20
/*--------------------------------------------------------------------------------------------------------------------------*/
void seedRandom();
float getRandom(float low, float high);
void clearB();
void statRatios(float *, float *, float *, float *, float *, int *);  // randomizing stat ratios and the level
void printStats(int *, int *, int *, int *, int *, int *); // printing of stats
/*--------------------------------------------------------------------------------------------------------------------------*/
int main(void)
{
    seedRandom();
    
    float strengthRatio, speedRatio, defenseRatio, intelligenceRatio, hpRatio;
    int level, HP, strength, speed, defense, intelligence, userInput;
    
    // randomizing stat ratios and the level
    statRatios(&strengthRatio, &speedRatio, &defenseRatio, &intelligenceRatio, &hpRatio, &level);
    
    // calculation of stats from randomized stat ratios
    strength = truncf(strengthRatio * powf((float)level, 2));
    speed = truncf(speedRatio * powf((float)level, 2));
    defense = truncf(defenseRatio * powf((float)level, 2));
    intelligence = truncf(intelligenceRatio * powf((float)level, 2));
    HP = truncf(hpRatio * (float)level);
    
    printf("\n\nEnemy Generator\n\n");
    
    // printing of stats
    printStats(&level, &HP, &strength, &speed, &defense, &intelligence);
    
    printf("Generate Another? (1-Yes | 2-No)\n");
    
    do
    {
        printf("Select: ");
        scanf(" %d", &userInput);
        if (userInput == 1)
        {
            printf("\n");
            statRatios(&strengthRatio, &speedRatio, &defenseRatio, &intelligenceRatio, &hpRatio, &level);
            
            strength = truncf(strengthRatio * powf((float)level, 2));
            speed = truncf(speedRatio * powf((float)level, 2));
            defense = truncf(defenseRatio * powf((float)level, 2));
            intelligence = truncf(intelligenceRatio * powf((float)level, 2));
            HP = truncf(hpRatio * (float)level);
            
            printStats(&level, &HP, &strength, &speed, &defense, &intelligence);
            printf("Generate Another? (1-Yes | 2-No)\n");
        }
        else if (userInput == 2)
        {
            break;
        }
        else
        {
            printf("\nInvalid Input\n");
            clearB();
        }
    } while (userInput != 2);
    
    printf("\nBuh Bye, Peace.\n\n");
    
    return 0;
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void seedRandom()
{
    srand((int)time(NULL));
}
/*--------------------------------------------------------------------------------------------------------------------------*/
float getRandom(float low, float high)
{
    float random;
    
    random = low + ((double) rand() / RAND_MAX * (high - low));
    return random;
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void clearB()
{
    while (getchar() != '\n')
        ;
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void statRatios(float *strRatio, float *spdRatio, float *defRatio, float *intRatio, float *hpRatio, int *lvl)
{
    *strRatio = getRandom(STAT_LOW, STAT_HIGH);
    *spdRatio = getRandom(STAT_LOW, STAT_HIGH);
    *defRatio = getRandom(STAT_LOW, STAT_HIGH);
    *intRatio = getRandom(STAT_LOW, STAT_HIGH);
    
    *hpRatio = getRandom(HP_LOW, HP_HIGH);
    
    *lvl = getRandom(LV_LOW, LV_HIGH);
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void printStats(int *lvl, int *hp, int *str, int *spd, int *def, int *inte)
{
    printf("Level - %d\n", *lvl);
    printf("HP - %d\n", *hp);
    printf("Strength - %d\n", *str);
    printf("Speed - %d\n", *spd);
    printf("Defense - %d\n", *def);
    printf("Intelligence - %d\n\n", *inte);
}
/*--------------------------------------------------------------------------------------------------------------------------*/