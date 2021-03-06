# Debug Tools
A set of simple tools for debugging C++ program;

#### Tested on
* Windows 10

#### What is available so far:
* Timer
* Printer
* C/D Counter
* Container Cleanup
* Random Number Generator

## Timer (KTimer)
Tool for calculating elapsed time in C++ program.

### Why?
Using `clock()` to calculate the time elapsed was getting annoying + convenience

#### Code Sample
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
[KTIMER] | NONAME timer's TestStamp timestamp: 2000.5275
==== TIMER END =====
[KTIMER] | NONAME timer's time is: 3001.7170
[KTIMER] | NONAME timer's time is: 0.0003
[KTIMER] | NONAME timer's time is: 2000.3136

*/
```
Uses system API to get accurate processor time thus Timer only works for Windows.


## Printer (KPrint)
A simple tool for printing stuff to the VS output window.

### Why?
Print traces save lives.

#### Code Sample
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


## C/D Counter Thing (KDebug)
A singleton class that suppose to count number of constructors and destructor called thus helping with detecting memory leaks.
Requires user to be diligent and put the functions in the proper places(see sample) 
Also since its a singleton it needs to be among the first things initialized and last things destroyed

### Why?
So that one can spot as much of those juicy leaks as possible.

#### Code Sample
```cpp
// Used within the context of game engine

#include "KDebug.h"

ImageAssetManager::ImageAssetManager()
{
	KDebug::LogConstructor("ImageAssetManager", "Singleton");
	//...
}

ImageAssetManager::~ImageAssetManager()
{
	KDebug::LogDestructor("ImageAssetManager", "Singleton");
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


## Container Cleanup functions (KCleanup)
Static functions that cleanup STL containers and the objects within them (as opposed to pointers only)

### Why?
Cause memory leaks 

#### Code Sample
```cpp
#include "KCleanup.h"
#include "KPrint.h"
#include <map>
#include <string>

class Node
{
public:
	Node() {};
	Node(const int& sp, const int& b) : spicy(sp), boi(b) {}
	~Node() { KPrint::print("				Node Destructor called\n"); }
	int spicy;
	int boi;
};

int main()
{
	std::string test1 = "T1";
	std::string test2 = "T2";
	std::string test3 = "T3";
	std::string test4 = "T4";
	std::string test5 = "T5";

	std::map<std::string, Node*>* map = new std::map<std::string, Node*>;
	
	(*map)[test1] = new Node(1, 11);
	(*map)[test2] = new Node(2, 21);
	(*map)[test3] = new Node(3, 31);
	(*map)[test4] = new Node(4, 41);
	(*map)[test5] = new Node(5, 51);


	KPrint::print("==========================\n");

	for (auto it = map->begin(); it != map->end(); it++)
	{
		KPrint::print("%s's value1: %i   value2: %i  \n", it->first.c_str(), it->second->spicy, it->second->boi);
	}

	KPrint::print("Map size: %i \n", map->size());

	/*
	KPrint::print("==========================\n");
	KPrint::print("Manual deletion \n");
	for (auto it = map->begin(); it != map->end(); it++)
		delete it->second;
	map->clear();
	*/

	KPrint::print("==========================\n");
	KPrint::print("KCleanup deletion \n");
	KCleanup::CleanUpMap(*map);
	KPrint::print("==========================\n");

}

/*
Sample Output: 

==========================
T1's value1: 1   value2: 11  
T2's value1: 2   value2: 21  
T3's value1: 3   value2: 31  
T4's value1: 4   value2: 41  
T5's value1: 5   value2: 51  
Map size: 5 
==========================
KCleanup deletion 
				Node Destructor called
				Node Destructor called
				Node Destructor called
				Node Destructor called
				Node Destructor called
PRE clear Map size: 0 
POST clear Map size: 0 
==========================

*/
```

## Random number generator (KRandom)
Static functions that return a random int or float. Can have specific start and end ranges

### Why?
Sometimes you need a number to help you figure out your mistakes

#### Code Sample
```cpp
#include "KRandom.h"
#include "KPrint.h"
int main()
{
	KPrint::print("==========================\n");
	for (int i = 0; i < 5; i++)
		KPrint::print("Random int: %i \n", KRandom::GetRandomInt());

	for (int i = 0; i < 5; i++)
		KPrint::print("Random int b/w 5 and 20: %i \n", KRandom::GetRandomInt(5, 20));

	for (int i = 0; i < 5; i++)
		KPrint::print("Random float: %f \n", KRandom::GetRandomFloat());

	for (int i = 0; i < 5; i++)
		KPrint::print("Random float b/w 14.5f and 24.2f: %f \n", KRandom::GetRandomFloat(14.5f, 24.2f));
	KPrint::print("==========================\n");

}

/*
Sample Output: 
==========================
Random int: 42 
Random int: 68 
Random int: 35 
Random int: 1 
Random int: 70 
Random int b/w 5 and 20: 17 
Random int b/w 5 and 20: 11 
Random int b/w 5 and 20: 19 
Random int b/w 5 and 20: 7 
Random int b/w 5 and 20: 5 
Random float: 18.410810 
Random float: 86.894348 
Random float: 72.050140 
Random float: 52.353497 
Random float: 31.399487 
Random float b/w 14.5f and 24.2f: 14.645350 
Random float b/w 14.5f and 24.2f: 15.386608 
Random float b/w 14.5f and 24.2f: 18.035185 
Random float b/w 14.5f and 24.2f: 15.928935 
Random float b/w 14.5f and 24.2f: 16.109217 
==========================

*/
```




