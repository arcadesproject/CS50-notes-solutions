import re

AMEX_PREFIX1 = 34
AMEX_PREFIX2 = 37
AMEX_LENGTH = 15
MASTERCARD_PREFIX_START = 51
MASTERCARD_PREFIX_END = 55
MASTERCARD_LENGTH = 16
VISA_PREFIX = 4
VISA_LENGTH1 = 13
VISA_LENGTH2 = 16

# try:
#     card_no = int(input("Number: "))
# except ValueError:
#     print("Only enter numbers between 13 and 16 digits long")
#     exit()

def get_input():
    card_input = input("Number: ").strip()
    # would check if 51-55, 34, 37 or 4 start then 11-14 extra digits so 12-16 long
    # if not re.fullmatch(r"(5[1-5]|34|37|4)\d{11,14}", card_input):
    # regexp to check 13-16 long
    if not re.fullmatch(r"\d{13,16}", card_input):
        print("Invalid input: must start with 51–55, 34, 37, or 4 and be 13–16 digits")
        exit()
    return card_input

def card_type(n):
    prefix = int(n[:2])
    v_prefix = int(n[0])
    card_length = len(n)

    if ((prefix == AMEX_PREFIX1 or prefix == AMEX_PREFIX2) and card_length == AMEX_LENGTH):
        return "AMEX"
    elif ((prefix >= MASTERCARD_PREFIX_START and prefix <= MASTERCARD_PREFIX_END) and
          card_length == MASTERCARD_LENGTH):
        return "MASTERCARD"
    elif (v_prefix == VISA_PREFIX and (card_length == VISA_LENGTH1 or card_length == VISA_LENGTH2)):
        return "VISA"

    return "INVALID"

# Luhn's algorithm to check card checksum
def valid_card(n):
    sum = 0
    alternate = False

    while (n > 0):
        # get last digit
        digit = n % 10
        if (alternate):
            digit *= 2
            # add together when over 10, 15 -> 6
            sum += digit - 9 if digit > 9 else digit
        else:
            sum += digit

        alternate = not alternate
        n = n // 10

    return sum % 10 == 0

card_no = get_input()
# turn string into int for valid_card
if (valid_card(int(card_no))):
    print(f"{card_type((card_no))}")
else:
    print("INVALID")
