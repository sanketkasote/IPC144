
#include <stdio.h>
int main(void)
{
    printf("+—————————---——+\n");
    printf("|              |\n");
    printf("|  CODE QUEST  |\n");
    printf("|              |\n");
    printf("+—————---——————+\n");
    
    int pStrength, pSpeed, pDefense, pIntelligence, pLuck, pHP = 10; // initialize player stats
    int eStrenght = 30, eDefense = 40, eIntelligence = 25, eHP = 10, move; // initialize enemy stats
    
    printf("\nCharacter Creation\n");
    printf("Please enter your desired stats for your character: \n");
    
    printf("\nEnter Strength: ");
    scanf(" %d", &pStrength); // enter player strength
    
    printf("Enter Speed: ");
    scanf(" %d", &pSpeed); // enter player speed
    
    printf("Enter Defense: ");
    scanf(" %d", &pDefense); // enter player defense
    
    printf("Enter Intelligence: ");
    scanf(" %d", &pIntelligence); // enter player intelligence
    
    float sum = pStrength + pSpeed + pDefense + pIntelligence; // initialize and calculate sum of all stats
    
    float pStrengthRatio = pStrength / sum; // initialize and calculate player strength ratio
    float pSpeedRatio = pSpeed / sum; // initialize and calculate player speed ratio
    float pDefenseRatio = pDefense / sum; // initialize and calculate player defense ratio
    float pIntelligenceRatio = pIntelligence / sum; // initialize and calculate player intelligence ratio
    
    pStrength = (int) (pStrengthRatio * 100); // calculate player strength
    pSpeed = (int) (pSpeedRatio * 100); // calculate player speed
    pDefense = (int) (pDefenseRatio * 100); // calculate player defense
    pIntelligence = (int) (pIntelligenceRatio * 100); // calculate player intelligence
    
    pLuck = (int)sum % 30; // calculate player luck
    
    printf("\nYour player's final stats are:\n");
    
    printf("\nStrength: %d", pStrength); // print calculated player strength
    printf("\nSpeed: %d", pSpeed); // print calculated player speed
    printf("\nDefense: %d", pDefense); // print calculated player defense
    printf("\nIntelligence: %d", pIntelligence); // print calculated player intelligence
    printf("\nLuck: %d\n\n", pLuck); // print calculated player luck
    
    float p_attack_power = (float) pStrength / (float) eDefense; // initialize player attack power
    float e_attack_power = (float) eStrenght / (float) pDefense; // initialize enemy attack power
    float p_magic_power = (float) pIntelligence / (float) eIntelligence; // initialize player magic power
    
    printf("\nBattle Start!\n");
    
    printf("\nYour HP: %d\n", pHP);
    printf("Enemy HP: %d\n", eHP);
    
    while ((pHP > 0) && (eHP > 0)) // while both player and enemy HPs are greater than 0
    {
        printf("\n1 - Attack\n");
        printf("2 - Magic\n");
        
        printf("\nSelect your move: ");
        scanf(" %d", &move);
        if ((move == 1) || (move == 2)) // if a move (1 or 2) is selected
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
            printf("\nYour HP: %d", pHP);
            printf("\nEnemy HP: %d\n", eHP);
        }
        else // else/when an invalid number is selected
        {
            printf("\nTry again dummy...\n");
        }
    }
    if (pHP <= 0) // if/when the player has 0 or less hp
    {
        printf("\nYou Died... Game Over!\n");
        printf("Please pay 0.99$ to try again.\n\n");
    }
    else if (eHP <= 0) // if/when the enemy has 0 or less hp
    {
        printf("\nYou Won!\n\n");
    }
    return 0;
}

/*
 more maybe?
 for less hp on player
 for less hp on enemy
 for a high damage attack? either
 
 if (3 <= pHP <=6 <= eHP)
 printf("\nOuch... That must've hurt");
 if (3 <= eHP <= 6 <= pHP)
 printf("\nWay to go, you're so good at this game");
 if (1 <= pHP <= 2 <= eHP)
 printf("\nYou're about to die, try doing the other move.");
 if (1 <= eHP <= 2 <= pHP)
 printf("\nYou're about to win! Don't spaz out and chose the wrong move next");
 */