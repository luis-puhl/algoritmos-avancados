#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <set>
#include <list>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <regex>

#define MAX_AUTHORS 10001
#define MAX_NAME_LEN 101 
#define MAX_PAPER_AUTHORS 5001 
#define MAX_INPUT_LEN 10001 
#define MAX_LINKS 501 

#define null NULL

using namespace std;

typedef bool boolean;

class Object {};
class String: public Object{
	public:
	String (){}
	String (String *other){}
	String (char *other){}
	String (int other){}
	void append(String *other){}
	int length(){
		return -1;
	}
	int compareTo(String other){
		return 0;
	}
	int compareTo(char *other){
		return 0;
	}
	int hashCode(){
		return 1;
	}
	boolean equals(String *other){
		return false;
	}
};

class Scanner : public Object{
	public:
	String *nextLine() {return null;}
	boolean hasNextLine() {return false;}
};

template <class String, class Author> class Entry : public Object{
	private:
	String key;
	Author value;
	public:
	String getKey() {
		return key;
	}
	Author getValue() {
		return value;
	}
	Author setValue(Author value) {
		this->value = value;
		return this->value;
	}
	Entry(String *s, Author *a) {
		this->key = s;
		this->value = a;
	}
};

template <typename T>class Iterator: public Object{
	public:
		virtual bool hasNext() { return false; }
		virtual T* next() {return null;}
		virtual ~Iterator(){}
};
template <typename T> class Collection: public Object{
	public:
		virtual bool add(T *const){ return false; }
		virtual void clear() { };
		virtual bool contains(T const&)const { return false; }
		virtual bool isEmpty()const { return true; }
		virtual Iterator<T>* iterator() { return null; }
		virtual bool remove(T *const) { return false; }
		virtual int size()const { return -1; }
		virtual void begin() {}
		virtual void end() {}
		virtual T* get(T* const) { return null;}
		virtual ~Collection() {}
};

template <class T> class Set : public Collection<T> { };
template <class T> class Queue : public Collection<T> {
	public:
	T* poll(){return null;}
};

template <class Key, class Value> class Map: public Object{
	public:
		virtual bool add(Entry<Key, Value> *const){ return false; }
		virtual bool put(Key *const, Value *const){ return false; }
		virtual void clear() { };
		virtual bool contains(Entry<Key, Value> *const) { return false; }
		virtual bool isEmpty()const { return true; }
		virtual Iterator<Entry<Key, Value>>* iterator() { return null; }
		virtual bool remove(Entry<Key, Value> *const) { return false; }
		virtual int size()const { return -1; }
		virtual void begin() {}
		virtual void end() {}
		virtual Value* get(Key* const) { return null;}
		virtual ~Map() {}
};

class Author : public Object{
	public:
	static int idCounter;
	int id;
	Set<Author> *publ;
	int depht = 0;
	boolean visited = false;

	static Author *erdosPtr;

	static Map<String, Author> *authors;

	String *lname, *fname;

	void process(Set<Author> *targets) {
		int count = 0;
		Queue<Author> *q, *n;
		int depht = 0;

		n = new Queue<Author>();

		n->add(this);
		targets->remove(this);

		this->depht = depht;
		this->visited = true;

		while (!targets->isEmpty() && !n->isEmpty()) {
			#ifdef DEBUG
				printf("level %d: %d targest to go whith %d nodes to see\n", depht,
						targets.size(), n.size());
			#endif
			// swap Queues
			depht++;
			q = n;
			n = new Queue<Author>();

			while (!q->isEmpty()) {
				count++;

				Author *v = q->poll();

				while (v->publ->iterator()->hasNext()){
					Author *i = v->publ->iterator()->next();
					if (!i->visited) {
						n->add(i);
						i->depht = depht;
						targets->remove(i);
						i->visited = true;
					}
				}
			}
		}
		#ifdef DEBUG
			printf("processed %d nodes\n", count);
		#endif
	}

	static Author *find(String *fname, String *lname) {
		String *fullname = new String();
		fullname->append(fname);
		fullname->append(lname);
		#ifdef DEBUG
			printf("\tLooking for '%s'\n", fullname);
			for (Entry<String, Author> it : authors.entrySet()) {
				printf("\t\t'%s'\n", it.getKey());
			}
		#endif
		Author *a = authors->get(fullname);
		return a;
	}

	Author(String *fname, String *lname) {
		#ifdef DEBUG
			printf("\t\tAuthor fname'%s' lname'%s'\n", fname, lname);
		#endif
		this->publ = new Set<Author>();
		id = idCounter++;

		if (lname->length() == 0 || fname->length() == 0) {
			throw 1;
		}
		this->lname = lname;
		this->fname = fname;
		if (lname->compareTo("Erdos") == 0 && fname->compareTo("P.") == 0) {
			erdosPtr = this;
		}

		String *fullname = new String();
		fullname->append(fname);
		fullname->append(lname);
		authors->put(fullname, this);

		#ifdef DEBUG
			printf("\tauhor '%s' alocated as %d\n", fullname, this->id);
		#endif
	}

	void publicouCom(Author *other) {
		if (other == null || other == this)
			return;
		#ifdef DEBUG
			printf("inserting %d on %d\n", other->id, this->id);
		#endif
		publ->add(other);
	}

	static void freeMemory() {
		#ifdef DEBUG
			printf("\tfreeMemory\n");
		#endif
		authors = new Map<String, Author>();
		authors->clear();
		erdosPtr = null;
		idCounter = 0;
	}

	int hashCode() {
		int prime = 31;
		int result = 1;
		result = prime * result + ((fname == null) ? 0 : fname->hashCode());
		result = prime * result + ((lname == null) ? 0 : lname->hashCode());
		return result;
	}

	boolean equals(Author *obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		Author *other = obj;
		if (fname == null) {
			if (other->fname != null)
				return false;
		} else if (!fname->equals(other->fname))
			return false;
		if (lname == null) {
			if (other->lname != null)
				return false;
		} else if (!lname->equals(other->lname))
			return false;
		return true;
	}

	int compareTo(Author *other) {
		return lname->compareTo(other->lname) + fname->compareTo(other->fname);
	}

};
Map<String, Author> *Author::authors = new Map<String, Author>();

class Erdos {
	public:
	
	void testAuthor() {
		String *lname, *fname;
		lname = new String("Erdos");
		fname = new String("P.");
		Author *n = new Author(fname, lname);
		Set<Author> *targets = new Set<Author>();
		Author *x, *k;
		for (int i = 0; i < MAX_AUTHORS; i++) {
			lname = new String(i);
			fname = new String(i);
			x = new Author(fname, lname);
			n->publicouCom(x);

			lname = new String(i);
			fname = new String(i);
			k  = new Author(fname, lname);
			x->publicouCom(k);
			targets->add(k);
		}
		if (k != null) {
			targets->add(k);
		}

		printf("targets %d\n", targets->size());
		getchar();
		
		Author::erdosPtr->process(targets);
	}

	void UvaErdo() {
		int scenarios, papers = 0, names = 0;
		int scenario;

		Scanner *scanIn = new Scanner();
		String s = scanIn->nextLine();
		scenarios = Integer->parseInt(s->trim());
		for (scenario = 1; scenario <= scenarios; scenario++) {
			printf("Scenario %d\n", scenario);

			String nextLine = scanIn->nextLine();
			String s2[] = nextLine->split(" ");
			int i = 0;
			for (; s2[i] != null; i++) {
				try {
					papers = Integer.parseInt(s2[i].trim());
					#ifdef DEBUG
						printf("\tConverted '%s' to %d\n", s2[i].trim(), papers);
					#endif
					break;
				} catch (NumberFormatException e) {
				}
			}
			i++;
			for (; i < s2.length; i++) {
				try {
					names = Integer.parseInt(s2[i].trim());
					#ifdef DEBUG
						printf("\tConverted '%s' to %d\n", s2[i].trim(), names);
					#endif
					break;
				} catch (NumberFormatException e) {
				}
			}
			#ifdef DEBUG
				printf("\tConverted '%s' to %d papers and %d names\n", nextLine, papers,
						names);
			#endif

			readPapers(papers, scanIn);

			#ifdef DEBUG
				printf("Scenario %d\n", scenario);
			#endif

			List<Entry<String, Author>> theMap = new ArrayList<Map.Entry<String, Author>>(names);
			Set<Author> targets = new TreeSet<Author>();

			readCases(names, scanIn, theMap, targets);

			if (Author.erdosPtr != null) {
				Author.erdosPtr.process(targets);
				#ifdef DEBUG
					printf("Author::erdosPtr not null\n");
				#endif
			}

			for (Entry<String, Author> it : theMap) {
				Author a = it.getValue();
				String bigname = it.getKey();
				if (a == null) {
					printf("%s infinity\n", bigname);
				} else {
					int d = a.depht;
					if (d <= 0 && Author.erdosPtr != a) {
						printf("%s, %s infinity\n", a.lname, a.fname);
					} else {
						printf("%s, %s %d\n", a.lname, a.fname, d);
					}
				}
			}

			theMap.clear();
			Author.freeMemory();
		}
	}

	void readPapers(int papers, Scanner scanIn) {
		int paper;
		for (paper = 1; paper <= papers; paper++) {
			String paperAuthors;

			paperAuthors = scanIn.nextLine();
			#ifdef DEBUG
				printf("paper #%d %s\n", paper, paperAuthors);
			#endif

			Author authors[] = new Author[Author.MAX_PAPER_AUTHORS];
			int authorsIndex = 0;

			Pattern p = Pattern.compile("\\s*(\\S*)[,]\\s*(\\S*)[,:]");
			Matcher m = p.matcher(paperAuthors);
			while (m.find()) {
				String lname = m.group(1);
				String fname = m.group(2);

				if (debug) {
					printf("\t'%s' => '%s', '%s'\n", paperAuthors, lname, fname);
				}

				authors[authorsIndex] = Author.find(fname, lname);
				if (authors[authorsIndex] == null) {
					if (lname.length() == 0 || fname.length() == 0) {
						continue;
					}
					authors[authorsIndex] = new Author(fname, lname);
				}
				authorsIndex++;
			}

			for (int i = 0; i < authorsIndex; i++) {
				for (int j = 0; j < authorsIndex; j++) {
					authors[i].publicouCom(authors[j]);
				}
			}
		}
	}

	int readCases(int names, Scanner *scanIn, Collection<Entry<String, Author>> *theMap,
			Set<Author> *targets) {
		int nameInd;
		for (nameInd = 1; nameInd <= names; nameInd++) {
			String bigname;

			bigname = scanIn.nextLine();
			#ifdef DEBUG
				printf("\tname #%d %s\n", nameInd, bigname);
			#endif

			Pattern p = Pattern.compile("\\s*(\\S*)[,]\\s*(\\S*)");
			Matcher m = p.matcher(bigname);
			if (m.find()) {
				String lname = m.group(1);
				String fname = m.group(2);

				#ifdef DEBUG
					printf("\tmatcher2'%s' => '%s', '%s'\n", bigname, lname, fname);
				#endif

				Author a = Author.find(fname, lname);response

				theMap.add(new MyEntry(bigname, a));
				if (a != null) {
					targets.add(a);
					#ifdef DEBUG
						printf("\tauthor case '%s' is #%d\n", a.lname, targets.size());
					#endif
				}
			} else {
				theMap.add(new Entry<String, Author>(bigname, null));
			}
		}
		return nameInd;
	}

	static void main() {
		Erdos erdos = new Erdos(false);
		// erdos.testAuthor();
		erdos.UvaErdo();
		#ifdef DEBUG
			printf("\nEND PROG\n");
		#endif
	}

};

int main(int argc, char **argv){
	Erdos::main();
}
