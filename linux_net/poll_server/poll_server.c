#include <stdio.h>
#include <poll.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_NUM 4096

int startup(const char* ip, int port)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		perror("socket");
		exit(2);
	}

	int opt = 1;
	if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0){
		perror("setsockopt");
	}

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip);

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
		printf("Usage: %s [local_ip] [local_port]\n", argv[0]);
		return 1;
	}

	int listen_sock = startup(argv[1], atoi(argv[2]));

	//struct pollfd {
	//	int   fd;         /* file descriptor */
	//  short events;     /* requested events */
	//  short revents;    /* returned events */
	//};
	struct pollfd evs[MAX_NUM]; //设置最大监测fd为MAX_NUM
	evs[0].fd = listen_sock; //先监测listen_sock的读事件
	evs[0].events = POLLIN;
	evs[0].revents = 0;

	int timeout = -1; //阻塞
	while(1)
	{
		//int poll(struct pollfd *fds, nfds_t nfds, int timeout);
		switch(poll(evs, MAX_NUM, timeout))
		{
			case 0:
				printf("timeout!\n");
				break;
			case -1:
				perror("poll");
				break;
			default:
				{
					int i = 0;
					for(; i < MAX_NUM; ++i)
					{
						//listen_sock就绪
						if(i == 0 && (evs[i].revents & POLLIN))
						{
							struct sockaddr_in remote;
							socklen_t len = sizeof(remote);
							int conn_sock = accept(listen_sock, (struct sockaddr*)&remote, &len);
							if(conn_sock < 0)
							{
								perror("accept");
								continue;
							}
							//把新连接添加到evs数组里，并监测读事件
							int j = 1;
							for(; j < MAX_NUM; ++j)
							{
								if(evs[j].fd == 0)
								  break;
							}

							if(j >= MAX_NUM)
							  close(conn_sock); //无法处理新连接
							else
							{
								evs[j].fd = conn_sock;
								evs[j].events = POLLIN;
								evs[j].revents = 0;
								printf("New Connection! %s:%d\n", inet_ntoa(remote.sin_addr), ntohs(remote.sin_port));
							}
						}
						//其他fd读事件就绪
						else if(i != 0 && (evs[i].revents & POLLIN))
						{
							char* buf[1024];
							ssize_t s = read(evs[i].fd, buf, sizeof(buf)-1);
							if(s > 0)
							{
								buf[s] = 0;
								printf("client: %s\n", buf);
								//把读事件改为写事件
								evs[i].events = POLLOUT;
								evs[i].revents = 0;
							}
							else if(s == 0)
							{
								printf("Closed!\n");
								close(evs[i].fd);
								//删除当前fd
								evs[i].fd = 0;
								evs[i].events = 0;
								evs[i].revents = 0;
							}
							else
							{
								perror("read");
								continue;
							}
						}
						//其他fd写事件就绪
						else if(i != 0 && (evs[i].revents & POLLOUT))
						{
							const char* msg = "HTTP/1.1 200 OK \r\n\r\n<html><h1>hello world! </h1></html>\n";
							write(evs[i].fd, msg, strlen(msg));	
							
							evs[i].fd = 0;
							evs[i].events = 0;
							evs[i].revents = 0;
							close(evs[i].fd);
						}
						//异常事件
						else
						{}
					}
				}
				break;
		}
	}
	return 0;
}
