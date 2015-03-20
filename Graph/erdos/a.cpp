#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;
int erdosRunner(int target);

class Author {
	public:
	static int idCounter;
	static Author *erdosPtr;
	int id;
	
	Author *publicouComArr[100];
	int publicouComArrIndex = 0;
	
	int erdosNumber = -1;
	
	char name[50], lname[20], fname[20];
	Author (char *name, char *lname, char *fname){
		this->id = this->idCounter++;
		strcpy(this->name, name);
		strcpy(this->lname, lname);
		strcpy(this->fname, fname);
		if ( strcmp("P.", fname) == 0 && strcmp("Erdos", lname) == 0){
			erdosPtr = this;
			this->erdosNumber = 0;
		}
	}
	/** @memory_leak(não verifica se já tem para poupar tempo) */
	void publicouCom (Author *a){
		if (this->id != a->id){
			printf("\t'%s' publicou com '%s'\n", this->lname, a->lname);
			publicouComArr[publicouComArrIndex++] = a;
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

void erdosIterate(queue<Author*> **queueOri, queue<Author*> **queueDes, int depth, int target, int *foundFLag){
	Author *a;
	while (queueOri != NULL && !(*queueOri)->empty() && !(*foundFLag)){
		a = (*queueOri)->front();
		(*queueOri)->pop();
		if (a == NULL){
			continue;
		}
		a->pushErdosNumber(depth);
		printf("\tlooking '%s' = %d\n", a->lname, a->id);
		if (a->id == target){
			(*foundFLag) = 1;
		}
		
		for (int i = 0; i < a->publicouComArrIndex; i++){
			if (a->publicouComArr[i] != NULL && a->publicouComArr[i]->erdosNumber < 0){
				printf("\t\tpushing '%s'\n", a->publicouComArr[i]->lname);
				(*queueDes)->push(a->publicouComArr[i]);
				a->publicouComArr[i]->pushErdosNumber(depth+1);
			}
		}
	}
}


queue<Author*> *globalqueueA, *globalqueueB;
int erdosRunner(int target){
	queue<Author*> *queueA, *queueB;
	int depth = 0;
	int foundFLag = 0;
	
	if (globalqueueA != NULL && globalqueueB != NULL){
		// já comecou o processo
		printf("\tRetomando processo\n");
		queueA = globalqueueA;
		queueB = globalqueueB;
		depth = globalqueueA->front()->erdosNumber;
	} else {
		// nao iniciado ainda
		printf("\tIniciando processo com Erdos\n");
		queueA = new queue<Author*>;
		queueB = new queue<Author*>;
		queueA->push(Author::erdosPtr);
	}
	
	printf("\tlooking for %d\n", target);
	
	while (1){
		if (queueA != NULL && queueB != NULL && !queueA->empty()){
			printf("\tdepth = %d\n", depth);
			erdosIterate(&queueA, &queueB, depth, target, &foundFLag);
			if (foundFLag){
				globalqueueA = queueA;
				globalqueueB = queueB;
				break;
			}
			depth++;
		}
		if (queueA != NULL && queueB != NULL && !queueB->empty()){
			printf("\tdepth = %d\n", depth);
			erdosIterate(&queueB, &queueA, depth, target, &foundFLag);
			if (foundFLag){
				globalqueueA = queueB;
				globalqueueB = queueA;
				break;
			}
			depth++;
		}
		if (queueA == NULL || queueB == NULL || (queueA->empty() && queueB->empty()) ){
			break;
		}
	}
	
	return foundFLag;
}

char toLower(char ch){
	if (ch >= 'A' && ch <= 'Z') return tolower(ch);
	return ch;
}

#define MAP_MULTI  10
#define MAX_MAP 36 * MAP_MULTI
Author *map[MAX_MAP];
int indexName(char *lname){
	return (toLower(lname[0]) - 'a') * 10;
}
void addAuthor(Author *a){
	int i = indexName(a->lname);
	//~ printf("\tadding %s %d\n", a->lname, i);
	for (; i < MAX_MAP; i++){
		if ( map[i] == NULL ){
			map[i] = a;
			return;
		}
	}
}
Author *findAuthor(char *fname, char *lname){
	int i = indexName(lname) - 1;
	int flag = 3;
	//~ printf("\tlooking for %s %d\n", lname, i);
	for (; i < MAX_MAP; i++){
		if ( map[i] == NULL ){
			flag--;
			if (flag) continue;
			break;
		}
		//~ printf("\t iteration %s\n", map[i]->lname);
		if ( strcmp( map[i]->lname, lname ) == 0 && strcmp( map[i]->fname, fname ) == 0){
			//~ printf("\t found\n");
			return map[i];
		}
	}
	return NULL;
}


char * explodeName(char *paperAuthors, char *name, char *fname, char *lname){
	// paperAuthors = "Smith, M.N., Martin, G., Erdos, P."
	int i = -1, flag = 0;
	int namePtr = 0, lnamePtr = 0, fnamePtr = 0;
	
	flag = 1;
	do {
		i++;
		switch (paperAuthors[i]){
			case ',':
			case ' ':
			break;
			default: flag = 0;
		}
	} while (flag);
	
	// lname
	while (paperAuthors[i] != ',' && paperAuthors[i] != '\0') {
		//~ printf("\tlname\n");
		name[namePtr] = paperAuthors[i];
		lname[lnamePtr] = paperAuthors[i];
		
		namePtr++;
		lnamePtr++;
		i++;
	}
	// spaces
	while ( (paperAuthors[i] == ' ' || paperAuthors[i] == ',') && paperAuthors[i] != '\0') {
		//~ printf("\tspaces\n");
		name[namePtr] = paperAuthors[i];
		i++;
		namePtr++;
	}
	// fname
	while (paperAuthors[i] != ',' && paperAuthors[i] != '\0') {
		//~ printf("\tfname\n");
		name[namePtr] = paperAuthors[i];
		fname[fnamePtr] = paperAuthors[i];
		
		namePtr++;
		fnamePtr++;
		i++;
	}
	
	
	//~ printf("\tendstring\n");
	name[namePtr] = '\0';
	lname[lnamePtr] = '\0';
	fname[fnamePtr] = '\0';
	
	return &(paperAuthors[i]);
}


void Paper(char *paperAuthors){
	char name[50], lname[30], fname[20];
	Author *authors[100];
	int authorsIndex = 0;
	
	while (paperAuthors[0] != '\0') {
		//~ printf("paperAuthors %s\n", paperAuthors);
		paperAuthors = explodeName(paperAuthors, name, fname, lname);
		//~ printf("'%s' => '%s', '%s'\n", name, lname, fname);
		
		authors[authorsIndex] = findAuthor(fname, lname);
		if (authors[authorsIndex] == NULL){
			authors[authorsIndex] = new Author{name, lname, fname};
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
			char paperAuthors[200];
			
			// Smith, M.N., Martin, G., Erdos, P.: Newtonian forms of prime factor matrices
			if ( scanf("%[^:]s\n", paperAuthors) != 1 ) printf("scanf problems\n");
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
			char name[50], lname[20], fname[20], bigname[60];
			Author *a;
			if ( scanf("%[^\n]s\n", bigname) < 1 ) printf("bigname scanf problems\n");
			while ( getchar() != '\n');
			explodeName(bigname, name, fname, lname);
			//~ printf("'%s' lname\n", lname);
			
			a = findAuthor(fname, lname);
			if (a == NULL){
				printf("'%s' infinity\n", name);
			} else {
				int d = a->erdos();
				if (d == -1){
					printf("'%s' infinity\n", name);
				} else {
					printf("%s %d\n", name, d);
				}
			}
		}
		
	}
	
	return 0;
}
