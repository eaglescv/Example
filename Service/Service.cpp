#include "Service.h"
#include <string.h>
#include <tchar.h>

CService::CService()
{
}

CService::~CService()
{
}

BOOL CService::Install(LPCTSTR serviceName)
{
	TCHAR ServiceFileName[MAX_PATH] = {0, };
	SC_HANDLE ServiceControlManager = NULL;
	SC_HANDLE ServiceHandle = NULL;

	if (!serviceName)
		return FALSE;

	//���� ���� �̸��� �޾ƿ´�.
	ServiceFileName[0] = '"';
	GetModuleFileName(NULL, ServiceFileName + 1, MAX_PATH - 1);
	_tcscat(ServiceFileName, _T("\""));

	//���� ���� �ɼ����� SCM�� Open
	ServiceControlManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
	if (!ServiceControlManager)
		return FALSE;

	//���񽺸� SERVICE_WIN32_OWN_PROCESS ���·� ����
	ServiceHandle = CreateService(ServiceControlManager,
		serviceName,
		serviceName,
		SERVICE_ALL_ACCESS,
		SERVICE_WIN32_OWN_PROCESS,
		SERVICE_DEMAND_START,
		SERVICE_ERROR_NORMAL,
		ServiceFileName,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL);

	if (!ServiceHandle)
	{
		CloseServiceHandle(ServiceControlManager);
		return FALSE;
	}

	//����� �ڵ��� �ݾ���.
	CloseServiceHandle(ServiceHandle);
	CloseServiceHandle(ServiceControlManager);

	return TRUE;
}

BOOL CService::Uninstall(LPCTSTR serviceName)
{
	SC_HANDLE ServiceControlManager = NULL;
	SC_HANDLE ServiceHandle = NULL;
	
	if (!serviceName)
		return FALSE;

	ServiceControlManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
	if (!ServiceControlManager)
		return FALSE;

	//DELETE�ϱ� ���ؼ� OpenService�� �Ѵ�.
	ServiceHandle = OpenService(ServiceControlManager, serviceName, DELETE);

	if (!ServiceHandle)
	{
		CloseServiceHandle(ServiceControlManager);
		return FALSE;
	}

	if (!DeleteService(ServiceHandle))
	{
		CloseServiceHandle(ServiceHandle);
		CloseServiceHandle(ServiceControlManager);
		return FALSE;
	}

	CloseServiceHandle(ServiceHandle);
	CloseServiceHandle(ServiceControlManager);
	return TRUE;
}

BOOL CService::Begin(LPCTSTR serviceName)
{
	if (!serviceName)
		return FALSE;

	//StartServiceCtrlDispatcher���� ����� ���� ȯ�� �����̴�.
	//SERVICE_TABLE_ENTRY DispathTable[] = 
	//{

	//};
}

void CService::End()
{
	//OnStoped();
}