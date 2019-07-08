#include"res.h"


#define FALSE 0
#define TRUE 1
#define BUFFSIZE 1024


int TCPSocket;
int UDPSocket;
char recvbuf[BUFFSIZE];
char sendbuf[BUFFSIZE];
MYSQL mysql;

struct sockaddr_in server_udp,client_udp;
struct sockaddr_in server_tcp,client_tcp;

void CreateUDPSocket();
void ConnectMysql();

void * udp_recv_thread(void *);
void * tcp_accept_thread(void *);
void * tcp_recv_thread(void *);



