#pragma once

#include <Windows.h>
#include <vector>

class CIocp
{
public:
	CIocp();
	~CIocp();

	//static VOID __stdcall WokerThreadCallback(VOID)
	//{
	//	BOOL Successed = FALSE;
	//	DWORD NumberOfByteTransfered = 0;	//몇 바이트의 IO가 발생했는지 확인
	//	VOID* CompletionKey = NULL;			//키 값
	//	OVERLAPPED* Overlapped = NULL;		//Overlapped값
	//										//OVERLAPPED_EX* OverlappedEx = NULL;
	//	VOID* Object = NULL;
	//}

	BOOL Begin(VOID);
	BOOL End(VOID);
	//BOOL RegisterSocketToIcocp(SOCKET Socket, ULONG_PTR CompletionKey);

private:
	HANDLE	mIocpHandle;
	HANDLE	mStartupEventHandle;
	INT		mWorkerThreadCount;
	std::vector<HANDLE> mWorkerThreadVector;
};

