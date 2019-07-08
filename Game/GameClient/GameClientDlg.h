
// GameClientDlg.h : ͷ�ļ�
//

#pragma once
#include"IMediator.h"
#include"Md5Encode.h"
#include"GameListDlg.h"
#include"RoomDlg.h"

// CGameClientDlg �Ի���
class CGameClientDlg : public CDialogEx
{
// ����
public:
	CGameClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GAMECLIENT_DIALOG/* IDD_DLG_GAME*/};

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
private:
	IMediator* m_pMediator;//�н��ߵ�ָ��

	// ���ɵ���Ϣӳ�亯��
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
