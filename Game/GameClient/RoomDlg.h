#pragma once
#include"res.h"
#include "afxwin.h"

// CRoomDlg �Ի���

class CRoomDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRoomDlg)

public:
	CRoomDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRoomDlg();
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnDeskMsg(WPARAM,LPARAM);
// �Ի�������
	enum { IDD = IDD_DLG_ROOM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_lstDeskUser1;
	CListBox m_lstDeskUser2;
};
