#include <stdlib.h>
#include <stdio.h>

int main()
{
    char *res = malloc(43 * sizeof(char));
    if (!res)
        return (0);
    printf("g");
}