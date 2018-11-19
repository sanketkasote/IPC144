/*--------------------------------------------------------------------------------------------------------------------------*/
// Code Quest Workshop 4
// codequest_w4.c
/*--------------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
/*--------------------------------------------------------------------------------------------------------------------------*/
void clearScreen();
void welcome(void);
void menu(void);
int validate(int low, int high);
void newGame();
void load();
void goodbye(void);
/*--------------------------------------------------------------------------------------------------------------------------*/
int main(void)
{
    int userChoice;
    
    clearScreen();
    
    welcome();
    
    menu();
    
    while ((userChoice = validate(0, 3)) != 3) // while userChoice is not 3
    {
        if (userChoice == 0) // welcome message is displayed
        {
            welcome();
        }
        else if (userChoice == 1) // user is promted again for input with validate while new game isnt implemented
        {
            newGame();
        }
        else if (userChoice == 2) // user is promted again for input with validate while load isnt implemented
        {
            load();
        }
    }
    
    goodbye();
    
    return 0;
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void clearScreen()
{
    for (int i = 0; i <= 40; i++)
    {
        printf("\n");
    }
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void welcome(void)
{
    printf("\nWelcome!\n");
    printf("Bienvenue!\n"); //french
    printf("Benvenuto!\n"); //italian
    printf("Bienvenido!\n"); //spanish
    printf("Willkommen!\n"); //german
    printf("Welina!\n"); //hawaian
    printf("欢迎!\n\n"); // chinese
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void menu(void)
{
    printf("--Main Menu--\n\n");
    
    printf("0 - Welcome\n");
    printf("1- New Game\n");
    printf("2 - Load Game\n");
    printf("3 - Exit\n\n");
}
/*--------------------------------------------------------------------------------------------------------------------------*/
int validate(int low, int high)
{
    int userInput;
    
    printf("Select: ");
    scanf(" %d", &userInput);
    while ((userInput < low) || (userInput > high))
    {
        printf("\nInvalid input, try again: ");
        scanf(" %d", &userInput);
    }
    return userInput;
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void newGame()
{
    printf("\nNot Implemented!\n\n");
    menu();
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void load()
{
    printf("\nNot Implemented!\n\n");
    menu();
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void goodbye(void)
{
    printf("\nGoodbye!\n");
    printf("Au Revoir!\n"); //fr
    printf("Arrivederci!\n"); //it
    printf("Adiós!\n"); //sp
    printf("Auf Wiedersehen!\n"); //ger
    printf("A hui hou!\n"); //hawa
    printf("再见!\n\n"); //chin
}
/*--------------------------------------------------------------------------------------------------------------------------*/