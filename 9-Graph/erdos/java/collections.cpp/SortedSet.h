#ifndef SORTEDSET_H_
#define SORTEDSET_H_

template<typename T>
class SortedSet : public Set<T>
{
	public:
		virtual Comparator<T> comparator() = 0;
		virtual T first() = 0;
		virtual SortedSet<T> headSet(T const& toElement) = 0;
		virtual T const& last()const = 0;
		virtual SortedSet<T> subSet(T const& fromElement, T const& toElement) = 0;
		virtual SortedSet<T> tailSet(T const& fromElement) = 0;
};

#endif /*SORTEDSET_H_*/
