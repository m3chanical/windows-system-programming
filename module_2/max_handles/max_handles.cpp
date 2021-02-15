#include <Windows.h>
#include <stdio.h>

void test_handles();

int main (void)
{
	UINT32 handle_count = 0;
	HANDLE mut = ::CreateMutex(nullptr, true, nullptr);
	HANDLE mutex_dup;
	if (!mut) // if createmutex fails, return is null
		return -1; 

	test_handles();
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

void test_handles()
{
	
	// synchronize
	HANDLE hProcess = ::OpenProcess(SYNCHRONIZE | PROCESS_TERMINATE | PROCESS_QUERY_LIMITED_INFORMATION, FALSE, 3888);
	if(hProcess)
	{
		BOOL success = ::TerminateProcess(hProcess, 1); // will fail without PROCESS_TERMINATE
		if (!success)
			return;
		::WaitForSingleObject(hProcess, INFINITE);
		DWORD code;
		success = ::GetExitCodeProcess(hProcess, &code); // needs PROCESS_QUERY_LIMITED_INFORMATION
		if(success)
			printf("notepad terminated (%u)\n", code);
		::CloseHandle(hProcess);
	}
	else
	{
		printf("error opening process T_T (%u)\n", GetLastError());
	}

	// inheritable handle
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.bInheritHandle = TRUE;
	
	HANDLE hEvent = ::CreateEvent(&sa, FALSE, FALSE, nullptr);
	//::SetHandleInformation(hEvent, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT); // with security attributes this isn't needed

	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	WCHAR name[] = L"notepad";
	if(::CreateProcess(nullptr, name, nullptr, nullptr, TRUE, 0, nullptr, nullptr, &si, &pi))
	{
		printf("process created successfully. pid=%u\n", pi.dwProcessId);
	}
	


}