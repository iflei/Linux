#include <stdio.h>
#include <poll.h>
#include <unistd.h>

//int poll(struct pollfd *fds, nfds_t nfds, int timeout);

//struct pollfd {
//	int   fd;         /* file descriptor */
//  short events;     /* requested events */
//  short revents;    /* returned events */
//};

int main()
{
	struct pollfd evs;
	evs.fd = 0;
	evs.events = POLLIN;
	evs.revents = 0;
	int timeout = -1; //阻塞
	while(1)
	{
		switch(poll(&evs, 1, timeout))
		{
			case 0:
				printf("timeout!\n");
				break;
			case -1:
				perror("poll");
				break;
			default:
				{
					if(evs.revents & POLLIN)
					{
						char buf[1024];
						ssize_t s = read(evs.fd, buf, sizeof(buf)-1);
						if(s > 0)
						{
							buf[s-1] = 0;
							printf("%s\n", buf);
						}
						else if(s < 0)
							perror("read");
					}
				}
				break;
		}
	}
	return 0;
}
