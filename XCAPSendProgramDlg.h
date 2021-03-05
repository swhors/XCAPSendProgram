// XCAPSendProgramDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

class CXcapPutReqSocket;

// CXCAPSendProgramDlg ��ȭ ����
class CXCAPSendProgramDlg : public CDialog
{
// �����Դϴ�.
public:
	CXCAPSendProgramDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_XCAPSENDPROGRAM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAbout();
	afx_msg void OnBnClickedOk();
	CButton m_btnPut;
	afx_msg void OnBnClickedReset();
	CButton m_btnReset;
	afx_msg void OnBnClickedPut();
	void SetInitState(void);
	void SetStateBudyItem(int lineNum, bool bState);
	CEdit m_ed_XML;
	CXcapPutReqSocket * m_putSocket;
	CEdit m_edID;
	CIPAddressCtrl m_IP;
	afx_msg	LRESULT OnRecvSockSend(WPARAM wParam, LPARAM lParam);
	afx_msg	LRESULT OnRecvSockClose(WPARAM wParam, LPARAM lParam);
	afx_msg	LRESULT OnRecvSockResult(WPARAM wParam, LPARAM lParam);
	afx_msg	LRESULT OnRetrySend(WPARAM wParam,LPARAM lParam);
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedParse();
	afx_msg void OnBnClickedAlltry();
	bool SendData(void);
	int Log(CString csStr);
};
