
// GameClientDlg.h : 头文件
//

#pragma once
#include"IMediator.h"
#include"Md5Encode.h"
#include"GameListDlg.h"
#include"RoomDlg.h"

// CGameClientDlg 对话框
class CGameClientDlg : public CDialogEx
{
// 构造
public:
	CGameClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GAMECLIENT_DIALOG/* IDD_DLG_GAME*/};

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
private:
	IMediator* m_pMediator;//中介者的指针

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_UserName;
	CString m_Password;
	afx_msg void OnBnClickedButton2();
	afx_msg LRESULT 	OnGameListMsg(WPARAM,LPARAM);
	afx_msg LRESULT 	OnDeskInfoMsg(WPARAM,LPARAM);
	CGameListDlg * m_pListDlg;
	CRoomDlg * m_pRoomDlg;
public:
	IMediator* GetMediator()
	{
		return m_pMediator;
	}
	afx_msg void OnBnClickedButton3();
};
