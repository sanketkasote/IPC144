/*--------------------------------------------------------------------------------------------------------------------------*/
// Milestone 1
// milestone_1.c
/*--------------------------------------------------------------------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
/*--------------------------------------------------------------------------------------------------------------------------*/
char getTileType(unsigned int);
void displayBoard(unsigned int);
void topBoxes(int);
void middleBoxes(int);
void boxSpaces(int);
void bottomBoxes(int);
/*--------------------------------------------------------------------------------------------------------------------------*/
int main(void)
{
    int s = 1;
    
    printf("--Program Start--\n\n");
    
    if (getTileType(153) != 'W')
        printf("153 should return W");
    
    else if (getTileType(65) != 'L')
        printf("65 should return L");
    
    else if (getTileType(49) != 'G')
        printf("49 should return G");
    
    else if (getTileType(0) != 'C')
        printf("0 should return C");
    
    else if (getTileType(105) != 'G')
        printf("105 should be G");
    
    else if (getTileType(79) != ' ')
        printf("79 should be space");
    
    else
    {
        printf("getTileType test passed!\nEnter board size: ");
        scanf("%d", &s);
        //printf("\n");
        displayBoard(s);
    }
    
    printf("\n\n--Program End--\n\n");
    
    return 0;
}
/*--------------------------------------------------------------------------------------------------------------------------*/
char getTileType(unsigned int index)
{
    char k;
    
    if (index == 0)
        k = 'C';
    
    else if (index % 7 == 0)
        k = 'G';
    
    else if (index % 5 == 0)
        k = 'L';
    
    else if (index % 3 == 0)
        k = 'W';
    
    else
        k = ' ';
    
    return k;
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void displayBoard(unsigned int size)
{
    topBoxes(size);
    if (size > 2) /* no middle boxes for less than board size 3 */
    {
        middleBoxes(size);
    }
    if (size > 1) /* no bottom boxes for board size 1 */
    {
        bottomBoxes(size);
    }
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void topBoxes(int size)
{
    int i;
    for (i = 0; i < size; i++) /* printing top parts of top boxes */
    {
        printf(" ___ ");
    }
    printf("\n");
    
    for (i = 0; i < size; i++) /* printing middle part with the tiles of top boxes */
    {
        printf("| %c |", getTileType(i));
    }
    printf("\n");
    
    for (i = 0; i < size; i++) /* printing bottom parts of top boxes */
    {
        printf("|___|");
    }
    printf("\n");
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void middleBoxes(int size)
{
    int i, r, minus = (size - 2), tileLeft = ((size * 4) - 5), tileRight = size; /* formula for the tile number calculation */
    
    for (r = 0; r < minus; r++) /* for loop for the # of rows */
    {
        for (i = 0; i < 2; i++) /* printing top parts of mid boxes */
        {
            printf(" ___ ");
            boxSpaces(minus); /* printing the space in the middle */
        }
        printf("\n");
        
        printf("| %c |", getTileType(tileLeft)); /* printing middle part of the LEFT box in middle */
        tileLeft--;
        boxSpaces(minus); /* printing the space in the middle */
        printf("| %c |", getTileType(tileRight)); /* printing middle part of the RIGHT box in middle */
        tileRight++;
        printf("\n");
        
        for (i = 0; i < 2; i++) /* printing bottom parts of middle boxes */
        {
            printf("|___|");
            boxSpaces(minus); /* printing the space in the middle */
        }
        printf("\n");
    }
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void boxSpaces(int times)  /* makes (size #) - 2 times of spacing */
{
    for (int i = 0; i < times; i++)
        printf("     "); /* makes the empty space inside the main big square */
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void bottomBoxes(int size) /* exactly the same as topBoxes() except for the tile in getTileType() */
{
    int i, tile = ((size * 3) - 3); /* formula for the tile number calculation */
    
    for (i = 0; i < size; i++) /* printing top parts of bottom boxes */
    {
        printf(" ___ ");
    }
    printf("\n");
    
    for (i = 0; i < size; i++) /* printing middle parts with tiles of bottom boxes */
    {
        printf("| %c |", getTileType(tile));
        tile--;
    }
    printf("\n");
    
    for (i = 0; i < size; i++) /* printing bottom parts of bottom boxes */
    {
        printf("|___|");
    }
    printf("\n");
}
/*--------------------------------------------------------------------------------------------------------------------------*/