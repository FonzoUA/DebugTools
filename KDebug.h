#ifndef K_DEBUG
#define K_DEBUG

#include "KPrint.h"

// Debug macro
#define _KDebug 1
#define _KDebugWithMessages 1
#define _DebugPrintStats 1

#include <string>

class K_Debug
{
private:
	/* === Singleton Setup === */
	static K_Debug* pK_DebugInstance;

	K_Debug();
	K_Debug(const K_Debug&) = delete;
	K_Debug& operator=(const K_Debug&) = delete;
	~K_Debug();

	static K_Debug& Instance()
	{
		if (!pK_DebugInstance)
			pK_DebugInstance = new K_Debug;
		return *pK_DebugInstance;
	}
	/* ======================== */

public:
	static void PrintConstructor(const std::string& className, const std::string& category = "Misk");
	static void PrintDestructor(const std::string& className, const std::string& category = "Misk");
	static void PrintStats();
	static void Terminate();
private:
	int _Constructors;
	int _Destructors;
};

#endif

