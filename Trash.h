#ifndef TRASH_H
#define TRASH_H


#include <vector>

#include "GlobalList.h"


using namespace std;


// Provides a way of cleaning up all instances of a derived class based on the global list of instances of the derived class. This management comes at the cost of added overhead computation in maintaining the list on construction and destruction. The clean up function must be called explicitly.
class Trash : public GlobalList<Trash>
{
public:

	Trash()
	: GlobalList<Trash>()
	{
	}


	virtual ~Trash()
	{
	}


	static void CleanUp()
	{
		for( unsigned int i = 0; i < Trash::_globalList.size(); ++i )
		{
			if( Trash::_globalList.at(i) )
			{
				Trash* trash = (Trash*)Trash::_globalList.at(i);
				if( trash )
				{
					delete trash;
				}
			}
			else
			{
				Trash::_globalList.erase(Trash::_globalList.begin()+i);
			}
			i--;
		}
	}
};
typedef Trash::GlobalList<Trash> GlobalTrashList;


#endif // TRASH_H