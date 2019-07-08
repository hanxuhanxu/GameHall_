
// GameClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GameClient.h"
#include "GameClientDlg.h"
#include "afxdialogex.h"
#include"UDPMediator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGameClientDlg �Ի���



CGameClientDlg::CGameClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGameClientDlg::IDD, pParent)
	, m_UserName(_T(""))
	, m_Password(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pMediator=new UDPMediator(this);
	m_pListDlg=new CGameListDlg;
	m_pRoomDlg=new CRoomDlg;
}

void CGameClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_UserName);
	DDX_Text(pDX, IDC_EDIT2, m_Password);
}

BEGIN_MESSAGE_MAP(CGameClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CGameClientDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CGameClientDlg::OnBnClickedButton3)
	ON_MESSAGE(UM_GAMELIST_MSG,& CGameClientDlg::OnGameListMsg)
	ON_MESSAGE(UM_DESKINFO_MSG,& CGameClientDlg::OnDeskInfoMsg)
END_MESSAGE_MAP()


// CGameClientDlg ��Ϣ�������

BOOL CGameClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	if(!m_pMediator->open())
	{
		TRACE("%d\n",GetLastError());
		MessageBox(_T("open failed"));
		return FALSE;
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CGameClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGameClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CGameClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGameClientDlg::OnBnClickedButton2()//�û�ע��
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	int nlen = m_UserName.GetLength();
	if(nlen <0 || nlen >16)
	{
		MessageBox(_T("�û���������1-16λ��Ч�ַ�"));
		return;
	}
	 nlen = m_Password.GetLength();
	if(nlen <6 || nlen >16)
	{
		MessageBox(_T("����������6-16λ��Ч�ַ�"));
		return;
	}

	//sd5����
	CString src =m_Password/*"fasdfasdfasdfnmmw,enrsudfnsmndfejkjhuasdmnf"*/;
	Md5Encode encode_obj;
	std::string s;
	s=CW2A(src.GetString());
	string ret = encode_obj.Encode(s);

	m_Password=ret.c_str();

    STRU_ONLINE so;
	so.m_nType=_DEF_PROTOCOL_REGISTER_RQ;
	WideCharToMultiByte(CP_ACP,0,m_UserName,-1,so.m_username,sizeof(so.m_username),0,0);
	WideCharToMultiByte(CP_ACP,0,m_Password,-1,so.m_password,sizeof(so.m_password),0,0);

	m_pMediator->SendData(_HOST_IP,(char*)&so,sizeof(so));
}


void CGameClientDlg::OnBnClickedButton3() //��¼
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	int nlen = m_UserName.GetLength();
	if(nlen <0 || nlen >16)
	{
		MessageBox(_T("�û���������1-16λ��Ч�ַ�"));
		return;
	}
	 nlen = m_Password.GetLength();
	if(nlen <6 || nlen >16)
	{
		MessageBox(_T("����������6-16λ��Ч�ַ�"));
		return;
	
	}

	CString src =m_Password/*"fasdfasdfasdfnmmw,enrsudfnsmndfejkjhuasdmnf"*/;
	Md5Encode encode_obj;
	std::string s;
	s=CW2A(src.GetString());
	string ret = encode_obj.Encode(s);

	m_Password=ret.c_str();

	STRU_LOINRQ so;
	so.m_nType=_DEF_PROTOCOL_ONLINE_RQ;
	so.m_userId= _ttoi(m_UserName);
	so.IfSuccess=0;
	char * sss="saaa";
	strcpy_s((char*)&so.m_HallIp,(size_t)sizeof(so.m_HallIp),sss);

	so.m_HallPort=1111;
	strcpy_s((char*)&so.m_username,(size_t)sizeof(so.m_username),sss);

	WideCharToMultiByte(CP_ACP,0,m_Password,-1,so.m_password,sizeof(so.m_password),0,0);
	m_pMediator->SendData(_HOST_IP,(char*)&so,sizeof(so));
}

LRESULT 	CGameClientDlg::OnGameListMsg(WPARAM w,LPARAM l)
{
	m_pListDlg->Create(IDD_DLG_GAME);
	STRU_HALL_GAMELIST_RS * game=(STRU_HALL_GAMELIST_RS*)w;

	m_pListDlg->SendMessage(UM_GAMEMSG,(WPARAM)game,0);

	m_pListDlg->ShowWindow(SW_SHOW);
	return 0;
}

LRESULT CGameClientDlg::	OnDeskInfoMsg(WPARAM w,LPARAM l)
{
	STRU_GAMECHOOSE_RS * sg=(STRU_GAMECHOOSE_RS* )w;
	m_pRoomDlg->Create(IDD_DLG_ROOM);
	m_pRoomDlg->SendMessage(UM_DESKMSG,(WPARAM)sg,0);
	m_pRoomDlg->ShowWindow(SW_SHOW);
	return 0;
}