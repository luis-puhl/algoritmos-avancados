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
void freeMemory();

class Snode{
	public:
	static nat idCounter;
	nat id;
	std::set<Snode*> publ;
	nat depht = 0;
	char visited = 0;
	void push(Snode *other){
		if (other==NULL) return;
		publ.insert(other);
	}
	Snode(){
		id = idCounter++;
		depht = 0;
	}
	void process(std::list<Snode*> *targets){
		int count = 0;
		std::queue<Snode*> *q, *n;
		nat depht = 0;
		n = new std::queue<Snode*>{};
		n->push(this);
		targets->remove(this);
		this->depht = depht;
		this->visited = 1;
		while ( !targets->empty() && !n->empty() ){
			//~ printf("level %d: %lu targest to go whith %lu nodes to see\n", depht, targets->size(), n->size());
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
					if (!(*i)->visited){
						n->push((*i));
						(*i)->depht = depht;
						targets->remove((*i));
						(*i)->visited = 1;
					}
				}
			}
		}
		//~ printf("processed %d nodes\n", count);
	}
};
nat Snode::idCounter = 0;

class Author: public Snode{
	public:
	static Author *erdosPtr;
	
	static std::set<Author*> authors;
	static Author *findAuthor(std::string fname, std::string lname){
		//~ printf("\tfindAuthor name = '%s', '%s'\n", lname.c_str(), fname.c_str());
		for (
			std::set<Author*>::iterator i = Author::authors.begin(); 
			i != Author::authors.end();
			i++
		){
			//~ printf("\t\t loking '%s', '%s'\n", (*i)->lname.c_str(), (*i)->fname.c_str());
			if (fname.compare( (*i)->fname ) == 0 && lname.compare( (*i)->lname ) == 0){
				return *i;
			}
		}
		//~ printf("\tAuthor not found\n");
		return NULL;
	}
	
	std::string lname, fname;
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
		//~ printf("\tauhor '%s', '%s' alocated as %d\n", this->lname.c_str(), this->fname.c_str(), this->id);
		authors.insert(this);
	}
	~Author(){
		//~ printf("\tauhor '%s', '%s' deleted\n", this->lname.c_str(), this->fname.c_str());
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
	
	//~ printf("\tendstring\n");
	lname[lnamePtr] = '\0';
	fname[fnamePtr] = '\0';
	
	return &(paperAuthors[i]);
}

void freeMemory(){
	//~ printf("\tfreeMemory\n");
	for (
		std::set<Author*>::iterator i = Author::authors.begin(); 
		i != Author::authors.end();
		i++
	){
		delete *i;
	}
	Author::authors.clear();
	Author::erdosPtr = NULL;
}

void UvaErdo(){
	int scenarios, papers, names;
	int scenario, paper, nameInd;
	int scanfreturnvalue;
	
	scanfreturnvalue = scanf("%d", &scenarios);
	for (scenario = 1; scenario <= scenarios; scenario++){
		//~ printf("Scenario %d\n", scenario);
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
				//~ printf("\t'%s' => '%s', '%s'\n", paperAuthors, lname, fname);
				
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
		std::list<Author*> *targets = new std::list<Author*>;
		std::list<std::string*> *targetsNames = new std::list<std::string*>;
		for (nameInd = 1; nameInd <= names; nameInd++){
			char lname[MAX_NAME_LEN], fname[MAX_NAME_LEN], bigname[MAX_INPUT_LEN];
			Author *a;
			scanfreturnvalue =  scanf("%[^\n]s\n", bigname);
			while ( getchar() != '\n');
			explodeName(bigname, fname, lname);
			//~ printf("\t'%s' => '%s', '%s'\n", bigname, lname, fname);
			
			std::string *bigstring = new std::string(bigname);
			targetsNames->push_back(bigstring);
			a = Author::findAuthor(fname, lname);
			if (a == NULL){
				continue;
			} else {
				//~ printf("'%s' lname\n", a->lname.c_str());
				targets->push_back(a);
			}
		}
		
		//~ if (Author::erdosPtr != NULL){
			//~ Author::erdosPtr->process(targets);
			//~ printf("Author::erdosPtr not NULL\n");
		//~ }
		
		std::list<std::string*>::iterator iNames = targetsNames->begin();
		for (std::list<Author*>::iterator a = targets->begin();
			a != targets->end() && iNames != targetsNames->end();
			a++
		){
			if ((*a) == NULL){
				printf("%s infinity\n", (*iNames)->c_str());
			} else {
				int d = (*a)->depht;
				if (d <= 0 && Author::erdosPtr != (*a)){
					printf("%s, %s infinity\n", (*a)->lname.c_str(), (*a)->fname.c_str());
				} else {
					printf("%s, %s %d\n", (*a)->lname.c_str(), (*a)->fname.c_str(), d);
				}
			}
			fflush(stdout);
			
			iNames++;
		}
		
		for (
			std::list<std::string*>::iterator i = targetsNames->begin();
			i != targetsNames->end();
			i++
		){
			delete *i;
		}
		
		delete targets;
		delete targetsNames;
		freeMemory();
	}
}


int main(int argc, char **argv){
	UvaErdo();
	return 0;
}
