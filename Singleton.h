#ifndef SINGLETON_H
#define SINGLETON_H


#include "Types.h"


// TODO (Viet Nguyen): Make the singleton more robust to errors.
template <class T>
class Singleton
{
public:

	Singleton()
	{
	}

	Singleton(const Singleton& other);

	Singleton& operator= (const Singleton& other);

	~Singleton()
	{
		delete this->_instance;
		this->_instance = NULL;
	}

	static T* Get()
	{
		if( Singleton::_instance == NULL )
		{
			Singleton::_instance = new T();
		}
		return Singleton::_instance;
	}

private:

	static T* _instance;
};


#endif // SINGLETON_H