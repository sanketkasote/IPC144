/*--------------------------------------------------------------------------------------------------------------------------*/
// Code Quest Workshop 9
// codequest_w9.c
// last edit = Jul 22, 3:10 PM
/*--------------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#define PLAYERS 2
#define INVENTORY_SIZE 2 // im guessing this is whats supposed to replace the "#define ITEMS 2" i did in the previous lab
#define TEXT 30 // max number of chars for save file name
/*--------------------------------------------------------------------------------------------------------------------------*/
struct Player { // 8
    int strength;
    int defense;
    int intelligence;
    int speed;
    int luck;
    int level;
    int currentHP;
    int maxHP;
};
// i did this instead of making different arrays for each players items/inventory
// this struct stores all items in "a" players inventory, 2 items
struct Items { // 4
    int type1; // item 1
    int power1; // item 1
    int type2; // item 2
    int power2; // item 2
};
//all of player 1's stats and items will be player[0] and items[0]
//all of player 2's stats and items will be player[1] and items[1]
struct Quantity { // not sure about the purpose of quantities, so not sure if i could make this struct work
    int q1;
    int q2;
};
int saveGame(struct Player [], struct Items [], struct Quantity [], int, int, float);
int loadSaveGame(struct Player [], struct Items [], struct Quantity [], int *, int *, float *);
/*--------------------------------------------------------------------------------------------------------------------------*/
int main()
{
    int validate = 0, validate2 = 0;
    struct Player player[PLAYERS]; // have 2 players
    struct Items items[INVENTORY_SIZE]; // player 1's items  --- changed, items struct have all of just 1 players items
    //struct Item items2[ITEMS]; // player 2's items         --- changed, not needed, made 1 array for all player items
    //int inventorySize = ITEMS;                             --- changed, its in the #define now
    struct Quantity quantity[INVENTORY_SIZE];
    
    // all things player 1
    player[0].strength = 10;
    player[0].defense = 20;
    player[0].speed = 30;
    player[0].intelligence = 40;
    player[0].level = 5;
    player[0].maxHP = 50;
    player[0].currentHP = 15;
    player[0].luck = 33;
    
    float days = 12;
    int exp = 24, nextLvl = 15;
    
    items[0].type1 = 3;
    items[0].power1 = 40;
    items[0].type2 = 2;
    items[0].power2 = 20;
    // int quantity[INVENTORY_SIZE] = {12,34}; // ITEMS for size b/c it was 2? or inventory size? or are all of it related?
    quantity[0].q1 = 12;
    quantity[0].q2 = 34;
    
    // wasnt sure what happens with/for invalid save file name, so didnt put a while loop
    validate = saveGame(player, items, quantity, exp, nextLvl, days);
    //printf("\n*** DEBUG: validate=%d ****\n", validate);
    
    // player 2
    // whats the point of player 2 for this lab? just to not mess with the stats of player 1? we couldve printed 0s with %d
    player[1].strength = 0;
    player[1].defense = 0;
    player[1].speed = 0;
    player[1].intelligence = 0;
    player[1].level = 0;
    player[1].maxHP = 0;
    player[1].currentHP = 0;
    player[1].luck = 0;
    
    items[1].type1 = 0;
    items[1].power1 = 0;
    items[1].type2 = 0;
    items[1].power2 = 0;
    //int quantity2[INVENTORY_SIZE]={0}; // whats the point of quantity?
    quantity[1].q1 = 0;
    quantity[1].q2 = 0;
    exp = days = nextLvl = 0;
    
    while (validate2 == 0) // changed it, added if, otherwise it kept printing the zeroed stats
    {
        validate2 = loadSaveGame(player, items, quantity, &exp, &nextLvl, &days);
        if (validate2 != 0)
        {
            printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n%d\t%d\n%d\t%d\n%d\t%d\n%d\t%d\t%.1f\n", player[1].strength, player[1].defense, player[1].intelligence, player[1].speed, player[1].luck, player[1].level, player[1].currentHP, player[1].maxHP, items[1].type1, items[1].power1, items[1].type2, items[1].power2, quantity[1].q1, quantity[1].q2, exp, nextLvl, days);
        }
    }
    
    return 0;
}
/*--------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------- ASSIGNMENT FUNCTIONS --------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/
int saveGame(struct Player player[], struct Items items[], struct Quantity quantity[], int exp, int nextLvl, float days)
{
    int retour = 0;
    char gameFile[TEXT];
    
    printf("Enter filename to write: ");
    scanf("%s", gameFile);
    
    FILE *file = fopen(gameFile, "w");
    
    if (file != NULL)
    {
        for (int i=0; i<1; i++) // for player 1 atm... i<PLAYERS for all players, but we dont initialize player 2's anything
        {
            fprintf(file, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%.1f\n", player[i].strength, player[i].defense, player[i].intelligence, player[i].speed, player[i].luck, player[i].level, player[i].currentHP, player[i].maxHP, items[i].type1, items[i].power1, items[i].type2, items[i].power2, quantity[i].q1, quantity[i].q2, exp, nextLvl, days);
        }
        fclose(file);
        retour = 1;
    }
    else
    {
        printf("ERROR!\n");
    }
    
    return retour;
}
/*--------------------------------------------------------------------------------------------------------------------------*/
int loadSaveGame(struct Player player[], struct Items items[], struct Quantity quantity[], int *exp, int *nextLvl, float *days)
{
    int retour = 0;
    char gameFile[TEXT];
    
    printf("Enter filename to read: ");
    scanf("%s", gameFile);
    
    FILE *file = fopen(gameFile, "r");
    
    if (file != NULL)
    {
        while (!feof(file))
        {
            fscanf(file, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%f\n", &player[1].strength, &player[1].defense, &player[1].intelligence, &player[1].speed, &player[1].luck, &player[1].level, &player[1].currentHP, &player[1].maxHP, &items[1].type1, &items[1].power1, &items[1].type2, &items[1].power2, &quantity[1].q1, &quantity[1].q2, exp, nextLvl, days);
            //printf("\nDEBUG: fscanf complete!\n");
        }
        fclose(file);
        retour = 1;
    }
    else
    {
        printf("Invalid save file!\n");
    }
    return retour;
}
/*--------------------------------------------------------------------------------------------------------------------------*/