#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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
	
	socklen_t len = sizeof(local);
	if(bind(sock, (struct sockaddr*)&local, len) < 0)
	{
		perror("bind");
		exit(3);
	}

	if(listen(sock, 5) < 0)
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
		if(socket < 0)
		{
			perror("accept");
			continue;
		}

		printf("client ip: %s, port: %d\n", inet_ntoa(remote.sin_addr), ntohs(remote.sin_port)); 

		char buf[1024];
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
				printf("client# %s\n", buf);
			}
			else
			{
				printf("client disconnect!\n");
				close(new_socket);
				break;
			}
		}
	}
	
	return 0;
}
