// RoomDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GameClient.h"
#include "RoomDlg.h"
#include "afxdialogex.h"


// CRoomDlg 对话框

IMPLEMENT_DYNAMIC(CRoomDlg, CDialogEx)

CRoomDlg::CRoomDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRoomDlg::IDD, pParent)
{

}

CRoomDlg::~CRoomDlg()
{
}

void CRoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lstDeskUser1);
	DDX_Control(pDX, IDC_LIST2, m_lstDeskUser2);
}

BOOL CRoomDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
}

BEGIN_MESSAGE_MAP(CRoomDlg, CDialogEx)
	ON_MESSAGE(UM_DESKMSG,&CRoomDlg::OnDeskMsg)
END_MESSAGE_MAP()


// CRoomDlg 消息处理程序
LRESULT CRoomDlg::OnDeskMsg(WPARAM w,LPARAM l)
{
	//在桌子界面显示信息
	STRU_GAMECHOOSE_RS * sg=(STRU_GAMECHOOSE_RS* )w;
	for(int i=1020;i<1029;i++)
	{
		CButton *pBtn = (CButton *)GetDlgItem(i);
		int num=sg->desk[i-1020].Num;
		CString mm;
		mm.Format(_T("%d"), num);
		mm+="\n";
		for(int j=0;j<sg->desk[i-1020].Num;j++)
		{
			CString name=(CString)sg->desk[i-1020].user[j].m_username;
			mm+=name;
			mm+="\n";
		}
		pBtn->SetWindowText(mm);
	}
	return 0;
}
