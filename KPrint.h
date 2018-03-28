#ifndef K_PRINT
#define K_PRINT

#include <Windows.h>
#include <stdio.h>
#include <stdarg.h>

class KPrint
{
private:
	static char DebugBuff[256];

public:
	static void print(const char* A, ...);
};

#endif
