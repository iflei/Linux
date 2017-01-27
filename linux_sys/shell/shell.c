/*************************************************************************
> File Name: shell.c
> Author: iflei
> Mail: admin@iflei.com
> Blog: www.iflei.com
************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/wait.h>

int main()
{
	while (1)
	{
		printf("[test@127.0.0.1 test]$ ");
		fflush(stdout);
		char buf[1024];
		ssize_t s = read(0, buf, sizeof(buf)-1);
		if (s > 0)
		{
			buf[s - 1] = 0; //去掉键盘输入读进去的空格
		}
		//解析命令及参数
		char* _argv[32];
		char* start = buf;
		//跳过空格
		while (*start == ' ')
		{
			start++;
		}

		_argv[0] = start;
		int i = 1;
		while (*start)
		{
			if (*start == ' ')
			{
				*start = 0;
				start++;

				if (*start != ' ')
					_argv[i++] = start;
			}
			else
			{
				start++;
			}
		}
		_argv[i] = NULL;

		//读取到exit不再循环读取命令直接退出
		if (strcmp(_argv[0], "exit") == 0)
			break;

		//解析输出重定向符号
		if (strcmp(_argv[i - 2], ">") == 0)
		{
			_argv[i - 2] = NULL;
			pid_t id = fork();
			if (id < 0)
				perror("fork");
			else if (id == 0)
			{
				close(1);
				open(_argv[i - 1], O_WRONLY | O_CREAT, 0664);
				execvp(_argv[0], _argv);
			}
			else
			{
				wait(0);
			}
		}
		else
		{
			//没有重定向符号直接创建子进程执行命令
			pid_t id = vfork();
			if (id < 0)
				perror("vfork");
			else if (id == 0)
			{
				execvp(_argv[0], _argv); //执行命令
			}
			else
			{
				wait(0);//等待命令执行结果
			}
		}
	}
	return 0;
}