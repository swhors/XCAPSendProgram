// XCAPSendProgramDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "XCAPSendProgram.h"
#include "XCAPSendProgramDlg.h"

#include "XcapPutReqSocket.h"

#include <List>
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


std::vector<CString> m_listFile;
int count = 0;

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CXCAPSendProgramDlg 대화 상자




CXCAPSendProgramDlg::CXCAPSendProgramDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXCAPSendProgramDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXCAPSendProgramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDPUT, m_btnPut);
	DDX_Control(pDX, IDRESET, m_btnReset);
	DDX_Control(pDX, IDXML, m_ed_XML);
	DDX_Control(pDX, IDCID, m_edID);
	DDX_Control(pDX, IDC_XCAPIP, m_IP);
}

BEGIN_MESSAGE_MAP(CXCAPSendProgramDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDABOUT, &CXCAPSendProgramDlg::OnBnClickedAbout)
	ON_BN_CLICKED(IDOK, &CXCAPSendProgramDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDRESET, &CXCAPSendProgramDlg::OnBnClickedReset)
	ON_BN_CLICKED(IDPUT, &CXCAPSendProgramDlg::OnBnClickedPut)
	ON_MESSAGE(WM_SOCK_SEND, OnRecvSockSend)
	ON_MESSAGE(WM_SOCK_RESULT,OnRecvSockResult)
	ON_MESSAGE(WM_SOCK_CLOSED,OnRecvSockClose)
	ON_MESSAGE(WM_USER_RETRY, OnRetrySend)
	ON_BN_CLICKED(IDOPEN, &CXCAPSendProgramDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDPARSE, &CXCAPSendProgramDlg::OnBnClickedParse)
	ON_BN_CLICKED(IDALLTRY, &CXCAPSendProgramDlg::OnBnClickedAlltry)
END_MESSAGE_MAP()


// CXCAPSendProgramDlg 메시지 처리기

BOOL CXCAPSendProgramDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.
	SetInitState();
	this->m_putSocket = NULL;
	m_listFile.clear();
	count = 0;
	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CXCAPSendProgramDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CXCAPSendProgramDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CXCAPSendProgramDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CXCAPSendProgramDlg::OnBnClickedAbout()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CAboutDlg pDlg;
	pDlg.DoModal();
}

void CXCAPSendProgramDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if( this->m_putSocket )
	{
		this->m_putSocket->Close();
	}
	OnOK();
}

void CXCAPSendProgramDlg::OnBnClickedReset()
{
	SetInitState();
}

void CXCAPSendProgramDlg::OnBnClickedPut()
{
	CString csID;
	CString csXML;
	CString csHost;
	this->m_IP.GetWindowText(csHost);
	this->m_edID.GetWindowText(csID);
	this->m_ed_XML.GetWindowText(csXML);
	m_putSocket = new CXcapPutReqSocket();
	if( m_putSocket )
	{
		if( m_putSocket->Create() > 0 )
		{
			m_putSocket->Connect(csHost, 9110);
		}
	}
	//this->m_putSocket.SendPut(csID, csXML);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CXCAPSendProgramDlg::SetInitState()
{
	this->m_ed_XML.SetWindowText(LPCTSTR(""));
}

void CXCAPSendProgramDlg::SetStateBudyItem(int lineNum, bool bState)
{
	this->m_ed_XML.SetWindowText(LPCTSTR(""));
}


LRESULT CXCAPSendProgramDlg::OnRecvSockSend(WPARAM wParam, LPARAM lParam)
{
#if 0 // Block B
	if( this->m_putSocket )
	{
		CString csHead;
		char head[1024];
		char entry[1024];
		CString csID;
		this->m_edID.GetWindowText(csID);
#if 0 // Block A
		wsprintf(entry, "<entry uri=\"0164524816\"><display-name>=ED=99=8D=EA=B8=B8=EB=8F=99</display-name><Group-ID>0002</Group-ID><GMarketID>test4sqm</GMarketID><Phone></Phone></entry>\r\n");
		wsprintf(head, "PUT /services/resource-lists/users/810283601/resource-list.xml/~~/resource-lists/list[1]/entry[@uri=\"0164524816\"] HTTP/1.1\r\n" \
			"Content-Type: application/xcap-el+xml\r\n"	\
			"User-Agent: gmsgphone_ed\r\n"	\
			"Host: 211.115.66.71:9110\r\n"	\
			"Content-Length: %d\r\n"	\
			"Cache-Control: no-cache\r\n\r\n%s"	\
			,strlen(entry), entry
			);
		this->m_putSocket->Send(head, strlen(head), 0);
#else  //Block A
		CString csBody;
		this->m_ed_XML.GetWindowText(csBody);
		csBody.Replace(">\n", ">\r\n");
		int length = csBody.GetLength();
		wsprintf(head, "PUT /services/resource-lists/users/%s/resource-list.xml HTTP/1.1\r\n"\
			"Content-Type: application/resource-lists+xml\r\n"\
			"Accept: *//*\r\n"\
			"User-Agent: gmsgphone_ed\r\n"\
			"Host: 211.115.66.71:9110\r\n"\
			"Content-Length: %d\r\n"\
			"Cache-Control: no-cache\r\n\r\n", csID, length);
		this->m_putSocket->Send(head, strlen(head), 0);
		this->m_putSocket->Send(csBody.GetBuffer(), length, 0);
#endif	//Block A
	}
#else	//Block B
	SendData();
#endif	// Block B
	return NULL;
}

LRESULT CXCAPSendProgramDlg::OnRetrySend(WPARAM wParam,LPARAM lParam)
{
	OnBnClickedPut();
	return NULL;
}

LRESULT CXCAPSendProgramDlg::OnRecvSockClose(WPARAM wParam, LPARAM lParam)
{
	if( this->m_putSocket )
	{
		AfxMessageBox(LPTSTR("Closed"));
		this->m_putSocket = NULL;
	}
	if( m_listFile.size() > 0 )
	{
		SendMessage(WM_USER_RETRY, NULL, NULL);
	}
	else
		AfxMessageBox("End");
	return NULL;
}

LRESULT CXCAPSendProgramDlg::OnRecvSockResult(WPARAM wParam, LPARAM lParam)
{
	if( this->m_putSocket )
	{
		Log(m_putSocket->mBuffer);
		this->m_putSocket->ShutDown(2);
		this->m_putSocket->Close();
		this->m_putSocket = NULL;
		if( m_listFile.size() > 0 )
		{
			SendMessage(WM_USER_RETRY, NULL, NULL);
		}
		else
		AfxMessageBox("End");
	}
	return NULL;
}

void CXCAPSendProgramDlg::OnBnClickedOpen()
{
	CFileDialog pDlg(true, "*", "*");
	if( pDlg.DoModal() == IDOK )
	{
		CString csFileName = pDlg.GetFileName();
		CString csTitle = pDlg.GetFileTitle();
		CFile cf;
		if( cf.Open(csFileName, CFile::modeRead, NULL ) )
		{
			int length = cf.GetLength();
			char *b  = new char[length+1];
			if( b )
			{
				memset(b,0, length+1);
				cf.Read(b, length);
				this->m_ed_XML.SetWindowTextA(b);
				this->m_edID.SetWindowTextA(csTitle);
				delete b;
			}
			cf.Close();
		}
	}
}

void CXCAPSendProgramDlg::OnBnClickedParse()
{
	CString csFileName;
	CFileDialog pDlg(true, "*", "*");
	if( pDlg.DoModal() == IDOK )
	{
		CString csFileName = pDlg.GetFileName();
		CString csTitle = pDlg.GetFileTitle();
		CFile cf;
		char tbuf[1024];
		FILE *fp = fopen(csFileName, "rt");
		if( fp)
		{
			while(fgets(tbuf, 1024, fp))
			{
				if(memcmp(tbuf, "\n", 1))
				{
					CString csSubFile = tbuf;
					csSubFile.Remove('\n');
					m_listFile.push_back(csSubFile);
					FILE *fpw = fopen(csSubFile, "w+t");
					if( fpw )
					{
						while(fgets(tbuf, 1024, fp) )
						{
							fprintf(fpw, "%s", tbuf);
							if( !memcmp(tbuf, "</resource-lists>", 17))
								break;
						}
						fclose(fpw);
					}
					else
						break;
				}
			}
		}
		if( fp )
			fclose(fp);
	}
}

void CXCAPSendProgramDlg::OnBnClickedAlltry()
{
	
}

bool CXCAPSendProgramDlg::SendData(void)
{
	if( this->m_putSocket )
	{
		CString csHead;
		char head[1024];
		CString csID;
		CString csBody;

		this->m_edID.GetWindowText(csID);
		if( m_listFile.size() > 0 )
		{
			CString csFileName;
			std::vector<CString>::iterator p = m_listFile.begin();
			csFileName = *p;
			m_listFile.erase(p);
			CFile cf;
			if( cf.Open(csFileName, CFile::modeRead, NULL ) )
			{
				int length = cf.GetLength();
				CString logTxt;
				logTxt.Format("%d %s", count++, csFileName);
				Log(logTxt);
				char *b  = new char[length+1];
				if( b )
				{
					memset(b,0, length+1);
					cf.Read(b, length);
					csBody = b;
					{
						csBody.Replace(">\n", ">\r\n");
						int length = csBody.GetLength();
						wsprintf(head, "PUT /services/resource-lists/users/%s/resource-list.xml HTTP/1.1\r\n"\
							"Content-Type: application/resource-lists+xml\r\n"\
							"Accept: *//*\r\n"\
							"User-Agent: gmsgphone_ed\r\n"\
							"Host: 211.115.66.71:9110\r\n"\
							"Content-Length: %d\r\n"\
							"Cache-Control: no-cache\r\n\r\n", csFileName, length);
						this->m_putSocket->Send(head, strlen(head), 0);
						this->m_putSocket->Send(csBody.GetBuffer(), length, 0);
					}
					delete b;
				}
				cf.Close();
			}
			
		}
	}
	return false;
}

int CXCAPSendProgramDlg::Log(CString csStr)
{
	FILE *f = fopen("log.txt", "a+t");
	if( f )
	{
		fprintf(f, "%s\n", csStr);
		fclose(f);
	}
	return 0;
}
