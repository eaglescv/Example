#include <iostream>
#include <Windows.h>
#include "CircularQueue.h"

struct QUEUE_DATA
{
	INT		iData1;
	BYTE	aData2[100];

	QUEUE_DATA() : iData1(0)
	{
		ZeroMemory(aData2, sizeof(aData2));
	}
};

int main()
{
	CCircularQueue<QUEUE_DATA> Queue;
	Queue.Begin();

	QUEUE_DATA PushData;
	PushData.iData1 = 10;

	Queue.Push(PushData);

	QUEUE_DATA PopData;
	Queue.Pop(PopData);
	
	getchar();
	return 0;
}