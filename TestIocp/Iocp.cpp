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

	//���� �ý����� ������ �����ɴϴ�.
	//������ �ý��� �������� CPU �������� ����� ���Դϴ�.
	SYSTEM_INFO SystemInfo;
	GetSystemInfo(&SystemInfo);

	//CPU�� ������ 2�踸ŭ WorkerThread�� ����ϴ�.
	mWorkerThreadCount = SystemInfo.dwNumberOfProcessors * 2;

	//IocpHandle�� �����մϴ�.
	//����IOCP�ڵ��� �����̹Ƿ� ��� �Ķ���� ���� 0 �Ǵ� NULL�Դϴ�.
	mIocpHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	//������ �����ߴٸ� ����˴ϴ�.
	if (!mIocpHandle)
		return FALSE;

	//������ �����ϴ� �̺�Ʈ�� �����մϴ�.
	mStartupEventHandle = CreateEvent(0, FALSE, FALSE, 0);
	if (mStartupEventHandle == NULL)
	{
		End();
		return FALSE;
	}

	//CPU������ 2�踸ŭ�� WorkerThread�� �����ؼ� mWorkerThreadVector�� �����մϴ�.
	//for (DWORD i = 0; i < mWorkerThreadCount; i++)
	//{
	//	HANDLE WorkerThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)WokerThreadCallback, this, 0, NULL);
	//	mWorkerThreadVector.push_back(WorkerThread);

	//	//�ϳ��� �����帶�� ������ �Ϸ�� ������ ����մϴ�.
	//	WaitForSingleObject(mStartupEventHandle, INFINITE);
	//}
	return TRUE;
}

BOOL CIocp::End(VOID)
{
	return TRUE;
}

//IOCP�� �����̳� ���� �ڵ��� ����ϴ� �Լ�
//BOOL CIocp::RegisterSocketToIcocp(SOCKET Socket, ULONG_PTR CompletionKey)
//{
//	//���� �ڵ��̳� Ű�� �߸��Ǿ��� ��쿡�� ��ϵ��� �ʽ��ϴ�.
//	if (!socket || !CompletionKey)
//		return FALSE;
//
//	//Begin���� �����ߴ� mIcopHandle�� �߰��� ���� �ڵ� �� Ű�� ����մϴ�.
//	mIocpHandle = CreateIoCompletionPort((HANDLE)socket, mIocpHandle, CompletionKey, 0);
//	if (!mIocpHandle)
//		return FALSE;
//
//	return TRUE;
//}