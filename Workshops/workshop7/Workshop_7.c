/*--------------------------------------------------------------------------------------------------------------------------*/
// Code Quest Workshop 7
// codequest_w7.c
// last edit = 7/12/2016 5:15PM
/*--------------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define SIZE 3
#define MIN 0 /* min number for random number generator */
#define MAX 4 /* max number for random number generator */
/*--------------------------------------------------------------------------------------------------------------------------*/
int getRandom(); //mine...extra
int mainMenu(); //mine...extra
int Find_Item(int[], int, int);
int Add_Item(int[], int[], int, int);
int Use_Item(int[], int[], int, int);
void Print_Item(int);
void debug(int [], int [], int *); //mine...extra
void menuGetNewItem(int [], int []); //mine...extra
void menuShowInventory(int [], int []); //mine...extra
void menuUseItem(int [], int []); //mine...extra
/*--------------------------------------------------------------------------------------------------------------------------*/
int main()
{
    int input; /*counter = 0*/
    int id[SIZE] = {0, 0, 0};
    int quantity[SIZE] = {0, 0, 0};
    
    printf("\n");
    do {
        input = mainMenu();
        switch (input)
        {
            case 1: // Get New Item
                /*debug(id, quantity, &counter);*/
                menuGetNewItem(id, quantity);
                /*debug(id, quantity, &counter);*/
                break;
            case 2: // Show Inventory
                /*debug(id, quantity, &counter);*/
                menuShowInventory(id, quantity);
                /*debug(id, quantity, &counter);*/
                break;
            case 3: // Use Item
                /*debug(id, quantity, &counter);*/
                menuUseItem(id, quantity);
                /*debug(id, quantity, &counter);*/
                break;
            case 4: // Quit Game
                break;
            default:
                printf("Try Again...\n");
                break;
        }
    } while (input != 4);
    
    printf("\nBuh Bye.\n\n");
    
    return 0;
}
/*--------------------------------------------------------------------------------------------------------------------------*/
int Find_Item(int id[], int item, int size)
{
    int index = -1;
    
    for(int i = 0; i < size; i++)
    {
        if (id[i] == item)
        {
            index = i;
            i = size;
        }
    }
    return index; // index will be -1 if an item was not found, if it was found it will be the index number of the array
}
/*--------------------------------------------------------------------------------------------------------------------------*/
int Add_Item(int id[], int quantity[], int item, int size)
{
    int searchID = Find_Item(id, item, size);
    int searchQuantity = Find_Item(quantity, 0, size);
    int validate = 0;
    
    if (searchID != -1) // if the item id is found
    {
        quantity[searchID] += 1;
        validate = 1;
    }
    else if ( (searchID == -1) && (searchQuantity != -1) ) // if the item id is not found and if a 0 was found in quantities
    {
        id[searchQuantity] = item; // id is changed into the random item number
        quantity[searchQuantity] += 1; // quantity is incremented
        validate = 1;
    }
    else
        validate = 0; // if no item id was found or no 0 in the quantity array was found
    
    return validate;
}
/*--------------------------------------------------------------------------------------------------------------------------*/
int Use_Item(int id[], int quantity[],int item, int size)
{
    int validate;
    int index = Find_Item(id, item, size); // b=-1 if the item id is not found, if found b will be equal to index number
    
    if ( (index!=-1) && (quantity[index]>0) )
    {
        quantity[index] -= 1;
        validate = 1;
    }
    else
    {
        validate = 0;
    }
    
    return validate; // a will be 0 if no item is used and 1 if the function was successful and an item was used
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void Print_Item(int item)
{
    switch (item)
    {
        case 0:
            printf("Potion x"); /* lower case x looks nicer */
            break;
        case 1:
            printf("HP Booster x");
            break;
        case 2:
            printf("Strength Booster x");
            break;
        case 3:
            printf("Defense Booster x");
            break;
        case 4:
            printf("Intelligence Booster x");
            break;
    }
}
/*--------------------------------------------------------------------------------------------------------------------------*/





int mainMenu()
{
    int input;
    
    printf("1. Get New Item\n"
           "2. Show Inventory\n"
           "3. Use Item\n"
           "4. Quit\n\n");
    
    printf("Select Option: ");
    scanf(" %d", &input);
    
    return input;
}
/*--------------------------------------------------------------------------------------------------------------------------*/
int getRandom()
{
    srand((int)time(NULL));
    int k = (MIN + rand() % (MAX + 1 - MIN));
    /*printf("getRandom=%d\n", k);*/
    return k;
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void menuGetNewItem(int id[], int quantity[])
{
    int validate;
    
    printf("\n");
    int random = getRandom();
    validate = Add_Item(id, quantity, random, SIZE);
    
    if (validate == 1)
    {
        printf("New item added.\n\n");
    }
    else if (validate == 0)
    {
        printf("Your inventory is full!\n\n");
    }
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void menuShowInventory(int id[], int quantity[])
{
    printf("\n");
    /*printf("\n");*/
    for (int i = 0; i < SIZE; i++)
    {
        if (quantity[i] > 0)
        {
            printf("%d. ", id[i]);
            Print_Item(id[i]);
            printf("%d\n", quantity[i]);
        }
    }
    printf("\n");
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void menuUseItem(int id[], int quantity[])
{
    int input, validate;
    
    printf("Select item: ");
    scanf(" %d", &input);
    
    validate = Use_Item(id, quantity, input, SIZE);
    
    if (validate == 0)
    {
        printf("You don't have that item!\n");
    }
    printf("\n");
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void debug(int id[], int quantity[], int *counter)
{
    *counter += 1;
    printf("\nDEBUG(%d)\n", *counter);
    for (int i = 0; i < SIZE; i++)
    {
        printf("id[%d]=%d  quantity[%d]=%d\n", i, id[i], i, quantity[i]);
    }
    printf("\n");
}
/*--------------------------------------------------------------------------------------------------------------------------*/