#ifndef K_CLEANUP
#define K_CLEANUP

#include <map>
#include <list>
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
	
	// cleans up a list and the objects within it
	template <class T>
	static void CleanUpList(std::list<T*>& somelist)
	{
		T* temp;
		while (!somelist.empty())
		{
			temp = somelist.front();
			somelist.pop_front();
			delete temp;
		}
	}
}


#endif // !K_CLEANUP
