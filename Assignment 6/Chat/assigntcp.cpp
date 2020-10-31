#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include <unistd.h> 
using namespace std;

#define PORT 3206

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int main(){
	int sockfd,newsockfd,n;
	char buffer[255];

	sockaddr_in server_addr,client_addr;
	socklen_t clilen;

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	
	if(sockfd<0)
		error("SOCKET CREATE ERROR");
	
	
	bzero((char *)&server_addr,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=INADDR_ANY;
	server_addr.sin_port=htons(PORT);

	if(bind(sockfd ,(struct sockaddr*)&server_addr,sizeof(server_addr)) <0)
		error("ERROR IN BINDING");

	listen(sockfd ,10); //10 - max no. of client that can connect
	clilen = sizeof(client_addr);


	newsockfd = accept(sockfd, (struct sockaddr*)&client_addr,&clilen);
	if(newsockfd<0)
		error("Error on accept");
	
	while(1)
	{
		cout<<"Awaiting for client.."<<endl;
		bzero(buffer,255);
		n = read(newsockfd , buffer ,255);
		if(n<0)
			error("Error in reading");
		cout<<"Client: "<<buffer<<endl;
		bzero(buffer,255);
		fgets(buffer, 255 , stdin);
		
		n = write(newsockfd, buffer, strlen(buffer));
		if(n<0)
			error("Error in writing");
		
	}

	close(sockfd);
	close(newsockfd);
	return 0;
	
}

