#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <set>
#include <list>
#include <queue>
#include <string>

#define MAX_AUTHORS 10001
#define MAX_NAME_LEN 101 
#define MAX_PAPER_AUTHORS 5001 
#define MAX_INPUT_LEN 10001 
#define MAX_LINKS 501 
typedef unsigned int nat; // stands for natural

// bitfield
class bitmap{
	/**
	 * Matriz simétrica com diagonal zero
	 **/
	#define _MAX_MAP ( (MAX_AUTHORS * MAX_AUTHORS) / 2 ) - 2
	bool map[_MAX_MAP];
	
	nat serialize(nat x, nat y){
		printf("\tserialize\n");
		if (x == y) return 0;
		if (x > y) return serialize(y, x);
		nat k = (x*y) / 2;
		if (k >= _MAX_MAP) return 0;
		printf("\tserialize(%d, %d) in to %u\n", x, y, k);
		return k;
	}
	public:
	bool get(nat x, nat y){
		nat se = serialize(x, y);
		if (se == 0) return false;
		return map[ se ];
	}
	bool put(nat x, nat y, bool k){
		nat se = serialize(x, y);
		if (se == 0) return false;
		map[ se ] = k;
		return true;
	}
	bool set(nat x, nat y){
		nat se = serialize(x, y);
		if (se == 0) return false;
		map[ se ] = true;
		return true;
	}
	/**
	 * @deprecated
	 */
	bool clear(nat x, nat y){
		nat se = serialize(x, y);
		if (se == 0) return false;
		map[ se ] = true;
		return true;
	}
	bitmap(){
		memset(map, 0, _MAX_MAP * ( sizeof(bool) * sizeof(int) ));
	}
};

int testBitmap(int argc, char **argv){
	bitmap yay;
	printf("teste size of bool %lu and bitmap is %lu\n", sizeof(bool), sizeof(bitmap));
	yay.set(MAX_AUTHORS - 2, MAX_AUTHORS - 1) ? : printf("\tfaild\n");
	printf("yay\n");
	bool x = yay.get(MAX_AUTHORS - 2, MAX_AUTHORS - 1);
	printf("yay\n");
	x ? printf("\\o/\n") : printf("\tfaild\n");
	printf("%d\n", x);
	
	return 0;
}

class Snode{
	public:
	static nat idCounter;
	nat id;
	std::set<Snode*> publ;
	nat depht = 0;
	void push(Snode *other){
		if (other==NULL) return;
		printf("inserting %u on %u\n", other->id, this->id);
		publ.insert(other);
	}
	Snode(){
		id = idCounter++;
		depht = 0;
	}
	~Snode(){
		for (std::set<Snode*>::iterator i = publ.begin(); i != publ.end(); i++){
			delete *i;
		}
		printf("id %d -> depht %d\n", this->id, this->depht);
	}
	void process(std::list<Snode*> *targets){
		int count = 0;
		std::queue<Snode*> *q, *n;
		nat depht = 0;
		n = new std::queue<Snode*>{};
		n->push(this);
		targets->remove(this);
		this->depht = depht;
		while ( !targets->empty() ){
			printf("level %d: %lu targest to go\n", depht, targets->size());
			// swap queues
			depht++;
			q = n;
			n = new std::queue<Snode*>{};
			
			while ( !q->empty() ){
				count++;
				
				Snode *v = q->front();
				q->pop();
				for (
					std::set<Snode*>::iterator i = v->publ.begin(); 
					i != v->publ.end();
					i++
				){
					if ((*i)->depht == 0){
						n->push((*i));
						(*i)->depht = depht;
						targets->remove((*i));
					}
				}
			}
		}
		printf("processed %d nodes\n", count);
	}
};
nat Snode::idCounter = 0;

void testSGraf(){
	Snode *n = new Snode;
	std::list<Snode*> targets;
	Snode *x, *k;
	for (int i = 0; i < 10; i++){
		x = new Snode;
		n->push(x);
		k = new Snode;
		x->push(k);
	}
	targets.push_back(k);
	
	printf("targets %lu\n", targets.size());
	n->process(&targets);
	
	getchar();
	delete n;
}

class Author: public Snode{
	public:
	static std::set<Author*> authors;
	static Author *findAuthor(std::string fname, std::string lname){
		for (
			std::set<Author*>::iterator i = Author::authors.begin(); 
			i != Author::authors.end();
			i++
		){
			if (fname.compare( (*i)->fname ) && lname.compare( (*i)->lname )){
				return *i;
			}
		}
		return NULL;
	}
	std::string lname, fname;
	static Author *erdosPtr;
	Author (char *lname, char *fname) : Snode() {
		if (strlen(lname) == 0 || strlen(fname) == 0){
			throw 1;
		}
		this->id = this->idCounter++;
		this->lname = lname;
		this->fname = fname;
		if ( strcmp("P.", fname) == 0 && strcmp("Erdos", lname) == 0){
			erdosPtr = this;
		}
		printf("\tauhor '%s', '%s' alocated as %d\n", this->lname.c_str(), this->fname.c_str(), this->id);
		authors.insert(this);
	}
	void publicouCom(Author *other){
		this->push(other);
	}
	void process(std::list<Author*> *targets){
		std::list<Snode*> t;
		for (
			std::list<Author*>::iterator i = targets->begin();
			i != targets->end();
			i++
		){
			t.push_back( (Snode*) *i );
		}
		Snode::process(&t);
	}
};
std::set<Author*> Author::authors;
Author* Author::erdosPtr;

void testAuthor(){
	char lname[MAX_NAME_LEN], fname[MAX_NAME_LEN];
	strcpy(lname, "Erdos");
	strcpy(fname, "P.");
	Author *n = new Author{lname, fname};
	std::list<Author*> targets;
	Author *x, *k;
	for (int i = 0; i < MAX_AUTHORS; i++){
		lname[0] = lname[0]=='Z'?lname[0]: 'a' - 1;
		lname[0]<'z' ? lname[0]++ : lname[1]<'z' ? lname[1]++ : lname[2]++;
		x = new Author{lname, fname};
		n->push(x);
		
		lname[0] = lname[0]=='Z'?lname[0]: 'a' - 1;
		lname[0]<'z' ? lname[0]++ : lname[1]<'z' ? lname[1]++ : lname[2]++;
		k = new Author{lname, fname};
		x->push(k);
	}
	targets.push_back(k);
	
	printf("targets %lu\n", targets.size());
	getchar();
	Author::erdosPtr->process(&targets);
	
	getchar();
	delete n;
}

char * explodeName(char *paperAuthors, char *fname, char *lname){
	// paperAuthors = "Smith, M.N., Martin, G., Erdos, P."
	int i = -1, flag = 0;
	int lnamePtr = 0, fnamePtr = 0;
	
	flag = 1;
	do {
		i++;
		switch (paperAuthors[i]){
			case ',':
			//~ case ' ':
			break;
			default: flag = 0;
		}
	} while (flag);
	
	while (paperAuthors[i] == ' '){
		i++;
	}
	
	// lname
	while (paperAuthors[i] != ',' && paperAuthors[i] != '\0') {
		//~ printf("\tlname\n");
		lname[lnamePtr] = paperAuthors[i];
		
		lnamePtr++;
		i++;
	}
	// spaces
	while ( (paperAuthors[i] == ' ' || paperAuthors[i] == ',') && paperAuthors[i] != '\0') {
		//~ printf("\tspaces\n");
		i++;
	}
	// fname
	while (paperAuthors[i] != ',' && paperAuthors[i] != '\0' && paperAuthors[i] != ' ') {
		//~ printf("\tfname\n");
		fname[fnamePtr] = paperAuthors[i];
		
		fnamePtr++;
		i++;
	}
	while (paperAuthors[i] != ',' && paperAuthors[i] != '\0') {
		i++;
	}
	
	printf("\tendstring\n");
	lname[lnamePtr] = '\0';
	fname[fnamePtr] = '\0';
	
	return &(paperAuthors[i]);
}

void freeMemory(){
	for (
		std::set<Author*>::iterator i = Author::authors.begin(); 
		i != Author::authors.end();
		i++
	){
		delete *i;
	}
}

void UvaErdo(){
	int scenarios, papers, names;
	int scenario, paper, nameInd;
	int scanfreturnvalue;
	
	scanfreturnvalue = scanf("%d", &scenarios);
	for (scenario = 1; scenario <= scenarios; scenario++){
		scanfreturnvalue = scanf("%d %d\n", &papers, &names);
		scanfreturnvalue = scanfreturnvalue / 2;
		
		char *ptr;
		ptr = (char*)malloc(sizeof(char) * MAX_INPUT_LEN);
		for (paper = 1; paper <= papers ; paper++){
			char *paperAuthors;
			paperAuthors = ptr;
			
			scanfreturnvalue = scanf("%[^:]s\n", paperAuthors);
			while ( getchar() != '\n');
			
			char lname[MAX_NAME_LEN], fname[MAX_NAME_LEN];
			Author *authors[MAX_PAPER_AUTHORS];
			int authorsIndex = 0;
			
			while (paperAuthors[0] != '\0') {
				paperAuthors = explodeName(paperAuthors, fname, lname);
				printf("\t'%s' => '%s', '%s'\n", paperAuthors, lname, fname);
				
				authors[authorsIndex] = Author::findAuthor(fname, lname);
				if (authors[authorsIndex] == NULL){
					if (strlen(lname) == 0 || strlen(fname) == 0){
						continue;
					}
					authors[authorsIndex] = new Author{lname, fname};
				}
				authorsIndex++;
			}
			
			for (int i = 0; i < authorsIndex; i++){
				for (int j = 0; j < authorsIndex; j++){
					authors[i]->publicouCom(authors[j]);
				}
			}
			ptr = (char*) memset(ptr, 0, sizeof(char) * MAX_INPUT_LEN);
		}
		
		printf("Scenario %d\n", scenario);
		std::list<Author*> *targets;
		targets = new std::list<Author*>;
		for (nameInd = 1; nameInd <= names; nameInd++){
			char lname[MAX_NAME_LEN], fname[MAX_NAME_LEN], bigname[MAX_INPUT_LEN];
			Author *a;
			if ( scanf("%[^\n]s\n", bigname) < 1 ) printf("bigname scanf problems\n");
			while ( getchar() != '\n');
			explodeName(bigname, fname, lname);
			//~ printf("'%s' lname\n", lname);
			
			a = Author::findAuthor(fname, lname);
			targets->push_back(a);
		}
		
		Author::erdosPtr->process(targets);
		for (std::list<Author*>::iterator a = targets->begin();
			a != targets->end(); a++
		){
			if ((*a) == NULL){
				printf("%s, %s infinity\n", (*a)->lname.c_str(), (*a)->fname.c_str());
			} else {
				int d = (*a)->depht;
				if (d < 0){
					printf("%s, %s infinity\n", (*a)->lname.c_str(), (*a)->fname.c_str());
				} else {
					printf("%s, %s %d\n", (*a)->lname.c_str(), (*a)->fname.c_str(), d);
				}
			}
		}
		
		freeMemory();
	}
}


int main(int argc, char **argv){
	UvaErdo();
	
	return 0;
}
