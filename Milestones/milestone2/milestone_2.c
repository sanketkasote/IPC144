/*--------------------------------------------------------------------------------------------------------------------------*/
// Milestone 2
// milestone_2.c
// last edit = Jul 19, 6:48 PM
/* CURRENTLY A WORK IN PROGRESS DUE TO CLEARBUFFER ISSUES T_T  THOUGH WORKS AS LONG AS THE PLAYER/USER ENTERS ACCURATE INPUT */
/*--------------------------------------------------------------------------------------------------------------------------*/
//#include "scribble.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#define MIN_CHAR '@' // getValidChar parameters for player name
#define MAX_CHAR 'Z' // getValidChar parameters for player name
#define MIN_DICE 1 // users number of dice rolls
#define MAX_DICE 3 // users number of dice rolls
#define DICE_LOW 1 // min dice output/roll
#define DICE_HIGH 6 // max dice output/roll
#define MIN_PRIZE 0 // min number of prizes
#define SIZE 10 // max number of prizes
/*--------------------------------------------------------------------------------------------------------------------------*/
int getValidInt(int, int);
char getValidChar(char, char);
void initPlayer(int *, int [], unsigned int *, char *, int *);
void playGame(unsigned int, int *, int [], unsigned int *, char *, int *, int); // edited...added
char getDisplayTile(unsigned int, unsigned int, char);
void displayBoard(unsigned int, unsigned int, char);
int getRandom(int, int);
unsigned int playerRoll();
void winPrize(int [], unsigned int *);
void winGrandPrize(int [], unsigned int *);
int loseItem(int [], unsigned int *);
int checkout(int *, int [], unsigned int *);
// EXTRA FUNCTIONS
char mainMenu(); // printing of main menu option and getting input/choice
void topBoxes(int, unsigned int, char);
void middleBoxes(int, unsigned int, char);
void boxSpaces(int);
void bottomBoxes(int, unsigned int, char);
void menuDisplayHS(char, int); // displaying high score from the menu option 's'
char getTileType(unsigned int); // miletone 1 (old) version
void instructions(); // prints instructions for menu option 'r'
void clearBuffer();
/*--------------------------------------------------------------------------------------------------------------------------*/
int main()
{
    int boardMax, playerScore, playerPosition, highScore = 100, playerPrizes[SIZE]={0,0,0,0,0,0,0,0,0,0};
    unsigned int boardSize, prizeCount;
    char userInput, playerName, highScorePlayer = ' ';
    int game = 1;
    
    do
    {
        userInput = mainMenu();
        switch (userInput)
        {
            case 'p':
            case 'P':
                printf("number of players is 1\n"); // OUTPUT CHECKED(-OUT)!
                initPlayer(&playerScore, playerPrizes, &prizeCount, &playerName, &playerPosition);
                printf("Enter board size: "); // OUTPUT CHECKED(-OUT)!
                boardSize = getValidInt(3, 20); // IDK 20? even thats VERY big, imo it should also be at least 3
                // BUFF
                printf("\n");
                boardMax = (boardSize*4)-5;
                playGame(boardSize, &playerScore, playerPrizes, &prizeCount, &playerName, &playerPosition, boardMax);
                if (playerScore > highScore)
                {
                    printf("\nYay new high score, congrats buddy! %d -> %d\n\n", highScore, playerScore); //mine...extra
                    highScore = playerScore;
                    highScorePlayer = playerName;
                }
                break;
                
            case 'q':
            case 'Q':
                printf("This game is much more fun than bash...\n");
                game = 0;
                break;
                
            case 'r':
            case 'R':
                instructions();
                break;
                
            case 's':
            case 'S':
                menuDisplayHS(highScorePlayer, highScore);
                break;
        }
    } while (game != 0);
    /*(userInput == 'q') || (userInput == 'Q')   not sure why but the game kept ending after each invalid input so i added the variable int game = 1, and it works with this now*/
    printf("\nBuh Bye.\n\n"); //mine...extra
    
    return 0;
}
/*--------------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------- ASSIGNMENT FUNCTIONS --------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/
int getValidInt(int low, int high) // WORKS!
{
    int input;
    do
    {
        // BUFF - NOPE
        scanf(" %d", &input);
        // BUFF - NOPE
        
        if ( (input < low) || (input > high) )
        {
            //printf("DEBUG: INPUT=%d\n", input);
            printf("Invalid input, try again: "); // OUTPUT CHECKED(-OUT)!
            clearBuffer(); // BUFF
        }
        
    } while ( (input < low) || (input > high) );
    
    return input;
}
/*--------------------------------------------------------------------------------------------------------------------------*/
char getValidChar(char low, char high) // WORKS!
{
    int number = 0;
    char input;
    do
    {
        //BUFF - NOPE
        scanf(" %c", &input); // LETS SAY INPUT IS ' b '
        //BUFF - NOPE
        
        if ( input >= 'a' && input <= 'z') // if the entered input is in lowercase
        {
            if ((high >= 'A') && (high <= 'Z')) // and if the low-high parameters are uppercase letter
            {                                   // meaning the expected input is supposed to be upper case
                input = toupper(input); // it changes it lowercase input into uppercase
                number = 1; // NUMBER IS 1
                //BUFF
            }
            else // or if the low-high parameters are in face lower case as well
            {
                number = 3; // the input wont be changed into uppercase and NUMBER WILL BE 3
                //BUFF
            }
            clearBuffer(); //BUFF
        }
        
        else if ( input >= 'A' && input <= 'Z' )
        {
            if ((high >= 'a') && (high <= 'z'))
            {
                input = tolower(input);
                number = 2;
                //BUFF
            }
            else
            {
                number = 3;
                //BUFF
            }
            clearBuffer(); //BUFF
        }
        
        else if (low < 'A') //!(high=='z' || high=='Z')
            if (input < 'A') // @ for the character name choice as an exception
            {
                number = 4; // even though number='4' isnt necessary, just in case number=3 will be something later on
                clearBuffer(); //BUFF
            }
        
        if ( (input < low) || (input > high) ) // once the input is changed so it can pass this statement
        {
            //printf("DEBUG: INPUT=%c\n", input);
            printf("Invalid input, try again: "); // OUTPUT CHECKED(-OUT)!
            number = 0;
            clearBuffer(); //BUFF
        }
        //BUFF - NOPE
    } while (number == 0);
    
    if (number == 1) // is the parameters are lowercase a-z, the number=1 that happened when the input was changed into
        input = tolower(input); // uppercase will change back into lowercase letter in here
    else if (number == 2)
        input = toupper(input);
    
    return input;
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void playGame(unsigned int boardSize, int *playerScore, int playerPrizes[], unsigned int *prizeCount, char *playerName, int *playerPosition, int boardMax) // FINALLY WORKS!
{
    int endGame = 2, dice = 0;
    char tile;
    do
    {
        displayBoard(boardSize, *playerPosition, *playerName);
        printf("\nScore: %d  |  Inventory: ", *playerScore); // OUTPUT CHECKED(-OUT)!
        for (int i = 0; i < SIZE; i++)
        {
            if (playerPrizes[i] > 0)
            {
                printf("%d", playerPrizes[i]);
                if (playerPrizes[i+1] > 0)
                    printf(", ");
            }
        }
        printf(" (%d items)\n", *prizeCount);
        // BUFF  -  NOPE
        dice = playerRoll();
        
        if ((*playerPosition + dice) > boardMax)
            *playerPosition = ((dice + *playerPosition) % boardMax) - 1;
        else
            *playerPosition += dice;
        
        tile = getTileType(*playerPosition);
        //printf("DEBUG: POSITION=%d\n", *playerPosition);
        switch (tile)
        {
            case 'G':
                winGrandPrize(playerPrizes, prizeCount);
                break;
            case 'W':
                winPrize(playerPrizes, prizeCount);
                break;
            case 'L':
                loseItem(playerPrizes, prizeCount);
                break;
            case 'C':
                endGame = checkout(playerScore, playerPrizes, prizeCount);
                break;
            default:
                printf("... Awww nothing happens, go again...\n"); // OUTPUT CHECKED(-OUT)! 
                break;
        }
        clearBuffer(); // DEFINITELY KEEP IT, NEEDED FOR AFTER CHECKOUT
    } while (endGame == 2);
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void initPlayer(int *playerScore, int playerPrizes[], unsigned int *prizeCount, char *playerName, int *playerPosition) // WORKS!
{
    *playerScore = 0;
    for (int i = 0; i < SIZE; i++)
        playerPrizes[i] = 0;
    *prizeCount = 0;
    *playerPosition = 0;
    
    printf("Enter player ID: "); // OUTPUT CHECKED(-OUT)! 
    // BUFF - NOPE
    *playerName = getValidChar(MIN_CHAR, MAX_CHAR);
    // BUFF - NOPE
}
/*--------------------------------------------------------------------------------------------------------------------------*/
char getDisplayTile(unsigned int index, unsigned int playerPosition, char playerName) // SHOULD WORK FINE
{
    char k;
    if (index == playerPosition)
        k = playerName;
    else if (index == 0)
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
void displayBoard(unsigned int size, unsigned int playerPosition, char playerName) // SHOULD WORK FINE
{
    topBoxes(size, playerPosition, playerName);
    if (size > 2) /* no middle boxes for less than board size 3 */
    {
        middleBoxes(size, playerPosition, playerName);
    }
    if (size > 1) /* no bottom boxes for board size 1 */
    {
        bottomBoxes(size, playerPosition, playerName);
    }
}
/*--------------------------------------------------------------------------------------------------------------------------*/
int getRandom(int low, int high) // WORKS!
{
    srand((int)time(NULL));
    int n = (low + rand() % (high + 1 - low));
    return n;
}
/*--------------------------------------------------------------------------------------------------------------------------*/
unsigned int playerRoll() // WORKS!
{
    int input = 0, a = 0, b = 0, c = 0, sum = 0;
    
    printf("\nYour turn, how many dice will you roll? (1-3) : "); // OUTPUT CHECKED(-OUT)! 
    // BUFF - NOPE
    input = getValidInt(MIN_DICE, MAX_DICE);
    // BUFF - NOPE
    
    a = getRandom(DICE_LOW,DICE_HIGH);
    b = getRandom(DICE_LOW,DICE_HIGH);
    c = getRandom(DICE_LOW,DICE_HIGH);
    
    printf("You rolled: "); // OUTPUT CHECKED(-OUT)! 
    if (input == 1)
    {
        printf("%d", a);
        sum = a;
    }
    else if (input == 2)
    {
        printf("%d, %d", a, b);
        sum = a + b;
    }
    else if (input == 3)
    {
        printf("%d, %d, %d", a, b, c);
        sum = a + b + c;
    }
    
    printf("\nAdvancing %d spaces\n\n", sum); // OUTPUT CHECKED(-OUT)! 
    return sum;
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void winPrize(int playerPrizes[], unsigned int *prizeCount) // SHOULD WORK FINE
{
    int random = getRandom(10, 100);
    
    if (*prizeCount < SIZE)
    {
        playerPrizes[*prizeCount] = random;
        *prizeCount += 1;
        printf("You won a prize of: %d", random); // OUTPUT CHECKED(-OUT)! 
    }
    else
    {
        printf("Inventory is full..."); // CHECK OUTPUT
    }
    printf("\n");
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void winGrandPrize(int playerPrizes[], unsigned int *prizeCount) // SHOULD WORK FINE
{
    int prize = getRandom(100, 200);
    
    if (*prizeCount < SIZE)
    {
        playerPrizes[*prizeCount] = prize;
        *prizeCount += 1;
        printf("You won a grand prize of: %d\n", prize); // OUTPUT CHECKED(-OUT)! 
    }
    else
    {
        printf("Inventory is full...\n"); // CHECK OUTPUT
    }
}
/*--------------------------------------------------------------------------------------------------------------------------*/
int loseItem(int playerPrizes[], unsigned int *prizeCount) // SHOULD WORK FINE
{
    int random;
    printf("loseitem;..dagh\n");
    
    random = getRandom(MIN_PRIZE, *prizeCount);
    
    if (*prizeCount > 0)
    {
        *prizeCount -= 1;
        printf("You lost a prize valued at %d!\n", playerPrizes[random]); // OUTPUT CHECKED(-OUT)! 
        for (int i = random; i+1 < SIZE; i++)
        {
            playerPrizes[i] = playerPrizes[i+1]; //playerPrize[random] = is replaced by playerPrize[random+1]
        }
        playerPrizes[SIZE-1] = 0;
    }
    else
    {
        printf("You dont have any prizes to lose...\n");
    }
    return random;
}
/*--------------------------------------------------------------------------------------------------------------------------*/
int checkout(int *playerScore, int playerPrizes[], unsigned int *prizeCount)
{
    int scoreRate = 0;
    for (int i = 0; i < SIZE; i++)
    {
        if (playerPrizes[i] > 0)
        {
            *playerScore += playerPrizes[i];
        }
        /*playerPrizes[i] = 0;*/  // not needed, initPlayer() does it
    }
    *prizeCount = 0;
    
    if (*playerScore >= 200)
    {
        scoreRate = 1;
    }
    printf("You checked out for $%d.00  |  score is now: $%d.00\n\n", *playerScore, *playerScore); // THIS IS INCORRECT
    return scoreRate;
}
/*--------------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------- EXTRA FUNCTIONS ----------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------------*/
char mainMenu() // WORKS!
{
    char input;
    printf("\nMain Menu:\n");
    printf("p-(p)lay  |  q-(q)uit  |  r-inst(r)uctions  |  s-HI(s)core\n");
    printf("Select: ");
    input = getValidChar('p', 's');
    // BUFF
    printf("\n");
    return input;
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void topBoxes(int size, unsigned int playerPosition, char playerName) // WORKS!
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf(" ___ ");
    }
    printf("\n");
    
    for (i = 0; i < size; i++)
    {
        printf("| %c |", getDisplayTile(i, playerPosition, playerName));
    }
    printf("\n");
    
    for (i = 0; i < size; i++)
    {
        printf("|___|");
    }
    printf("\n");
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void middleBoxes(int size, unsigned int playerPosition, char playerName) // WORKS!
{
    int i, r, minus = (size - 2), tileLeft = ((size * 4) - 5), tileRight = size; /* formula for the tile number calculation */
    
    for (r = 0; r < minus; r++) /* for loop for the # of rows */
    {
        for (i = 0; i < 2; i++)
        {
            printf(" ___ ");
            boxSpaces(minus);
        }
        printf("\n");
        
        printf("| %c |", getDisplayTile(tileLeft, playerPosition, playerName)); /* printing middle part of the LEFT box in middle */
        tileLeft--;
        boxSpaces(minus);
        printf("| %c |", getDisplayTile(tileRight, playerPosition, playerName)); /* printing middle part of the RIGHT box in middle */
        tileRight++;
        printf("\n");
        
        for (i = 0; i < 2; i++)
        {
            printf("|___|");
            boxSpaces(minus);
        }
        printf("\n");
    }
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void boxSpaces(int times)  // WORKS!
{
    for (int i = 0; i < times; i++)
        printf("     "); /* makes the empty space inside the main big square */
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void bottomBoxes(int size, unsigned int playerPosition, char playerName) // WORKS!
{
    int i, tile = ((size * 3) - 3); /* formula for the tile number calculation */
    
    for (i = 0; i < size; i++)
    {
        printf(" ___ ");
    }
    printf("\n");
    
    for (i = 0; i < size; i++)
    {
        printf("| %c |", getDisplayTile(tile, playerPosition, playerName));
        tile--;
    }
    printf("\n");
    
    for (i = 0; i < size; i++)
    {
        printf("|___|");
    }
    printf("\n");
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void menuDisplayHS (char playerName, int highScore) // WORKS!
{
    printf("__\n");
    printf("  \\_______\n");
    printf("   \\++++++|\n");
    printf("    \\=====|\n");
    printf("     0--- 0\n\n");
    
    printf("HI SCORE: %d  Player Name: %c\n\n", highScore, playerName);
}
/*--------------------------------------------------------------------------------------------------------------------------*/
char getTileType(unsigned int index) // WORKS!
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
void instructions()
{
    printf("‘p’: to (p)lay the game\n");
    printf("‘q’: to (q)uit back to the terminal shell prompt\n");
    printf("‘r’: to show inst(r)uctions\n");
    printf("‘s’: to display high (s)core and the name of the player that earned the high score\n\n");
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void clearBuffer()
{
    while (getchar() != '\n')
        ;
}
/*--------------------------------------------------------------------------------------------------------------------------*/