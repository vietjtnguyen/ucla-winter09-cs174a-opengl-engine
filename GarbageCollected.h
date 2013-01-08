#ifndef GARBAGE_COLLECTED_H
#define GARBAGE_COLLECTED_H


#include <vector>

#include "GlobalListItem.h"


using namespace std;


class GarbageCollected : GlobalListItem<GarbageCollected>
{
public:

	GarbageCollected()
	: GlobalListItem<GarbageCollected>()
	{
	}


	virtual ~GarbageCollected()
	{
	}


	static void CleanUp()
	{
		for( unsigned int i = 0; i < GarbageCollected::_globalList.size(); ++i )
		{
			if( GarbageCollected::_globalList.at(i) )
			{
				delete GarbageCollected::_globalList.at(i);
			}
			else
			{
				GarbageCollected::_globalList.erase(GarbageCollected::_globalList.begin()+i);
			}
			i--;
		}
	}
};


#endif // GARBAGE_COLLETED_H