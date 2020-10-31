#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include <unistd.h> 
#include<math.h>

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
	
	int choice;
	char a[5];

	do{
				n = write(newsockfd, "Enter choice: \n1.Sin\n2.Cos\n3.Tan\n4.Cosine\n5.Sec\n6.Cot\n0.Exit\n",strlen("Enter choice: 					\n1.Sin\n2.Cos\n3.Tan\n4.Cosine\n5.Sec\n6.Cot\n0.Exit\n"));
			read(newsockfd, &choice,sizeof(int));
			cout<<"Client- Choice is"<<choice<<endl;
			
			if(choice!=0)
			{
				n = write(newsockfd, "Enter angle in degree: ",strlen("Enter angle in degree"));
				if(n < 0)
					error("Error writing socket");
				
				read(newsockfd, (char*)&a,sizeof(a));
				cout<<"Client- Angle is"<<a<<endl;
				float angle=(float)atof(a);
				while(angle>360)
				{
					angle=angle-360;
				}
				angle=angle*(3.14/180);
				cout<<"angle(radian)"<<angle<<endl;
				float answer = 0;
				switch(choice)
				{
					case 1:answer = sin(angle);break;
					case 2: answer = cos(angle);break;
					case 3: answer = tan(angle);break;
					case 4:answer = 1/(sin(angle)); break;
					case 5:answer = 1/(cos(angle));break;
					case 6: answer = 1/(tan(angle));break;
					
				}
				write(newsockfd, &answer, sizeof(float));
			}

			
			
			
			
	}while(choice!=0);

	

	

	

	close(sockfd);
	close(newsockfd);
	return 0;
	
}

