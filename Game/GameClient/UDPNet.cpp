#include "stdafx.h"
#include "UDPNet.h"

bool bFlagQuit;
UDPNet::UDPNet(IMediator* pMediator)
{
	bFlagQuit=true;
	m_socketClient=NULL;
	m_TCPsockClient=NULL;
	m_pMediator=pMediator;
	m_hThread=NULL;
	m_hThreadRecv=NULL;
}


UDPNet::~UDPNet(void)
{
}


bool UDPNet::InitNetWork()
{
	WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {

		UnInitNetWork();
        return false;
    }


    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {

       UnInitNetWork();
        return false;
    }


	/*	STRU_ONLINERS so;
		so.m_nType=_DEF_PROTOCOL_GAMECHOOSE_RQ;
		ConnectHall((char*)&so);*/
	

//2.雇个人  接口 套接字
	m_socketClient=socket(AF_INET ,SOCK_DGRAM ,IPPROTO_UDP );
	BOOL bval = TRUE;

	if(INVALID_SOCKET==m_socketClient)
	{
		UnInitNetWork();
        return false;
	}

	TRACE("%d\n",GetLastError());
//3.选址--连接
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr =GetValidIp();
    addr.sin_port = htons(8000);
	if(SOCKET_ERROR == bind(m_socketClient,(const sockaddr*)&addr,sizeof(addr)))
	{
		UnInitNetWork();
			TRACE("%d\n",GetLastError());
		return false;
	}
//	//创建线程
	m_hThread=(HANDLE)_beginthreadex(NULL,0,&ThreadProc,this,0,0);
	TRACE("%d\n",GetLastError());
	return true;
}

bool UDPNet::ConnectHall(char * szbuf)
{
	STRU_ONLINERS* so=(STRU_ONLINERS*)szbuf;
	CString name;
	name=so->m_username;
	m_TCPsockClient=socket(AF_INET ,SOCK_STREAM ,IPPROTO_TCP );
	if(INVALID_SOCKET==m_TCPsockClient)
	{
		UnInitNetWork();
        return false;
	}

	sockaddr_in addr2;
	addr2.sin_family = AF_INET;
	addr2.sin_addr.S_un.S_addr =/*GetValidIp()*/inet_addr("192.168.43.66");/*;inet_addr(so->m_HallIp*//*);*/
	addr2.sin_port = htons(/*so->m_HallPort*/8888);

	if(SOCKET_ERROR == connect(m_TCPsockClient,(const sockaddr*)&addr2,sizeof(addr2)))
	{
		TRACE("%d\n",GetLastError());
		UnInitNetWork();
		TRACE("%d\n",GetLastError());
		return false;
	}

	//给大厅发一个请求连接包
	STRU_CONNECT_HALL sc;
	sc.m_nType=_DEF_PROTOCOL_CONNECTHALL_RQ;
	User me;

	me.m_userId=so->m_userId;
	strcpy_s((char*)me.m_username,(size_t)sizeof(me.m_username),(char*)&name);
	m_pMediator->SendDataTCP(inet_addr("192.168.43.66"),(char*)&sc,sizeof(sc));
	//((CMyQQClientDlg*)GetParent())->GetMediator()->SendDataTCP(_HOST_IP,((char *)&sp),sizeof(sp));

	m_hThreadRecv = (HANDLE)_beginthreadex(NULL,0,&ThreadRecv,this,0,0);
	return true;
}

unsigned  __stdcall  UDPNet::ThreadProc( void * lpvoid)
{
	UDPNet * pthis=(UDPNet*)lpvoid;
	//recv
	char RecvBuf[_DEF_BUFFERSIZE]={0};
	sockaddr_in addrClient;
	int nClientSize=sizeof(sockaddr_in);
	int nRelReadNum=0;
	
	while(/*pthis->*/bFlagQuit)
	{
		nRelReadNum=recvfrom(pthis->m_socketClient,RecvBuf,_DEF_BUFFERSIZE,0,(sockaddr *)&addrClient,&nClientSize);

		  TRACE("%d\n",GetLastError());

		if(nRelReadNum>0)
		{
			//处理
			pthis->m_pMediator->DealData(RecvBuf,addrClient.sin_addr.S_un.S_addr);
		}
	}
	return 0;
}

unsigned  __stdcall UDPNet::ThreadRecv( void * lpvoid)
 {
	UDPNet* pthis  = (UDPNet*)lpvoid;
	int nRelReadNum;
	int nPackSize=0;
	CString str; //提示语
	while(bFlagQuit)
	{
		//接收包大小
		/*nRelReadNum =  recv(pthis->m_TCPsockClient,(char*)&nPackSize,sizeof(int),0);
		if(nRelReadNum <=0)
		{
			continue;
		}*/
		HWND  mainHwnd = ::GetForegroundWindow();//当前最顶端窗口句柄			
//		//接收完整数据包
		char pszbuf[21000]={0}; 
		/* int noffset = 0;
		 while(1)
		 {*/
			nRelReadNum =  recv(pthis->m_TCPsockClient,pszbuf,21000,0);
			//noffset += nRelReadNum;
			////nPackSize -= nRelReadNum;
	  //     if(nRelReadNum<=0)
		 //  {
			//   break;
		 //  }
		 //}
			STRU_HALL_GAMELIST_RS * game=( STRU_HALL_GAMELIST_RS *)pszbuf;
		 	int * ptype=(int *)pszbuf;
			//switch (* ptype)
			//{
			//case _DEF_PROTOCOL_GAMELIST_RS: //大厅的连接回复包
			//	{
			//		STRU_CONNECT_HALL_RS* sc=(STRU_CONNECT_HALL_RS*)pszbuf;
					/*if(sc->IfSuccess==TRUE)
					{*/
						
						pthis->m_pMediator->DealDataTCP((char*)pszbuf,pthis->m_TCPsockClient);
				/*	}
					else
					{
						str="连接大厅失败";
						MessageBox(mainHwnd,str,_T("提示"),MB_OKCANCEL);
						return 0;
					}		
					 str="";
		             str.Empty();*/
				memset(pszbuf,0,sizeof(pszbuf)/sizeof(char));
		/*		}
					 break;
				case */
			
   }	
	return 0;
}

bool UDPNet::SendData(long lSendIP, char *szbuf ,int nlen)
{
	sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(/*_DEF_PORT*/4000/*8003*/);
	addr.sin_addr.S_un.S_addr=lSendIP;

	if(!szbuf || nlen <=0)
		return false;
	int * ptype=(int *)szbuf;
		if(sendto(m_socketClient,( char *)szbuf,nlen,0,(sockaddr *)&addr,sizeof(addr))<=0)
		{
			TRACE("%d\n",WSAGetLastError());
	         return false;
	    }
	return true;
}


bool UDPNet::SendDataTCP(SOCKET sock,char* szbuf,int nlen)
{
		if(!szbuf || nlen <=0)
		return false;

		////发送包大小
		//if(send(m_TCPsockClient,(const char*)&nlen,sizeof(int),0)<0)
		//return false;
		//包内容
		if(send(m_TCPsockClient,szbuf,nlen,0)<0)
			return false;
	
		return true;
}

void UDPNet::UnInitNetWork()
{
	bFlagQuit=false;
	WSACleanup();
	if(m_hThreadRecv )
	{
		if(WAIT_TIMEOUT == WaitForSingleObject(m_hThreadRecv,100))
			TerminateThread(m_hThreadRecv,-1);
		
		CloseHandle(m_hThreadRecv);
		m_hThreadRecv = NULL;
	
	}
	 if(m_socketClient)
	 {
		 closesocket(m_socketClient);
		 m_socketClient=INVALID_SOCKET;
		 m_socketClient = NULL;
	 }
	 // if(m_TCPsockClient)
	 //{
		// shutdown(m_TCPsockClient,SD_BOTH);
		// closesocket(m_TCPsockClient);
		// m_TCPsockClient = NULL;
	 //}
	 if(m_hThread)
	 {
		  if( WaitForSingleObject(m_hThread,100) == WAIT_TIMEOUT)
		 {
			 TerminateThread(m_hThread,-1);
		 }
		 CloseHandle(m_hThread);
		 m_hThread=NULL;
	 }

}