#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // NORMAL LIST BUT NOT MALLEABLE

    // int list[3];
    // list[0] = 1;
    // list[1] = 2;
    // list[2] = 3;

    // for (int i = 0; i < 3; i++)
    // {
    //     printf("%i\n", list[i]);
    // }

    // CAN ALTER WITH MALLOC BUT TOO LENGTHY
    int *list = malloc(3 * sizeof(int));
    if (list == NULL)
    {
        return 1;
    }

    list[0] = 1;
    list[1] = 2;
    list[2] = 3;

    // Time passes

    // int *tmp = malloc(4 * sizeof(int));
    // Use realloc instead of malloc here, same chunk but bigger version
    // realloc needs address of original chunk of memory so list here
    int *tmp = realloc(list, 4 * sizeof(int));

    if (tmp == NULL)
    {
        free(list); // would be memory leak as exiting program with not freeing prev value
        return 1;
    }

    // if used malloc
    // for (int i = 0; i < 3; i++)
    // {
    //     tmp[i] = list[i];
    // }

    tmp[3] = 4;

    free(list);

    list = tmp;

    for (int i = 0; i < 4; i++)
    {
        printf("%i\n", list[i]);
    }

    free(list);

    return 0;
}
