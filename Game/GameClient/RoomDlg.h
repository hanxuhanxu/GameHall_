#pragma once
#include"res.h"
#include "afxwin.h"

// CRoomDlg 对话框

class CRoomDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRoomDlg)

public:
	CRoomDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRoomDlg();
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnDeskMsg(WPARAM,LPARAM);
// 对话框数据
	enum { IDD = IDD_DLG_ROOM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_lstDeskUser1;
	CListBox m_lstDeskUser2;
};
