/**
 * @file alignment.c
 * @author Jiangjie Gao (gaojiangjie@live.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-06
 * 
 * 
 */

#include <stdlib.h>
#include <stdio.h>

struct pack
{
    char a;
    char b;
    float x;
};
struct pack1
{
    float x;
    char a;
    char b;
};

#pragma pack(push)
#pragma pack(1) //or #pragma pack(push,1)
struct pack2
{
    char a;
    char b;
    float x;
};
struct pack3
{
    float x;
    char a;
    char b;
};
#pragma pack(pop)

#ifdef _MSC_VER
__declspec(align(32))
struct MyStruct1
{
    float f[4][4];
};
__declspec(align(128))
struct MyStruct2
{
    float f[4][4];
};
#else
struct MyStruct1
{
    float f[4][4];
} __attribute__((aligned(32)));
struct MyStruct2
{
    float f[4][4];
} __attribute__((aligned(128)));
#endif

int main(int argc, char* args[])
{
    printf("sizeof(struct pack) = %d\n", (int)sizeof(struct pack));//sizeof(struct pack1) = 8
    printf("sizeof(struct pack1) = %d\n", (int)sizeof(struct pack1));//sizeof(struct pack1) = 8
    printf("sizeof(struct pack2) = %d\n", (int)sizeof(struct pack2));//sizeof(struct pack2) = 6
    printf("sizeof(struct pack3) = %d\n", (int)sizeof(struct pack3));//sizeof(struct pack3) = 6
    printf("sizeof(struct MyStruct1) = %d\n", (int)sizeof(struct MyStruct1));//sizeof(struct MyStruct1) = 64
    printf("sizeof(struct MyStruct2) = %d\n", (int)sizeof(struct MyStruct2));//sizeof(struct MyStruct1) = 128
    return 0;
}
