#ifndef TA_GETLINES_H
#define TA_GETLINES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Reads lines from file and allocates new memory for them, so it must be freed later.
If max_line_length is 0 then it will be set to 4096 bytes.
lines_read will be set to the number of lines read.
*/
char **getlines(FILE *file, uint max_line_length, uint *lines_read)
{
    char c;
    int line_count = 1;

    while ((c = fgetc(file)) != EOF)
        if (c == '\n')
            line_count++;

    char **buffer = (char **)calloc(line_count, sizeof(char *));
    int line_i = 0, line_num = 0, arg2;
    if (max_line_length == 0)
        max_line_length = 4096;
    char line[max_line_length];

    rewind(file);
    while ((c = fgetc(file)) != EOF)
    {
        line[line_i++] = c;
        if (c == '\n' || line_i == max_line_length)
        {
            line[line_i - 1] = '\0';
            buffer[line_num] = (char *)malloc(line_i);
            strncpy(buffer[line_num], line, line_i);
            line_num++;
            bzero(line, max_line_length);
            line_i = 0;
        }
    }

    buffer[line_num] = (char *)malloc(line_i);
    strncpy(buffer[line_num], line, line_i);

    *lines_read = line_num + 1;
    return buffer;
}
#endif
