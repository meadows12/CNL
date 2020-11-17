#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;

#define PORT 3206
#define buflen 1000;
#define SERVER_ADDRESS "127.0.0.1"
void die(const char *s) //method to print error and exit
{
	perror(s);
	exit(1);
}
int main() 
{

	struct sockaddr_in server_addr;
	
	//step 1: Creating Socket
	int sock;
	if((sock=socket(AF_INET,SOCK_DGRAM,0))==-1) //SOCK_DGRAM= SOCKET Type is datagram
	{											//0=PACKET TYPE USUALLY 0 or (IPPROTo_UDP)
		die("SOCKET CREATE ERROR");
	}
	//specify server address type, port as 8999 and address
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(PORT);
	server_addr.sin_addr.s_addr=inet_addr(SERVER_ADDRESS);; //INADDR_ANY takes current IP Address of PC
	//htons() converts the unsigned short integer hostshort from host byte order to network byte order.
	
	int slen=sizeof(server_addr);
	socklen_t cli=sizeof(server_addr);
	int choice = 1,msg_len;
	do
	{
		cout<<"Enter choice\n1.Send text file\n0.Exit\n";
		cin>>choice;
		char num = choice;
		sendto(sock,&num,sizeof(num),0,(struct sockaddr *)&server_addr,slen); //send choice
		switch(choice)
		{
			case 1:
				cout<<"\nENter Filename:";
				char filename[100];
				cin>>filename;
				fstream fout1;
				fout1.open(filename,ios::in|ios::out|ios::binary);
				fout1.seekg(0,ios::end);
				int filesize=fout1.tellg(); //get file size
				char *filebuff=new char[filesize];
				fout1.seekg(0,ios::beg);
				fout1.read(filebuff,filesize); //reading file content

				msg_len=sendto(sock,filename,strlen(filename),0,(struct sockaddr *)&server_addr,slen); //send filename
				if(msg_len==-1)
					die("Filename error");

				msg_len=sendto(sock,(void *)&filesize,sizeof(filesize),0,(struct sockaddr *)&server_addr,slen); //send filesize
				if(msg_len==-1)
					die("Filesize error");



				msg_len=sendto(sock,filebuff,filesize,0,(struct sockaddr *)&server_addr,slen); //send file conetents
				if(msg_len==-1)
					die("File transmission error");
				else
					cout<<"Transmission Successful";
				fout1.close();
		}	
	
	
	}while(choice!=0);
}
