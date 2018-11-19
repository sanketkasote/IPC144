/*--------------------------------------------------------------------------------------------------------------------------*/
// Code Quest Workshop 5
// codequest_w5.c
/*--------------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
/*--------------------------------------------------------------------------------------------------------------------------*/
void menu(float *, int *, int *);
void rest_at_inn(float *, int *, int);
void train(float *, int *, int *);
void battle_demon_lord(int *);
/*--------------------------------------------------------------------------------------------------------------------------*/
int main(void)
{
    int hp_remaining = 10, max = 10, experience = 0, userInput;
    float days_remaining = 8;
    
    do
    {
        menu(&days_remaining, &hp_remaining, &experience);
        
        printf("\nSelect: ");
        scanf(" %d", &userInput);
        
        if (userInput == 1)
        {
            rest_at_inn(&days_remaining, &hp_remaining, max);
        }
        else if (userInput == 2)
        {
            train(&days_remaining, &hp_remaining, &experience);
        }
        else if (userInput == 3)
        {
            battle_demon_lord(&hp_remaining);
        }
        else if (userInput == 4)
        {
            printf("Okay buh bye then...\n\n");
        }
        else
        {
            printf("Errr try again...\n\n");
        }
        
    } while ((userInput != 4) && (hp_remaining > 0));
    
    printf("\nGame Over!\n\n");
    
    return 0;
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void menu(float *x, int *y, int *z)
{
    printf("\n\nDays remaining: %.2f | HP: %d | EXP: %d\n\n", *x, *y, *z);
    printf("1 - Rest at Inn\n");
    printf("2 - Train\n");
    printf("3 - Fight the Demon Lord\n");
    printf("4 - Quit Game\n");
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void rest_at_inn(float *days_remaining, int *hp_remaining, int max)
{
    *hp_remaining = max;
    *days_remaining -= 1;
    printf("\nYou rested up at the inn\n");
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void train(float *days_remaining, int *hp_remaining, int *experience)
{
    *experience += 10;
    *hp_remaining -= 2;
    *days_remaining -= 0.5;
    printf("\nYou did some training, wow look at those muscles!\n");
}
/*--------------------------------------------------------------------------------------------------------------------------*/
void battle_demon_lord(int *current_hp)
{
    *current_hp = 0;
    printf("\nRun, it's Godzilla!\n\n");
}
/*--------------------------------------------------------------------------------------------------------------------------*/