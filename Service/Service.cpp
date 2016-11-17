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

	//실행 파일 이름을 받아온다.
	ServiceFileName[0] = '"';
	GetModuleFileName(NULL, ServiceFileName + 1, MAX_PATH - 1);
	_tcscat(ServiceFileName, _T("\""));

	//서비스 생성 옵션으로 SCM을 Open
	ServiceControlManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
	if (!ServiceControlManager)
		return FALSE;

	//서비스를 SERVICE_WIN32_OWN_PROCESS 형태로 생성
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

	//사용한 핸들을 닫아줌.
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

	//DELETE하기 위해서 OpenService를 한다.
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

	//StartServiceCtrlDispatcher에서 등록할 서비스 환경 정보이다.
	//SERVICE_TABLE_ENTRY DispathTable[] = 
	//{

	//};
}

void CService::End()
{
	//OnStoped();
}