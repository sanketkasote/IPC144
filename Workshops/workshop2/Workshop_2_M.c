#include <stdio.h>
#include <stdlib.h>

int main()
{
    int strength, speed, defense, intelligence, luck; //create variables

    //print welcome
    printf("Character Creation\n");
    printf("Please eneter your desired stats for your character:\n");

    //get values from input
    printf("Enter strength: ");
    scanf("%d", &strength);
    printf("Enter speed: ");
    scanf("%d", &speed);
    printf("Enter defense: ");
    scanf("%d", &defense);
    printf("Enter intelligence: ");
    scanf("%d", &intelligence);

    //Sum has to be a float because when you divide an integer by another integer it will give you an integer back (whole number) instead of a number with decimals
    float sum = strength + speed + defense + intelligence; //calculate sum of all values


    //calculate ratios by diving values by sum, store as a float so we can hold decimal numbers
    float strengthRatio = strength/sum;
    float speedRatio = speed/sum;
    float defenseRatio = defense / sum;
    float intelligenceRatio = intelligence / sum;

    //Multiply ratios by a 100 and convert them to ints -- (int) is called a cast, it is what converts floating point to ints
    strength = (int) (strengthRatio * 100);   //We can override the old int values because we won't need them again
    speed = (int) (speedRatio * 100);
    defense = (int) (defenseRatio * 100);
    intelligence = (int) (intelligenceRatio * 100);

    //Next we get luck using modulas - the % sign gives you the remained of a number, such as 10 % 3 = 1 because three goes into 10 three times remainder 1
    luck = (int)sum % 30;

    //Print values
    printf("\nYour player's final stats are:\n");
    printf("\nStrength: %d", strength); //This is how a number from a variable is printed out, we type %d inside the string and that's where the number will appear, such as printf("hmm %d hmm", strength); would be hmm 27 hmm if strength  = 27
    printf("\nSpeed: %d", speed);
    printf("\nDefense: %d", defense);
    printf("\nIntelligence: %d", intelligence);
    printf("\nLuck: %d", luck);

    //Exists program
    return 0;
}
