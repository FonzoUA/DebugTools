#include "KDebug.h"

K_Debug* K_Debug::pK_DebugInstance = nullptr;

K_Debug::K_Debug()
{
	KPrint::print("==========================================\n [Karma] [Constructor] [K_Debug] Constructor call (this should be first thing called) \n ");
	_Constructors = 0;
	_Destructors = 0;	// <== 1 b/c of Engine Destructor
}

K_Debug::~K_Debug()
{
	KPrint::print("==========================================\n [Karma] [Constructor] [K_Debug] Destructr call (this should be last thing called) \n ");
	pK_DebugInstance = nullptr;
}

void K_Debug::PrintConstructor(const std::string& className, const std::string& category)
{
#if _KDebugWithMessages 
	//KPrint::out("C_ [Karma] [Constructor] [%s] %s contructor called\n", category.c_str(), className.c_str());
	KPrint::print("%s | %s [contructor] called\n", category.c_str(), className.c_str());
#else
	className; category; // Warning suppressors
#endif
	Instance()._Constructors++;
}

void K_Debug::PrintDestructor(const std::string& className, const std::string& category)
{
#if _KDebugWithMessages 
	//KPrint::out("D_ [Karma] [Destructor] [%s] %s destructor called\n", category.c_str(), className.c_str());
	KPrint::print("%s | %s [destructor] called\n", category.c_str(), className.c_str());
#else
	className; category; // Warning suppressors
#endif
	Instance()._Destructors++;
}

void K_Debug::PrintStats()
{
#if _DebugPrintStats
	KPrint::print("S_ [Karma] [Stats]	%i contructors called \n", Instance()._Constructors);
	KPrint::print("S_ [Karma] [Stats]	%i destructors called \n", Instance()._Destructors);
	if (Instance()._Destructors != 0)
	{
		KPrint::print("S_ [Karma] [Stats]	C/D ratio: %f  with C-D=%i \n", (float(Instance()._Constructors) / float(Instance()._Destructors)), (Instance()._Constructors - Instance()._Destructors));
	}
#endif
}

void K_Debug::Terminate()
{
	delete pK_DebugInstance;
}