/*-----------------------------------------------------------------------------------------------*/
// Milestone 4
// milestone_4.c
// Last Edit: Aug 3, 7:57 PM
/*-----------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#define NAME 35
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
struct Player{ // 5
    char name[NAME]; // 34+1 =35
    char id; // a single char as player's name on board
    int money; // player's current amount of money (score)
    int items; // number of inventory items, IS PRIZE COUNT from MS2
    int position;
    int prizes[MAX_PRIZES]; // 10
    int flag;
};
// ASSIGNMENT FUNCTIONS
void displayInstructions();
void addToLeaderboard (int, struct Player *);
void displayHighestScore();
// MAIN FUNCTIONS
char mainMenu();
void resetPlayers(struct Player [], struct Player *);
void resetPlayer(struct Player *);
void initializePlayers(struct Player [], int *);
void initializeBoard(int *, int *);
void whosTheWinner(struct Player [], struct Player *, int);
// PLAY GAME FUNCTIONS
void playGame(int, struct Player [], int, int);
void displayBoard(int, struct Player [], int);
char getTileType(int, struct Player [], int);
char tileAction(struct Player *);
void playerStatus(struct Player *);
int playerRoll(struct Player *);
void calculatePosition(struct Player *, int, int);
void changePositions(struct Player [], int, int, int);
void stealPrize(struct Player [], int, int);
void winPrize(struct Player *);
void winGrandPrize(struct Player *);
int loseItem(struct Player *);
int checkout(struct Player *, int *);
// EXTRA FUNCTIONS
void clearBuffer();
int getRandom(int, int);
int getValidInt(int, int);
char getValidChar(char, char);
/*-----------------------------------------------------------------------------------------------*/
int main()
{
    struct Player players[MAX_PLAYERS];
    struct Player winner;
    int endGame=1, game=0, playerCount=0, boardSize=0, boardMax=0;
    char userInput;
    winner.money=100;
    winner.id=' ';
    
    printf("WELCOME TO CHECKOUT\n\n");
    
    do
    {
        userInput = mainMenu();
        printf("\n");
        
        switch (userInput)
        {
            case 'p':
            case 'P':
                resetPlayers(players, &winner);
                initializePlayers(players, &playerCount);
                printf("\n");
                initializeBoard(&boardSize, &boardMax);
                printf("\n");
                playGame(boardSize, players, playerCount, boardMax);
                game++;
                whosTheWinner(players, &winner, playerCount);
                addToLeaderboard(game, &winner);
                break;
                
            case 'q':
            case 'Q':
                printf("This game is much more fun than bash...\n");
                endGame = 0;
                break;
                
            case 'r':
            case 'R':
                displayInstructions();
                break;
                
            case 's':
            case 'S':
                displayHighestScore();
                break;
                
            default:
                break;
        }
        
    } while (endGame != 0);
    
    printf("\nBuh bye now. But be warned, the night is dark and full of terrors.\n\n");     // GOT QUOTE
    
    return 0;
}
/*-----------------------------------------------------------------------------------------------*/
/*---------------------------------------- MAIN FUNCTIONS ---------------------------------------*/
/*-----------------------------------------------------------------------------------------------*/
char mainMenu() // prints out the main menu options & gets user input, returns the validated input
{
    char input;
    printf("\nMain Menu:\n");
    printf("p-(p)lay  |  q-(q)uit  |  r-inst(r)uctions  |  s-HI(s)core\n");
    printf("Select: ");
    input = getValidChar('p', 's');
    return input;
}
/*-----------------------------------------------------------------------------------------------*/
void resetPlayers(struct Player players[], struct Player *winner)
{
    for (int i=0; i<MAX_PLAYERS; i++)
    {
        players[i].flag = 0;
        players[i].id = ' ';
        players[i].items = 0;
        players[i].money = 0;
        players[i].position = 0;
        strcpy(players[i].name, " ");
        //for (int j=0; j<NAME; j++)
            //players[i].name[j] = ' ';
        for (int k=0; k<MAX_PRIZES; k++)
            players[i].prizes[k] = 0;
    }
    winner->id = ' ';
    winner->money = 0;
    strcpy(winner->name, " ");
    //for (int l=0; l<NAME; l++)
        //winner->name[l] = ' ';
    
}
/*-----------------------------------------------------------------------------------------------*/
void resetPlayer(struct Player *player)
{
    for (int i=0; i<MAX_PLAYERS; i++)
    {
        player->flag = 0;
        player->id = ' ';
        player->money = 0;
        player->position = 0;
        player->items = 0;
        strcpy(player->name, " ");
        //for (int j=0; j<NAME; j++)  // is this accurate? anything/nothing about '\0'?
            //player->name[j] = ' ';
        for (int k=0; k<MAX_PRIZES; k++)
            player->prizes[k] = 0;
    }
}
/*-----------------------------------------------------------------------------------------------*/
void initializePlayers(struct Player players[], int *playerCount)
{
    printf("Enter number of players: ");
    *playerCount = getValidInt(MIN_PLAYERS, MAX_PLAYERS);
    
    for (int i=0; i<*playerCount; i++)
    {
        printf("Enter player name: ");
        scanf(" %[^\n]s", players[i].name);
        
        printf("Enter player ID: ");
        players[i].id = getValidChar(MIN_CHAR, MAX_CHAR);
    }
}
/*-----------------------------------------------------------------------------------------------*/
void initializeBoard(int *boardSize, int *boardMax)
{
    printf("Enter board size: ");
    *boardSize = getValidInt(MIN_BOARD, MAX_BOARD);
    *boardMax = ((*boardSize*4)-5);
}
/*-----------------------------------------------------------------------------------------------*/
void whosTheWinner(struct Player players[], struct Player *winner, int playerCount)
{
    for (int i=0; i<playerCount; i++)
    {
        if (players[i].money > winner->money)
        {
            winner->money = players[i].money;
            winner->id = players[i].id;
            strcpy(winner->name, players[i].name);
        }
    }
}
/*-----------------------------------------------------------------------------------------------*/
void displayInstructions()
{
    
    printf("*******************\n");
    printf("* Full Game Rules *\n");
    printf("*******************\n");
    printf("Up to 8 players compete to be the first to obtain $500\n");
    printf("Game takes place on a square board with 5 tile types\n");
    printf("->Empty Tile: No effect\n");
    printf("->Win Tile (W): Win a random prize\n");
    printf("->Lose Tile (L): Lose a random prize\n");
    printf("->Grand Prize Tile (G): Win a grand prize\n");
    printf("->Checkout Tile (C): Sells all your prizes for cash\n");
    printf("Players can roll 1 - 3 dice to determine how many tiles they move each turn\n");
    printf("If a player lands on the same tile as another player, that player steals a prize and moves 1 tile back\n");
}
/*-----------------------------------------------------------------------------------------------*/
void addToLeaderboard (int game, struct Player *winner)
{
    FILE *file = fopen("Leaderboard.dat", "a");
    
    if (file != NULL)
    {
        fprintf(file, "GAME:%d %s(%c)-%d\n", game, winner->name, winner->id, winner->money);
        fclose(file);
    }
    else
    {
        printf("File not available!\n");
    }
}
/*-----------------------------------------------------------------------------------------------*/
void displayHighestScore()
{
    int game, score=0;
    struct Player player;
    struct Player highest;
    //printf("**DEBUG! ENTER DISPLAYHIGHESTSCORE()**\n");
    FILE *file = fopen("Leaderboard.dat", "r");
    //printf("**DEBUG! FOPEN(LEADERBOARD.DAT)**\n");
    if (file != NULL)
    {
        //printf("**DEBUG! FILE != NULL**\n");
        while (fscanf(file, "GAME:%d %[^(](%c)-%d\n", &game, player.name, &player.id, &player.money) != EOF)
        {
            //printf("**DEBUG! ENTER WHILE LOOP**\n");
            
            if (player.money > score)
            {
                //printf("**DEBUG! PLAYER.MONEY > SCORE YAY!**\n");
                score = player.money;
                strcpy(highest.name, player.name);
                highest.id = player.id;
                highest.money = player.money;
            }
        }
        
        //printf("**DEBUG! WHILE LOOP ENDS!**\n");
        fclose(file);
        //printf("**DEBUG! FCLOSE(FILE)**\n");
        
        printf("************************\n");
        printf("Player With the Highest Score\n");
        printf("************************\n");
        printf("Player Name\tID\tScore\n");
        printf("%s\t(%c)\t$%d\n\n", highest.name, highest.id, highest.money);
    }
    else
    {
        printf("No data available!\n");
    }
}
/*-----------------------------------------------------------------------------------------------*/
/*-------------------------------------- PLAY GAME FUNCTIONS ------------------------------------*/
/*-----------------------------------------------------------------------------------------------*/
void playGame(int boardSize, struct Player players[], int playerCount, int boardMax)
{
    int endGame=2, dice=0, flag=0, position;
    char tile;
    
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
                printf("\n");
                playerStatus(&players[i]);
                printf("\n");
                position = players[i].position; // position will have the value of the players position before it moves
                dice = playerRoll(&players[i]);
                //printf("\n");
                calculatePosition(&players[i], dice, boardMax); // adjust the position according to current place
                changePositions(players, i, playerCount, boardMax);
                printf("\n");
                
                if (players[i].position != position) // if players position is NOT as same as its original position before the dice rolling and moving around
                {
                    tile = tileAction(&players[i]);
                    
                    switch (tile)
                    {
                        case 'G':
                            winGrandPrize(&players[i]); // void, no return
                            break;
                            
                        case 'W':
                            winPrize(&players[i]); // void, no return
                            break;
                            
                        case 'L':
                            loseItem(&players[i]); // returns "random" item number if successful, "1" if no items were lost
                            break;
                            
                        case 'C':
                            endGame = checkout(&players[i], &flag); // returns "0" for regular, "1" for when player has more money/score than 200
                            players[i].position = boardMax+1; // take player off board
                            break;
                            
                        default:
                            printf("You do nothing.\n");
                            break;
                    }
                }
                else
                    printf("You do nothing...\n");
                
                playerStatus(&players[i]);
                printf("\n");
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
            k = players[i].id;
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
char tileAction(struct Player *player)
{
    char k=' ';
    
    if (player->position == 0)
        k='C';
    else if (player->position % 7 == 0)
        k='G';
    else if (player->position % 5 == 0)
        k='L';
    else if (player->position % 3 == 0)
        k='W';
    
    return k;
}
/*-----------------------------------------------------------------------------------------------*/
void playerStatus(struct Player *player)
{
    printf("%s's (%c) Score: %d  |  Items:", player->name, player->id, player->money);
    for (int i=0; i<player->items; i++)
    {
        if (player->prizes > 0)
        {
            printf(" %d", player->prizes[i]);
            if (player->prizes[i+1] > 0)
                printf(",");
        }
    }
    printf(" (%d items)", player->items);
}
/*-----------------------------------------------------------------------------------------------*/
int playerRoll(struct Player *players)
{
    int input=0, dice1=0, dice2=0, dice3=0, sum=0;
    
    printf("%s's (%c) turn, how many dice will you roll: ", players->name, players->id);
    
    input = getValidInt(MIN_DICE, MAX_DICE);
    
    dice1 = getRandom(DICE_LOW, DICE_HIGH);
    dice2 = getRandom(DICE_LOW, DICE_HIGH);
    dice3 = getRandom(DICE_LOW, DICE_HIGH);
    
    printf("You rolled: ");
    if (input==1)
    {
        sum = dice1;
        printf("%d", dice1);
    }
    else if (input==2)
    {
        sum = dice1 + dice2;
        printf("%d, %d", dice1, dice2);
    }
    else if (input==3)
    {
        sum = dice1 + dice2 + dice3;
        printf("%d, %d, %d", dice1, dice2, dice3);
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
    printf("\nAdvancing %d spaces", sum);
    
    return sum;
}
/*-----------------------------------------------------------------------------------------------*/
void calculatePosition(struct Player *player, int dice, int boardMax)
{
    if ( (player->position + dice) > boardMax ) // if players current position plus dice is bigger than the last tile on board
    {
        player->position = ((dice + player->position) % boardMax) - 1; // calculate so that player goes on another turn on board
    }
    else // else just add the dice roll to the players current position
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
    int random=0, value=0;
    
    if (players[other].items > 0) // if the other player has items
    {
        do
        {
            random = getRandom(MIN_PRIZE, players[other].items-1); // -1 cause total items & prizes arrays conflicts, ex: items=7 but 7th item is array[6]
        } while (players[other].prizes[random]==0); // just in case theres a bug and random's value happens to be 0
        
        value = players[other].prizes[random]; // value is the value of the prize thats loss, and possibly stolen
        
        //enemy (other) player's loss of item/prize:
        players[other].prizes[random] = players[other].prizes[players[other].items-1]; // INSTEAD OF SHIFTING PLAYERS INVENTORY, REPLACE THE LOST ITEM ARRAY WITH THE LAST PRIZE
        /*for (int i=random; i<players[other].items; i++) // for i=random, while random is smaller than the inventory
         players[other].prizes[i] = players[other].prizes[i+1];*/
        
        players[other].items -= 1; // other players item count is decremented
        players[other].money -= value; // other players score is decreased by the item value thats lost
        
        // (current) player's gain of item/prize:
        if (players[current].items < MAX_PRIZES) // if current player doenst have a maxed out inventory
        {
            printf("You stole an item (%d) from '%c'", value, players[other].id);
            
            // (current) player's gain of item/prize:
            players[current].prizes[players[current].items] = players[other].prizes[random];
            players[current].money += value; // current players score is increased by the gained item value
            players[current].items += 1;
        }
        else // when player doesnt have any inventory space for a new item
            printf("You were unable to steal from %c\n", players[other].id);
    }
    
    else // if other player doesnt have any items to give
        printf("You were unable to steal from %c\n", players[other].id);
}
/*-----------------------------------------------------------------------------------------------*/
void winPrize(struct Player *players)
{
    int random = getRandom(WIN_PRIZE_MIN, WIN_PRIZE_MAX); // 10-100
    
    if (players->items < MAX_PRIZES) // if players items/prizeCount is less than the max limit (10)
    {
        players->prizes[players->items] = random; // player's item number 'count' is now the randomly generated prize
        players->items += 1; // items/prizeCount is +1
        printf("You won a prize valued at $%d\n", random);
        players->money += random; // players money/score is increased by the gained prize amount
    }
    else // if the items/prizeCount is maxed out, that means there is not space for a new prize
        printf("Inventory is full...\n");
    
}
/*-----------------------------------------------------------------------------------------------*/
void winGrandPrize(struct Player *players)
{
    int random = getRandom(GRAND_PRIZE_MIN, GRAND_PRIZE_MAX); // 100-200
    
    if (players->items < MAX_PRIZES)
    {
        players->prizes[players->items] = random;
        players->items += 1;
        printf("You won a grand prize valued at $%d\n", random);
        players->money += random; // players money/score is increased by the gained prize amount
    }
    else
        printf("Inventory is full...\n");
}
/*-----------------------------------------------------------------------------------------------*/
int loseItem(struct Player *player)
{
    int random=0;
    
    if (player->items > 0) // if the player has prizes in inventory (if they have more than 0 items)
    {
        do
        {
            random = getRandom(MIN_PRIZE, player->items-1); // -1 cause total items & prizes arrays conflicts, ex: items=7 but 7th item is array[6]
        } while (player->prizes[random]==0); // just in case theres a bug and random's value happens to be 0
        
        printf("You lost a prize valued at $%d\n", player->prizes[random]);
        
        player->money -= player->prizes[random]; // players money/score is decreased by the lost prizes value
        
        // INSTEAD OF SHIFTING:
        player->prizes[random] = player->prizes[player->items-1]; // the lost item is replaced with the last item on the inventory
        
        /*for (int i=random; i+1<MAX_PRIZES; i++)
         player->prizes[i] = player->prizes[i+1]; // player prizes are shifted
         player->prizes[MAX_PRIZES-1] = 0;*/
        
        player->items -= 1;
        
    }
    else
    {
        printf("You dont have any prizes to lose...\n");
        random = 0; // JUST ADDED, CHECK LATER!!
    }
    return random;
}
/*-----------------------------------------------------------------------------------------------*/
int checkout(struct Player *player, int *flag)
{
    int scoreRate=0;
    /*for (int i=0; i<MAX_PRIZES; i++) // check the whole inventory of the player in question
     {
     if (player->prizes[i] > 0) // if the prize[i] is more than 0
     player->money += player->prizes[i]; // it add the amount to the players current amount of money/score
     }*/
    
    if (player->money >= 200) // if players money/score is bigger or equal to 200 scoreRate=1, if not it'll stay 0
        scoreRate=1;
    
    printf("__\n");
    printf("  \\_______\n");
    printf("   \\++++++|\n");
    printf("    \\=====|\n");
    printf("     0--- 0\n\n");
    printf("%s (%d) checked out for $%d\n\n", player->name, player->id, player->money);
    
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
        
        if ((input==0) && ((low==1)&&(high==3))) // if statement will only apply for when func is called for valid dice amount
            break;
        
        else if ( (input < low) || (input > high) )
        {
            printf("You know nothing. Try again: ");
            clearBuffer();
        }
        
    } while ( (input < low) || (input > high) );
    
    return input;
}
/*-----------------------------------------------------------------------------------------------*/
char getValidChar(char low, char high)
{
    int number=0;
    char input=' ';
    
    while (number==0)
    {
        scanf(" %c", &input);
        
        if ((input < low) || (input > high))
        {
            char upper = toupper(input);
            char lower = tolower(input);
            if ((lower >= low) && (lower <= high))
            {
                number=1;
            }
            else if ((upper >= low) && (upper <= high))
            {
                number=2;
            }
            else
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