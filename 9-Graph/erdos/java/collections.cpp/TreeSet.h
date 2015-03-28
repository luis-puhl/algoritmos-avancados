#ifndef TREESET_H_
#define TREESET_H_

template <typename T>
class TreeSet : public AbstractSet<T>, public NavigableSet<T>
{
	public:
		template <typename T>
		TreeSet();
		template <typename T>
		TreeSet(Collection<T> c);
		template <typename T>
		TreeSet(Comparator<T> comparator);
		template <typename T>
		TreeSet(SortedSet<T> s);

		bool add(T e);
		bool addAll(Collection<T> c);
		T ceiling(T e);
		void clear();
		TreeSet<T> clone();
		Comparator<T> comparator();
		bool contains(T e);
		Iterator<T> descendingIterator();
		NavigableSet<T> descendingSet();
		T first();
		T floor(T e);
		SortedSet<T> headSet(T toElement);
		NavigableSet<T> headSet(T toElement, bool inclusive);
		T higher(T e);
		bool isEmpty();
		Iterator<T> iterator();
		T last();
		T lower(T e);
		T pollFirst();
		T pollLast();
		bool remove(T e);
		int size();
		NavigableSet<T> subSet(T fromElement, bool fromInclusive, T toElement, bool toInclusive);
		SortedSet<T> subSet(T fromElement, T toElement);
		SortedSet<T> tailSet(T fromElement);
		NavigableSet<T> tailSet(T fromElement, bool inclusive);
};

#endif /*TREESET_H_*/
