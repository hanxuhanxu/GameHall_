#ifndef _PACKDEF_H
#define _PACKDEF_H 

#include<list>
#include <string>
#include<iostream>
#include<WinSock2.h>
using namespace std;


#define _HOST_IP        inet_addr("192.168.43.66")
//#define _MY_IP      inet_addr(/*"10.51.211.173"*/"192.168.43.187"/*"10.50.131.160"*/)
#define _MY_IP_STR   "192.168.137.1"
//边界值
#define _DEF_PORT 1234   /* 8003*/
#define _DEF_NAME_SIZE  64       //用户名长度
#define _DEF_PASSWORD_SIZE  64
#define _DEF_ID_SIZE   64             //用户id
#define _DEF_GAME_NAME  64
#define _DEF_GAME_NUM  100    //游戏数
#define _DEF_DESK_NUM  100     //桌子数
#define _DEF_SIZE 4096       
#define _DEF_BUFFERSIZE  2000*1024   
#define _DEF_GAMEBUFFERSIZE  30*1024 
#define _MAX_PROTOCOL_LEN 100    //协议长度
//#define _MAX_PATH_LEN  100
//#define _MAX_NAME_LEN  100
//#define _DEF_STREAMSIZE  1024/**1024*/

//消息
#define UM_GAMEMSG      WM_USER + 1
#define UM_DESKMSG     WM_USER + 2
#define UM_GAMELIST_MSG  WM_USER + 3
#define UM_DESKINFO_MSG  WM_USER + 4
////网络消息
//#define NM_READMSG  WM_USER + 50

//协议包类型

#define _DEF_PROTOCOL_BASE  100
#define _DEF_PROTOCOL_ONLINE_RQ                 _DEF_PROTOCOL_BASE  +0     //登录
#define _DEF_PROTOCOL_ONLINE_RS                  _DEF_PROTOCOL_BASE  +1     //登录回复
#define _DEF_PROTOCOL_OFFLINE_RQ                _DEF_PROTOCOL_BASE  +2     //下线
#define  _DEF_PROTOCOL_REGISTER_RQ              _DEF_PROTOCOL_BASE  +3     //注册
#define  _DEF_PROTOCOL_REGISTER_RS               _DEF_PROTOCOL_BASE  +4    //注册回复
#define  _DEF_PROTOCOL_GAMELIST_RS	             _DEF_PROTOCOL_BASE +5    //游戏列表回复
#define _DEF_PROTOCOL_GAMECHOOSE_RQ	     _DEF_PROTOCOL_BASE +6    //游戏选择请求
#define _DEF_PROTOCOL_GAMECHOOSE_RS	     _DEF_PROTOCOL_BASE +7    //回复桌子情况
#define _DEF_PROTOCOL_CONNECTHALL_RQ      _DEF_PROTOCOL_BASE+8    //连接大厅请求
#define _DEF_PROTOCOL_CONNECTHALL_RS       _DEF_PROTOCOL_BASE+9    //连接大厅回应
#define _DEF_PROTOCOL_LOGINHALL_RQ            _DEF_PROTOCOL_BASE+8
#define _DEF_PROTOCOL_LOGINHALL_RS             _DEF_PROTOCOL_BASE+9

//#define _DEF_PROTOCOL_HALLINFO					_DEF_PROTOCOL_BASE+100    //登录
#define _DEF_PROTOCOL_SITDOWN_RQ             _DEF_PROTOCOL_BASE +20
#define _DEF_PROTOCOL_SITDOWN_RS              _DEF_PROTOCOL_BASE +21//对用户选择桌子的回复  满了就回复不能坐，能做就把位置发给用户,并对本桌其他人发送本桌信息
#define _DEF_PROTOCOL_PARTNET_RS   _DEF_PROTOCOL_BASE +22//回复桌子上人的信息,若此桌子上加入了人我就重新把本桌信息发过去
#define _DEF_PROTOCOL_GAMEREADY_RQ   _DEF_PROTOCOL_BASE +23//请求准备
#define _DEF_PROTOCOL_GAMEREADY_RS  _DEF_PROTOCOL_BASE +24//发送本桌信息，如果全都准备了客户端自己就开始
#define _DEF_PROTOCOL_GAMEOVER_RQ  _DEF_PROTOCOL_BASE +25//还不知道怎么写
#define _DEF_PROTOCOL_GAMEOVER_RS  _DEF_PROTOCOL_BASE +26

#define _DEF_PROTOCOL_GAMEMSG_RQ  _DEF_PROTOCOL_BASE +27//要转发的消息
#define _DEF_PROTOCOL_GAMEMSG_RS  _DEF_PROTOCOL_BASE +28//转发给你的消息
//协议包
typedef int PackdefType;
//上线请求 上线回复 下线请求

struct User  //用户结构体
{
	//char m_userId[_DEF_ID_SIZE];
	int m_userId;
	char m_username[_DEF_NAME_SIZE];
	int score;
	int IsReady;//这里我加了一个是否准备，客户端需要显示的
};
struct Desk  //桌子结构体
{
	int Num;
	User user[20];
};

//CString myid;

struct Game{
	int playnum;//这里加了一个这个游戏是几个人玩
	char  GameNum[20];
	char GameName[64];
	char GameInfo[4096];

};

struct STRU_ONLINE  //注册请求包
{
	PackdefType m_nType;//协议类型
	char m_username[_DEF_NAME_SIZE];
	char m_password[_DEF_PASSWORD_SIZE];
};

struct STRU_REGISTER_RS  //注册回复
{
	PackdefType m_nType;//协议类型
	BOOL IfSuccess;
	int m_userId;
};

typedef struct STRU_ONLINERS//登录请求
{
	PackdefType m_nType;//协议类型
	BOOL IfSuccess;
	int		m_userId;//id
	char m_username[_DEF_NAME_SIZE]; //用户名
	char m_password[_DEF_PASSWORD_SIZE];
	char m_HallIp[16];  //登录成功返回的大厅服务器的ip
	int		m_HallPort;       //登录成功返回的大厅服务器的port
}STRU_LOINRQ;

 struct STRU_OFFLINE
{
	PackdefType m_nType;//协议类型
	char m_MyIP[16];
	char m_username[_DEF_PASSWORD_SIZE];
};




typedef struct STRU_CONNECT_HALL  //大厅连接请求包
{
	PackdefType m_nType;//协议类型
	User user;
}STRU_LOGINHALL_RQ;

typedef struct STRU_CONNECT_HALL_RS  //大厅连接回复包
{
	PackdefType m_nType;//协议类型
	BOOL IfSuccess;
}STRU_LOGINHALL_RS;

struct STRU_HALL_GAMELIST_RS  //游戏列表回复包
{
	PackdefType m_nType;
	Game	m_szGameList[5];
	int GameCount;   //游戏总数
};

struct STRU_GAMECHOOSE_RQ   //选择游戏请求包
{ 
	PackdefType m_nType;
	char i[20]; //游戏编号
}; 

struct STRU_GAMECHOOSE_RS   //选择游戏回复包
{
	PackdefType m_nType;
	Desk desk[_DEF_DESK_NUM];
};

struct STRU_HALL_INFO
{
	PackdefType m_nType;
	int m_ManNum;
};


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


#endif