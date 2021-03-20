#include <iostream>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <time.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT	 5101

//Client side socket

int main() { 
	int sockfd, n;
	socklen_t len;
	char buffer[1024];
	struct sockaddr_in servaddr;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if(sockfd < 0){
		std::cout << "Error establishing connection\n";
		exit(1);
	}	
	
	std::cout <<"Connection established\n";

	memset(&servaddr, 0, sizeof(servaddr)); 
	strcpy(buffer,"ping");
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; // localhost
	servaddr.sin_port = htons(PORT); // port number

	/*Sets the server time out to 1 second*/
	time_t start, now; //RTT variables, start = after the ping message, now = after the pong message	
	struct timeval timeout;
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;

	if(setsockopt(sockfd,SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof timeout) < 0){
		std::cout<<"Error setting timeout\n";
		exit(1);
	}

	/*Sends 10 pings to the server. If the server responds, prints out the RTT (now-start)
	 * If the server doesn't respond, prints an error message.*/
	for(int i = 0; i < 10; i++){
		sendto(sockfd, (const char *)buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *) &servaddr, len);
		time(&start);
		n = recvfrom(sockfd, (char *)buffer, sizeof(buffer),MSG_WAITALL, ( struct sockaddr *) &servaddr, &len);
		now = time(NULL);

		if(n == -1){
			std::cout << "Server timeout\n";
		}
		else{
			buffer[n] = '\0';
			std::cout << difftime(now,start)  << "\n";
		}
	}
	close(sockfd);
	return 0;
}
