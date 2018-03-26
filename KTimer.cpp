#include "KTimer.h"
#include "KPrint.h"
#include <assert.h>

KTimer::KTimer()
	: timerName("NONAME"),
	isRunning(false)
{
	QPFrequency(&perfCounterFreq);
}

KTimer::KTimer(const char* name)
	: timerName(name),
	isRunning(false)
{
	QPFrequency(&perfCounterFreq);
}

KTimer::~KTimer()
{
}

// Starts the timer
void KTimer::Start()
{
	isRunning = true;
	timeStart = CurClock(&timeStart);
	prevTimestamp = timeStart;
}

// Stops the timer
void KTimer::Stop()
{
	assert(isRunning);
	isRunning = false;
	timeEnd = CurClock(&timeEnd);
}

// Essentially a Start() but can only be used if the timer is already running
void KTimer::Reset()
{
	assert(isRunning);
	timeStart = CurClock(&timeStart);
	prevTimestamp = timeStart;
}

// Retrieves the current value of the performance counter
// https://msdn.microsoft.com/en-us/library/windows/desktop/ms644904(v=vs.85).aspx
qpf_time KTimer::CurClock(qpf_time* OUT_time)
{
	QueryPerformanceCounter(OUT_time);
	return *OUT_time;
}

// Calculates time elapsed between two values
float KTimer::privCalculateTimeElapsed(const qpf_time& begin, const qpf_time& end)
{
	// Since QPC uses LARGE_INTEGER, we need to access specific member within it to 
	// retrieve the value. Since its not a portable code no union shenanigans
	// https://msdn.microsoft.com/en-us/library/windows/desktop/aa383713(v=vs.85).aspx
	// https://stackoverflow.com/questions/3606902/cant-make-sense-of-large-integer-struct
	return (end.QuadPart - begin.QuadPart) * 1000.0f / perfCounterFreq.QuadPart;
}

// Calculates time elapsed since previous timestamp
float KTimer::privGetTimeSinceTimestamp(const float& timetype)
{
	assert(isRunning);
	qpf_time temp;
	temp = CurClock(&temp);
	float returnVal = privCalculateTimeElapsed(prevTimestamp, temp) / timetype;
	prevTimestamp = temp;
	return returnVal;
}

// Print time elapsed since prev timestamp with desired time unit
void KTimer::PrintTimestamp(const char* timestampName, const _timeTypes& timetype)
{
	KPrint::print("[KTIMER] | %s timer's %s timestamp: %.4f \n", timerName, timestampName, privGetTimeSinceTimestamp((float)timetype));
}

// Calculates time between the start and current point in time. If the timer is no 
// longer running returns time elapsed b/w the its start and end times
float KTimer::privGetTotalTime(const float& timetype)
{
	if (isRunning)
	{
		qpf_time temp;
		temp = CurClock(&temp);
		return privCalculateTimeElapsed(timeStart, temp) / timetype;
	}
	return privCalculateTimeElapsed(timeStart, timeEnd) / timetype;
}

// Prints time between the start and current point in time. If the timer is no longer running 
// returns time elapsed b/w the its start and end times
void KTimer::PrintTime(const _timeTypes& timetype)
{
	KPrint::print("[KTIMER] | %s timer's time is: %.4f \n", timerName, privGetTotalTime((float)timetype));
}