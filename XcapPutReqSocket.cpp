// XcapPutReqSocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "XCAPSendProgram.h"
#include "XcapPutReqSocket.h"


// CXcapPutReqSocket

CXcapPutReqSocket::CXcapPutReqSocket()
{
}

CXcapPutReqSocket::~CXcapPutReqSocket()
{
}


// CXcapPutReqSocket ��� �Լ�

int CXcapPutReqSocket::SendPut(CString UserID, CString BudyName)
{
	
	return 0;
}

void CXcapPutReqSocket::OnConnect(int nErrorCode)
{
	SendMessage(AfxGetApp()->m_pMainWnd->m_hWnd, WM_SOCK_SEND, NULL, NULL);
	CAsyncSocket::OnConnect(nErrorCode);
}

void CXcapPutReqSocket::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	memset( mBuffer, 0, 1024);
	Receive(this->mBuffer, 1024, 0 );
	SendMessage(AfxGetApp()->m_pMainWnd->m_hWnd, WM_SOCK_RESULT, NULL, NULL);
	CAsyncSocket::OnReceive(nErrorCode);
}

void CXcapPutReqSocket::OnClose(int nErrorCode)
{
	SendMessage(AfxGetApp()->m_pMainWnd->m_hWnd, WM_SOCK_CLOSED, NULL, NULL);
	CAsyncSocket::OnClose(nErrorCode);
}
