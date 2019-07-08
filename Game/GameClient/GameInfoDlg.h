#pragma once
#include "afxwin.h"


// CGameInfoDlg 对话框

class CGameInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CGameInfoDlg)

public:
	CGameInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGameInfoDlg();
	virtual BOOL OnInitDialog();
// 对话框数据
	enum { IDD = IDD_DLG_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_lstBox;
};
