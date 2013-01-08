#ifndef GLOBAL_LIST_ITEM_H
#define GLOBAL_LIST_ITEM_H


#include <vector>


using namespace std;


template <class T>
class GlobalListItem
{
public:

	GlobalListItem()
	{
		GlobalListItem::_globalList.push_back(this);
	}


	virtual ~GlobalListItem()
	{
		for( unsigned int i = 0; i < GlobalListItem::_globalList.size(); ++i )
		{
			if( GlobalListItem::_globalList.at(i) == this )
			{
				GlobalListItem::_globalList.erase(GlobalListItem::_globalList.begin()+i);
				break;
			}
		}
	}


	static unsigned int GetSize()
	{
		return this->_globalList.size();
	}


	static T* GetItem(unsigned int i)
	{
		return (T*)this->_globaList.at(i)
	}

protected:

	static vector<GlobalListItem*>	_globalList;
};


#endif // GLOBAL_LIST_ITEM_H