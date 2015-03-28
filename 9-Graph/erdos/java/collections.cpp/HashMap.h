#ifndef HASHMAP_H_
#define HASHMAP_H_

template <typename T1, typename T2>
class HashMap : public AbstractMap<T1, T2>, public Map<T1, T2>
{
	public:
		template <typename T1, typename T2>
		HashMap();
		template <typename T1, typename T2>
		HashMap(int initialCapacity);
		template <typename T1, typename T2>
		HashMap(int initialCapacity, fload loadFactor);
		template <typename T1, typename T2>
		HashMap(Map<T1, T2> map);

		void clear();
		HashMap<T1, T2> clone();
		bool containskey(T1 key);
		bool containsValue(T2 value);
		Set<Map::Entry<T1, T2> > entrySet();
		T2 get(T1 key);
		bool isEmpty();
		Set<T1> keySet();
		T2 put(T1 key, T2 value);
		void putAll(Map<T1, T2> m);
		T2 remove(T1 key);
		int size();
		Collection<T2> values();
};

#endif /*HASHMAP_H_*/
