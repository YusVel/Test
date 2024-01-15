#include "good_foo.h"

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
	int choice = 0;
	char S_adr[64] = {0};
	gethostname(S_adr,64);
	printf("HOSTNAME: %s\n",S_adr);
	do
	{
	printf("Укажите какой адрес сервера использовать(IPv4):\n");
	printf("1 - НИДЕРЛАНДЫ\n");
	printf("2 - Localhost loopback (127.0.0.1)\n");
	printf("3 - IP адресс, назначенный сетью(роутером/провайдером) \n");
	printf("4 - Ввести в адресс ручную -->");
	choice = get_valid_int();
	switch(choice)
	{
		case 1:serveradr.sin_addr.s_addr = inet_addr(ADRESS);break;
		case 2:serveradr.sin_addr.s_addr = inet_addr("127.0.0.1");break;
		case 3:serveradr.sin_addr.s_addr = inet_addr("127.0.0.1");break;
		case 4: printf("IPv4 (ddd.ddd.ddd.ddd): "); 
				char tmp[14] = {0};
				mark:
				scanf("%s",tmp);
				if(inet_pton(AF_INET,tmp,&serveradr.sin_addr)==0){printf("Введенный адрес не соответствует IPv4!Повторите ввод: ");goto mark;}
	}

	}while(choice<1||choice>3);	
	
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
		get_adress (clientsocket,S_adr,64);
		printf("ACCEPT new client (%s)!\n",S_adr);
	}
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
