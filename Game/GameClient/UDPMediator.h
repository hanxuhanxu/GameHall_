#pragma once
#include"IMediator.h"
#include"GameListDlg.h"
#include"resource.h"
#include"RoomDlg.h"

class UDPMediator;
typedef void (UDPMediator::*PFUN) (char *  , long);

struct ProtocolMap
{
	PackdefType m_nType;
	PFUN        m_pfun;
};

class UDPMediator:public IMediator
{
public:
	UDPMediator(CWnd * pWnd);
	virtual~UDPMediator(void);
public:
	bool open();
	void close();
	bool SendData(long lSendIP, char * szbuf ,int nlen);
	bool SendDataTCP(SOCKET sock, char * szbuf ,int nlen);
	void DealData(char * szbuf , long lRecvIP) ;
	void DealDataTCP(char * szbuf ,SOCKET sock) ;
	void DealRegisterInfoRs(char * szbuf , long lRecvIP) ;
	void DealGameList(char * szbuf ,SOCKET sock) ;
	void DealDesk(char * szbuf ,SOCKET sock) ;
public:
	INet * m_pUDPNetClient;
	PFUN m_protocolMap[_MAX_PROTOCOL_LEN];
	CWnd * m_pWnd;
	CGameListDlg * pGameDlg;
	CRoomDlg * pDeskDlg;
public:
	void DealOnLineRs(char * szbuf , long lRecvIP);//DealOffLineRq   上线回应
public:
	void GameMenu();
};

