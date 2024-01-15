
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

void get_adress(int sock, char adr[], int size_adr)
{
	
	struct sockaddr_in a = {0};
	socklen_t s = sizeof(a);
	int err = getpeername(sock, (struct sockaddr*)&a,&s);
	if(err==-1){printf("ERROR getsockname");};
	sprintf(adr,"%s", inet_ntoa(a.sin_addr));
}


void get_my_IP(char adr[])
{
	
}