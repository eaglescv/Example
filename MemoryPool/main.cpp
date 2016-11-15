#include <iostream>
#include <Windows.h>
#include "MemoryPool.h"

class CDataMP : public CMemoryPool<CDataMP>
{
public:
	void Test()
	{
		for (INT i = 0; i < 1000000; i++)
		{
			CDataMP* pData = new CDataMP;
			delete pData;
		}
	}

private:
	BYTE a[1024];
	BYTE b[1024];
};

class CData
{
public:
	void Test()
	{
		for (INT i = 0; i < 1000000; i++)
		{
			CData* pData = new CData;
			delete pData;
		}
	}

private:
	BYTE a[1024];
	BYTE b[1024];
};

int main()
{
	CData data1;
	data1.Test();

	CDataMP data2;
	data2.Test();

	return 0;
}