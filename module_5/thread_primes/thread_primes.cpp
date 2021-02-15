#include <Windows.h>
#include <stdio.h>
#include <memory>

int CalcPrimes(int, int, int);
DWORD WINAPI ThreadCalc(PVOID param);
bool IsPrime(int n);

struct ThreadData
{
	int first;
	int last;
	int count; // amt of primes in the range
};


int main(int argc, const char* argv[])
{
	int threads = 1;
	if(argc > 1)
	{
		threads = atoi(argv[1]); // need to do some error handling, but for demo... eh
	}

	// measure time
	DWORD64 start = ::GetTickCount64();
	
	int count = CalcPrimes(threads, 3, 20000000);

	DWORD64 diff = ::GetTickCount64() - start;

	printf("Count: %d Elapsed Time: %u msec\n", count, (DWORD) diff);
	
}

int CalcPrimes(int threads, int first, int last)
{
	int chunk = (last - first + 1) / threads;

	// options:
	// 
	// ThreadData* data = (ThreadData*) malloc(threads * sizeof(ThreadData));
	// std::unique_ptr<ThreadData[]> data = std::make_unique<ThreadData[]>(threads);

	auto data = std::make_unique<ThreadData[]>(threads); // thanks c++. manages internally so we don't need to free
	auto handle = std::make_unique<HANDLE[]>(threads);

	for(int i = 0; i < threads; i++)
	{
		data[i].first = first + i * chunk;
		data[i].last = i == threads - 1 ? last : data[i].first + chunk - 1;
		handle[i] = ::CreateThread(nullptr, 0, ThreadCalc, &data[i], 0, nullptr);
	}
	::WaitForMultipleObjects(threads, handle.get(), TRUE, INFINITE);

	int count = 0;
	for(int i = 0; i < threads; i ++)
	{
		count += data[i].count;
		::CloseHandle(handle[i]);
	}

	//free(data);
	return count;
}

bool IsPrime(int n)
{
	int limit = (int)sqrt(n);
	for (int i = 2; i <= limit; i++)
		if (n % i == 0)
			return false;

	return true;
}

DWORD WINAPI ThreadCalc(PVOID param)
{
	ThreadData* data = (ThreadData*)param;
	int count = 0;
	for(int i = data->first; i <= data->last; i ++)
	{
		if (IsPrime(i))
			count++;
	}

	data->count = count;
	return 0;
}