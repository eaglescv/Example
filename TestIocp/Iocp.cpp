#include "Iocp.h"

CIocp::CIocp()
{
	mIocpHandle = NULL;
	mStartupEventHandle = NULL;
	mWorkerThreadCount = 0;
	mWorkerThreadVector.clear();
}

CIocp::~CIocp()
{
}

BOOL CIocp::Begin(VOID)
{
	mIocpHandle = NULL;

	//서버 시스텀의 정보를 가져옵니다.
	//가져온 시스템 정보에서 CPU 정보만을 사용할 것입니다.
	SYSTEM_INFO SystemInfo;
	GetSystemInfo(&SystemInfo);

	//CPU의 개수의 2배만큼 WorkerThread를 만듭니다.
	mWorkerThreadCount = SystemInfo.dwNumberOfProcessors * 2;

	//IocpHandle을 생성합니다.
	//메인IOCP핸들의 생성이므로 모든 파라미터 값이 0 또는 NULL입니다.
	mIocpHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	//생성이 실패했다면 종료됩니다.
	if (!mIocpHandle)
		return FALSE;

	//시작을 관리하는 이벤트도 생성합니다.
	mStartupEventHandle = CreateEvent(0, FALSE, FALSE, 0);
	if (mStartupEventHandle == NULL)
	{
		End();
		return FALSE;
	}

	//CPU개수의 2배만큼의 WorkerThread를 생성해서 mWorkerThreadVector로 관리합니다.
	//for (DWORD i = 0; i < mWorkerThreadCount; i++)
	//{
	//	HANDLE WorkerThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)WokerThreadCallback, this, 0, NULL);
	//	mWorkerThreadVector.push_back(WorkerThread);

	//	//하나의 스레드마다 생성이 완료될 떄까지 대기합니다.
	//	WaitForSingleObject(mStartupEventHandle, INFINITE);
	//}
	return TRUE;
}

BOOL CIocp::End(VOID)
{
	return TRUE;
}

//IOCP에 소켓이나 파일 핸들을 등록하는 함수
//BOOL CIocp::RegisterSocketToIcocp(SOCKET Socket, ULONG_PTR CompletionKey)
//{
//	//소켓 핸들이나 키가 잘못되었을 경우에는 등록되지 않습니다.
//	if (!socket || !CompletionKey)
//		return FALSE;
//
//	//Begin에서 생성했던 mIcopHandle에 추가로 소켓 핸들 및 키를 등록합니다.
//	mIocpHandle = CreateIoCompletionPort((HANDLE)socket, mIocpHandle, CompletionKey, 0);
//	if (!mIocpHandle)
//		return FALSE;
//
//	return TRUE;
//}