#include "KPrint.h"

char KPrint::DebugBuff[256];

void KPrint::print(const char* A, ...)
{
	va_list args;
	va_start(args, A);
	vsprintf_s(DebugBuff, A, args);
	OutputDebugString(DebugBuff);
};