#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

int main()
{
	int sv[2];
	//在指定的域中创建一个未命名的连接套接字
	//socketpair和pipe很像，并且可以双向通信
	if(socketpair(PF_LOCAL, SOCK_STREAM, 0, sv) < 0)
	{
		perror("socketpair");
	}

	printf("fd[0]: %d, fd[1]: %d\n", sv[0], sv[1]);
	pid_t id = fork();
	if(id == 0) //child
	{
		close(sv[0]);

		char buf[1024];
		const char* msg = "I am child...";
		while(1)
		{
			//先写
			write(sv[1], msg, strlen(msg));
			//后读
			ssize_t s = read(sv[1], buf, sizeof(buf)-1);
			if(s > 0)
			{
				buf[s] = 0;
				printf("father# %s\n", buf);
			}
			else
				break;

			sleep(1);
		}
		close(sv[1]);
		exit(1);
	}
	else //father
	{
		close(sv[1]);
		const char* msg = "I am father...";
		char buf[1024];

		while(1)
		{
			//先读
			ssize_t s = read(sv[0], buf, sizeof(buf)-1);
			if(s > 0)
			{
				buf[s] = 0;
				printf("child# %s\n", buf);
			}
			else
				break;
			//后写
			write(sv[0], msg, strlen(msg));
		}
		
		waitpid(id, NULL, 0);
		close(sv[0]);
	}
	return 0;
}
