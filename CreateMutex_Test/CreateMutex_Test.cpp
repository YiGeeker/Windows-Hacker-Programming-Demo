#include <iostream>
#include <tchar.h>
#include <Windows.h>

// Determine if the run is repeated
bool IsAlreadyRun()
{
	HANDLE hMutex = NULL;
	hMutex = ::CreateMutex(NULL, FALSE, "TEST");
	if (hMutex)
	{
		if (ERROR_ALREADY_EXISTS == ::GetLastError())
		{
			return TRUE;
		}
	}
	return FALSE;
}


int _tmain(int argc, _TCHAR* argv[])
{
	// Determine if the run is repeated
	if (IsAlreadyRun())
	{
		std::cout << "Already Run!!!!\n";
	}
	else
	{
		std::cout << "NOT Already Run!\n";
	}

	system("pause");
	return 0;
}
