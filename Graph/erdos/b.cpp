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
typedef unsigned int nat; // stands for natural

using namespace std;

vector<string*> GC_string;

class Author{
	public:
	static nat idCounter;
	nat id;
	set<Author*> publ;
	nat depht = 0;
	bool visited = 0;
	
	static Author *erdosPtr;
	
	static map<string, Author*> authors;
	
	string *lname, *fname;
	
	void process(set<Author*> &targets){
		int count = 0;
		queue<Author*> *q, *n;
		nat depht = 0;
		
		n = new queue<Author*>;
		
		n->push(this);
		targets.erase(this);
		
		this->depht = depht;
		this->visited = 1;
		
		while ( !targets.empty() && !n->empty() ){
			//~ printf("level %d: %lu targest to go whith %lu nodes to see\n", depht, targets.size(), n->size());
			// swap queues
			depht++;
			q = n;
			n = new queue<Author*>;
			
			while ( !q->empty() ){
				count++;
				
				Author *v = q->front();
				q->pop();
				
				for (auto i = v->publ.begin(); i != v->publ.end(); ++i){
					if (!(*i)->visited){
						n->push((*i));
						(*i)->depht = depht;
						targets.erase((*i));
						(*i)->visited = 1;
					}
				}
			}
		}
		printf("processed %d nodes\n", count);
	}
	
	static Author *find(string *fname, string *lname){
		string fullname (*lname);
		fullname.append(*fname);
		pair<string, Author*> a = *authors.find(fullname);
		return a.second;
	}
	
	Author (string *fname, string *lname) {
		id = idCounter++;
		
		if (lname->size() == 0 || fname->size() == 0){
			throw 1;
		}
		this->lname = lname;
		this->fname = fname;
		if ( lname->compare("Erdos") == 0 && fname->compare("P.") ){
			erdosPtr = this;
		}
		
		string fullname (*lname);
		fullname.append(*fname);
		pair<string, Author*> a (fullname, this);
		authors.insert(a);
		
		//~ printf("\tauhor '%s', '%s' alocated as %d\n", this->lname.c_str(), this->fname.c_str(), this->id);
	}
	
	Author (char *fname, char *lname){
		string *l = new string(lname);
		string *f = new string(fname);
		GC_string.push_back(l);
		GC_string.push_back(f);
		Author(f, l);
	}
	
	void publicouCom(Author *other){
		if (other==NULL || other == this) return;
		//~ printf("inserting %u on %u\n", other->id, this->id);
		publ.insert(other);
	}
	
	~Author(){
		//~ printf("\tauhor '%s', '%s' deleted\n", this->lname.c_str(), this->fname.c_str());
	}
	static void freeMemory(){
		printf("\tfreeMemory\n");
		for (auto i = authors.begin(); i != authors.end(); ++i){
			//~ delete i->first;
			delete i->second;
		}
		for (auto i : GC_string){
			delete i;
		}
		authors.clear();
		erdosPtr = NULL;
	}
};
nat Author::idCounter = 0;
map<string, Author*> Author::authors;
Author* Author::erdosPtr;

/* -------------------------------------------------------------------------------- */

void testAuthor(){
	char lname[MAX_NAME_LEN], fname[MAX_NAME_LEN];
	strcpy(lname, "Erdos");
	strcpy(fname, "P.");
	Author *n = new Author(fname, lname);
	set<Author*> targets;
	Author *x, *k;
	for (int i = 0; i < MAX_AUTHORS; i++){
		lname[0] = lname[0]=='Z'?lname[0]: 'a' - 1;
		lname[0]<'z' ? lname[0]++ : lname[0] , lname[1]<'z' ? lname[1]++ : lname[2]++;
		x = new Author(fname, lname);
		n->publicouCom(x);
		
		lname[0] = lname[0]=='Z'?lname[0]: 'a' - 1;
		lname[0]<'z' ? lname[0]++ : lname[0] , lname[1]<'z' ? lname[1]++ : lname[2]++;
		k = new Author(fname, lname);
		x->publicouCom(k);
	}
	targets.insert(k);
	
	printf("targets %lu\n", targets.size());
	//~ getchar();
	Author::erdosPtr->process(targets);
	
	//~ getchar();
	Author::freeMemory();
}

/* -------------------------------------------------------------------------------- */

char * explodeName(char *paperAuthors, string **fname, string **lname){
	// paperAuthors = "Smith, M.N., Martin, G., Erdos, P."
	int i = -1;
	bool flag;
	int lnamePtr = 0, fnamePtr = 0;
	char Llname[MAX_NAME_LEN], Lfname[MAX_NAME_LEN];
	
	flag = 0;
	do {
		i++;
		flag |= paperAuthors[i] == ',';
		flag |= paperAuthors[i] == ' ';
		flag |= paperAuthors[i] == '\t';
	} while (flag);
	
	// lname
	while (paperAuthors[i] != ',' && paperAuthors[i] != '\0') {
		Llname[lnamePtr] = paperAuthors[i];
		lnamePtr++;
		i++;
	}
	// spaces
	while (
		(paperAuthors[i] == ' ' || paperAuthors[i] == ',' || paperAuthors[i] == '\t')
		&& paperAuthors[i] != '\0'
	) i++;
	// fname
	while (paperAuthors[i] != ',' && paperAuthors[i] != '\0' && paperAuthors[i] != ' ') {
		Lfname[fnamePtr] = paperAuthors[i];
		fnamePtr++;
		i++;
	}
	while (paperAuthors[i] != ',' && paperAuthors[i] != '\0') {
		i++;
	}
	
	Llname[lnamePtr] = '\0';
	Lfname[fnamePtr] = '\0';
	*fname = new string(Lfname);
	*lname = new string(Llname);
	GC_string.push_back(*fname);
	GC_string.push_back(*lname);
	return &(paperAuthors[i]);
}

/* -------------------------------------------------------------------------------- */

void UvaErdo(){
	int scenarios, papers, names;
	int scenario, paper, nameInd;
	int scanfreturnvalue;
	
	scanfreturnvalue = scanf("%d", &scenarios);
	for (scenario = 1; scenario <= scenarios; scenario++){
		printf("Scenario %d\n", scenario);
		scanfreturnvalue = scanf("%d %d\n", &papers, &names);
		scanfreturnvalue = scanfreturnvalue / 2;
		
		for (paper = 1; paper <= papers ; paper++){
			char *paperAuthors = (char*) malloc( sizeof(char) * MAX_INPUT_LEN );
			
			scanfreturnvalue = scanf("%[^:]s\n", paperAuthors);
			while ( getchar() != '\n');
			
			string *fname, *lname;
			Author *authors[MAX_PAPER_AUTHORS];
			int authorsIndex = 0;
			
			while (paperAuthors[0] != '\0') {
				paperAuthors = explodeName(paperAuthors, &fname, &lname);
				printf("\t'%s' => '%s', '%s'\n", paperAuthors, lname->c_str(), fname->c_str());
				
				authors[authorsIndex] = Author::find(fname, lname);
				if (authors[authorsIndex] == NULL){
					if (lname->size() == 0 || fname->size()  == 0){
						continue;
					}
					authors[authorsIndex] = new Author(lname, fname);
				}
				authorsIndex++;
			}
			
			for (int i = 0; i < authorsIndex; i++){
				for (int j = 0; j < authorsIndex; j++){
					authors[i]->publicouCom(authors[j]);
				}
			}
			
			free(paperAuthors);
		}
		
		printf("Scenario %d\n", scenario);
		
		unordered_map<string*, Author*> theMap;
		for (nameInd = 1; nameInd <= names; nameInd++){
			
			char *bigname = (char*) malloc( sizeof(char) * MAX_INPUT_LEN );
			
			string *fname, *lname;
			scanfreturnvalue =  scanf("%[^\n]s\n", bigname);
			//~ getline(cin, bigname);
			while ( getchar() != '\n');
			explodeName(bigname, &fname, &lname);
			printf("\t'%s' => '%s', '%s'\n", bigname, lname->c_str(), fname->c_str());
			
			string *bigstring = new string(bigname);
			Author *a = Author::find(fname, lname);
			
			pair<string*, Author*> d(bigstring, a);
			theMap.insert( d );
			
			free(bigname);
		}
		
		if (Author::erdosPtr != NULL){
			set<Author*> targets;
			for (auto i : theMap){
				if (i.second != NULL){
					targets.insert(i.second);
				}
			}
			
			Author::erdosPtr->process(targets);
			printf("Author::erdosPtr not NULL\n");
		}
		
		for ( auto it = theMap.begin(); it != theMap.end(); ++it ){
			Author *a = it->second;
			if (a == NULL){
				printf("%s infinity\n", it->first->c_str());
			} else {
				int d = a->depht;
				if (d <= 0 && Author::erdosPtr != a){
					printf("%s, %s infinity\n", a->lname->c_str(), a->fname->c_str());
				} else {
					printf("%s, %s %d\n", a->lname->c_str(), a->fname->c_str(), d);
				}
			}
			fflush(stdout);
			
		}
		
		for ( auto it = theMap.begin(); it != theMap.end(); ++it ){
			delete it->first;
			//~ delete it->second;
		}
		
		Author::freeMemory();
	}
}

/* -------------------------------------------------------------------------------- */

int main(int argc, char **argv){
	
	UvaErdo();
	
	printf("\nEND PROG\n");
	//~ getchar();
	
	return 0;
}
