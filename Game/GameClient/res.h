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
//�߽�ֵ
#define _DEF_PORT 1234   /* 8003*/
#define _DEF_NAME_SIZE  64       //�û�������
#define _DEF_PASSWORD_SIZE  64
#define _DEF_ID_SIZE   64             //�û�id
#define _DEF_GAME_NAME  64
#define _DEF_GAME_NUM  100    //��Ϸ��
#define _DEF_DESK_NUM  100     //������
#define _DEF_SIZE 4096       
#define _DEF_BUFFERSIZE  2000*1024   
#define _DEF_GAMEBUFFERSIZE  30*1024 
#define _MAX_PROTOCOL_LEN 100    //Э�鳤��
//#define _MAX_PATH_LEN  100
//#define _MAX_NAME_LEN  100
//#define _DEF_STREAMSIZE  1024/**1024*/

//��Ϣ
#define UM_GAMEMSG      WM_USER + 1
#define UM_DESKMSG     WM_USER + 2
#define UM_GAMELIST_MSG  WM_USER + 3
#define UM_DESKINFO_MSG  WM_USER + 4
////������Ϣ
//#define NM_READMSG  WM_USER + 50

//Э�������

#define _DEF_PROTOCOL_BASE  100
#define _DEF_PROTOCOL_ONLINE_RQ                 _DEF_PROTOCOL_BASE  +0     //��¼
#define _DEF_PROTOCOL_ONLINE_RS                  _DEF_PROTOCOL_BASE  +1     //��¼�ظ�
#define _DEF_PROTOCOL_OFFLINE_RQ                _DEF_PROTOCOL_BASE  +2     //����
#define  _DEF_PROTOCOL_REGISTER_RQ              _DEF_PROTOCOL_BASE  +3     //ע��
#define  _DEF_PROTOCOL_REGISTER_RS               _DEF_PROTOCOL_BASE  +4    //ע��ظ�
#define  _DEF_PROTOCOL_GAMELIST_RS	             _DEF_PROTOCOL_BASE +5    //��Ϸ�б�ظ�
#define _DEF_PROTOCOL_GAMECHOOSE_RQ	     _DEF_PROTOCOL_BASE +6    //��Ϸѡ������
#define _DEF_PROTOCOL_GAMECHOOSE_RS	     _DEF_PROTOCOL_BASE +7    //�ظ��������
#define _DEF_PROTOCOL_CONNECTHALL_RQ      _DEF_PROTOCOL_BASE+8    //���Ӵ�������
#define _DEF_PROTOCOL_CONNECTHALL_RS       _DEF_PROTOCOL_BASE+9    //���Ӵ�����Ӧ
#define _DEF_PROTOCOL_LOGINHALL_RQ            _DEF_PROTOCOL_BASE+8
#define _DEF_PROTOCOL_LOGINHALL_RS             _DEF_PROTOCOL_BASE+9

//#define _DEF_PROTOCOL_HALLINFO					_DEF_PROTOCOL_BASE+100    //��¼
#define _DEF_PROTOCOL_SITDOWN_RQ             _DEF_PROTOCOL_BASE +20
#define _DEF_PROTOCOL_SITDOWN_RS              _DEF_PROTOCOL_BASE +21//���û�ѡ�����ӵĻظ�  ���˾ͻظ��������������Ͱ�λ�÷����û�,���Ա��������˷��ͱ�����Ϣ
#define _DEF_PROTOCOL_PARTNET_RS   _DEF_PROTOCOL_BASE +22//�ظ��������˵���Ϣ,���������ϼ��������Ҿ����°ѱ�����Ϣ����ȥ
#define _DEF_PROTOCOL_GAMEREADY_RQ   _DEF_PROTOCOL_BASE +23//����׼��
#define _DEF_PROTOCOL_GAMEREADY_RS  _DEF_PROTOCOL_BASE +24//���ͱ�����Ϣ�����ȫ��׼���˿ͻ����Լ��Ϳ�ʼ
#define _DEF_PROTOCOL_GAMEOVER_RQ  _DEF_PROTOCOL_BASE +25//����֪����ôд
#define _DEF_PROTOCOL_GAMEOVER_RS  _DEF_PROTOCOL_BASE +26

#define _DEF_PROTOCOL_GAMEMSG_RQ  _DEF_PROTOCOL_BASE +27//Ҫת������Ϣ
#define _DEF_PROTOCOL_GAMEMSG_RS  _DEF_PROTOCOL_BASE +28//ת���������Ϣ
//Э���
typedef int PackdefType;
//�������� ���߻ظ� ��������

struct User  //�û��ṹ��
{
	//char m_userId[_DEF_ID_SIZE];
	int m_userId;
	char m_username[_DEF_NAME_SIZE];
	int score;
	int IsReady;//�����Ҽ���һ���Ƿ�׼�����ͻ�����Ҫ��ʾ��
};
struct Desk  //���ӽṹ��
{
	int Num;
	User user[20];
};

//CString myid;

struct Game{
	int playnum;//�������һ�������Ϸ�Ǽ�������
	char  GameNum[20];
	char GameName[64];
	char GameInfo[4096];

};

struct STRU_ONLINE  //ע�������
{
	PackdefType m_nType;//Э������
	char m_username[_DEF_NAME_SIZE];
	char m_password[_DEF_PASSWORD_SIZE];
};

struct STRU_REGISTER_RS  //ע��ظ�
{
	PackdefType m_nType;//Э������
	BOOL IfSuccess;
	int m_userId;
};

typedef struct STRU_ONLINERS//��¼����
{
	PackdefType m_nType;//Э������
	BOOL IfSuccess;
	int		m_userId;//id
	char m_username[_DEF_NAME_SIZE]; //�û���
	char m_password[_DEF_PASSWORD_SIZE];
	char m_HallIp[16];  //��¼�ɹ����صĴ�����������ip
	int		m_HallPort;       //��¼�ɹ����صĴ�����������port
}STRU_LOINRQ;

 struct STRU_OFFLINE
{
	PackdefType m_nType;//Э������
	char m_MyIP[16];
	char m_username[_DEF_PASSWORD_SIZE];
};




typedef struct STRU_CONNECT_HALL  //�������������
{
	PackdefType m_nType;//Э������
	User user;
}STRU_LOGINHALL_RQ;

typedef struct STRU_CONNECT_HALL_RS  //�������ӻظ���
{
	PackdefType m_nType;//Э������
	BOOL IfSuccess;
}STRU_LOGINHALL_RS;

struct STRU_HALL_GAMELIST_RS  //��Ϸ�б�ظ���
{
	PackdefType m_nType;
	Game	m_szGameList[5];
	int GameCount;   //��Ϸ����
};

struct STRU_GAMECHOOSE_RQ   //ѡ����Ϸ�����
{ 
	PackdefType m_nType;
	char i[20]; //��Ϸ���
}; 

struct STRU_GAMECHOOSE_RS   //ѡ����Ϸ�ظ���
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

		//1.���������
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