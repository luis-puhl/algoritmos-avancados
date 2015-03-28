#ifndef HASHSET_H_
#define HASHSET_H_

template <typename T>
class HashSet : public AbstractSet<T>, public Set<T>
{
	public:
		template <typename T>
		HashSet();
		template <typename T>
		HashSet(Collection<T> c);
		template <typename T>
		HashSet(int initialCapacity);
		template <typename T>
		HashSet(int initialCapacity, float loadFactor);

		bool add(T e);
		void clear();
		HashSet<T> clone();
		bool contains(T e);
		bool isEmpty();
		Iterator<T> iterator();
		bool remove(T e);
		int size();
};

#endif /*HASHSET_H_*/
