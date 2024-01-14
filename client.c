#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define port 5000

int main()
{
	printf("Server: Hello!\n");
	int serversocket,clientsocket;
	struct sockaddr_in serveradr = {0};
	clientsocket  = socket(AF_INET,SOCK_STREAM,0);
	
	if(clientsocket==-1)
	{
	printf("ERROR! Fail of getting clientFD"); exit(1);
	}
	else
	{
	printf("ClientFD = %i\n",serversocket);
	}
	serveradr.sin_family = AF_INET;
	serveradr.sin_port = htons(port);
	serveradr.sin_addr.s_addr = inet_addr("178.208.81.25");
	if(connect(clientsocket,(struct sockaddr*)&serveradr, sizeof(serveradr))==-1)
	{
		printf("ERROR! Fail of BIND serversocet"); exit(1);
	}
	else
	{
		printf("BIND succesed!\n");
	}
	char msg[256] = "0";
	read(clientsocket,msg,256);
	for (int i = 0;i<1000000;i++)
	{
		printf("GET from server: %s \n",msg);
		sprintf(msg,"%i",i);
		write(clientsocket,msg, 256);
		read(clientsocket,msg,256);
	}

	
	shutdown(clientsocket,SHUT_RDWR);
	close(clientsocket);
	
return 0;
}