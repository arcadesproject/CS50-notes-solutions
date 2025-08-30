#include <cs50.h>
#include <stdio.h>

#define AMEX_PREFIX1 34
#define AMEX_PREFIX2 37
#define AMEX_LENGTH 15
#define MASTERCARD_PREFIX_START 51
#define MASTERCARD_PREFIX_END 55
#define MASTERCARD_LENGTH 16
#define VISA_PREFIX 4
#define VISA_LENGTH1 13
#define VISA_LENGTH2 16

string card_type(long n);
bool valid_card(long n);

int main(void)
{
    long card_number = get_long("Enter card number: ");

    if (valid_card(card_number))
    {
        printf("%s\n", card_type(card_number));
    }
    else
    {
        printf("INVALID\n");
    }
}

string card_type(long n)
{
    long temp = n;
    int card_length = 2;

    while (temp >= 100)
    {
        temp /= 10;
        card_length++;
    }

    if ((temp == AMEX_PREFIX1 || temp == AMEX_PREFIX2) && card_length == AMEX_LENGTH)
    {
        return "AMEX";
    }
    else if ((temp >= MASTERCARD_PREFIX_START && temp <= MASTERCARD_PREFIX_END) &&
             card_length == MASTERCARD_LENGTH)
    {
        return "MASTERCARD";
    }
    // one less for VISA
    temp /= 10;
    if (temp == VISA_PREFIX && (card_length == VISA_LENGTH1 || card_length == VISA_LENGTH2))
    {
        return "VISA";
    }

    return "INVALID";
}

// Use Luhn's algorithm to check card checksum
bool valid_card(long n)
{
    int sum = 0;
    long temp = n;
    bool alternate = false;

    while (temp > 0)
    {
        // gets last digit
        int digit = temp % 10;
        if (alternate)
        {
            digit *= 2;
            // when over 10 need to 'add' digits together e.g. 15 -> 6, 18 -> 9
            sum += (digit > 9) ? (digit - 9) : digit;
        }
        else
        {
            sum += digit;
        }

        alternate = !alternate;
        // removes last digit
        temp /= 10;
    }

    // Checks if ends in 0
    return (sum % 10 == 0);
}
