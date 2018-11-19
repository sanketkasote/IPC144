/*--------------------------------------------------------------------------------------------------------------------------*/
// Code Quest Workshop 3
// codequest_w3.c
/*--------------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
/*--------------------------------------------------------------------------------------------------------------------------*/
int main(void)
{
    int pStrength = 10, pDefense = 20, pIntelligence = 40, pHP = 10, eStrenght = 30, eDefense = 40, eIntelligence = 25, eHP = 10, move; // initialize stats
    
    float p_attack_power = (float) pStrength / (float) eDefense; // initialize player attack power
    float e_attack_power = (float) eStrenght / (float) pDefense; // initialize enemy attack power
    float p_magic_power = (float) pIntelligence / (float) eIntelligence; // initialize player magic power
    
    printf("\nBattle Start!\n");
    
    printf("\nYour HP: %d\n", pHP);
    printf("Enemy HP: %d\n", eHP);
    
    while (pHP > 0 && eHP > 0) // while both player and enemy HPs are greater than 0
    {
        printf("\n1 - Attack\n");
        printf("2 - Magic\n");
        
        printf("\nSelect your move: ");
        scanf(" %d", &move);
        if (move == 1 || move == 2) // when a move (1 or 2) is selected
        {
            if (move == 1) // if move 1 is selected
            {
                eHP = eHP - (p_attack_power * 5); // calculate the damage to enemy hp by player attack power
                printf("\nYou attacked the enemy!\n");
            }
            else if (move == 2) // if move 2 is selected
            {
                eHP = eHP - (p_magic_power * 5); // calculate the damage to enemy hp by player magic power
                printf("\nYou shocked the enemy!\n");
            }
            if (eHP > 0) // if enemy hasnt died yet, it will attack next
            {
                pHP = pHP - (e_attack_power * 5); // calculate the damage to player by enemy attack power
                printf("The enemy attacked you!\n");
            }
            printf("\nYour HP: %d\n", pHP);
            printf("Enemy HP: %d\n", eHP);
        }
        else // else/when an invalid number is selected
        {
            printf("\nTry again dummy...\n");
        }
    }
    if (pHP <= 0) // if/when the player has 0 or less hp
    {
        printf("\nYou Died... Game Over!\n\n");
        printf("Please pay 0.99$ to try again.\n\n");
    }
    else if (eHP <= 0) // if/when the enemy has 0 or less hp
    {
        printf("\nYou Won!\n\n");
    }
    return 0;
}
/*--------------------------------------------------------------------------------------------------------------------------*/