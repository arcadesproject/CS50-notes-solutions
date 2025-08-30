#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
} node;

int main(void)
{
    node *list = NULL;

    for (int i = 0; i < 3; i++)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            // TODO: Free any memory malloc'd
            return 1;
        }
        // using cs50 get_int still not real c
        // use scanf
        n->number = get_int("Number: ");
        // currently created node ends next field to be that of list
        // for prepend this would insert blindly at start
        // n->next = list;
        // list = n
        n -> next = NULL;

        // update list itself to point at node
        // but is all backwards 3, 2, 1
        // list = n;

        // if list is empty
        if (list == NULL)
        {
            list = n;
        }
        // if has numbers already
        else
        {
            // sets ptr to stard of list, until it's not null, iterate pointing to next node, then next etc.
            for (node *ptr = list; ptr != NULL; ptr = ptr->next)
            {
                // if at end of list add one more node, stop
                if (ptr->next == NULL)
                {
                    ptr->next = n;
                    break;
                }
            }
        }
    }

    // Time passes
    // list is currently only variable pointing to anything
    // ptr will point to first element
    // node *ptr = list;

    // // while still pointing at valid memory
    // while (ptr != NULL)
    // {
    //     // print current nodes number field
    //     printf("%i\n", ptr->number);
    //     // update with what it is now and next node
    //     ptr = ptr->next;
    // }

    // appending version
    for (node *ptr = list; ptr!=NULL; ptr = ptr->next)
    {
        printf("%i\n", ptr->number);
    }

    // Time passes, free memory
    node *ptr = list;
    while (ptr != NULL)
    {
        // need to set this in temp as can't free address and then reference it
        // couldn't do ptr->next where we do ptr = next
        node *next = ptr->next;
        free(ptr);
        ptr = next
    }

    return 0;
}
