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
		mFreePointer = *reinterpret_cast<UCHAR**>(ReturnPointer);	//mFreePointer에는 리턴하는 블록 앞에 4바이트로 있던 주소가 들어간다.
		return ReturnPointer;
	}

	static VOID operator delete(VOID* deletePointer)
	{
		*reinterpret_cast<UCHAR**>(deletePointer) = mFreePointer;	//delete된 블록의 Next에 현재 mFreePointer의 주소를 넣어준다.
		mFreePointer = static_cast<UCHAR*>(deletePointer);			//mFreePointer를 업데이트 한다.
	}

private:
	static VOID allockBlock()
	{
		mFreePointer = new UCHAR[sizeof(T) * ALLOC_BLOCK_SIZE];		//mFreePointer에 사용할 크기의 메모리를 할당한다.
		
		UCHAR** Current = reinterpret_cast<UCHAR**>(mFreePointer);	//할당한 메모리의 첫 블록의 포인터를 Current에 넣는다
		UCHAR* Next = mFreePointer;									//할당된 메모리 첫 블록이다.

		for (INT i = 0; i < ALLOC_BLOCK_SIZE - 1; ++i)
		{
			Next += sizeof(T);							//다음 블록을 계산한다.
			*Current = Next;							//할당된 메모리 앞 4바이트에 다음 불록의 주소를 넣는다.
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