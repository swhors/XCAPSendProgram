#pragma once

// CXcapPutReqSocket 명령 대상입니다.

class CXcapPutReqSocket : public CAsyncSocket
{
public:
	CXcapPutReqSocket();
	virtual ~CXcapPutReqSocket();
	int SendPut(CString UserID, CString BudyName);
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	char	mBuffer[1024];
};


