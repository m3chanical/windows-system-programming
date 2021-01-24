#include <Windows.h>
#include <stdio.h>

int main (void)
{
	UINT32 handle_count = 0;
	HANDLE mut = ::CreateMutex(nullptr, true, nullptr);
	HANDLE mutex_dup;
	if (!mut) // if createmutex fails, return is null
		return -1; 

	/* CREATE JOB OBJECT TEST */

	//while(::CreateJobObjectW(nullptr, nullptr))
	//{
	//	handle_count++;
	//}
	
	/* DUPLICATE HANDLE TEST */

	//while(DuplicateHandle(GetCurrentProcess(), 
	//						mut, 
	//						GetCurrentProcess(),
	//						&mutex_dup,
	//						0,
	//						FALSE,
	//						DUPLICATE_SAME_ACCESS))
	//{
	//	handle_count++;
	//}

	// Duplicate Handle also gets up to 16 mil.

	/* MAX HANDLE TEST */
	
	//while(::CreateMutex(nullptr, true, nullptr))
	//{
	//	handle_count++;
	//}
	//// should get around 16 mil handles
	
	printf("CreateMutex failed at %d handles. Last Error: %lu\n", handle_count, GetLastError());
	return 0;
}