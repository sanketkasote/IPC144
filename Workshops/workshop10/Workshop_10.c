/*-----------------------------------------------------------------------------------------------*/
// Code Quest Workshop 10
// codequest_w10.c
// last edit = Aug 3, 8:56 PM
/*-----------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define NAME 11
#define ARRAY 5
struct Struct // i did struct already but i guess i couldve changed it to a 2D array after todays lecture
{
    char name[NAME];
};
int Validate_Alphanumberic(const struct Struct *);
void Get_Valid(struct Struct []);
void clearBuffer();
/*-----------------------------------------------------------------------------------------------*/
int main()
{
    struct Struct array[ARRAY];
    
    Get_Valid(array);
    
    printf("\n");
    for (int i=0; i<ARRAY; i++)
    {
        printf("%d - %s\n", i, array[i].name);
    }
    printf("\n");
    
    return 0;
}
/*-----------------------------------------------------------------------------------------------*/
int Validate_Alphanumberic(const struct Struct *array) // returns 1 if valid, 0 is not
{
    int validate=1;
    unsigned long len = strlen(array->name);
    //printf("*DEBUG! len=%lu*\n", len);

    for (int i=0; i<len; i++) // will not look at \0
    {
        if (array->name[i] != ' ')
        {
            //printf("*DEBUG! not space!*\n");
            if (!((array->name[i] >= '0') && (array->name[i] <= '9')))
            {
                //printf("*DEBUG! not a digit!*\n");
                if (!((array->name[i] >= 'A') && (array->name[i] <= 'Z')))
                {
                    //printf("*DEBUG! not uppercase letter!*\n");
                    if (!((array->name[i] >= 'a') && (array->name[i] <= 'z')))
                    {
                        //printf("*DEBUG! not lowercase letter!*\n");
                        validate = 0;
                        break;
                    }
                }
            }
        }
    }
    
    return validate;
}
/*-----------------------------------------------------------------------------------------------*/
void Get_Valid(struct Struct array[])
{
    int validate=0;
    
    printf("Please enter item names\n");
    
    for (int i=0; i<ARRAY; i++)
    {
        printf("Item %d: ", i+1);
        scanf(" %[^\n]", array[i].name);
        validate = Validate_Alphanumberic(&array[i]);
        
        while (validate==0)
        {
            printf("Invalid, try again: ");
            clearBuffer();
            scanf("%[^\n]s", array[i].name);
            validate = Validate_Alphanumberic(&array[i]);
        }
    }
}
/*-----------------------------------------------------------------------------------------------*/
void clearBuffer()
{
    while (getchar() != '\n')
        ;
}
/*-----------------------------------------------------------------------------------------------*/