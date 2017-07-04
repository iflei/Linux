#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>

void usage(const char* proc)
{
	printf("Usage: %s [local_ip] [local_port]\n", proc);
}

int startup(const char* ip, const char* port)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0); //IPv4 TCP
	if(sock < 0)
	{
		perror("socket");
		exit(2);
	}

//struct sockaddr_in {
//  __kernel_sa_family_t	sin_family;	/* Address family		*/
//  __be16		sin_port;	/* Port number			*/
//  struct in_addr	sin_addr;	/* Internet address		*/
//};

//struct in_addr {
//	__be32	s_addr;
//};

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(atoi(port));
	local.sin_addr.s_addr = inet_addr(ip);

	//避免地址占用问题
	int opt = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		perror("setsockopt");
	
	socklen_t len = sizeof(local);
	if(bind(sock, (struct sockaddr*)&local, len) < 0)
	{
		perror("bind");
		exit(3);
	}

	if(listen(sock, 10) < 0)
	{
		perror("listen");
		exit(4);
	}

	return sock;
}

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		usage(argv[0]);
		return 1;
	}

	int listen_socket = startup(argv[1], argv[2]);

	struct sockaddr_in remote;
	socklen_t len = sizeof(remote);

	while(1)
	{	
		int new_socket = accept(listen_socket, (struct sockaddr*)&remote, &len);
		if(new_socket < 0)
		{
			perror("accept");
			continue;
		}

		//多进程版本
		pid_t pid = fork();
		if(pid < 0)
		{
			perror("fork");
			exit(5);
		}
		else if(pid == 0) //child
		{
			close(listen_socket); //关闭不需要的文件描述符 

			//子进程里再fork，然后exit子进程，让孙子进程完成工作
			if(fork() > 0) 
			{
				close(new_socket);
				exit(0);
			}
			printf("New Connection! %s:%d\n", inet_ntoa(remote.sin_addr), ntohs(remote.sin_port)); 
			char buf[1024];
			//read write
			while(1)
			{
				ssize_t s = read(new_socket, buf, sizeof(buf)-1);
				if(s < 0)
				{
					perror("read");
					continue;
				}
				else if(s > 0)
				{
					buf[s] = 0;
					//client say
					printf("%s:%d# %s\n", inet_ntoa(remote.sin_addr), ntohs(remote.sin_port), buf);
					//server echo
					write(new_socket, buf, sizeof(buf)-1);
				}
				else //s == 0
				{
					printf("Closed! %s:%d\n", inet_ntoa(remote.sin_addr), ntohs(remote.sin_port));
					close(new_socket);
					exit(6); //进程结束必须exit
				}
			}
		}
		else //father
		{
			//让子进程fork后立即exit，让孙子进程完成socket任务，所以wait不会长时间阻塞
			waitpid(-1, NULL, 0); 
			close(new_socket);
		}

	}
	
	return 0;
}
