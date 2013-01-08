#ifndef HANDLE_H
#define HANDLE_H


// TODO (Viet Nguyen): Fix this smart pointer implementation.
template <class T>
class Handle
{
public:

	Handle(T* pointer)
	:_pointer(pointer)
	,_refCount(1)
	{
	}

	~Handle()
	{
		this->_refCount--;
		if( this->_refCount <= 0 )
		{
			delete this->_pointer;
		}
	}

	Handle(Handle<T>& other)
	:_pointer(other._pointer)
	,_refCount(other._refCount)
	{
		this->_refCount++;
	}

	inline Handle<T>& operator =(Handle<T>& other) const
	{
		Handle<T>& newHandle;
		newHandle._pointer = other._pointer;
		newHandle._refCount = other._refCount+1;
		return newHandle;
	}

	inline T* operator ->()
	{
		return this->_pointer;
	}

	inline unsigned int GetRefCount() const
	{
		return this->_refCount;
	}

private:
	T*				_pointer;
	unsigned int	_refCount;
};


#endif // HANDLE_H