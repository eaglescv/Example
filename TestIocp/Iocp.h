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
	//	DWORD NumberOfByteTransfered = 0;	//�� ����Ʈ�� IO�� �߻��ߴ��� Ȯ��
	//	VOID* CompletionKey = NULL;			//Ű ��
	//	OVERLAPPED* Overlapped = NULL;		//Overlapped��
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

