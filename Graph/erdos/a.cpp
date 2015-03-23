#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//~ #include <iostream>
//~ #include <vector>
//~ #include <cmath>
#include <set>
#include <queue>

using namespace std;
int erdosRunner(int target);

// multiplicidade para ter MAX_MAP >= 5001
// nomes comecando com a mesma letra
#define MAP_MULTI  53
#define MAX_MAP 95 * MAP_MULTI
#define MAX_NAME_LEN 101 
#define MAX_PAPER_AUTHORS 5001 
#define MAX_INPUT_LEN 10001 
#define MAX_LINKS 501 

class Author {
	public:
	static int idCounter;
	static Author *erdosPtr;
	int id;
	
	Author *publicouComArr[MAX_LINKS];
	int publicouComArrIndex = 0;
	
	int erdosNumber = -1;
	
	char lname[MAX_NAME_LEN], fname[MAX_NAME_LEN];
	Author (char *lname, char *fname){
		if (strlen(lname) == 0 || strlen(fname) == 0){
			throw 1;
		}
		this->id = this->idCounter++;
		strcpy(this->lname, lname);
		strcpy(this->fname, fname);
		if ( strcmp("P.", fname) == 0 && strcmp("Erdos", lname) == 0){
			erdosPtr = this;
			this->erdosNumber = 0;
		}
		printf("\tauhor '%s' alocated as %d\n", this->lname, this->id);
	}
	/** @memory_leak(não verifica se já tem para poupar tempo) */
	void publicouCom (Author *a){
		if (this->id != a->id){
			printf("\t'%s' publicou com '%s'\n", this->lname, a->lname);
			for (int i = 0; i < publicouComArrIndex+1; i++){
				if (publicouComArr[i] == a){
					break;
				}
				if (publicouComArr[i] == NULL){
					publicouComArr[i] = a;
					publicouComArrIndex++;
				}
			}
		}
	}
	void pushErdosNumber(int newNumber){
		int old = this->erdosNumber;
		this->erdosNumber = (old == -1 || old > newNumber) ? newNumber : old;
	}
	int erdos(){
		if (this->erdosNumber == -1){
			erdosRunner(this->id);
		}
		return this->erdosNumber;
	}
};

int Author::idCounter = 0;
Author *Author::erdosPtr = NULL;

set<int> targets;
int isTarget(int id){
	printf("\tisTarget(%d)\n", id);
	set<int>::iterator it = targets.find(id);
	if (*it == id){
		targets.erase(it);
	}
	return targets.empty();
}
/**
 * @param a queue
 * @param d depth
 * @param @output f flag
 * @return new queue
 **/
queue<Author*> *consume(queue<Author*> *in, int d, int *f){
	printf("\tconsume\n");
	queue<Author*> *out;
	out = new queue<Author*>;
	while (in != NULL && !in->empty()){
		printf("\twhile\n");
		Author* a = in->front();
		in->pop();
		if (a == NULL){
			break;
		}
		a->pushErdosNumber(d);
		if ( isTarget(a->id) ){
			*f = 1;
		}
		printf("\tbefore for publicouComArrIndex = %d\n", a->publicouComArrIndex);
		for (int i = 0; i < a->publicouComArrIndex; i++){
			printf("\tfor\n");
			Author* v = a->publicouComArr[i];
			if (v == NULL){
				break;
			}
			if (v->erdosNumber == -1 || v->erdosNumber > d){
				out->push(v);
				v->pushErdosNumber(d+1);
			}
		}
	}
	return out;
}

queue<Author*> *toVisit;
int depth;
void erdosCalculate(){
	int flag = 0;
	if (toVisit == NULL){
		toVisit = new queue<Author*>;
		toVisit->push(Author::erdosPtr);
		depth = 0;
	}
	do {
		toVisit = consume(toVisit, depth, &flag);
	} while ( !flag || toVisit == NULL || toVisit->empty() );
}

int erdosRunner(int target){
	targets.insert(target);
	//~ erdosCalculate();
	return 0;
}

Author *map[MAX_MAP];
int indexName(char *lname){
	char ch = lname[0];
	return (ch - 0x21) * MAP_MULTI;
}
void addAuthor(Author *a){
	int i = indexName(a->lname);
	//~ printf("\tadding %s %d\n", a->lname, i);
	// tenta alocar 
	for (; i < MAX_MAP; i++){
		if ( map[i] == NULL ){
			map[i] = a;
			return;
		}
	}
	// se não consegue antes do final do vetor volta ao inicio
	for (i = 0; i < MAX_MAP; i++){
		if ( map[i] == NULL ){
			map[i] = a;
			return;
		}
	}
}
Author *findAuthor(char *fname, char *lname){
	int i = indexName(lname);
	int flag = 2;
	printf("\tlooking for %s %d\n", lname, i);
	// busca do 'hash' até o final
	for (; i < MAX_MAP; i++){
		//~ printf("\t iteration %d %llx\n", i, (long long int)(map[i]) );
		if ( map[i] == NULL ){
			flag--;
			if (flag) continue;
			break;
		}
		printf("\t iteration %s\n", map[i]->lname);
		if ( strcmp( map[i]->lname, lname ) == 0 && strcmp( map[i]->fname, fname ) == 0){
			//~ printf("\t found\n");
			return map[i];
		}
	}
	// se estava tudo lotado procura do comeco
	if (!flag){
		for (i = 0; i < MAX_MAP; i++){
			if (map[i] == NULL){
				break;
			}
			if (strcmp( map[i]->lname, lname ) == 0 && strcmp( map[i]->fname, fname ) == 0){
				printf("\t found\n");
				return map[i];
			}
		}
	}
	return NULL;
}
void clearAuhtors(){
	for (int i = 0; i < MAX_MAP; i++){
		if (map[i] != NULL){
			delete map[i];
			map[i] = NULL;
		}
	}
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

void Paper(char *paperAuthors){
	char lname[MAX_NAME_LEN], fname[MAX_NAME_LEN];
	Author *authors[MAX_PAPER_AUTHORS];
	int authorsIndex = 0;
	
	while (paperAuthors[0] != '\0') {
		paperAuthors = explodeName(paperAuthors, fname, lname);
		printf("\t'%s' => '%s', '%s'\n", paperAuthors, lname, fname);
		
		authors[authorsIndex] = findAuthor(fname, lname);
		if (authors[authorsIndex] == NULL){
			if (strlen(lname) == 0 || strlen(fname) == 0){
				continue;
			}
			authors[authorsIndex] = new Author{lname, fname};
			addAuthor(authors[authorsIndex]);
		}
		authorsIndex++;
	}
	
	for (int i = 0; i < authorsIndex; i++){
		for (int j = 0; j < authorsIndex; j++){
			authors[i]->publicouCom(authors[j]);
		}
	}
	
}

void freeMemory(){
	delete toVisit;
	toVisit = NULL;
	targets.clear();
	clearAuhtors();
}

int main(int argc, char **argv){
	int scenarios, papers, names;
	int scenario, paper, nameInd;
	
	if ( scanf("%d", &scenarios) != 1 ) printf("scanf problems\n");
	//~ printf("scenarios %d\n", scenarios);
	for (scenario = 1; scenario <= scenarios; scenario++){
		if ( scanf("%d %d\n", &papers, &names) != 2 ) printf("scanf problems\n");
		//~ printf("papers %d\t names %d\n", papers, names);
		
		for (paper = 1; paper <= papers ; paper++){
			// scan papers
			char paperAuthors[MAX_INPUT_LEN];
			
			scanf("%[^:]s\n", paperAuthors);
			while ( getchar() != '\n');
			//~ printf("\n'%s' paperAuthors\n", paperAuthors);
			// paperAuthors = "Smith, M.N., Martin, G., Erdos, P."
			
			/**
			Smith, M.N., Martin, G., Erdos, P.: Newtonian forms of prime factor matrices
			Erdos, P., Reisig, W.: Stuttering in petri nets
			Smith, M.N., Chen, X.: First oder derivates in structured programming
			Jablonski, T., Hsueh, Z.: Selfstabilizing data structures
			*/
			
			Paper(paperAuthors);
			
		}
		
		printf("Scenario %d\n", scenario);
		for (nameInd = 1; nameInd <= names; nameInd++){
			char lname[MAX_NAME_LEN], fname[MAX_NAME_LEN], bigname[MAX_INPUT_LEN];
			Author *a;
			if ( scanf("%[^\n]s\n", bigname) < 1 ) printf("bigname scanf problems\n");
			while ( getchar() != '\n');
			explodeName(bigname, fname, lname);
			//~ printf("'%s' lname\n", lname);
			
			a = findAuthor(fname, lname);
			if (a == NULL){
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
	
	return 0;
}
