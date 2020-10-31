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

	int choice;
	char a[5];
	do
	{
		float answer = 0;
		bzero(buffer,255);
		
		n = read(sockfd, buffer, 255);   //entering choice
		if(n<0)
			error("Error in reading"); 
		cout<<"Server- "<<buffer<<endl;
		cin>>choice;
		write(sockfd, &choice, sizeof(int));

		if(choice!=0)
		{
			bzero(buffer,255);
		
			n = read(sockfd, buffer, 255);   //entering angle
			if(n<0)
				error("Error in reading"); 
			cout<<"Server- "<<buffer<<endl;
			cin>>a;
			write(sockfd, (char*)&a, sizeof(a));
			
			read(sockfd, &answer, sizeof(float));
			cout<<"Server- Answer is: "<<answer<<endl;
		}

		
		
		
	}while(choice!=0);

	
	close(sockfd);
	return 0;
}
