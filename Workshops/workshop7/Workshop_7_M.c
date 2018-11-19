#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define SIZE 3
#define MIN 0
#define MAX 4

int getRandom();
void mainMenu(int *);
void getNewItem(int[], int[]);
void showInventory(int[], int[]);
void useItem(int[], int[]);
int Find_Item(int[], int);
int Add_Item(int[], int[], int);
int Use_Item(int[], int[], int);
void Print_Item(int);

int main()
{
    int input;
    int id[SIZE] = {0, 1, 2};
    int quantity[SIZE] = {0, 0, 0};
    
    do {
        mainMenu(&input);
        
        switch (input) {
            case 1:
                getNewItem(id, quantity);
                break;
            case 2:
                showInventory(id, quantity);
                break;
            case 3:
                useItem(id, quantity);
                break;
            default:
                break;
        }
    } while (input != 4);
    
    printf("Buh Bye.\n\n");
    
    return 0;
}

void mainMenu(int *input)
{
    int a;
    
    printf("\n\n1. Get New Item\n"
           "2. Show Inventory\n"
           "3. Use Item\n"
           "4. Quit\n\n");
    
    printf("Select Option: ");
    scanf(" %d", &a);
    
    *input = a;
}

int Find_Item(int id[], int item)
{
    int i, index = -1;
    
    for(i = 0; i < SIZE; i++)
    {
        if (id[i] == item)
        {
            index = i;
            break;
        }
    }
    return index;
}

int Add_Item(int id[], int quantity[], int item)
{
    int l = 0;
    int m = Find_Item(quantity, 0);
    int n = Find_Item(id, item);
    
    if (n != -1)
    {
        quantity[n] += 1;
        l = 1;
    }
    else
    {
        quantity[m] += 1;
        l = 1;
    }
    return l;
}

int Use_Item(int id[], int quantity[], int item)
{
    int a = 0;
    int b = Find_Item(id, item);
    
    if (b != -1)
    {
        if (quantity[b] > 0)
        {
            quantity[b] -= 1;
            a = 1;
        }
    }
    return a;
}

void Print_Item(int item)
{
    if (item == 0)
        printf("0 - Potion X");
    else if (item == 1)
        printf("1 - HP Booster X");
    else if (item == 2)
        printf("2 - Strength Booster X");
    else if (item == 3)
        printf("3 - Defense Booster X");
    else if (item == 4)
        printf("4 - Intelligence Booster X");
}

void getNewItem(int id[], int quantity[])
{
    srand((int)time(NULL));
    int item = getRandom();
    
    Add_Item(id, quantity, item);
}

void showInventory(int id[], int quantity[])
{
    int i;
    for (i = 0; i < SIZE; i++)
    {
        printf("%d. ", id[i]);
        Print_Item(id[i]);
        printf("%d\n", quantity[i]);
    }
}

void useItem(int id[], int quantity[])
{
    int itemId;
    int itemIndex;
    printf("Please input ID:");
    scanf("%d", &itemId);
    printf("\n");
    itemIndex = Find_Item(id, itemId);
    if ((itemIndex != -1)  && (quantity[itemIndex] > 0))
    {
        quantity[itemIndex] -= 1;
        printf("Item used!");
    }
    else
    {
        printf("You don't have that item!\n");
    }
}

int getRandom()
{
    int k = (MIN + rand() % (MAX + 1 - MIN));
    return k;
}