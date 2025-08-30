# credit.c notes

Checks credit card numbers for visa, mastercard or amex are valid

Uses Luhn's algorithm

Uses % 10 to get final digit

Uses /= 10 to remove final digit

sum += (digit > 9) ? (digit - 9) : digit; to add together if over ten e.g. 16 -> 7 (1+6)