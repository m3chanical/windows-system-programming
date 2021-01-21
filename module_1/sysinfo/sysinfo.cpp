#ifndef SECURITY_WIN32 
#define SECURITY_WIN32 
#endif

#include <Windows.h>
#include <security.h>
#include <secext.h>
#include <lmcons.h>

#include <iostream>

const char* cpu_arch_to_string(DWORD arch);

int main()
{
	DWORD productInfo;
	if (::GetProductInfo(6, 3, 0, 0, &productInfo) == 0)
	{
		printf_s("GetProductInfo returned %d\n", GetLastError());
	}
	{
		printf("Product Info for 6.3.0.0: %lu\n", productInfo);
	}

	LARGE_INTEGER perfCount;
	if (::QueryPerformanceCounter(&perfCount) == 0)
	{
		printf_s("QueryPerformanceCounter returned %d\n", GetLastError());
	}
	else
	{
		printf("Performance Counter Before: %llu\n", perfCount.QuadPart);
	}

	WCHAR winDirectory[MAX_PATH];
	ULONG winDirectorySize = sizeof(winDirectory);
	if (::GetWindowsDirectory(winDirectory, winDirectorySize) == 0)
	{
		printf_s("GetWindowsDirectory returned %d\n", GetLastError());
	}
	else
	{
		printf("Windows Directory Path: %ls\n", winDirectory);
	}

	WCHAR compName[MAX_COMPUTERNAME_LENGTH + 1];
	ULONG compNameSize = sizeof(compName);
	if (::GetComputerNameW(compName, &compNameSize) == 0)
	{
		printf_s("GetComputerName returned %d\n", GetLastError());
	}
	else
	{
		printf("Current Computer Name: %ls\n", compName);
	}

	TCHAR user[UNLEN + 1];
	DWORD user_len_lpdword = UNLEN + 1;
	if (GetUserName(user, &user_len_lpdword) == 0)
	{
		printf_s("GetUserName returned %d\n", GetLastError());
	}
	else
	{
		printf("Current User Name : %ls\n", user);
	}

	TCHAR system_dir[256];
	if (GetSystemDirectory(system_dir, 256) == 0)
	{
		printf_s("GetSystemDirectory returned: %d\n", GetLastError());
	}
	else
	{
		printf("System Directory: %ls\n", system_dir);
	}

	SYSTEM_INFO si;
	::GetNativeSystemInfo(&si);
	printf("Number of logical processors: %lu\n", si.dwNumberOfProcessors);
	printf("Page size: %lu Bytes\n", si.dwPageSize);
	printf("Processor Mask: 0x%p\n", (PVOID)si.dwActiveProcessorMask);
	printf("Minimum Processor address: 0x%p\n", si.lpMinimumApplicationAddress);
	printf("Maximum Processor address: 0x%p\n", si.lpMaximumApplicationAddress);
	printf("Active Processor Level: 0x%x\n", si.wProcessorLevel);
	printf("Active Processor Revision: 0x%x\n", si.wProcessorRevision);
	printf("Active Processor Architecture: %s\n", cpu_arch_to_string(si.wProcessorArchitecture));

	WCHAR compObjName[512];
	ULONG compObjNameSize = sizeof(compObjName);
	if (GetComputerObjectNameW(NameGivenName, compObjName, &compObjNameSize) == 0)
	{
		printf_s("GetComputerObjectName returned %d\n", GetLastError());
	}
	else
	{
		printf("ComputerName: %ls", compObjName);
	}
	if (QueryPerformanceCounter(&perfCount) == 0)
	{
		printf_s("QueryPerformanceCounter returned %d\n", GetLastError());
	}
	else
	{
		printf("Performance Counter After: %llu\n", perfCount.QuadPart);
	}

	return 0;
}

const char* cpu_arch_to_string(DWORD arch)
{
	switch (arch)
	{
	case PROCESSOR_ARCHITECTURE_AMD64: return "x64";
		// ... TODO: check documentation for more ^_^
	}
	return "(Unknown)";
}