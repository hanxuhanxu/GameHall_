#include "stdafx.h"
#include "UDPMediator.h"
#include"UDPNet.h"




UDPMediator::UDPMediator(CWnd * pWnd)
{
	m_pUDPNetClient=new UDPNet(this);
	m_pWnd=pWnd;
	m_HallIP=NULL;
	m_HallPort=0;
	pGameDlg=new CGameListDlg;
	pDeskDlg=new CRoomDlg;
}


UDPMediator::~UDPMediator(void)
{
    if(m_pUDPNetClient)
	{
		delete(m_pUDPNetClient);
		m_pUDPNetClient=NULL;
	}
	 if(pGameDlg)
	{
		delete(pGameDlg);
		pGameDlg=NULL;
	}
}

static const ProtocolMap m_ProtocolMapEntries[] =
{
	{_DEF_PROTOCOL_ONLINE_RS,&UDPMediator::DealOnLineRs},
	{_DEF_PROTOCOL_REGISTER_RS,&UDPMediator::DealRegisterInfoRs},
	{0,0}

};


bool UDPMediator::open(){
	/*STRU_HALL_GAMELIST_RS sh;
	sh.GameCount=2;
	SOCKET sock=NULL;
	Game game1;

	strcpy_s((char*)&game1.GameNum,(size_t)sizeof(game1.GameNum),"1");
	strcpy_s((char*)&game1.GameName,(size_t)sizeof(game1.GameName),"五子棋");

	strcpy_s((char*)&game1.GameInfo,(size_t)sizeof(game1.GameInfo),"这是五子棋游戏");
	Game game2;

	strcpy_s((char*)&game2.GameNum,(size_t)sizeof(game2.GameNum),"2");
	strcpy_s((char*)&game2.GameName,(size_t)sizeof(game2.GameName),"斗地主");

	strcpy_s((char*)&game2.GameInfo,(size_t)sizeof(game2.GameInfo),"这是斗地主游戏");

	sh.m_szGameList[0]=game1;
	sh.m_szGameList[1]=game2;*/



	//(pGameDlg->m_tabGame).InsertItem(0, (TCITEMW*)game2.GameName);

	//DealGameList((char*)&sh,sock);

	//STRU_GAMECHOOSE_RS sg;
	//sg.desk[3];
	////for(int i=0;i<3;i++)
	////{
	////	sg.desk[i].Num=i%2+1;
	////}
	//sg.desk[0].Num=2;
	//strcpy_s((char*)&sg.desk[0].user[0].m_username,(size_t)sizeof(sg.desk[0].user[0].m_username),"张三");
	//strcpy_s((char*)&sg.desk[0].user[1].m_username,(size_t)sizeof(sg.desk[0].user[1].m_username),"李四");

	//sg.desk[1].Num=1;
	//strcpy_s((char*)&sg.desk[1].user[0].m_username,(size_t)sizeof(sg.desk[1].user[0].m_username),"三三");

	//sg.desk[2].Num=3;
	//strcpy_s((char*)&sg.desk[2].user[0].m_username,(size_t)sizeof(sg.desk[2].user[0].m_username),"丽丽");
	//strcpy_s((char*)&sg.desk[2].user[1].m_username,(size_t)sizeof(sg.desk[2].user[1].m_username),"哈哈");
	//strcpy_s((char*)&sg.desk[2].user[2].m_username,(size_t)sizeof(sg.desk[2].user[1].m_username),"小王");


	//DealDesk((char*)&sg,sock);

	if( ! m_pUDPNetClient->InitNetWork())
	{
		TRACE("%d\n",GetLastError());
		return false;
	}

	STRU_ONLINERS so;
		so.m_nType=_DEF_PROTOCOL_GAMECHOOSE_RQ;
		m_pUDPNetClient->	ConnectHall((char*)&so);
	return true;
}
void UDPMediator::close()
{
	m_pUDPNetClient->UnInitNetWork();
}

bool UDPMediator::SendData(long lSendIP, char * szbuf ,int nlen)
{
	in_addr ia;
	ia.S_un.S_addr=lSendIP;
	int * ptype=(int *)szbuf;
		
	switch ( * ptype)
	{
	case _DEF_PROTOCOL_ONLINE_RS:
		{
			STRU_ONLINE* sd=(STRU_ONLINE*)szbuf;
			if( !m_pUDPNetClient->SendData(lSendIP,szbuf,nlen))
			return false;
			break;
		}
	case _DEF_PROTOCOL_ONLINE_RQ:
		{
			STRU_LOINRQ* sd=(STRU_LOINRQ*)szbuf;
			if( !m_pUDPNetClient->SendData(lSendIP,szbuf,nlen))
			return false;
			break;
		}

	default:
			STRU_ONLINE *so=(STRU_ONLINE *)szbuf;
			if( !m_pUDPNetClient->SendData(lSendIP,szbuf,nlen))
			return false;
		break;
	}
	return true;
}

bool UDPMediator::SendDataTCP(SOCKET sock, char * szbuf ,int nlen)
{
	int * ptype=(int *)szbuf;
		
	switch ( * ptype)
	{
	case _DEF_PROTOCOL_CONNECTHALL_RQ:
		{
			STRU_CONNECT_HALL * sc=(STRU_CONNECT_HALL*)szbuf;
			if( !m_pUDPNetClient->SendDataTCP(sock,szbuf,nlen))
			return false;
		}
		break;
	case _DEF_PROTOCOL_GAMECHOOSE_RQ:
		{
			STRU_GAMECHOOSE_RQ *sg=(STRU_GAMECHOOSE_RQ*)szbuf;
			if( !m_pUDPNetClient->SendDataTCP(sock,szbuf,nlen))
			return false;
		}
		break;

	default:
		break;
	}
	return true;
}

void UDPMediator::DealData(char * szbuf , long lRecvIP) 
{
	//拿到包的前四个字节代表包类型
	int * ptype=(int *)szbuf;
	int nn=sizeof(szbuf);
	//处理数据 遍历消息映射表
	int i = 0;
	while(1)
	{
		if(m_ProtocolMapEntries[i].m_nType == *ptype)
		{
			(this->*m_ProtocolMapEntries[i].m_pfun)(szbuf,lRecvIP);
			return ;
		}
		else if(m_ProtocolMapEntries[i].m_nType ==0 &&m_ProtocolMapEntries[i].m_pfun ==0 )
			return;

		i++;
	}
}

void UDPMediator::DealDataTCP(char * szbuf ,SOCKET sock) 
{

			int * ptype=(int *)szbuf;
			switch (* ptype)
			{
			case _DEF_PROTOCOL_CONNECTHALL_RS:  //大厅连接回应
				{
					//连接成功 进入选择游戏界面
					GameMenu();
                     //DealFileInfoRs(szbuf,sock);
				}
					 break;

			case _DEF_PROTOCOL_GAMELIST_RS: //游戏链表回应
				{
					STRU_HALL_GAMELIST_RS * game=( STRU_HALL_GAMELIST_RS *)szbuf;
                     DealGameList(szbuf,sock);


				}
					 break;

			case _DEF_PROTOCOL_GAMECHOOSE_RS:   //游戏桌子回应
				{
				      STRU_GAMECHOOSE_RS * sg=(STRU_GAMECHOOSE_RS*) szbuf;
					  DealDesk(szbuf,sock);
				}
				break;
			default:
				break;
			}
	
			return;
}

void UDPMediator::DealRegisterInfoRs(char * szbuf , long lRecvIP) 
{

	STRU_REGISTER_RS* sr=(STRU_REGISTER_RS*)szbuf;
	CString ID;
	ID.Format(_T("%d"), sr->m_userId);
	if(sr->IfSuccess==TRUE)
	{
		MessageBox((HWND)m_pWnd->m_hWnd,ID,_T("注册成功 ！ 您的用户名"),NULL);
		return;
	}
	else if(sr->IfSuccess==FALSE)
	{
		MessageBox((HWND)m_pWnd->m_hWnd,_T("用户名已存在"),_T("提示"),NULL);
		return;
	}
}

void UDPMediator::DealOnLineRs(char * szbuf , long lRecvIP) 
{
	STRU_ONLINERS* so=(STRU_ONLINERS*)szbuf;
	if(so->IfSuccess==TRUE)
	{
		//m_pWnd->PostMessage(UM_ONLINEMSG,(WPARAM)so,lRecvIP);
		//登录服务器返回大厅服务器的 ip port  连接大厅服务器
		m_HallIP=so->m_HallIp;
		m_HallPort=so->m_HallPort;
		m_pUDPNetClient->ConnectHall((char*)so);
	}
	else if(so->IfSuccess==FALSE)
	{
		MessageBox((HWND)m_pWnd->m_hWnd,_T("用户名或密码错误"),_T("提示"),NULL);
		return;
	}
}


void UDPMediator::GameMenu()
{
	pGameDlg->Create(IDD_DLG_GAME);
	pGameDlg->ShowWindow(SW_SHOW);
	pGameDlg->SetFocus();
}

void UDPMediator::DealGameList(char * szbuf ,SOCKET sock) 
{	
	STRU_HALL_GAMELIST_RS * game=(STRU_HALL_GAMELIST_RS*)szbuf;
	m_pWnd->SendMessage(UM_GAMELIST_MSG,(WPARAM)game,sock);
}

void UDPMediator::DealDesk(char * szbuf ,SOCKET sock) 
{
	STRU_GAMECHOOSE_RS * sg=(STRU_GAMECHOOSE_RS* )szbuf;
	m_pWnd->SendMessage(UM_DESKINFO_MSG,(WPARAM)sg,sock);
}