#ifndef TEST_TIMER
#define TEST_TIMER

#include "TestAlign16.h"
#include "KTimer.h"

// https://msdn.microsoft.com/en-us/library/windows/desktop/ms644905(v=vs.85).aspx
// Retrieves the frequency of the performance counter. The frequency of the performance counter is fixed 
// at system boot and is consistent across all processors. Therefore, the frequency need only be queried upon application 
// initialization, and the result can be cached.
// Only works on Windows
#include <Windows.h>
#define QPFrequency(freq) QueryPerformanceFrequency(freq)

#include <time.h>

typedef LARGE_INTEGER qpf_time;


// Used in maths to get value in desired time format
enum _timeTypes
{
	Minutes = 60000,
	Seconds = 1000,
	Milliseconds = 1
};

class KTimer : public Align16
{
public:
	KTimer();
	KTimer(const char* name);
	KTimer(const KTimer&) = delete;
	KTimer& operator=(const KTimer&) = delete;
	virtual ~KTimer();

	void Start();
	void Stop();
	void Reset();

	void PrintTimestamp(const char* timestampName, const _timeTypes& timetype = Milliseconds);
	void PrintTime(const _timeTypes& timetype = Milliseconds);

private:
	qpf_time CurClock(qpf_time* OUT_time);

	float privGetTimeSinceTimestamp(const float& timetype);
	float privGetTotalTime(const float& timetype);
	float privCalculateTimeElapsed(const qpf_time& begin, const qpf_time& end);

	qpf_time timeStart;
	qpf_time timeEnd;
	qpf_time prevTimestamp;
	qpf_time perfCounterFreq;

	const char* timerName;
	bool isRunning;
};


#endif // !TEST_TIMER
