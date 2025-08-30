#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string convert_text(string text, string cipher);
bool all_alphabetical(string text);
bool all_unique(string text);

const int cipher_length = 26;

int main(int argc, string argv[])
{
    // Needs to be string / chars
    // if no arg or not chars then Usage: ./substitution key
    // Needs to be 26 length first arg
    // Key must contain 26 characters
    // Then text = get_string("plaintext: ")
    // Then return ciphertext: converted

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // if not 26 chars or contains non alphabetic char or has char more than once
    else if (strlen(argv[1]) != cipher_length || !all_alphabetical(argv[1]) || !all_unique(argv[1]))
    {
        printf("Key must contain 26 unique, alphabetical characters\n");
        return 1;
    }

    string cipher = argv[1];
    string text = get_string("plaintext: ");
    string converted_text = convert_text(text, cipher);
    printf("ciphertext: %s\n", converted_text);
    return 0;
}

string convert_text(string text, string cipher)
{
    int length = strlen(text);

    for (int i = 0; i < length; i++)
    {
        if (islower(text[i]))
        {
            // Uses ascii numbering to get index and keep them lower case if that was input even if
            // cipher is uppercase
            text[i] = tolower(cipher[text[i] - 'a']);
        }
        else if (isupper(text[i]))
        {
            // needs to take away higher value for capitals as later in ascii and keep them upper
            // case
            text[i] = toupper(cipher[text[i] - 'A']);
        }
    }
    return text;
}

bool all_alphabetical(string text)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (!isalpha(text[i]))
        {
            return false;
        }
    }
    return true;
}

bool all_unique(string text)
{
    // Create an array of 26 booleans (one for each letter in the alphabet)
    // All set to false initially, meaning "letter not yet seen"
    bool seen[26] = {false};

    for (int i = 0; i < strlen(text); i++)
    {
        // Convert current character to lowercase to ensure case-insensitive check
        char c = tolower(text[i]);

        // Get the alphabet index (0 for 'a', 1 for 'b', ..., 25 for 'z')
        int index = c - 'a';

        // If this character has already been seen, it's a duplicate
        if (seen[index])
        {
            return false; // Not unique
        }

        // Mark this character as seen
        seen[index] = true;
    }

    // If we loop through the whole string without finding duplicates, all characters are unique
    return true;
}
