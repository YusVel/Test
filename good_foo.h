#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <math.h>
#include "good_foo.c"

#define MSG_SIZE  256
#define ADRESS "178.208.81.25" ///удаленный сервер Нидерланды
#define port 5000

double calculate (double x,double y, char action);
int good_num(char msg[],int size_of_msg);
int good_action(char ch);
void get_adress(int sock, char adr[], int size_adr);
