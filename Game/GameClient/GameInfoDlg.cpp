// GameInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GameClient.h"
#include "GameInfoDlg.h"
#include "afxdialogex.h"


// CGameInfoDlg �Ի���

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


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}


BEGIN_MESSAGE_MAP(CGameInfoDlg, CDialog)
END_MESSAGE_MAP()


// CGameInfoDlg ��Ϣ�������
