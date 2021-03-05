// XcapPutReqSocket.cpp : 구현 파일입니다.
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


// CXcapPutReqSocket 멤버 함수

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
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
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
