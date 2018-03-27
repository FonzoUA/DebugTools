#ifndef K_RANDOM
#define K_RANDOM

#include "KPrint.h"
#include <assert.h>
#include <stdlib.h>

namespace KRandom
{
	// Return random int between 1 and 100
	static int GetRandomInt()
	{
		return rand() % 100 + 1;
	}
	
	// Return random int between rangeStart and rangeEnd
	static int GetRandomInt(const int& rangeStart, const int& rangeEnd)
	{
		assert(rangeStart > 0 || rangeEnd > 0 || rangeStart < rangeEnd);
		return (rand() % (rangeEnd - rangeStart + 1)) + rangeStart;
	}

	// Return random float between 1 and 100
	static float GetRandomFloat()
	{
		return (rand() / (float)RAND_MAX * 100.0f) + 1.0f;
	}
	
	// Return random float between rangeStart and rangeEnd
	static float GetRandomFloat(const float& rangeStart, const float& rangeEnd)
	{
		assert(rangeStart > 0 || rangeEnd > 0 || rangeStart < rangeEnd);
		return (rand() / (float)RAND_MAX * (rangeEnd - rangeStart)) + rangeStart;
	}
}

#endif // !K_RANDOM
