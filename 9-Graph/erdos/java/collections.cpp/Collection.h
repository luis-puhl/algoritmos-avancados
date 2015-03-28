#ifndef COLLECTION_H_
#define COLLECTION_H_

#include "Iterator.h"

template <typename T>
class Collection
{
	public:

		virtual bool add(T const&) = 0;
		virtual void clear() = 0;
		virtual bool contains(T const&)const = 0;
		virtual bool empty()const = 0;
		virtual Iterator<T>* iterator() = 0;
		virtual bool remove(T const&) = 0;
		virtual int size()const = 0;
		virtual ~Collection() {}
};

#endif /*COLLECTION_H_*/
