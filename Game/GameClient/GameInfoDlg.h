#pragma once
#include "afxwin.h"


// CGameInfoDlg �Ի���

class CGameInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CGameInfoDlg)

public:
	CGameInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGameInfoDlg();
	virtual BOOL OnInitDialog();
// �Ի�������
	enum { IDD = IDD_DLG_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_lstBox;
};
