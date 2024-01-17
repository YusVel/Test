#define MSG_SIZE  256
#define ADRESS "178.208.81.25" ///удаленный сервер Нидерланды
#define PORT 5000
double calculate(double x, double y, char action)
{
	switch (action)
	{
	case '+': return x + y; break;
	case '-': return x - y; break;
	case '*': return x * y; break;
	case '/': return x / y; break;
	}
}

int good_num(char msg[],int size_of_msg)
{
	int count_points = 0;
	for(int i = 0;i<size_of_msg&&msg[i]!='\0';i++)
	{
		if((msg[i] ==','||msg[i] =='.')&&i>0)
		{
			msg[i] ='.';
			count_points++;
			if(count_points>1)
			{
				return 0;
			}
			continue;
		}
		if(msg[i]<48||msg[i]>57)
		{
			return 0;
		}
	}
	return 1;
}
int good_action(char ch)
{
	if(ch=='+'||ch=='-'||ch=='*'||ch=='/'){return 1;}
	else{return 0;}
}


int get_valid_int()
{

int num = 0;
int good_read =scanf("%d",&num);
while(good_read!=1||getchar()!=10)
{
printf("INPUT ERROR! ENTER INT AGAIN!!! ");
	
	while (getchar()!=10)
	{	
		good_read = 0;
	}
	good_read = scanf("%d",&num);
}
return num;
}

void get_adress_from_sock(int sock, char adr[], int size_adr)
{
	
	struct sockaddr_in a = {0};
	socklen_t s = sizeof(a);
	int err = getpeername(sock, (struct sockaddr*)&a,&s);
	if(err==-1){printf("ERROR getsockname");};
	sprintf(adr,"%s", inet_ntoa(a.sin_addr));
}

void get_CLIENT_IP( char buffer[], int s_buffer)
{
const char* router_server = "192.168.0.1";
int dns_port = 0;
 
struct sockaddr_in serv ={0};
 
int sock = socket ( AF_INET, SOCK_DGRAM, 0);
 

if(sock < 0)
{
perror("Socket error");
}
serv.sin_family = AF_INET;
serv.sin_addr.s_addr = inet_addr(router_server);
serv.sin_port = htons( 0 );
int err = connect( sock , (const struct sockaddr*) &serv , sizeof(serv) );
if(err==-1){printf("connect faild (get_client_IP)\n");exit(EXIT_FAILURE);}
struct sockaddr_in name;
socklen_t namelen = sizeof(name);
err = getsockname(sock, (struct sockaddr*) &name, &namelen);

inet_ntop(AF_INET, &name.sin_addr, buffer, s_buffer);
shutdown(sock,SHUT_RDWR);
close(sock); 
}

void get_SERVER_IP(char adr[], int size_adr)
{
	struct sockaddr_in host_adr = {0};
	gethostname(adr,size_adr);
	struct hostent *host;
	if ((host = gethostbyname(adr)) == NULL)
	{
        printf("gethostbyname error\n");
        exit(0);
   	}
	host_adr.sin_family = AF_INET;
	host_adr.sin_port = htons(PORT);
	host_adr.sin_addr = *((struct in_addr*)host->h_addr_list[0]);
	char *tmp = inet_ntoa(host_adr.sin_addr);
	sprintf(adr,"%s", inet_ntoa(host_adr.sin_addr));
	if(adr[0]=='1'&&adr[1]=='2'&&adr[2]=='7'&&adr[4]=='0')
	{
	get_CLIENT_IP(adr,size_adr);
	}
}
 int BIND (int socketFD, const struct sockaddr_in *addr, socklen_t addr_size)
 {
	 int result = bind (socketFD,(struct sockaddr*)addr,addr_size);
	 if(result==-1){perror("\n***BINDING ERROR***\n"); exit(EXIT_FAILURE);}
	 else {printf("***BINDING SUCCESSED***\n"); return result;}
 }

 int SOCKET (int domain, int type, int protocol)
 {
	 int result = socket (domain, type, protocol);
	 if(result==-1){perror("\n***SOCKET CREATION ERROR***\n"); exit(EXIT_FAILURE);}
	 else {printf("SOCKET FD: %i \n",result);return result;}
 }
 
  int ACCEPT (int socket_server, const struct sockaddr_in *addr, socklen_t *addr_size)
 {
	 int result = accept (socket_server,(struct sockaddr*)addr,addr_size);
	 if(result==-1){perror("\n***ACCEPTION ERROR***\n"); exit(EXIT_FAILURE);}
	 else {return result;}
 }
 int CONNECT (int socket_server, const struct sockaddr_in *addr_server, socklen_t addr_size)
 {
	 int result = connect (socket_server,(struct sockaddr*)addr_server,addr_size);
	 if(result==-1){perror("\n***CONNECTION ERROR***\n"); exit(EXIT_FAILURE);}
	 else {printf("***CONNECTION SUCCESSED***\n");return result;}
 }
  int LISTEN (int socket_server, int lim_clients)
 {
	 int result = listen (socket_server,lim_clients);
	 if(result==-1){perror("\n***LISTENING ERROR***\n"); exit(EXIT_FAILURE);}
	 else {printf("LISTENING.....\n");return result;}
 }
 
 void check_connetion_with_clients(int serversocket,int clientsocket[],struct sockaddr_in clientadr[], int *count_clients)
 {
	 int clientadr_size = sizeof(clientadr[0]);
	 memset(&clientadr[0],0,clientadr_size);
	 char buffer[128] = {0};
	 if((*count_clients)==0)
	 {
		 memset(&clientadr[0],0,clientadr_size);
		 printf("***ЖДЕМ КЛИЕНТОВ***\n");
		 int s = ACCEPT(serversocket,&clientadr[0],&clientadr_size);
		 clientsocket[0] = s;
		 get_adress_from_sock(clientsocket[0],buffer,128);
		 printf("**ACCEPT new client (%s)!***\n",buffer);
		 if(s!=-1){(*count_clients)++;}
		 
	 }
	 struct sockaddr_in name;
	 socklen_t namelen = sizeof(name);
	 for (int i = 0;i<(*count_clients);i++)
	 {
		//printf("ВСЕГО клиентов %i\n",(*count_clients));
		//printf("CLIENT %i\n",i);
		char test[32] = "TEST5";
		write(clientsocket[i],test,32);
		read(clientsocket[i],test,32);
		if(strlen(test)==9)
		{
			getsockname(clientsocket[i], (struct sockaddr*) &name, &namelen);
			inet_ntop(AF_INET, &name.sin_addr, buffer, 128);
			//printf("Connection with client(%s) exists\n",buffer);
		}
		else
		{
			getsockname(clientsocket[i], (struct sockaddr*) &name, &namelen);
			inet_ntop(AF_INET, &name.sin_addr, buffer, 128);
			printf("***We loose client (%s)***\n",buffer);
			(*count_clients)--;
			printf("***На сервере %i клиент(-а)(-ов)***\n",*count_clients);
			int temp = i;
			while(temp<*count_clients)
			{
				clientsocket[temp]= clientsocket[++temp];
			}
		}
	 }
	 // printf("***На сервере %i клиент(-а)(-ов)***\n",*count_clients);
 }
 int check_connetion_with_server(int clientsocket, const struct sockaddr_in serveradr )
 {
	char test[32] = "TEST5";
	int err = read(clientsocket,test,32);
	//printf("Количество прочитанных байт: %i\n",err);
	/*
	if(err!=5)
	{
		printf("***ПОТЕРЯНО СОЕДИНЕНИЕ С СЕРВЕРОМ***\n");
		//shutdown(clientsocket,SHUT_RDWR);
		//close(clientsocket);
		//clientsocket = SOCKET(AF_INET,SOCK_STREAM,0);
		for(int i = 0;i<15;i++)
		{
			if(CONNECT(clientsocket,serveradr,sizeof(serveradr))==0){break;}
			else{printf("***ПОТЕРЯНО СОЕДИНЕНИЕ С СЕРВЕРОМ***\n");}
			if(i==14){printf("\n**ПИЗДА СЕРВАКУ***\n");exit(EXIT_FAILURE);}
		}
	return 1;
	}
	*/
	//printf("получил от сервера: %s\n",test);
	sprintf(test,"%s","123456789");
	write(clientsocket,test,32);
	//printf("Отправил серверу: %s\n",test);
 }