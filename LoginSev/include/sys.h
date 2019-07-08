#ifndef _PACKDEF_H
#define _PACKDEF_H

#include<list>
#include <string>
#include<iostream>
using namespace std;


#define _HOST_IP  inet_addr(/*"10.51.211.173"*//*"192.168.43.161"*/"10.50.131.160")
#define _MY_IP      inet_addr(/*"10.51.211.173"*//*"192.168.43.161"*/"10.50.131.160")
#define _MY_IP_STR /*"10.51.211.173"*/"10.50.131.160"
//边界值
#define EPOLL_SIZE 1000
#define _DEF_PORT 1234
#define SERVER_PORT 4000
#define _DEF_NAME_SIZE  64       //用户名长度
#define _DEF_PASSWORD_SIZE  64
#define _DEF_ID_SIZE   64             //用户id
#define _DEF_GAME_NUM  100    //游戏数
#define _DEF_DESK_NUM  100     //桌子数
#define _DEF_SIZE 4096
#define _DEF_BUFFERSIZE  2000*1024
#define _MAX_PROTOCOL_LEN 100    //协议长度
//#define _MAX_PATH_LEN  100
//#define _MAX_NAME_LEN  100
//#define _DEF_STREAMSIZE  1024/**1024*/

//消息
//#define UM_ONLINEMSG      WM_USER + 1
//#define UM_OFFLINEMSG     WM_USER + 2
//#define UM_DATAINFOMSG  WM_USER + 3
//#define UM_DESTROYMSG  WM_USER + 4
//#define UM_FILEINFOMSG   WM_USER + 5
//#define UM_PICINFOMSG    WM_USER + 6
//#define UM_ONLINE_ADD   WM_USER + 7
//#define UM_OFFLINE_ADD  WM_USER + 8
//#define UM_INVITEMSG       WM_USER + 9
//#define UM_JOINMSG          WM_USER + 10
//#define UM_JOIN_HIS_MSG   WM_USER + 11
//#define UM_ONKEEPCONNECTMSG  WM_USER + 12
//#define UM_FILEINFO  WM_USER + 13
////网络消息
//#define NM_READMSG  WM_USER + 50

//协议包类型

#define _DEF_PROTOCOL_BASE  100
#define _DEF_PROTOCOL_ONLINE_RQ                 _DEF_PROTOCOL_BASE  +0    //登录
#define _DEF_PROTOCOL_ONLINE_RS                  _DEF_PROTOCOL_BASE  +1
#define _DEF_PROTOCOL_OFFLINE_RQ                _DEF_PROTOCOL_BASE  +2    //下线
#define  _DEF_PROTOCOL_REGISTER_RQ              _DEF_PROTOCOL_BASE  +3     //注册
#define  _DEF_PROTOCOL_REGISTER_RS               _DEF_PROTOCOL_BASE  +4
#define  _DEF_PROTOCOL_GAMELIST_RS	             _DEF_PROTOCOL_BASE +5    //游戏列表回复
#define _DEF_PROTOCOL_GAMECHOOSE_RQ	     _DEF_PROTOCOL_BASE +6    //游戏选择请求
#define _DEF_PROTOCOL_GAMECHOOSE_RS	     _DEF_PROTOCOL_BASE +7
//协议包
typedef int PackdefType;
//上线请求 上线回复 下线请求

typedef struct User  //用户结构体
{
	char m_userId[_DEF_ID_SIZE];
	char m_username[_DEF_NAME_SIZE];
};
typedef struct Desk  //桌子结构体
{
	int Num;
	User one;
	User two;
	User three;
};

struct STRU_ONLINE  //注册
{
	PackdefType m_nType;//协议类型
	char m_username[_DEF_NAME_SIZE];
	char m_password[_DEF_PASSWORD_SIZE];
};

struct STRU_OFFLINE
{
	PackdefType m_nType;//协议类型
	char m_MyIP[16];
	char m_username[_DEF_PASSWORD_SIZE];
};
struct STRU_REGISTER_RS
{
	PackdefType m_nType;//协议类型
    bool IfSuccess;
	int m_userId;
};

typedef struct STRU_ONLINERS//登录回复
{
	PackdefType m_nType;//协议类型
    bool IfSuccess;
	int m_userId;//id
	char m_username[_DEF_NAME_SIZE]; //用户名
	char m_HallIp[16];  //登录成功返回的大厅服务器的ip
	int m_HallPort;       //登录成功返回的大厅服务器的port
}STRU_LOINRQ;//登录请求

struct STRU_HALL_GAMELIST_RS  //游戏列表回复包
{
	PackdefType m_nType;
	char	m_szGameList[_DEF_GAME_NUM];
};

struct STRU_GAMECHOOSE_RQ
{
	PackdefType m_nType;
	int i;
};

struct STRU_GAMECHOOSE_RS
{
	PackdefType m_nType;
	Desk desk[_DEF_DESK_NUM];
};

/*
static long GetValidIp()
{
	char szName[20] = { 0 };
	struct hostent *remoteHost = NULL;
	long ip;
	struct in_addr addr;

	//1.获得主机名
	if (!gethostname(szName, sizeof(szName)))
	{
		//2.IPLIST
		remoteHost = gethostbyname(szName);
		int i = 0;
		while (remoteHost->h_addr_list[i] != 0) {
			addr.s_addr = *(u_long *)remoteHost->h_addr_list[i++];
			ip = addr.s_addr;
		}
	}
	return ip;
    }
*/

#endif
