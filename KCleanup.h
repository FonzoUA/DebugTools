#ifndef K_CLEANUPs
#define K_CLEANUP

#include <map>

namespace KCleanup
{
	// Cleans up a map and the objects within it (assuming key needs no explicit deletion)
	template <typename T>
	static void CleanUpMap(T& somemap)
	{
		for (auto it = somemap.begin(); it != somemap.end(); it++)
			delete it->second;
		somemap.clear();
	}
}


#endif // !K_CLEANUP
