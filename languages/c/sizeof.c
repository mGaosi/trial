#pragma once

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* args[])
{
#ifdef _M_X64
    static_assert(sizeof(int) >= (size_t)2u, "");
    static_assert(sizeof(int) <= (size_t)4u, "");
    static_assert(sizeof(int) <= sizeof(long), "");
#else

#endif
    printf("sizeof(int) = %d\n", (int)sizeof(int));
    printf("sizeof(long) = %d\n", (int)sizeof(long));
    return 0;
}