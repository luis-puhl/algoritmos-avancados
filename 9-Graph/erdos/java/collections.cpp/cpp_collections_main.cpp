#include "SimpleCollection.h"

#include <iostream>


int main(void)
{
	SimpleCollection<int> sc;

	assert(sc.size() == 0);

	for(int i = 1; i <= 100; i++)
		sc.add(i);

	Iterator<int>* si = sc.iterator();
	for(int i = 1;si->hasNext(); i++)
	{
		assert(si->next() == i);
	}

	assert(sc.size() == 100);

	sc.clear();

	assert(sc.size() == 0);

	assert(sc.empty() == 1);

	sc.add(100);
	sc.add(440);

	assert(sc.size() == 2);

	assert(sc.contains(100) == 1);

	assert(sc.contains(49) == 0);

	assert(sc.empty() == 0);

	assert(sc.remove(100) == 1);

	assert(sc.contains(100) == 0);

	return 0;
}
