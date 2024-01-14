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
	struct sockaddr_in serveradr = {0}, clientadr ={0};
	
	serversocket = socket(AF_INET,SOCK_STREAM,0);
	if(serversocket==-1){printf("ERROR! Fail of getting serverFD"); exit(1);}
	else{printf("serverFD = %i\n",serversocket);}
	serveradr.sin_family = AF_INET;
	serveradr.sin_port = htons(port);
	serveradr.sin_addr.s_addr = inet_addr("178.208.81.25");
	
	char S_adr[64] = {0};
	inet_ntop(AF_INET,&serveradr.sin_addr,S_adr,64);
	printf("SERVER ADRESS: %s\n",S_adr);
	printf("SERVER PORT: %i\n",ntohs(serveradr.sin_port));
	
	if(bind(serversocket,(struct sockaddr*)&serveradr, sizeof(serveradr))==-1)
	{
		printf("ERROR! Fail of BIND serversocet"); exit(1);
	}
	else
	{
		printf("BIND succesed!\n");
	}
	
	if(listen(serversocket,5)==-1)
	{
		printf("ERROR! Fail of LISTEN serversocet"); exit(1);
	}
	else
	{
		printf("LISTENING....\n");
	}
	int clientadr_size = sizeof(clientadr);
	clientsocket = accept(serversocket,(struct sockaddr*)&clientadr, &clientadr_size);
	if(clientsocket ==-1)
	{
		printf("ERROR! Fail of ACCEPT clientsocet"); exit(1);
	}
	else
	{
		printf("ACCEPT new client!\n");
	}
	char msg[256] = "Hello, my friend!\n";
	int i = 0;
	do
	{
	write(clientsocket,msg, 256);
	read(clientsocket,msg,256);
	printf("%s\n",msg);
	i=atoi(msg);
	}while(i<1000000);

	
	
	shutdown(clientsocket,SHUT_RDWR);
	close(clientsocket);
	shutdown(serversocket,SHUT_RDWR);
	close(serversocket);
	
	return 0;
}
