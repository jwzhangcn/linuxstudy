#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == sockfd){
		perror("socket");
		return -1;
	}
	struct sockaddr_in myaddr;
	memset(&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INET_ANY);
	myaddr.sin_port = htons(8080);

	if(-1 == bind(sockfd, (struct sockaddr*)&myaddr), sizeof(myaddr)){
		perror("bind");
		return -1;
	}

	if(-1 == listen(sockfd, 4)){
		perror("listen");
		return -1;
	}

	fd_set fds, rfds;
	int keyboard_fd = 0;
	FD_ZERO(&fds);
	FD_SET(sockfd, &fds);
	FD_SET(keyboard_fd, &fds);
	while (1) {
		rfds = fds;
		struct timeval tv = {1}; //1s
		retval = select(fd+1, &rfds, NULL, NULL, &tv);
		if (retval < 0) {
			perror("select");
			break;
		} else if (0 == retval) {
			printf("timeout.........!\n");
			continue;
		}


		char buf[1024];
		if (FD_ISSET(keyboard_fd, &rfds)) {

			printf("Datafromkeyboard!\n");
			read(0, buf, sizeof(buf));
		}

		if
			(FD_ISSET(sockfd, &rfds)){
				struct sockaddr_in cliaddr;
				memset(&cliaddr, 0, sizeof(cliaddr));
				int connfd = accept(sockfd, (struct sockaddr*)&cliaddr, sizeof(cliaddr));
				if(-1 == connfd){
					perror("connected");
					return -1
				}
			}
	}
			return 0;
	}
