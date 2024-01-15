#include "good_foo.h"
#define MSG_SIZE  256
#define ADRESS "178.208.81.25" ///удаленный сервер Нидерланды
#define PORT 5000
int main()
{
	printf("Server: Hello!\n");
	int serversocket,clientsocket;
	struct sockaddr_in serveradr = {0};
	clientsocket = socket(AF_INET,SOCK_STREAM,0);
	

	
	if(clientsocket==-1)
	{
	printf("ERROR! Fail of getting clientFD"); exit(1);
	}
	else
	{
	printf("ClientFD = %i\n",serversocket);
	}
	serveradr.sin_family = AF_INET;
	serveradr.sin_port = htons(PORT);

	int choice = 0;
	char S_adr[MSG_SIZE] = {0};
	gethostname(S_adr,MSG_SIZE);
	printf("CLIENTNAME: %s\n",S_adr);
	get_my_IP(S_adr,MSG_SIZE);
	
	do
	{
	printf("Укажите адрес сервера для подключения(IPv4):\n");
	printf("1 - НИДЕРЛАНДЫ\n");
	printf("2 - Localhost loopback (127.0.0.1)\n");
	printf("3 - IP адрес: %s - назначен вашим роутером/провайдером\n",S_adr);
	printf("4 - Ввести адрес вручную -->");
	choice = get_valid_int();
	switch(choice)
	{
		case 1:serveradr.sin_addr.s_addr = inet_addr(ADRESS);break;
		case 2:serveradr.sin_addr.s_addr = inet_addr("127.0.0.1");break;
		case 3:serveradr.sin_addr.s_addr = inet_addr(S_adr);break;
		case 4: printf("IPv4 (ddd.ddd.ddd.ddd): "); 
				char tmp[14] = {0};
				mark:
				scanf("%s",tmp);
				if(inet_pton(AF_INET,tmp,&serveradr.sin_addr)==0){printf("Введенный адрес не соответствует IPv4!Повторите ввод: ");goto mark;}
	}

	}while(choice<1||choice>3);	
	

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
