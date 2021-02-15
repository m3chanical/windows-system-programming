#include <Windows.h>
#include <stdio.h>

struct Data
{
	int x;
	int y;
	int sum;
	int product;
};

DWORD WINAPI DoWork(PVOID param)
{
	Data *data = (Data *)param;
	printf("Thread %u running\n", ::GetCurrentThreadId());
	::Sleep(2000 + ::GetCurrentThreadId() / 10); //simple way to change the work time of each thread
	printf("Thread %u done!\n", GetCurrentThreadId());

	data->sum = data->y + data->x;
	data->product = data->y * data->x;
	return 1;
}

int main()
{
	// basic create thread usage
	Data d[2];
	d[0].x = 10;
	d[0].y = 20;
	d[1].x = 7;
	d[1].y = 44;

	HANDLE hThread = ::CreateThread(nullptr, 0, DoWork, &d[0], 0, nullptr);
	HANDLE hThread2 = ::CreateThread(nullptr, 0, DoWork, &d[1], 0, nullptr);
	printf("Main Thread ID: %u\n", ::GetCurrentThreadId());

	//::WaitForSingleObject(hThread, INFINITE);
	HANDLE h[] = { hThread, hThread2 };
	::WaitForMultipleObjects(_countof(h), h, TRUE, INFINITE);

	for(int i = 0; i < _countof(h); i++)
	{
		printf("Worker Thread %u done!\n", ::GetThreadId(h[i]));
		DWORD code;
		::GetExitCodeThread(h[i], &code);
		printf("Result: %u\n", code);
		if (code)
		{
			printf("result: sum: %d, product %d\n", d[i].sum, d[i].product);
		}
		::CloseHandle(hThread);
	}
	
	printf("Worker Thread %u done!\n", ::GetThreadId(hThread));

	

	return 0;
}