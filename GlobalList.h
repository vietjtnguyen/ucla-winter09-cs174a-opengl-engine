#ifndef GLOBAL_LIST_H
#define GLOBAL_LIST_H


#include <vector>


using namespace std;


// Provides an iterable global list of instances of the derived class at the cost of overhead computation maintaining the list in construction and destruction
template <class T>
class GlobalList
{
public:

	GlobalList()
	{
		GlobalList::_globalList.push_back(this);
	}


	virtual ~GlobalList()
	{
		for( unsigned int i = 0; i < GlobalList::_globalList.size(); ++i )
		{
			if( GlobalList::_globalList.at(i) == this )
			{
				GlobalList::_globalList.erase(GlobalList::_globalList.begin()+i);
				break;
			}
		}
	}


	static unsigned int GetListSize()
	{
		return T::GlobalList<T>::_globalList.size();
	}


	static T* GetListItem(unsigned int i)
	{
		return (T*)T::GlobalList<T>::_globalList.at(i);
	}

public:

	static vector<GlobalList*>	_globalList;
};


#endif // GLOBAL_LIST_H