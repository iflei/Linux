#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

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

void* do_connect(void* arg)
{
	int new_socket = *(int*)arg; //获取参数
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
			printf("client# %s\n", buf);
			//server echo
			write(new_socket, buf, sizeof(buf)-1);
		}
		else //s == 0
		{
			printf("Closed!\n");
			close(new_socket);
			pthread_exit((void*)6);
		}
	}
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

		printf("New Connection! %s:%d\n", inet_ntoa(remote.sin_addr), ntohs(remote.sin_port)); 
		
		//创建线程
		pthread_t tid;
		int err;
		if(err = pthread_create(&tid, NULL, do_connect, &new_socket))
		{
			printf("pthread_create: %s\n",strerror(err));
			exit(5);
		}
		//线程分离，无需等待
		pthread_detach(tid);
	}
	
	return 0;
}
