#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "getlines.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "usage: %s [PATH] [MAX LINE LENGTH]\nmaximum line legth is optional and the default is 4096 bytes.\n", argv[0]);
        return 1;
    }

    if (access(argv[1], R_OK))
    {
        fprintf(stderr, "%s does not exist\n", argv[1]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        fprintf(stderr, "failed to open %s\n", argv[1]);
        return 1;
    }

    int line_count, arg2;
    uint max_line_length = (argc >= 3 && (arg2 = atoi(argv[2])) > 0) ? arg2 : 0;
    char **lines = getlines(file, max_line_length, &line_count);

    printf("line count = %u\n", line_count);

    for (uint i = 0; i < line_count; i++)
        printf("line %u: %s\n", i + 1, lines[i]);

    return line_count;
}