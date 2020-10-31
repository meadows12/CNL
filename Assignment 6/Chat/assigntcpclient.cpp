#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include <unistd.h> 
using namespace std;

#define PORT 3206
#define SERVER_ADDRESS "127.0.0.1"
void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int main(){
	int sockfd,newsockfd,n;
	char buffer[255];

	sockaddr_in server_addr;
	socklen_t clilen;

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	
	if(sockfd<0)
		error("SOCKET CREATE ERROR");
	else
		cout<<"Socket Created."<<endl;
	
	bzero((char *)&server_addr,sizeof(server_addr));
	
	server_addr.sin_addr.s_addr=inet_addr(SERVER_ADDRESS);
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(PORT);

	if(connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr))< 0 )
		error("Connection failed");

	while(1)
	{	
		bzero(buffer , 255);
		fgets(buffer , 255, stdin);
		n = write(sockfd , buffer , strlen(buffer));
		if(n<0)
			error("Error on writing");
		bzero(buffer , 255);
		n = read(sockfd, buffer , 255);
		if(n<0)
			error("Error on reading");
		cout<<"Server: "<<buffer<<endl;
		
	}
	close(sockfd);
	return 0;
}
