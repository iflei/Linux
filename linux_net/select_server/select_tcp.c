#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


void usage(const char* proc)
{
	printf("Usage: %s [local_ip] [local_port]\n", proc);
}

int startup(const char* ip, int port)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		perror("socket");
		exit(2);
	}
	//避免地址占用问题
	int opt = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		perror("setsockopt");

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
		usage(argv[0]);
		return 1;
	}

	int rfd[sizeof(fd_set)*8]; //保存要检测的读文件句柄
	int wfd[sizeof(fd_set)*8]; //保存要检测的写文件句柄
	const int nums = sizeof(fd_set)*8;
	int i = 0;
	for(; i < nums; ++i)
	{
		rfd[i] = -1;  //-1是无效文件句柄
		wfd[i] = -1;
	}

	int listen_sock = startup(argv[1], atoi(argv[2]));
	
	rfd[0] = listen_sock; //把listen_sock加入要检测的数组
	fd_set rfds; //读文件描述符集
	fd_set wfds; //写文件描述符集
	struct sockaddr_in remote;
	socklen_t len = sizeof(remote);

	while(1)
	{
		int maxfd = -1; //最大的文件句柄
		FD_ZERO(&rfds); //empty rfds
		FD_ZERO(&wfds);

		for(i = 0; i < nums; ++i) //遍历数组
		{
			if(rfd[i] != -1)
			  FD_SET(rfd[i], &rfds); //添加到rfds
			if(wfd[i] != -1)
			  FD_SET(wfd[i], &wfds);
			
			//记录最大的文件句柄
			if(rfd[i] > maxfd)
				maxfd = rfd[i]; 
			if(wfd[i] > maxfd)
				maxfd = wfd[i]; 
		}
		
		struct timeval timeout = {3, 0}; //设置3秒超时
		//等待rfds中文件句柄读事件发生
		switch(select(maxfd+1, &rfds, &wfds, NULL, NULL /*&timeout*/ ))
		{
			case -1: //error
				perror("select");
				break;
			case 0: //timeout
				printf("select timeout\n");
				break;
			default: //at least one fd ready
				{
					for(i = 0; i < nums; ++i) //遍历数组
					{
						if(rfd[i] == -1 && wfd[i] == -1)
						  continue;

						//循环时检测是否有新连接
						//accept就绪
						if(i == 0 && FD_ISSET(rfd[i], &rfds))	
						{
							int conn_sock = accept(listen_sock, (struct sockaddr*)&remote, &len);
							if(conn_sock < 0)
							{
								perror("accept");
								continue;
							}

							int j = 0;
							for(; j < nums; ++j) //遍历数组
							{
								if(rfd[j] == -1) //把conn_sock添加到数组里
								{
									rfd[j] = conn_sock;
									printf("New Connection! %s:%d\n", inet_ntoa(remote.sin_addr), ntohs(remote.sin_port));
									break;
								}
							}

							if(j == nums)
							  close(conn_sock); //fd_set存不下
						}
						//conn_sock读事件就绪
						else if(i != 0 && FD_ISSET(rfd[i], &rfds))
						{
							char buf[1024];
							ssize_t s = read(rfd[i], buf, sizeof(buf)-1);
							if(s > 0)
							{
								buf[s] = 0;
								printf("client# %s\n", buf);
								//读完后再监测写事件
								int j = 0;
								for(; j < nums; ++j) //遍历数组
								{
									if(wfd[j] == -1) 
									{
										wfd[j] = rfd[i];
										break;
									}
								}

								rfd[i] = -1; //不监测读了
								if(j == nums)
								  close(rfd[i]); //无法监测更多的写事件

							}
							else if(s == 0)
							{
								printf("Closed!\n");
								close(rfd[i]);
								rfd[i] = -1;
								break;
							}
							else
							{
								perror("read");
								continue;
							}
						}
						//conn_sock写事件就绪
						else if(i != 0 && FD_ISSET(wfd[i], &wfds))
						{
							const char* msg = "HTTP/1.1 200 OK \r\n\r\n<html><h1>hello world! </h1></html>\n";
							write(wfd[i], msg, strlen(msg));
							wfd[i] = -1;
							close(wfd[i]);
						}
					}
				}
				break;
		}

		
	}

	close(listen_sock);
	return 0;
}
