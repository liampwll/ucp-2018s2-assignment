/*
 * FILE:     fgetslength.c
 * AUTHOR:   Liam Powell (19236221)
 * UNIT:     UCP (COMP1000)
 * PURPOSE:  Line reading function similar to fgets.
 * LAST MOD: 2018-10-18
 */

#include <stddef.h>
#include <stdio.h>

size_t fgetsLength(char *s, size_t size, FILE *stream)
{
    size_t retval;
    int in;
    int hadError;

    retval = 0;
    hadError = 0;
    in = ' ';
    while ((retval < size - 1) && !hadError && (in != '\n') && (in != EOF))
    {
        in = getc(stream);
        if (in == EOF)
        {
            if (!feof(stream))
            {
                hadError = 1;
                retval = 0;
            }
        }
        else
        {
            s[retval] = (char)in;
            retval++;
        }
    }

    s[retval] = '\0';

    return retval;
}
