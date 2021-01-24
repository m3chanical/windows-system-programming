
#include <Windows.h>
#include <tchar.h>
#include <Psapi.h>
#include <stdio.h>

int main()
{
	HANDLE mut = ::CreateMutex(nullptr, true, TEXT("SingleInstance"));
	if (mut == nullptr)
		return GetLastError();

	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		// already exists... exit
	}

	// do cool stuff.


/*
	// random code notes:
	// standard C...
	char name[] = "notepad";
	wchar_t wname[] = L"notepad"; // 2-byte character. also need to add the prefix L to indicate to the compiler that it needs to create a utf16 str

	//what about either? can use preprocessor macros --> "ifdef UNICODE ... "
	// this also works:
	TCHAR tname[] = _T("notepad");
	WCHAR wname_2[] = L"notepad"; 


	wchar_t path[MAX_PATH];
	::GetSystemDirectory(path, _countof(path)); // _countof --> sizeof(x) / sizeof(x[0])

	TCHAR pc_name[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD size = _countof(pc_name);
	::GetComputerName(pc_name, &size); // if true, success. --> _Out_ parameters must be pointers

	// deprecated:
	OSVERSIONINFO osvi;
	osvi.dwOSVersionInfoSize = sizeof(osvi);
	::GetVersionEx(&osvi);
	
	PERFORMANCE_INFORMATION pi;
	for(;;)
	{
		::GetPerformanceInfo(&pi, sizeof(pi));
		printf("Threads: %u Handles: %u Committed: %zu MB\n",
			pi.ThreadCount, pi.HandleCount, pi.CommitTotal >> 8); // bytes, to MB 
		::Sleep(1000);
	}
	
*/
	return 0;
}

