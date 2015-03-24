#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <set>
#include <vector>
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
	void process(std::set<Snode*> *targets){
		int count = 0;
		std::queue<Snode*> *q, *n;
		nat depht = 0;
		n = new std::queue<Snode*>{};
		n->push(this);
		targets->erase(this);
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
						targets->erase((*i));
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
	std::set<Snode*> targets;
	Snode *x, *k;
	for (int i = 0; i < 10; i++){
		x = new Snode;
		n->push(x);
		k = new Snode;
		x->push(k);
	}
	targets.insert(k);
	
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
	Author *erdosPtr;
	Author (char *lname, char *fname){
		if (strlen(lname) == 0 || strlen(fname) == 0){
			throw 1;
		}
		this->id = this->idCounter++;
		this->lname = lname;
		this->fname = fname;
		if ( strcmp("P.", fname) == 0 && strcmp("Erdos", lname) == 0){
			erdosPtr = this;
		}
		printf("\tauhor '%s' alocated as %d\n", this->lname.c_str(), this->id);
		authors.insert(this);
	}
	void publicouCom(Author *other){
		this->push(other);
	}
};

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
	
	scanf("%d", &scenarios);
	for (scenario = 1; scenario <= scenarios; scenario++){
		scanf("%d %d\n", &papers, &names);
		
		char *ptr;
		std::vector<Author*> *targets;
		ptr = (char*)malloc(sizeof(char) * MAX_INPUT_LEN);
		for (paper = 1; paper <= papers ; paper++){
			char *paperAuthors;
			paperAuthors = ptr;
			
			scanf("%[^:]s\n", paperAuthors);
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
		targets = new std::vector<Author*>;
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
		Author::process(targets);
		for (std::vector<Author*>::iterator a = targets->begin();
			a != targets->end(); a++
		){
			if ((*a) == NULL){
				printf("%s infinity\n", bigname);
			} else {
				int d = a->erdos();
				if (d < 0){
					printf("%s infinity\n", bigname);
				} else {
					printf("%s %d\n", bigname, d);
				}
			}
		}
		
		freeMemory();
	}
}


int main(int argc, char **argv){
	testSGraf();
	
	return 0;
}
