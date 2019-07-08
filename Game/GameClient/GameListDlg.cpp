// GameListDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GameClient.h"
#include "GameListDlg.h"
#include "afxdialogex.h"
#include"GameClientDlg.h"

// CGameListDlg �Ի���

IMPLEMENT_DYNAMIC(CGameListDlg, CDialogEx)

CGameListDlg::CGameListDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGameListDlg::IDD, pParent)
{
	m_pWnd=pParent;
}

CGameListDlg::~CGameListDlg()
{
}

void CGameListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB2, m_tabGame);
	DDX_Control(pDX, IDC_BUTTON1, m_btnTest);
}

BOOL CGameListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_tabInfo.Create(IDD_DLG_INFO,&(m_tabGame));
	CRect tabRect;
	m_tabGame.GetClientRect(&tabRect);
	m_tabGame.InsertItem(0,_T(""));
	m_tabInfo.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_SHOWWINDOW); 
	m_tabGame.SetCurFocus(0);
	//CButton *pBtn = (CButton *)GetDlgItem(IDC_BUTTON1);
	//pBtn->SetWindowText(_T("ѡ����Ϸ"));

	return FALSE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}



BEGIN_MESSAGE_MAP(CGameListDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB2, &CGameListDlg::OnTcnSelchangeTab2)
	ON_MESSAGE(UM_GAMEMSG,&CGameListDlg::OnGameMsg)
	ON_BN_CLICKED(IDC_BUTTON1, &CGameListDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CGameListDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CGameListDlg ��Ϣ�������

LRESULT CGameListDlg::OnGameMsg(WPARAM w,LPARAM l)
{
	STRU_HALL_GAMELIST_RS * game=(STRU_HALL_GAMELIST_RS*)w;
	sh=*game;

	for(int i=0;i<game->GameCount;i++)
	{
		char * a=game->m_szGameList[i].GameName;
		CString b=(CString)a;
		(m_tabGame).InsertItem(i, b);
	}
	//������Ϸ��Ϣ
	CString info=(CString)(game->m_szGameList[0]).GameInfo;
	m_tabInfo.m_lstBox.AddString(info);

	m_tabGame.SetCurFocus(0);
	ShowWindow(SW_SHOW);

	return 0;
}


void CGameListDlg::OnTcnSelchangeTab2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString info;
    switch(m_tabGame.GetCurSel()) 
    { 
    case 0: 
		{			
			info=(CString)(sh.m_szGameList[0]).GameInfo;
		}
	 break; 
    case 1: 
		{
			info=(CString)(sh.m_szGameList[1]).GameInfo;
		}
	break; 
	default:
		break;
	}
	m_tabInfo.m_lstBox.ResetContent();
	m_tabInfo.m_lstBox.AddString(info);
	info="";
	info.Empty();
}


void CGameListDlg::OnBnClickedButton1()  //ѡ����Ϸ�����͸�����
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	STRU_GAMECHOOSE_RQ sg;
	sg.m_nType=_DEF_PROTOCOL_GAMECHOOSE_RQ;
	int num;
	 switch(m_tabGame.GetCurSel()) 
    { 
    case 0: 
		{			
			num=0;
		}
	 break; 
    case 1: 
		{
			num=1;
		}
	break; 
	default:
		break;
	}
	   char bb[10]={0};
	    _itoa_s(num,bb,10);
		//sg.i=num;
		CString gamenum;
		gamenum.Format(_T("%d"),num);

	 //strcpy_s((char*)&sg.i,(size_t)sizeof(sg.i),gamenum);
	 WideCharToMultiByte(CP_ACP,0,gamenum,-1,sg.i,sizeof(sg.i),0,0);
	 ((CGameClientDlg*)GetParent())->GetMediator()->SendDataTCP(SOCKET(((CGameClientDlg*)GetParent())->GetMediator()->m_HallIP),((char *)&sg),sizeof(sg));
}


void CGameListDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
