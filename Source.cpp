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

	KPrint::print("==========\n");
	KPrint::print("Hello World!\n");
	KPrint::print("----------\n");
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
