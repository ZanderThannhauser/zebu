
#ifdef WINDOWS_PLATFORM

#include <stdio.h>
#include <windows.h>

#include "timer_thread.h"

volatile void (*timer_handler)(int) = NULL;

static DWORD WINAPI runme(void* _)
{
	for (unsigned i = 0; timer_handler && i < 10; i++)
	{
		Sleep(100);
	}
	
	while (timer_handler)
	{
		timer_handler(2);
		Sleep(250);
	}
	
	return 0;
}

static HANDLE handle;

void start_timer_thread()
{
	handle = CreateThread(NULL, 0, runme, NULL, 0, NULL);
}

void join_timer_thread()
{
	timer_handler = NULL;
	WaitForSingleObject(handle, INFINITE);
}

#endif
