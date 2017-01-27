#include <stdio.h>
#include <stdlib.h>

int g_var = 100;
float g_uninit_var;

void test()
{
    int a = 10;
    int b = 20;
    printf("stack address 1: %p\n", &a);
    printf("stack address 2: %p\n", &b);
}

void (*pfunc)();

int main(int argc, char* argv[], char* env[])
{
    int a = 5;
    int* heap = (int*)malloc(sizeof(int));
    pfunc = test;

    printf("code address: %p\n", pfunc); //代码段
    printf("init data address: %p\n", &g_var); //已初始化数据
    printf("uninit data address: %p\n", &g_uninit_var); //未初始化数据
    printf("heap address: %p\n", heap); //堆
    printf("stack address 0: %p\n", &a); //栈
    pfunc();
    printf("argv address: %p\n", argv[0]); //命令行参数
    printf("argv address: %p\n", env[0]); //环境变量
    return 0;
}
