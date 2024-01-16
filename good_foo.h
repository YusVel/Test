#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <math.h>
#include "good_foo.c"


double calculate (double x,double y, char action);
int good_num(char msg[],int size_of_msg);
int good_action(char ch);
void get_adress_from_sock(int sock, char adr[], int size_adr);
int get_valid_int();
void get_SERVER_IP(char adr[], int size_adr);
void get_CLIENT_IP( char *buffer, int s_buffer);
int BIND (int socketFD, const struct sockaddr_in *addr, socklen_t addr_size);
int ACCEPT (int socket_server, const struct sockaddr_in *addr, socklen_t *addr_size);
int SOCKET (int domain, int type, int protocol);
int CONNECT (int socket_server, const struct sockaddr_in *addr_server, socklen_t addr_size);
int LISTEN (int socket_server, int lim_clients);
