// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

char *replace(char *word);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Enter program and one word into CLI");
        return 1;
    }

    char *replaced = replace(argv[1]);

    printf("%s\n", replaced);
}

char *replace(char *word)
{
    for (int i = 0; i < strlen(word); i++)
    {
        char letter = tolower(word[i]);
        switch (letter)
        {
            case 'a':
                word[i] = '6';
                break;

            case 'e':
                word[i] = '3';
                break;

            case 'i':
                word[i] = '1';
                break;

            case 'o':
                word[i] = '0';
                break;
        }
    }
    return word;
}
