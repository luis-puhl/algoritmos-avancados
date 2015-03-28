#ifndef MAP_H_
#define MAP_H_

template<typename T1, typename T2>
class Map
{
	public:
		virtual void clear() = 0;
		virtual bool containsKey(T1 key) = 0;
		virtual bool containsValue(T2 val) = 0;
		virtual Set<Map::Entry<T1,T2> > entrySet() = 0;
		virtual bool equals(Map<T1,T2> e) = 0;
		virtual T2 get(T1 key) = 0;
		virtual int hashCode() = 0;
		virtual bool isEmpty() = 0;
		virtual Set<T1> keySet() = 0;
		virtual T2 put(T1 key, T2 val) = 0;
		virtual void putAll(Map<T1, T2> m) = 0;
		virtual T2 remove(T1 key) = 0;
		virtual int size() = 0;
		virtual Collection<T2> values() = 0;
};

#endif /*MAP_H_*/
