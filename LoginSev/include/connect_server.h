#pragma once
#include <stdio.h>
#include <ctype.h>
#include <pthread.h>
#include <signal.h>
#include <mysql/mysql.h>
#include <sys/stat.h>
#include <iostream>
#include <list>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "res.h"
#include <stdlib.h>
#include <cstdlib>
#include <list>
using namespace std;
typedef struct DTinfor
{

	char IP[16];
	 int port;
};//大厅的ip port
typedef struct DTsize
{
	int client;
	int num;//这个大厅的人数
    DTinfor dtinfor;
};
class connect_server
{
public:
	connect_server();
	~connect_server();
private:
	struct sockaddr_in serverAddr;//这个socket是监听客户端的
	//还有一个socket监听大厅 我accept()
	int listener;
	int DTlisten;
	MYSQL mysql;
public:
	void Bind();
	void Listen();
	void Run();
	bool sqlfind(int id,char *password);
	int sqlAdd(char *name, char *password);
	void sendDTip();
	void accept_connect(int epollfd, int fd);
    void addfd(int epollfd, int fd, bool enable_et);//添加事件
	int setnonblocking(int sockfd);//设置非阻塞
	void connect_mysql();
	DTinfor chooseDT();
	list<DTsize> DTlist;
     


	
};

