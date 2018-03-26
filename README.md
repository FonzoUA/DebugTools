# Debug Tools
A set of simple tools for debugging C++ program;

#### Tested on
* Windows 10

## Timer (KTimer)
Tool for calculating elapsed time in C++ program.

### Why?
Using `clock()` to calculate the time elapsed was getting annoying + convenience

## Code Sample
```cpp
#include "KTimer.h"
#include "KPrint.h"
#define SLEEPYBOI(x) Sleep(x * 1000)

int main()
{
	KTimer timer;
	timer.Start();
	KPrint::print("===== TIMER START =====\n");

	SLEEPYBOI(2);
	timer.PrintTimestamp("TestStamp", _timeTypes::Milliseconds);

	SLEEPYBOI(1);

	KPrint::print("==== TIMER END ===== \n");
	timer.PrintTime();
	timer.Reset();
	timer.PrintTime();

	SLEEPYBOI(2);
	timer.Stop();
	timer.PrintTime();
}

/*
Sample output:

===== TIMER START =====
[FTIMER] | NONAME timer's TestStamp timestamp: 2000.5275
==== TIMER END =====
[FTIMER] | NONAME timer's time is: 3001.7170
[FTIMER] | NONAME timer's time is: 0.0003
[FTIMER] | NONAME timer's time is: 2000.3136

*/
```
Uses system API to get accurate processor time thus Timer only works for Windows.


## Printer (KPrint)
A simple tool for printing stuff to the VS output window.

### Why?
Print traces save lives.

## Code Sample
```cpp
#include "KPrint.h"

int main()
{
	KPrint::print("==========\n");
	KPrint::print("Hello World!");
	KPrint::print("----------\n");
}

/*
Sample Output:

==========
Hello World!
----------
*/
```


## C/D Counter Thing (K_Debug)
A singleton class that suppose to count number of constructors and destructor called thus helping with detecting memory leaks.
Requires user to be diligent and put the functions in the proper places(see sample) 
Also since its a singleton it needs to be among the first things initialized and last things destroyed

### Why?
So that one can spot as much of those juicy leaks as possible.

## Code Sample
```cpp
// Used within the context of game engine

#include "KDebug.h"

ImageAssetManager::ImageAssetManager()
{
#if _KDebug
	K_Debug::PrintConstructor("ImageAssetManager", "Singleton");
#endif
	//...
}

ImageAssetManager::~ImageAssetManager()
{
#if _KDebug
	K_Debug::PrintDestructor("ImageAssetManager", "Singleton");
#endif
	//...
}

/*
Sample Output: 

==========================================
[Karma] [Constructor] [K_Debug] Constructor call (this should be first thing called) 
Singleton | ImageAssetManager [Constructor] called
...
Singleton | ImageAssetManager [destructor] called
...
S_ [Karma] [Stats]	934 contructors called 
S_ [Karma] [Stats]	934 destructors called 
S_ [Karma] [Stats]	C/D ratio: 1.000  with C-D=0 
==========================================
[Karma] [Constructor] [K_Debug] Destructr call (this should be last thing called) 
----------
*/
```




