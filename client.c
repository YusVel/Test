#include "good_foo.h"

int main()
{
	printf("Server: Hello!\n");
	int serversocket,clientsocket;
	struct sockaddr_in serveradr = {0};
	clientsocket = socket(AF_INET,SOCK_STREAM,0);
	
	char S_adr[64] = {0};
	
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
	serveradr.sin_addr.s_addr = inet_addr(ADRESS);
	if(connect(clientsocket,(struct sockaddr*)&serveradr, sizeof(serveradr))==-1)
	{
		printf("ERROR! Fail of CONNECTION to server"); exit(1);
	}
	else
	{
		printf("CONNECTION successed!\n");
	}
	char msg[MSG_SIZE] = "0";
	read(clientsocket,msg,MSG_SIZE);
	printf("SERVER: ""%s""\n",msg);


	do
	{
		read(clientsocket,msg,MSG_SIZE);
		do
		{
		printf("SERVER: ""%s""",msg);
		scanf("%s",msg);
		write(clientsocket,msg,MSG_SIZE);
		
		if(good_num(msg,MSG_SIZE)==0)
		{
			read(clientsocket,msg,MSG_SIZE);
		}
		}while(good_num(msg,MSG_SIZE)==0);
		
		read(clientsocket,msg,MSG_SIZE);
		do
		{
		printf("SERVER: ""%s""",msg);
		scanf("%s",msg);
		write(clientsocket,msg,MSG_SIZE);
		if(good_num(msg,MSG_SIZE)==0)
		{
			read(clientsocket,msg,MSG_SIZE);
		}
		}while(good_num(msg,MSG_SIZE)==0);
		
		read(clientsocket,msg,MSG_SIZE);
		do
		{
		printf("SERVER: ""%s""",msg);
		scanf("%s",msg);
		write(clientsocket,msg,MSG_SIZE);
		if(good_action(msg[0])==0)
		{
			read(clientsocket,msg,MSG_SIZE);
		}
		}while(good_action(msg[0])==0);
			
		read(clientsocket,msg,MSG_SIZE);
		printf("SERVER: ""%s""",msg);
		memset(msg,'\0',MSG_SIZE);

		read(clientsocket,msg,MSG_SIZE);
		printf("SERVER: ""%s""",msg);
		scanf("%s",msg);
		write(clientsocket,msg,MSG_SIZE);
		if(msg[0]=='q'&&msg[1]=='\0'){break;}
	}while(1);
	
	shutdown(clientsocket,SHUT_RDWR);
	close(clientsocket);
	
return 0;
}
