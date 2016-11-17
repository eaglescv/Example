#pragma once

#include <Windows.h>

class CService
{
public:
	CService();
	~CService();

	BOOL Install(LPCTSTR serviceName);
	BOOL Uninstall(LPCTSTR serviceName);
	BOOL Begin(LPCTSTR serviceName);
	void End();
};

