#pragma once
#include"resource.h"
#include "afxcmn.h"
#include"GameInfoDlg.h"
#include"res.h"
#include "afxwin.h"

// CGameListDlg �Ի���

class CGameListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameListDlg)

public:
	CGameListDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGameListDlg();
	virtual BOOL OnInitDialog();

	afx_msg void OnTcnSelchangeTab2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg LRESULT OnGameMsg(WPARAM,LPARAM);
// �Ի�������
	enum { IDD = IDD_DLG_GAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
public:
	CWnd* m_pWnd;
	CTabCtrl m_tabGame;
	CGameInfoDlg m_tabInfo;
	//Game m_game;
	STRU_HALL_GAMELIST_RS sh;
	afx_msg void OnBnClickedButton1();
	CButton m_btnTest;
	afx_msg void OnBnClickedButton3();
};
