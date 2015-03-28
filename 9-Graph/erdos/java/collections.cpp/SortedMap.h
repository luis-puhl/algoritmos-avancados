#ifndef SORTEDMAP_H_
#define SORTEDMAP_H_

template<typename T1, typename T2>
class SortedMap : public Map<T1, T2>
{
	public:
		virtual Comparator<T1> comparator() = 0;
		virtual Set<Map::Entry<T1, T2> > entrySet() = 0;
		virtual T1 firstKey() = 0;
		virtual SortedMap<T1, T2> headMap(T1 toKey) = 0;
		virtual Set<T1> keySet() = 0;
		virtual T1 lastKey() = 0;
		virtual SortedMap<T1, T2> subMap(T1 fromKey, T1 toKey) = 0;
		virtual SortedMap<T1, T2> tailMap(T1 fromKey) = 0;
		virtual Collection<T2> values() = 0;

};

#endif /*SORTEDMAP_H_*/
