#pragma once

#define MAX_QUEUE_LENGTH 5

template <class T>
class CCircularQueue
{
public:
	CCircularQueue()
	{
		Begin();
	}
	~CCircularQueue() {}

private:
	T		mQueue[MAX_QUEUE_LENGTH];
	DWORD	mQueueHead;
	DWORD	mQueueTail;

public:
	BOOL Begin()
	{
		ZeroMemory(mQueue, sizeof(mQueue));
		mQueueHead = 0;
		mQueueTail = 0;
		return TRUE;
	}

	BOOL End() { return TRUE; }

	BOOL Push(T data)
	{
		DWORD TempTail = (mQueueTail + 1) % MAX_QUEUE_LENGTH;
		if (TempTail == mQueueHead)
			return FALSE;

		CopyMemory(&mQueue[TempTail], &data, sizeof(T));

		mQueueTail = TempTail;
		return TRUE;
	}

	BOOL Pop(T& data)
	{
		if (mQueueHead == mQueueTail)
			return FALSE;

		DWORD TempHead = (mQueueHead + 1) % MAX_QUEUE_LENGTH;
		CopyMemory(&data, &mQueue[TempHead], sizeof(T));

		mQueueHead = TempHead;
		return TRUE;
	}

	BOOL IsEmpty()
	{
		if (mQueueHead == mQueueTail)
			return TRUE;
		return FALSE;
	}
};

