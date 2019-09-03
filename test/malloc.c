/*
 * FILE:      malloc.c
 * AUTHOR:    Liam Powell (19236221)
 * UNIT:      UCP (COMP1000)
 * PURPOSE:   Testing malloc failures. Based on the strategy used by SQLite.
 * REFERENCE: https://www.sqlite.org/malloc.html#testing
 * LAST MOD:  2018-10-21
 */

/*
 * This file is used to make sure that the program can handle malloc failing
 * at any point. It calls the main function of the program and makes the first
 * call to malloc and all calls after that fail, then it calls main and makes
 * the second call to malloc and all calls after that fail, etc. until the
 * program doesn't reach the failing malloc call, meaning that we've tested
 * malloc failing at every possible point. Then we do the same thing again
 * except only one call to malloc fails and the rest are allowed to succeed.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

void *__real_malloc(size_t);

static int shouldFail(int reset, int resetFirstOnly)
{
    static unsigned long max = 0;
    static unsigned long count = 0;
    static int firstOnly = 0;

    if (reset)
    {
        ++max;
        count = 0;
        if (!!firstOnly != !!resetFirstOnly)
        {
            max = 0;
        }
        firstOnly = resetFirstOnly;
    }
    else if (count < max)
    {
        ++count;
    }
    else if ((count == max) && firstOnly)
    {
        ++count;
    }

    return count == max;
}

void *__wrap_malloc(size_t size)
{
    return shouldFail(0, 0) ? NULL : __real_malloc(size);
}

int __real_main(int argc, char **argv);

int __wrap_main(int argc, char **argv)
{
    while (shouldFail(0, 0))
    {
        shouldFail(1, 0);
        __real_main(argc, argv);
    }

    while (shouldFail(0, 0))
    {
        shouldFail(1, 1);
        __real_main(argc, argv);
    }

    return 0;
}

/* Make sure nothing is outputted, we don't care about any of it. */

int __wrap_printf(const char *format, ...)
{
    return 1;
}

int __wrap_fprintf(FILE *stream, const char *format, ...)
{
    return 1;
}

int __wrap_vfprintf(FILE *stream, const char *format, va_list ap)
{
    return 1;
}

int __wrap___printf_chk(int flag, const char * format)
{
    return 1;
}

int __wrap___fprintf_chk(FILE * stream, int flag, const char * format)
{
    return 1;
}

int __wrap___vfprintf_chk(FILE * fp, int flag, const char * format, va_list ap)
{
    return 1;
}
