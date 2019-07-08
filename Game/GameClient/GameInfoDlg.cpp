// GameInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GameClient.h"
#include "GameInfoDlg.h"
#include "afxdialogex.h"


// CGameInfoDlg 对话框

IMPLEMENT_DYNAMIC(CGameInfoDlg, CDialog)

CGameInfoDlg::CGameInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGameInfoDlg::IDD, pParent)
{

}

CGameInfoDlg::~CGameInfoDlg()
{
}

void CGameInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lstBox);
}

BOOL CGameInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


BEGIN_MESSAGE_MAP(CGameInfoDlg, CDialog)
END_MESSAGE_MAP()


// CGameInfoDlg 消息处理程序
