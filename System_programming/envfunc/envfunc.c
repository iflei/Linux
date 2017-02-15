/*************************************************************************
	> File Name: envfunc.c
	> Author: iflei
	> Mail: admin@iflei.com
	> Blog: www.iflei.com
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main()
{
     //char *getenv( const char *name  );
     //int putenv( char *str  );
     //int setenv( const char *name, const char *value, int rewrite  );
     //int unsetenv( const char *name  );
    putenv("LEI=123:456");
    char* get = getenv("LEI");
    printf("%s\n", get);
    setenv("LEI", "789", 1);
    get = getenv("LEI");
    printf("%s\n", get);
    unsetenv("LEI");

    //getenv函数返回指向name=value中的value的指针；putenv函数把字符串name=value放入环境表中，如果name已经存在，则先删除原来的定义
    //setenv函数将name设置为value，如果name存在且rewrite==0，则删除其现有定义，若rewrite为0，则不删除其现有定义；unsetenv函数删除name的定义，即使不存在也不会出错。
    return 0;
}
