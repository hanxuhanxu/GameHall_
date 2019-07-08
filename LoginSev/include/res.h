#ifndef _PACKDEF_H
#define _PACKDEF_H 

#include<list>
#include <string>
#include<iostream>
//#include<WinSock2.h>
using namespace std;


#define _HOST_IP  inet_addr(/*"10.51.211.173"*//*"192.168.43.247"*//*"10.50.92.200"*//*"192.168.88.130"*/"192.168.43.66")
//#define _MY_IP      inet_addr(/*"10.51.211.173"*/"192.168.43.187"/*"10.50.131.160"*/)
#define _MY_IP_STR /*"10.51.211.173"*//*"10.50.131.160"*/"192.168.137.1"
//边界值
#define  DT_MAX_NUM 100
#define EPOLL_SIZE 1000
#define _DEF_PORT 1234   /* 8003*/
#define _DEF_NAME_SIZE  64       //用户名长度
#define _DEF_PASSWORD_SIZE  64
#define _DEF_ID_SIZE   64             //用户id
#define _DEF_GAME_NAME  64
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
#define _DEF_PROTOCOL_ONLINE_RS                  _DEF_PROTOCOL_BASE  +1     //登录回复
#define _DEF_PROTOCOL_OFFLINE_RQ                _DEF_PROTOCOL_BASE  +2    //下线
#define  _DEF_PROTOCOL_REGISTER_RQ              _DEF_PROTOCOL_BASE  +3     //注册
#define  _DEF_PROTOCOL_REGISTER_RS               _DEF_PROTOCOL_BASE  +4    //注册回复
#define  _DEF_PROTOCOL_GAMELIST_RS	             _DEF_PROTOCOL_BASE +5    //游戏列表回复
#define _DEF_PROTOCOL_GAMECHOOSE_RQ	     _DEF_PROTOCOL_BASE +6    //游戏选择请求
#define _DEF_PROTOCOL_GAMECHOOSE_RS	     _DEF_PROTOCOL_BASE +7
#define _DEF_PROTOCOL_CONNECTHALL_RQ      _DEF_PROTOCOL_BASE+8   //连接大厅请求
#define _DEF_PROTOCOL_CONNECTHALL_RS       _DEF_PROTOCOL_BASE+9    //连接大厅回应
#define _DEF_PROTOCOL_LOGINHALL_RQ            _DEF_PROTOCOL_BASE+8
#define _DEF_PROTOCOL_LOGINHALL_RS             _DEF_PROTOCOL_BASE+9
//协议包
typedef int PackdefType;
//上线请求 上线回复 下线请求

struct User  //用户结构体
{
	char m_userId[_DEF_ID_SIZE];
	char m_username[_DEF_NAME_SIZE];
};
struct Desk  //桌子结构体
{
	int Num;
	User user[3];

};

struct STRU_ONLINE  //注册，登录请求包（一体）
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

typedef struct STRU_ONLINERS//登录回复
  {
      PackdefType m_nType;//协议类型
      bool IfSuccess;
      int m_userId;//id
      char m_username[_DEF_NAME_SIZE]; //用户名
      char m_password[_DEF_PASSWORD_SIZE];
	 char m_HallIp[16];  //登录成功返回的大厅服务器的ip
     int m_HallPort;       //登录成功返回的大厅服务器的port
 }STRU_LOINRQ;//登录请求


struct STRU_REGISTER_RS
{
	PackdefType m_nType;//协议类型
	bool IfSuccess;
	int m_userId;
};

struct STRU_CONNECT_HALL  //大厅连接请求包
{
	PackdefType m_nType;//协议类型
	User user;
};

struct STRU_CONNECT_HALL_RS  //大厅连接回复包
{
	PackdefType m_nType;//协议类型
	bool IfSuccess;
};

struct STRU_HALL_GAMELIST_RS  //游戏列表回复包
{
	PackdefType m_nType;
	char	m_szGameList[_DEF_GAME_NUM];
};

struct STRU_GAMECHOOSE_RQ   //选择游戏请求包
{ 
	PackdefType m_nType;
	int i; //游戏编号
}; 

struct STRU_GAMECHOOSE_RS
{
	PackdefType m_nType;
	Desk desk[_DEF_DESK_NUM];
};

struct STRU_HALL_INFO
{
	PackdefType m_nType;
	int m_ManNum;
};
/*

static long GetValidIp()
	{
		char szName[20] = {0};
		struct hostent *remoteHost = NULL;
		long ip;
		struct in_addr addr;

		//1.获得主机名
		if(!gethostname(szName,sizeof(szName)))
		{
				//2.IPLIST		
			remoteHost = gethostbyname(szName);
			int i = 0;
			while (remoteHost->h_addr_list[i] != 0) {
                 addr.s_addr = *(u_long *) remoteHost->h_addr_list[i++];
				 ip= addr.s_addr ;
            }
		}
		return ip;
	}

*/
#endif
