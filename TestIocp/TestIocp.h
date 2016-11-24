#pragma once

#include <Windows.h>
#include "Iocp.h"

class CTestSession;
#define MAX_SESSION 10

class CTestIocp : public CIocp
{
public:
	CTestIocp();
	~CTestIocp();
	
	BOOL Begin(VOID);
	BOOL End(VOID);

private:
	CTestSession*	mListenSession;
	CTestSession*	mTestSessions[MAX_SESSION];
};

