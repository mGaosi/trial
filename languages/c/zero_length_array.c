#pragma once

/*
* Array of Zero Length
* https://gcc.gnu.org/onlinedocs/gcc/Zero-Length.html
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

typedef struct _string
{
    size_t uLength;
    char pData[0];
}string;

typedef struct _string1
{
    size_t uLength;
    char* pData;
}string1;

typedef struct _string2
{
    // C2229
    char pData[0];
    size_t uLength;
}string2;

int main(int argc, char* args[])
{
    {
        static_assert(sizeof(string) == sizeof(size_t), "string size must be equal sizeof(size_t)");
        string* pStr = malloc(sizeof(string) + 10);
        if (pStr)
        {
            pStr->uLength = 10u;
            // OK
            assert((void*)(&pStr->uLength + 1) == (void*)pStr->pData);
            // OK
            assert((void*)(&pStr->uLength + 1) == (void*)(&pStr->pData[0]));
            // OK
            pStr->pData[0] = 0;
            // C2106
            str.pData = pBuf;
        }
        free(pStr);
    }
    {
        static_assert(sizeof(string1) == (sizeof(size_t) + sizeof(void*)), "string1 size must be equal sizeof(size_t) + sizeof(void*)");
        char pBuf[] = "";
        string1* pStr = malloc(sizeof(string));
        // OK
        pStr->pData = pBuf;
        // OK
        assert((void*)(&pStr->uLength + 1) != (void*)pStr->pData);
        assert((void*)(&pStr->uLength + 1) == (void*)(&pStr->pData));
    }
    return 0;
}
