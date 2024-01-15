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
const char* google_dns_server = "192.168.0.1";
int dns_port = 0;
 
struct sockaddr_in serv ={0};
 
int sock = socket ( AF_INET, SOCK_DGRAM, 0);
 

if(sock < 0)
{
perror("Socket error");
}
serv.sin_family = AF_INET;
serv.sin_addr.s_addr = inet_addr(google_dns_server);
serv.sin_port = htons( 0 );
int err = connect( sock , (const struct sockaddr*) &serv , sizeof(serv) );
if(err==-1){printf("connect faild (get_client_IP)\n");}
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


