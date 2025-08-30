// Practice using structs
// Practice writing a linear search function

/**
 * Beach Burger Shack has the following 10 items on their menu
 * Burger: $9.5
 * Vegan Burger: $11
 * Hot Dog: $5
 * Cheese Dog: $7
 * Fries: $5
 * Cheese Fries: $6
 * Cold Pressed Juice: $7
 * Cold Brew: $3
 * Water: $2
 * Soda: $2
 */

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Number of menu items
// Adjust this value (10) to number of items input below
#define NUM_ITEMS 10

// Menu itmes have item name and price
typedef struct
{
    char *item;
    float price;
} menu_item;

// Array of menu items
menu_item menu[NUM_ITEMS];

// Add items to menu
void add_items(void);

// Calculate total cost
float get_cost(char *item);

int main(void)
{
    add_items();

    printf("\nWelcome to Beach Burger Shack!\n");
    printf("Choose from the following menu to order. Press enter when done.\n\n");

    for (int i = 0; i < NUM_ITEMS; i++)
    {
        printf("%s: $%.2f\n", menu[i].item, menu[i].price);
    }
    printf("\n");

    float total = 0;
    while (true)
    {
        char *item = get_string("Enter a food item: ");
        if (strlen(item) == 0)
        {
            printf("\n");
            break;
        }

        total += get_cost(item);
    }

    printf("Your total cost is: $%.2f\n", total);
}

// Add at least the first four items to the menu array
void add_items(void)
{
    menu_item burger = {"Burger", 9.00};
    menu_item vegan_burger = {"Vegan Burger", 11.00};
    menu_item hot_dog = {"Hot Dog", 5.00};
    menu_item cheese_dog = {"Cheese Dog", 7.00};
    menu_item fries = {"Fries", 5.00};
    menu_item cheese_fries = {"Cheese Fries", 6.00};
    menu_item cold_pressed_juice = {"Cold Pressed Juice", 7.00};
    menu_item cold_brew = {"Cold Brew", 3.00};
    menu_item water = {"Water", 2.00};
    menu_item soda = {"Soda", 2.00};

    menu[0] = burger;
    menu[1] = vegan_burger;
    menu[2] = hot_dog;
    menu[3] = cheese_dog;
    menu[4] = fries;
    menu[5] = cheese_fries;
    menu[6] = cold_pressed_juice;
    menu[7] = cold_brew;
    menu[8] = water;
    menu[9] = soda;
}

// Search through the menu array to find an item"s cost
float get_cost(char *item)
{
    if (item == NULL)
    {
        return -1.00;
    }

    for (int i = 0; i < NUM_ITEMS; i++)
    {
        if (strcasecmp(item, menu[i].item) == 0)
        {
            return menu[i].price;
        }
    }

    return -1.00;
}
