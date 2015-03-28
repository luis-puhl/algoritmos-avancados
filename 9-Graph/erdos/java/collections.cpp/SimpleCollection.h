#ifndef SIMPLECOLLECTION_H_
#define SIMPLECOLLECTION_H_

#include "Collection.h"
#include <vector>
#include <cassert>
#include <algorithm>
#include <iterator>

template <typename T>
class SimpleIterator;

template <typename T>
class SimpleCollection : public Collection<T>
{
public:
	SimpleCollection();
	~SimpleCollection();
	SimpleCollection(SimpleCollection<T> const&);
	bool add(T const&);
	void clear();
	bool contains(T const&)const;
	bool empty()const;
	Iterator<T>* iterator();
	bool remove(T const&);
	int size()const;

private:
	std::vector<T> elems;


	friend  class SimpleIterator<T>;
};


template <typename ForIter>
class SimpleIterator : public Iterator<typename std::iterator_traits<ForIter>::value_type>
{
	public:
		typedef typename std::iterator_traits<ForIter>::value_type value_type;
		SimpleIterator(ForIter begin, ForIter end);
		bool hasNext();
		typename std::iterator_traits<ForIter>::value_type next();
		~SimpleIterator();

	private:
		ForIter begin, end;
};

template <typename ForIter>
SimpleIterator<ForIter>::SimpleIterator(ForIter begin, ForIter end): begin(begin), end(end)
{

}

template <typename ForIter>
SimpleIterator<ForIter>::~SimpleIterator()
{

}

template <typename ForIter>
bool SimpleIterator<ForIter>::hasNext()
{
	return begin != end;
}

template <typename ForIter>
typename std::iterator_traits<ForIter>::value_type SimpleIterator<ForIter>::next()
{
	return *begin++;
}

template <typename T>
SimpleCollection<T>::SimpleCollection()
{
}
template <typename T>
SimpleCollection<T>::~SimpleCollection()
{
}

template <typename T>
SimpleCollection<T>::SimpleCollection(SimpleCollection<T> const& sc)
{
}

template <typename T>
bool SimpleCollection<T>::add(T const& elem)
{
	elems.push_back(elem);
	return true;
}


template <typename T>
void SimpleCollection<T>::clear()
{
	elems.resize(0);
}

template <typename T>
bool SimpleCollection<T>::contains(T const& elem)const
{
	return std::find(elems.begin(), elems.end(), elem) != elems.end();
}

template <typename T>
bool SimpleCollection<T>::empty()const
{
	return elems.empty();
}

template <typename T>
Iterator<T>* SimpleCollection<T>::iterator()
{
	return new SimpleIterator<typename std::vector<T>::iterator>(elems.begin(), elems.end());
}

template <typename T>
bool SimpleCollection<T>::remove(T const& elem)
{
	typename std::vector<T>::iterator iter = std::find(elems.begin(), elems.end(), elem);

	if (iter == elems.end())
		return false;
	elems.erase(iter);
	return true;
}

template <typename T>
int SimpleCollection<T>::size()const
{
	return elems.size();
}

#endif /*SIMPLECOLLECTION_H_*/
