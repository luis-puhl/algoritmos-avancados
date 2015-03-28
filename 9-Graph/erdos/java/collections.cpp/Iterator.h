#ifndef ITERATOR_H_
#define ITERATOR_H_

template <typename T>
class Iterator
{
	public:
		virtual bool hasNext() = 0;
		virtual T next() = 0;
		virtual ~Iterator(){};
};

#endif /*ITERATOR_H_*/
