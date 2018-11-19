/*--------------------------------------------------------------------------------------------------------------------------*/
// Code Quest Workshop 8
// codequest_w8.c
// last edit = Jul 19, 7:30 PM
/*--------------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#define ITEMS 2 // number of items
#define PLAYERS 1 // number of players
//#include "scribble.h"
/*--------------------------------------------------------------------------------------------------------------------------*/
struct Player {
    int level;
    int strength;
    int speed;
    int defense;
    int intelligence;
    int luck;
    int maxHP;
    int currentHP;
};
struct Item {
    int type;
    int power;
};
struct Item loadItem();
struct Player loadPlayer();
void printData(struct Player [], struct Item []);
/*--------------------------------------------------------------------------------------------------------------------------*/
int main()
{
    struct Item items[ITEMS];
    struct Player player[PLAYERS];
    int i;
    
    for (i=0; i<PLAYERS; i++)
    {
        player[i] = loadPlayer();
    }
    
    for (i=0; i<ITEMS; i++)
    {
        items[i] = loadItem();
    }
    
    printData(player, items);
    
    return 0;
}
/*--------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------- ASSIGNMENT FUNCTIONS --------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/
struct Player loadPlayer()
{
    struct Player player;
    
    printf("Please Enter the following player info:");
    printf("\nLevel: ");
    scanf(" %d", &player.level);
    printf("Strength: ");
    scanf(" %d", &player.strength);
    printf("Speed: ");
    scanf(" %d", &player.speed);
    printf("Defense: ");
    scanf(" %d", &player.defense);
    printf("Intelligence: ");
    scanf(" %d", &player.intelligence);
    printf("Luck: ");
    scanf(" %d", &player.luck);
    printf("Max HP: ");
    scanf(" %d", &player.maxHP);
    printf("\n");
    
    return player;
}
/*--------------------------------------------------------------------------------------------------------------------------*/
struct Item loadItem()
{
    struct Item items;
    
    printf("Please enter the following item info:\n");
    printf("Type: ");
    scanf(" %d", &items.type);
    printf("Power: ");
    scanf(" %d", &items.power);
    printf("\n");
    
    return items;
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void printData(struct Player player[], struct Item items[])
{
    int i;
    
    printf("\nCollected Input:\n"); // the extra \n at the beginning makes it nicer
    printf("\nLvl\tStr\tSpd\tDef\tInt\tLck\tMHP\n");
    for (i=0; i<PLAYERS; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", player[i].level, player[i].strength, player[i].speed, player[i].defense, player[i].intelligence, player[i].luck, player[i].maxHP);
    }
    
    printf("\nType\tPower\n");
    for (i=0; i<ITEMS; i++)
    {
        printf("%d\t%d\n", items[i].type, items[i].power);
    }
}
/*--------------------------------------------------------------------------------------------------------------------------*/