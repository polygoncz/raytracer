/*
 * reference.h
 *
 *  Created on: 19. 8. 2013
 *      Author: pavel
 */

#ifndef REFERENCE_H_
#define REFERENCE_H_

#include <cstdlib>

class ReferenceCounted
{
public:
	ReferenceCounted() { count = 0; }
	mutable unsigned int count;
};

template<class T>
class Reference
{
public:
	Reference(T *_ptr = NULL)
		: ptr(_ptr)
	{
		if (ptr)
			ptr->count++;
	}

	Reference(const Reference<T>& orig)
	{
		ptr = orig.ptr;

		if (ptr) ptr->count++;
	}

	virtual ~Reference()
	{ decrementCount();	}

	T& operator* ()
	{ return *ptr; }

	T* operator-> ()
	{ return ptr; }

	T* operator& ()
	{ return ptr; }

	bool operator== (const Reference<T>& right) const
	{ return ptr == right.ptr; }

	bool operator!= (const Reference<T>& right) const
	{ return ptr != right.ptr; }

	Reference<T>& operator= (T* right)
	{
		if (right) right->count++;

		decrementCount();

		ptr = right;

		return *this;
	}

	Reference<T>& operator= (const Reference<T>& right)
	{
		if (this == &right)
			return *this;

		decrementCount();

		right.ptr->count++;
		ptr = right.ptr;

		return *this;
	}

	operator bool ()
	{ return ptr == NULL; }

	void Unset()
	{
		decrementCount();
		ptr = NULL;
	}

private:
	void decrementCount()
	{
		if (ptr)
		{
			if (--ptr->count == 0 && ptr)
			{
				delete ptr;
				ptr = NULL;
			}
		}
	}

private:
	T *ptr;
};

#endif /* REFERENCE_H_ */
