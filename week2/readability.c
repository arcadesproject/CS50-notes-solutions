#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int calculate_level(int letters, int words, int sentences);
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    float reading_level = calculate_level(letters, words, sentences);
    int grade = (int) reading_level;

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

int calculate_level(int letters, int words, int sentences)
{
    // Coleman-Liau index
    // index = 0.0588 * L - 0.296 * S - 15.8
    // where L is the average number of letters per 100 words in the text
    // S is the average number of sentences per 100 words in the text.
    float L = (100.0 / words) * letters;
    float S = (100.0 / words) * sentences;
    return round(0.0588 * L - 0.296 * S - 15.8);
}

int count_letters(string text)
{
    // Return the number of letters in text
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if isalpha (text[i])
        {
            count++;
        }
    }
    return count;
}

int count_words(string text)
{
    // Return the number of words in text
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if isspace (text[i])
        {
            count++;
        }
    }
    return count + 1;
}

int count_sentences(string text)
{
    // Return the number of sentences in text
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '?' || text[i] == '.' || text[i] == '!')
        {
            count++;
        }
    }
    return count;
}
