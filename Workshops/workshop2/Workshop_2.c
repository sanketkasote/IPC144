/*--------------------------------------------------------------------------------------------------------------------------*/
// Code Quest Workshop 2
// codequest_w2.c
/*--------------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
/*--------------------------------------------------------------------------------------------------------------------------*/
int main(void)
{
	int strength, speed, defense, intelligence, luck;

	printf("\nCharacter Creation\n");
	printf("Please enter your desired stats for your character: \n");

	printf("\nEnter Strength: ");
	scanf(" %d", &strength); // enter player strength

	printf("Enter Speed: ");
	scanf(" %d", &speed); // enter player speed

	printf("Enter Defense: ");
	scanf(" %d", &defense); // enter player defense

	printf("Enter Intelligence: ");
	scanf(" %d", &intelligence); // enter player intelligence

	float sum = strength + speed + defense + intelligence; // initialize and calculate sum of all stats

	float strengthRatio = strength / sum; // initialize and calculate player strength ratio
	float speedRatio = speed / sum; // initialize and calculate player speed ratio
	float defenseRatio = defense / sum; // initialize and calculate player defense ratio
	float intelligenceRatio = intelligence / sum; // initialize and calculate player intelligence ratio

	strength = (int) (strengthRatio * 100); // calculate player strength
	speed = (int) (speedRatio * 100); // calculate player speed
	defense = (int) (defenseRatio * 100); // calculate player defense
	intelligence = (int) (intelligenceRatio * 100); // calculate player intelligence

	luck = (int)sum % 30; // calculate player luck

	printf("\nYour player's final stats are:\n");

	printf("\nStrength: %d", strength); // print calculated player strength
	printf("\nSpeed: %d", speed); // print calculated player speed
	printf("\nDefense: %d", defense); // print calculated player defense
	printf("\nIntelligence: %d", intelligence); // print calculated player intelligence
	printf("\nLuck: %d\n\n", luck); // print calculated player luck

	return 0;
}
/*--------------------------------------------------------------------------------------------------------------------------*/