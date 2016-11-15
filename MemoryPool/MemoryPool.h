#pragma once

#include <assert.h>

template <class T, int ALLOC_BLOCK_SIZE = 50>
class CMemoryPool
{
public:
	static VOID* operator new(std::size_t allocLength)
	{
		assert(sizeof(T) == allocLength);
		assert(sizeof(T) >= sizeof(UCHAR*));

		if (!mFreePointer)
			allockBlock();

		UCHAR* ReturnPointer = mFreePointer;
		mFreePointer = *reinterpret_cast<UCHAR**>(ReturnPointer);	//mFreePointer���� �����ϴ� ��� �տ� 4����Ʈ�� �ִ� �ּҰ� ����.
		return ReturnPointer;
	}

	static VOID operator delete(VOID* deletePointer)
	{
		*reinterpret_cast<UCHAR**>(deletePointer) = mFreePointer;	//delete�� ����� Next�� ���� mFreePointer�� �ּҸ� �־��ش�.
		mFreePointer = static_cast<UCHAR*>(deletePointer);			//mFreePointer�� ������Ʈ �Ѵ�.
	}

private:
	static VOID allockBlock()
	{
		mFreePointer = new UCHAR[sizeof(T) * ALLOC_BLOCK_SIZE];		//mFreePointer�� ����� ũ���� �޸𸮸� �Ҵ��Ѵ�.
		
		UCHAR** Current = reinterpret_cast<UCHAR**>(mFreePointer);	//�Ҵ��� �޸��� ù ����� �����͸� Current�� �ִ´�
		UCHAR* Next = mFreePointer;									//�Ҵ�� �޸� ù ����̴�.

		for (INT i = 0; i < ALLOC_BLOCK_SIZE - 1; ++i)
		{
			Next += sizeof(T);							//���� ����� ����Ѵ�.
			*Current = Next;							//�Ҵ�� �޸� �� 4����Ʈ�� ���� �ҷ��� �ּҸ� �ִ´�.
			Current = reinterpret_cast<UCHAR**>(Next);
		}
		*Current = 0;
	}

private:
	static UCHAR* mFreePointer;

protected:
	~CMemoryPool() {}
};

template <class T, int ALLOC_BLOCK_SIZE>
UCHAR* CMemoryPool<T, ALLOC_BLOCK_SIZE>::mFreePointer;