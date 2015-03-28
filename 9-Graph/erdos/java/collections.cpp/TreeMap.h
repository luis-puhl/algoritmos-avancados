#ifndef TREEMAP_H_
#define TREEMAP_H_

template <typename T1, typename T2>
class TreeMap
{
	template <typename T1, typename T2>
	TreeMap();
	template <typename T1, typename T2>
	TreeMap(Comparator<T1> comparator);
	template <typename T1, typename T2>
	TreeMap(Map<T1, T2> m);
	template <typename T1, typename T2>
	TreeMap(SortedMap<T1, T2> m);

	Map::Entry<T1, T2> ceilingEntry(T1 key);
	T1 ceilingKey(T1 key);
	void clear();
	TreeMap<T1, T2> clone();
	Comparator<T1> comparator();
	bool containsKey(T1 key);
	bool containsValue(T1 value);
	NavigableSet<T1> descendingKeySet();
	NavigableMap<T1, T2> descendingMap();
	Set<Map::Entry<T1, T2> > entrySet();
	Map::Entry<T1, T2> firstEntry();
	T1 firstKey();
	Map::Entry<T1, T2> floorEntry(T1 key);
	T1 floorKey(T1 key);
	T2 get(T1 key);
	SortedMap<T1, T2> headMap(T1 toKey);
	NavigableMap<T1, T2> headMap(T1 toKey, bool inclusive);
	Map::Entry<T1, T2> higherEntry(T1 key);
	T1 higherKey(T1 key);
	Set<T1> keySet();
	Map::Entry<T1, T2> lastEntry();
	T1 lastKey();
	Map::Entry<T1, T2> lowerEntry(T1 key);
	T1 lowerKey(T1 key);
	NavigableSet<T1> navigableKeySet();
	Map::Entry<T1, T2> pollFirstEntry();
	Map::Entry<T1, T2> pollLastEntry();
	T2 put(T1 key, T2 value);
	void putAll(Map<T1, T2> map);
	T2 remove(T1 key);
	int size();
	NavigableMap<T1, T2> subMap(T1 fromKey, bool fromInclusive, T2 toKey, bool toInclusive);
	SortedMap<T1, T2> subMap(T1 fromKey, T1 toKey);
	SortedMap<T1, T2> tailMap(T1 fromKey);
	NavigableMap<T1, T2> tailMap(T1 fromKey, bool inclusive);
	Collection<T2> values();
};

#endif /*TREEMAP_H_*/
