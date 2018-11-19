/*-----------------------------------------------------------------------------------------------*/
// Milestone 3
// milestone_3.c
// last edit = Jul 29, 11:55 PM
/*-----------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#define MIN_PLAYERS 1 // min/max number of players
#define MAX_PLAYERS 8
#define MIN_PRIZE 0 // min/max number of prizes
#define MAX_PRIZES 10
#define MIN_CHAR '!' // getValidChar parameters for player name ...might as well as expand the parameter limits
#define MAX_CHAR '~'
#define MIN_DICE 1 // users number of dice rolls
#define MAX_DICE 3
#define DICE_LOW 1 // min/max dice output/roll
#define DICE_HIGH 6
#define MIN_BOARD 3 // min/max number for board size
#define MAX_BOARD 10
#define WIN_PRIZE_MIN 10 // min/max regular prize parameters
#define WIN_PRIZE_MAX 100
#define GRAND_PRIZE_MIN 100 // min/max grand prize parameters
#define GRAND_PRIZE_MAX 200
/*-----------------------------------------------------------------------------------------------*/
struct Player { // 5 variables
    char name; // a single char as player's name
    int money; // player's current amount of money (score)
    int items; // number of inventory items, IS PRIZE COUNT from MS2
    int position;
    int prizes[MAX_PRIZES]; // 10
    int flag;
};
// MAIN FUNCTIONS
char mainMenu(); // printing of main menu option and getting input/choice
void resetPlayers(struct Player []); // resets every player stats
void resetPlayer(struct Player *); // resets only the player the function is called with
void initializePlayers(struct Player [], int *); // asks for number of players, resets all player stats, asks for player names
void initializeBoard(int *); // asks for the board size, asks for user input and validates the input
void displayInstructions(); // prints instructions for menu option 'r'
void displayHighScore(char, int); // displaying high score from the menu option 's'
void playGame(int, struct Player [], int, int);
// PLAY GAME FUNCTIONS
void displayBoard(int, struct Player [], int);
char getTileType(int, struct Player [], int );
void playerStatus(struct Player *); // prints the score of the players and the number of items
int playerRoll(struct Player *);
void calculatePosition(struct Player *, int, int);
void changePositions(struct Player [], int, int , int); // changes players position if they landed on top of another player
void stealPrize(struct Player [], int, int);
char getTile(struct Player *); // only returns "G" or "W" or "L" or "C", for the switch statement that decides which "action" to take
void winPrize(struct Player *); // "action"
void winGrandPrize(struct Player *); // "action"
int loseItem(struct Player *); // "action"
int checkout(struct Player *, int *); // "action"
// EXTRA FUNCTIONS
void clearBuffer();
int getRandom(int, int); // getting random numbers accounting/including the parameters
int getValidInt(int, int); // function to get a valid int input in between the parameters
char getValidChar(char, char); // function to get a valid char input in between the parameters
void removePlayer(struct Player [], int, int *);
/*-----------------------------------------------------------------------------------------------*/
int main()
{
    struct Player players[MAX_PLAYERS]; // 8 players
    int boardSize, i, boardMax, highScore = 100, game = 1, playerCount = 0;
    char userInput, highScorePlayer = ' ';
    
    printf("WELCOME TO CHECKOUT\n");
    do
    {
        userInput = mainMenu();
        
        switch (userInput)
        {
            case 'p':
            case 'P':
                resetPlayers(players);
                initializePlayers(players, &playerCount); // asks for number of players, resets all player stats, asks for player names
                initializeBoard(&boardSize); // asks for the board size, asks for user input and validates the input
                boardMax = (boardSize*4)-5; // calculates the last tile's number, which is the tile right before the first tile (tile 0)
                playGame(boardSize, players, playerCount, boardMax);
                
                for (i=0; i<playerCount; i++) // loop to check every players score, whoever has the highest will overwrite the highscore
                {
                    if (players[i].money > highScore)
                    {
                        highScore = players[i].money;
                        highScorePlayer = players[i].name;
                        //printf("\nYay new high score(%d), congrats '%c'!\n", highScore, highScorePlayer);
                        printf("\nYou are the god of t**s and wine '%c'! You are now richer ($%d.00 more) than a Lannister!\n", highScorePlayer, highScore); // GOT QUOTE
                    }
                }
                break;
                
            case 'q':
            case 'Q':
                //printf("This game is much more fun than bash...\n");
                printf("Time to check HBO GO now.\n");      // GOT QUOTES
                game = 0;
                break;
                
            case 'r':
            case 'R':
                displayInstructions();
                break;
                
            case 's':
            case 'S':
                displayHighScore(highScorePlayer, highScore);
                break;
                
            default:
                break;
        }
        
    } while (game != 0);
    
    printf("\nBuh bye now. But be warned, the night is dark and full of terrors.\n\n");     // GOT QUOTE
    
    return 0;
}
/*-----------------------------------------------------------------------------------------------*/
/*---------------------------------------- MAIN FUNCTIONS ---------------------------------------*/
/*-----------------------------------------------------------------------------------------------*/
// this function prints out the main menu option and gets the user input, then returns the validated input
char mainMenu() // CLEARLY SHOULD WORK
{
    char input;
    printf("\nMain Menu:\n");
    printf("p-(p)lay  |  q-(q)uit  |  r-inst(r)uctions  |  s-HI(s)core\n");
    //printf("Select: ");
    printf("Choose: ");     // GOT QUOTE
    input = getValidChar('p', 's');
    
    printf("\n");
    return input;
}
/*-----------------------------------------------------------------------------------------------*/
void resetPlayers(struct Player players[]) // resets every player stats
{
    for (int i=0; i<MAX_PLAYERS; i++)
    {
        players[i].name = ' ';
        players[i].items = 0;
        players[i].money = 0;
        players[i].position = 0;
        players[i].flag = 0;
        for (int k=0; i<MAX_PRIZES; i++)
        {
            players[i].prizes[k] = 0;
        }
    }
}
/*-----------------------------------------------------------------------------------------------*/
void resetPlayer(struct Player *player) // resets only the player the function is called with
{
    for (int i=0; i<MAX_PLAYERS; i++)
    {
        player->name = ' ';
        player->items = 0;
        player->money = 0;
        player->position = 0;
        for (int k=0; i<MAX_PRIZES; i++)
        {
            player->prizes[k] = 0;
        }
    }
}
/*-----------------------------------------------------------------------------------------------*/
// asks for the amount of players, resets all player stats, then asks for player names for the entered amount of players
void initializePlayers(struct Player players[], int *playerCount)
{
    //printf("Enter number of players: ");
    printf("Enter number of warriors of light: ");      // GOT QUOTE
    *playerCount = getValidInt(MIN_PLAYERS, MAX_PLAYERS);
    
    for (int i=0; i<*playerCount; i++)
    {
        //printf("Enter player ID: ");
        printf("Enter Soldier ID: ");       // GOT QUOTE
        
        players[i].name = getValidChar(MIN_CHAR, MAX_CHAR);
    }
}
/*-----------------------------------------------------------------------------------------------*/
// asks for the board size, asks for user input and validates the input
void initializeBoard(int *boardSize) // CLEARLY SHOULD WORK
{
    printf("\nEnter board size: ");
    *boardSize = getValidInt(MIN_BOARD, MAX_BOARD);
    
    printf("\n");
}
/*-----------------------------------------------------------------------------------------------*/
void displayInstructions() // CLEARLY SHOULD WORK
{
    printf("‘p’: to (p)lay the game\n");
    printf("‘q’: to (q)uit back to the terminal shell prompt\n");
    printf("‘r’: to show inst(r)uctions\n");
    printf("‘s’: to display high (s)core and the name of the player that earned the high score\n");
}
/*-----------------------------------------------------------------------------------------------*/
void displayHighScore(char playerName, int highScore) // CLEARLY SHOULD WORK
{
    printf("__\n");
    printf("  \\_______\n");
    printf("   \\++++++|\n");
    printf("    \\=====|\n");
    printf("     0--- 0\n\n");
    
    //printf("HI SCORE: %d  Player Name: %c\n", highScore, playerName);
    printf("Gold: %d  Warrior ID: %c\n", highScore, playerName);       // GOT QUOTE
}
/*-----------------------------------------------------------------------------------------------*/
/*-------------------------------------- PLAY GAME FUNCTIONS ------------------------------------*/
/*-----------------------------------------------------------------------------------------------*/
void playGame(int boardSize, struct Player players[], int playerCount, int boardMax)
{
    int endGame=2, dice=0, flag=0;
    
    do
    {
        for (int i=0; i<playerCount; i++)
        {
            if (players[i].flag == 1)
            {
                ;
            }
            else
            {
                displayBoard(boardSize, players, playerCount);
                
                //playerStatus(&players[i]); // printing of players score and items
                
                dice = playerRoll(&players[i]);
                
                calculatePosition(&players[i], dice, boardMax); // adjust the position according to current place
                
                changePositions(players, i, playerCount, boardMax);
                
                if (getTile(&players[i]) == 'G') // getTile returns 'C' 'G' 'W' 'L' or ' '
                {
                    winGrandPrize(&players[i]); // void, no return
                }
                else if (getTile(&players[i]) == 'W')
                {
                    winPrize(&players[i]); // void, no return
                }
                else if (getTile(&players[i]) == 'L')
                {
                    loseItem(&players[i]); // returns "random" item number if successful, "1" if no items were lost
                }
                else if (getTile(&players[i]) == 'C')
                {
                    endGame = checkout(&players[i], &flag); // returns "0" for regular, "1" for when player has more money/score than 200
                    players[i].position = boardMax+1;
                }
                else if (getTile(&players[i]) == ' ')
                {
                    //printf("Nothing happens.\n");
                    printf("HODOR....\n");      // GOT QUOTE
                }
            }
        }
        
    } while (flag<playerCount); // loop will go on until a player lands on checkout  // (endGame==2) && (flag!=playerCount)
}
/*-----------------------------------------------------------------------------------------------*/
void displayBoard(int boardSize, struct Player players[], int playerCount)
{
    int top, mid1, mid2, mid3, bottom, tileLeft=(boardSize*4-5), tileRight=boardSize, tileBottom=(boardSize*3-3);
    
    // topBoxes() function from MS2
    for (top=0; top<boardSize; top++)
        printf(" ___ ");
    printf("\n");
    
    for (top=0; top<boardSize; top++)
        printf("| %c |", getTileType(top, players, playerCount));
    printf("\n");
    
    for (top=0; top<boardSize; top++)
        printf("|___|");
    printf("\n");
    
    // middleBoxes() function from MS2
    for (mid1=0; mid1<boardSize-2; mid1++)
    {
        for (mid2=0; mid2<2; mid2++)
        {
            printf(" ___ ");
            for (mid3=0; mid3<boardSize-2; mid3++) // boxSpaces() function from MS2
                printf("     ");
        }
        printf("\n");
        
        printf("| %c |", getTileType(tileLeft, players, playerCount));
        tileLeft--;
        for (mid2=0; mid2<boardSize-2; mid2++) // boxSpaces()
            printf("     ");
        
        printf("| %c |", getTileType(tileRight, players, playerCount));
        tileRight++;
        for (mid2=0; mid2<boardSize-2; mid2++) // boxSpaces()
            printf("     ");
        printf("\n");
        
        for (mid2=0; mid2<2; mid2++)
        {
            printf("|___|");
            for (mid3=0; mid3<boardSize-2; mid3++) // boxSpaces()
                printf("     ");
        }
        printf("\n");
    }
    
    // bottomBoxes() function from MS2
    for (bottom=0; bottom<boardSize; bottom++)
        printf(" ___ ");
    printf("\n");
    
    for (bottom=0; bottom<boardSize; bottom++)
    {
        printf("| %c |", getTileType(tileBottom, players, playerCount));
        tileBottom--;
    }
    printf("\n");
    
    for (bottom=0; bottom<boardSize; bottom++)
        printf("|___|");
    printf("\n");
}
/*-----------------------------------------------------------------------------------------------*/
char getTileType(int index, struct Player players[], int playerCount)
{
    char k = ' ';
    
    for (int i=0; i<playerCount; i++)
    {
        if (index == players[i].position)
        {
            k = players[i].name;
            break;
        }
        else if (index == 0)
            k = 'C';
        
        else if (index%7 == 0)
            k = 'G';
        
        else if (index%5 == 0)
            k = 'L';
        
        else if (index%3 == 0)
            k = 'W';
        
        else
            k = ' ';
    }
    return k;
}
/*-----------------------------------------------------------------------------------------------*/
char getTile(struct Player *player)
{
    char k = ' ';
    
    if (player->position == 0)
        k = 'C';
    else if (player->position % 7 == 0)
        k = 'G';
    else if (player->position % 5 == 0)
        k = 'L';
    else if (player->position % 3 == 0)
        k = 'W';
    
    return k;
}
/*-----------------------------------------------------------------------------------------------*/
void playerStatus(struct Player *player)
{
    //printf("\n%c's Score: %d  |  Inventory: ", player->name, player->money);
    printf("\n%c's Gold: %d  |  Supplies: ", player->name, player->money);     // GOT QUOTES
    
    for (int i=0; i<MAX_PRIZES; i++)
    {
        if (player->prizes[i] > 0)
        {
            printf("%d", player->prizes[i]);
            if (player->prizes[i+1] > 0)
                printf(", ");
        }
    }
    printf(" (%d items)\n", player->items);
}
/*-----------------------------------------------------------------------------------------------*/
int playerRoll(struct Player *players) // SHOULD WORK
{
    int input=0, dice1=0, dice2=0, dice3=0, sum=0;
    
    //printf("\n%c's turn, how many dice will you roll: ", players->name);
    printf("\n%c's turn, how many heads will you try to roll: ", players->name);       // GOT QUOTE
    
    input = getValidInt(MIN_DICE, MAX_DICE);
    
    dice1 = getRandom(DICE_LOW, DICE_HIGH);
    dice2 = getRandom(DICE_LOW, DICE_HIGH);
    dice3 = getRandom(DICE_LOW, DICE_HIGH);
    
    //printf("You rolled: ");
    printf("Heads rolled: ");       // GOT QUOTE
    if (input==1)
    {
        printf("%d", dice1);
        sum = dice1;
    }
    else if (input==2)
    {
        printf("%d, %d", dice1, dice2);
        sum = dice1 + dice2;
    }
    else if (input==3)
    {
        printf("%d, %d, %d", dice1, dice2, dice3);
        sum = dice1 + dice2 + dice3;
    }
    else if (input==0)
    {
        printf("%d... DEBUGGING! Enter how much you want to advance: ", input);
        scanf(" %d", &sum);
    }
    else
    {
        printf("\nHow did you manage to break my getValidInt() .... ?\n");
    }
    //printf("\nAdvancing %d spaces\n\n", sum);
    printf("\nLong night is coming, better get a move on! Advancing %d spaces\n\n", sum);       // GOT QUOTE
    
    return sum;
}
/*-----------------------------------------------------------------------------------------------*/
void calculatePosition(struct Player *player, int dice, int boardMax)
{
    if ( (player->position + dice) > boardMax )
    {
        player->position = ((dice + player->position) % boardMax) - 1;
    }
    else
    {
        player->position += dice;
    }
}
/*-----------------------------------------------------------------------------------------------*/
void changePositions(struct Player players[], int current, int playerCount, int boardMax)
{
    for(int i=0; i<playerCount; i++)
    {
        if ( (players[current].position == players[i].position) && (current != i) )
        {
            stealPrize(players, current, i);
            if (players[current].position != 0)
                players[current].position -= 1;
            else
                players[current].position = boardMax;
        }
    }
}
/*-----------------------------------------------------------------------------------------------*/
void stealPrize(struct Player players[], int current, int other)
{
    if (players[other].items > 0) // if the other player does have items that can be stolen
    {
        int random = getRandom(MIN_PRIZE, players[other].items-1); // -1 cause total items & prizes arrays conflicts, ex: items=7 but 7th item is array[6]
        int value = players[other].prizes[random];
        
        //enemy (other) player's loss of item/prize:
        for (int i=random; i+1<MAX_PRIZES; i++)
            players[other].prizes[i] = players[other].prizes[i+1]; // prizes are shifted
        players[other].prizes[MAX_PRIZES-1] = 0;
        players[other].items -= 1;
        
        if (players[current].items < MAX_PRIZES) // if current player doenst have a maxed out inventory
        {
            //printf("You stode an item (%d) from '%c'\n", players[other].prizes[random], players[other].name);
            printf("A '%c' always pays his debts (%d gold).\n", players[other].name, players[other].prizes[random]);       // GOT QUOTE
            
            // (current) player's gain of item/prize:
            players[current].prizes[players[current].items] = value;
            players[current].items += 1;
        }
        else // when player doesnt have any inventory space for a new item
            //printf("You were unable to steam from %c\n", players[other].name);
            printf("You are '%c' and you will take what is yours, with fire and blood! Eventually...!\n", players[other].name);      // GOT QUOTE
    }
    else // if other player doesnt have any items to give
        //printf("You were unable to steam from %c\n", players[other].name);
        printf("'%c' doesn't have any supplies you can take. Poor lad won't last the winter...\n", players[other].name);      // GOT QUOTE
}
/*-----------------------------------------------------------------------------------------------*/
void winPrize(struct Player *players)
{
    int random = getRandom(WIN_PRIZE_MIN, WIN_PRIZE_MAX);
    
    if (players->items < MAX_PRIZES) // if players items/prizeCount is less than the max limit (10)
    {
        players->prizes[players->items] = random; // player's item number 'count' is now the randomly generated prize
        players->items += 1; // items/prizeCount is +1
        //printf("You won a prize of: %d\n", random);
        printf("Winter is coming. Better stock up! Here's an item: %d\n", random);      // GOT QUOTE
    }
    else // if the items/prizeCount is maxed out, that means there is not space for a new prize
        //printf("Inventory is full...\n");
        printf("Inventory is full. Shame...\n");      // GOT QUOTE
    
}
/*-----------------------------------------------------------------------------------------------*/
void winGrandPrize(struct Player *players)
{
    int random = getRandom(GRAND_PRIZE_MIN, GRAND_PRIZE_MAX);
    
    if (players->items < MAX_PRIZES)
    {
        players->prizes[players->items] = random;
        players->items += 1;
        //printf("You won a grand prize of: %d\n", random);
        printf("Your uncle has been stabbed to death. You just got your grand inheritance of %d gold\n", random);      // GOT QUOTE
        //printf("Lord of Light looks down upon you with favor... bla bla idk %d\n", random);      // GOT QUOTE
    }
    else
        //printf("Inventory is full...\n");
        printf("Inventory is full. Shame...\n");        // GOT QUOTE
}
/*-----------------------------------------------------------------------------------------------*/
int loseItem(struct Player *player)
{
    int random = 0;
    
    if (player->items > 0) // if the player has prizes in inventory (if they have more than 0 items)
    {
        random = getRandom(MIN_PRIZE, player->items-1); // -1 cause total items & prizes arrays conflicts, ex: items=7 but 7th item is array[6]
        player->items -= 1;
        //printf("You lost a prize valued at %d!\n", player->prizes[random]);
        printf("You spent %d gold on Littlefinger's whores. More wine...\n", player->prizes[random]);      // GOT QUOTE
        for (int i=random; i+1<MAX_PRIZES; i++)
            player->prizes[i] = player->prizes[i+1]; // player prizes are shifted
        player->prizes[MAX_PRIZES-1] = 0;
    }
    else
    {
        //printf("You dont have any prizes to lose...\n");
        printf("You dont have any supplies to lose. You poor lad...\n");      // GOT QUOTE
        random = 0; // JUST ADDED, CHECK LATER!!
    }
    return random;
}
/*-----------------------------------------------------------------------------------------------*/
int checkout(struct Player *player, int *flag)
{
    int scoreRate=0;
    for (int i=0; i<MAX_PRIZES; i++) // check the whole inventory of the player in question
    {
        if (player->prizes[i] > 0) // if the prize[i] is more than 0
            player->money += player->prizes[i]; // it add the amount to the players current amount of money/score
    }
    
    if (player->money >= 200) // if players money/score is bigger or equal to 200 scoreRate=1, if not it'll stay 0
        scoreRate=1;
    
    //printf("You checked out for $%d.00  |  Score is now: $%d.00\n\n", player->money, player->money);
    printf("When you play the game of thrones, you win or you die. Here are your funeral expenses: %d gold\n\n", player->money);  // GOT QUOTE
    
    player->flag = 1;
    *flag += 1;
    
    return scoreRate;
}
/*-----------------------------------------------------------------------------------------------*/
/*---------------------------------------- EXTRA FUNCTIONS --------------------------------------*/
/*-----------------------------------------------------------------------------------------------*/
void clearBuffer()
{
    while (getchar() != '\n')
        ;
}
/*-----------------------------------------------------------------------------------------------*/
int getRandom(int low, int high)
{
    //srand((int)time(NULL));
    int number = (low + rand() % (high + 1 - low));
    return number;
}
/*-----------------------------------------------------------------------------------------------*/
int getValidInt(int low, int high)
{
    int input;
    do
    {
        scanf(" %d", &input);
        
        if (input==0)
        {
            //printf("DEBUGGING!");
            break;
        }
        else if ( (input < low) || (input > high) )
        {
            printf("You know nothing. Try again: ");
            clearBuffer();
        }
        
    } while ( (input < low) || (input > high) );
    
    return input;
}
/*-----------------------------------------------------------------------------------------------*/
char getValidChar(char low, char high) // parameters are (p,s)  p,q,r,s           :{ LET SAY }:
{
    int number=0;
    char input=' ';
    
    while (number==0)
    {
        scanf(" %c", &input); // input is a
        
        if ((input < low) || (input > high)) // TRUE
        {
            char upper = toupper(input); // A
            char lower = tolower(input); // a
            if ((lower >= low) && (lower <= high)) // NOT TRUE
            {
                number=1; // number is still 0
            }
            else if ((upper >= low) && (upper <= high)) // NOT TRUE
            {
                number=2; // number still 0
            }
            else // TRUE
            {
                printf("You know nothing. Try again: ");
                clearBuffer();
            }
        }
        else
            number=1;
    }
    return input;
}
/*-----------------------------------------------------------------------------------------------*/