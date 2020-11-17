#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fstream>
using namespace std;

#define PORT 3206
#define buflen 1000;


int main()
{
	
	int sd,connfd,len;
	
	
	struct sockaddr_in servaddr,cliaddr;
	
	//creation of socket
	sd = socket(AF_INET,SOCK_DGRAM,0);
	//SOCK_DGRAM= SOCKET Type is datagram, AF_INET= Domain, Address family
		//if the protocol is unspecified (a value of 0), the system selects a protocol that supports the requested socket   type.											//0=PACKET TYPE USUALLY 0 or (IPPROTo_UDP)
	if(sd == -1)
	{
		cout<<"Socket error"<<endl;
		exit(0);
	}
	else
		cout<<"Socket created in server"<<endl;

	bzero(&servaddr, sizeof(servaddr));

	//specify server address type, port as 8999 and address
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(PORT); 
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY); //INADDR_ANY takes current IP Address of PC
	//htons() converts the unsigned short i	nteger hostshort from host byte order to network byte order.

	//BINDING socket to port
	if(bind(sd,(struct sockaddr *)&servaddr,sizeof(servaddr))==-1)   //sock= socket(socket descriptor)
		cout<<"BINDIND ERROR";
	else
		cout<<"\nUDP SERVER STARTED.";

	
	len = sizeof(cliaddr);
	socklen_t cli=sizeof(cliaddr);

	int choice = 1,msg_len;
	while(1)
	{
		char num;
		recvfrom(sd,&num,sizeof(num),0,(struct sockaddr *)&cliaddr, &cli);
		choice = num;
		switch(choice)
		{
			case 1:
				char filename[100];
				bzero((char *)filename,sizeof(filename));
				msg_len=recvfrom(sd,filename,99,0,(struct sockaddr*)&cliaddr,&cli);
				if(msg_len==-1)
					cout<<"Filename error";
				cout<<"\nFilename:"<<filename;

				int filesize;
				msg_len=recvfrom(sd,(void *)&filesize,sizeof(filesize),0,(struct sockaddr*)&cliaddr,&cli);
				cout<<"\nFileSize:"<<filesize;
				char *filebuff=new char[filesize];


				bzero((char *)filebuff,sizeof(filebuff));
				msg_len=recvfrom(sd,filebuff,filesize,0,(struct sockaddr*)&cliaddr,&cli);
				ofstream fout1;
				fout1.open(filename,ios::out|ios::binary);
				if(!fout1)
				cout<<"CANNOT CREATE FILE";
				else
				{
					fout1.write(filebuff,filesize);
					fout1.close();
					cout<<"File received";
				}break;
			
		}
	}
	close(sd);
	return 0;
		
	
}
