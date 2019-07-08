#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<fcntl.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<openssl/ssl.h>
#include<openssl/err.h>
#include<sys/mman.h>
#include<regex.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include<sys/epoll.h>
#include<pthread.h>

//using namespace std;

//#define BOOL bool
#define FALSE 0
#define TRUE 1

#define _DEF_PROTOCOL_BASE  100
#define _DEF_PROTOCOL_ONLINE_RQ                 _DEF_PROTOCOL_BASE  +0
#define _DEF_PROTOCOL_ONLINE_RS                  _DEF_PROTOCOL_BASE  +1
#define _DEF_PROTOCOL_OFFLINE_RQ                _DEF_PROTOCOL_BASE  +2
#define _DEF_PROTOCOL_DATAINFO_RQ            _DEF_PROTOCOL_BASE  +3
#define _DEF_PROTOCOL_DATAINFO_RS             _DEF_PROTOCOL_BASE  +4
#define  _DEF_PROTOCOL_REGISTER_RQ              _DEF_PROTOCOL_BASE  +5
#define  _DEF_PROTOCOL_REGISTER_RS               _DEF_PROTOCOL_BASE  +6

typedef int PackdefType;
//上线请求 上线回复 下线请求

struct STRU_ONLINE
{
	PackdefType m_nType;//协议类型
	char m_username[64];
	char m_password[64];
};

 struct STRU_OFFLINE
{
	PackdefType m_nType;//协议类型
	char m_MyIP[20];
	char m_username[64];
};

struct STRU_ONLINERS
{
	PackdefType m_nType;//协议类型
	//BOOL IfSuccess;
	char m_username[64];
};

struct STRU_REGISTER_RS
{
	PackdefType m_nType;//协议类型
	//BOOL IfSuccess;
};
