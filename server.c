#include "good_foo.h"
#define MSG_SIZE  256
#define ADRESS "178.208.81.25" ///удаленный сервер Нидерланды
#define PORT 5000
#define LIM_CLIENTS 4

int main()
{
	printf("Server: Hello!\n");
	int serversocket,clientsocket;
	struct sockaddr_in serveradr = {0}, clientadr ={0};
	
	serversocket = SOCKET(AF_INET,SOCK_STREAM,0);
	serveradr.sin_family = AF_INET;
	serveradr.sin_port = htons(PORT);
	int choice = 0;
	char S_adr[MSG_SIZE] = {0};
	
	gethostname(S_adr,MSG_SIZE);
	printf("SERVERNAME: %s\n",S_adr);
	get_SERVER_IP(S_adr,MSG_SIZE);
	
	do
	{
	printf("Укажите какой адрес использоват для инициализации сокета (IPv4):\n");
	printf("1 - Localhost loopback (127.0.0.1)\n");
	printf("2 - IP адрес: %s - назначен вашим роутером/провайдером\n",S_adr);
	printf("3 - Ввести адрес вручную -->");
	choice = get_valid_int();
	switch(choice)
	{
		case 1:serveradr.sin_addr.s_addr = inet_addr("127.0.0.1");break;
		case 2:serveradr.sin_addr.s_addr = inet_addr(S_adr);break;
		case 3: printf("IPv4 (ddd.ddd.ddd.ddd): "); 
				char tmp[14] = {0};
				mark:
				scanf("%s",tmp);
				if(inet_pton(AF_INET,tmp,&serveradr.sin_addr)==0){printf("Введенный адрес не соответствует IPv4!Повторите ввод: ");goto mark;}
	}

	}while(choice<1||choice>3);	
	
	inet_ntop(AF_INET,&serveradr.sin_addr,S_adr,64);
	printf("SERVER ADRESS: %s\n",S_adr);
	printf("SERVER PORT: %i\n",ntohs(serveradr.sin_port));
	
	BIND(serversocket,&serveradr, sizeof(serveradr));
	
	LISTEN(serversocket,LIM_CLIENTS);
	
	int clientadr_size = sizeof(clientadr);
	
	clientsocket = ACCEPT(serversocket,&clientadr, &clientadr_size);
	get_adress_from_sock(clientsocket,S_adr,64);
	printf("ACCEPT new client (%s)!\n",S_adr);

	char msg[MSG_SIZE] = "Hello, my friend!";
	write(clientsocket,msg,MSG_SIZE);
	memset(msg,'\0',MSG_SIZE);
	double x = 0;
	double y = 0;
	double result = 0;
	do
	{
		sprintf(msg,"Введите первое число: ");
		do
		{
		write(clientsocket,msg,MSG_SIZE);
		read(clientsocket,msg,MSG_SIZE);
		if(good_num(msg,MSG_SIZE)==0)
		{
			sprintf(msg,"Недопустимые символы в сообщении! Введите повторно ПЕРВОЕ число: ");
		}
		}while(good_num(msg,MSG_SIZE)==0);
		x = atoi(msg);
		memset(msg,'\0',MSG_SIZE);
		
		
		sprintf(msg,"Введите второе число: ");
		do
		{
		write(clientsocket,msg,MSG_SIZE);
		read(clientsocket,msg,MSG_SIZE);
		if(good_num(msg,MSG_SIZE)==0)
		{
			sprintf(msg,"Недопустимые символы в сообщении! Введите повторно ВТОРОЕ число: ");
		}
		}while(good_num(msg,MSG_SIZE)==0);
		y = atoi(msg);
		memset(msg,'\0',MSG_SIZE);
		
		
		sprintf(msg,"Введите действие (-,+,/,*): ");
		do
		{
		write(clientsocket,msg,MSG_SIZE);
		read(clientsocket,msg,MSG_SIZE);
		if(good_action(msg[0])==0)
		{
			sprintf(msg,"Недопустимые символы в сообщении! Введите ДЕЙСТВИЕ повторно: ");
		}
		}while(good_action(msg[0])==0);
			
		result = calculate(x,y,msg[0]);
		sprintf(msg,"Результат вычисления: %5.2lf %c %5.2lf = %5.2lf\n",x,msg[0],y,result);
		printf("%s",msg);
		write(clientsocket,msg,MSG_SIZE);
		memset(msg,'\0',MSG_SIZE);

		sprintf(msg,"Для выхода введите символ 'q'. Для продолжения введите любое сообщение: ");
		write(clientsocket,msg,MSG_SIZE);
		read(clientsocket,msg,MSG_SIZE);
		if(msg[0]=='q'&&msg[1]=='\0'){break;}
	}while(1);


	
	shutdown(clientsocket,SHUT_RDWR);
	close(clientsocket);
	shutdown(serversocket,SHUT_RDWR);
	close(serversocket);
	
	return 0;
}
