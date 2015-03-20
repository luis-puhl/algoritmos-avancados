#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;
int erdosRunner(int target);

#define MAP_MULTI  36
#define MAX_MAP 36 * MAP_MULTI
#define SHORT_NAME 40
#define LONG_NAME 2*SHORT_NAME + 20
#define MAX_PAPER_AUTHORS 100

class Author {
	public:
	static int idCounter;
	static Author *erdosPtr;
	int id;
	
	Author *publicouComArr[MAX_MAP];
	int publicouComArrIndex = 0;
	
	int erdosNumber = -1;
	
	char name[LONG_NAME], lname[SHORT_NAME], fname[SHORT_NAME];
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
	void publicouCom (Author *a){
		if (this->id != a->id){
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
		if (a->id == target){
			(*foundFLag) = 1;
		}
		
		for (int i = 0; i < a->publicouComArrIndex; i++){
			if (a->publicouComArr[i] != NULL && a->publicouComArr[i]->erdosNumber < 0){
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
		queueA = globalqueueA;
		queueB = globalqueueB;
		depth = globalqueueA->front()->erdosNumber;
	} else {
		queueA = new queue<Author*>;
		queueB = new queue<Author*>;
		queueA->push(Author::erdosPtr);
	}
	
	while (1){
		if (queueA != NULL && queueB != NULL && !queueA->empty()){
			erdosIterate(&queueA, &queueB, depth, target, &foundFLag);
			if (foundFLag){
				globalqueueA = queueA;
				globalqueueB = queueB;
				break;
			}
			depth++;
		}
		if (queueA != NULL && queueB != NULL && !queueB->empty()){
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

Author *map[MAX_MAP];
int indexName(char *lname){
	char ch = lname[0];
	ch = (ch >= 'A' && ch <= 'Z')? tolower(ch): ch;
	return (ch - 'a') * MAP_MULTI;
}
void addAuthor(Author *a){
	int i = indexName(a->lname);
	for (; i < MAX_MAP; i++){
		if ( map[i] == NULL ){
			map[i] = a;
			return;
		}
	}
}
Author *findAuthor(char *fname, char *lname){
	int i = indexName(lname) - 1;
	int flag = 2;
	for (; i < MAX_MAP; i++){
		if ( map[i] == NULL ){
			flag--;
			if (flag) continue;
			break;
		}
		if ( strcmp( map[i]->lname, lname ) == 0 && strcmp( map[i]->fname, fname ) == 0){
			return map[i];
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

char * explodeName(char *paperAuthors, char *name, char *fname, char *lname){
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
	
	while (paperAuthors[i] != ',' && paperAuthors[i] != '\0') {
		name[namePtr] = paperAuthors[i];
		lname[lnamePtr] = paperAuthors[i];
		
		namePtr++;
		lnamePtr++;
		i++;
	}
	while ( (paperAuthors[i] == ' ' || paperAuthors[i] == ',') && paperAuthors[i] != '\0') {
		name[namePtr] = paperAuthors[i];
		i++;
		namePtr++;
	}
	while (paperAuthors[i] != ',' && paperAuthors[i] != '\0') {
		name[namePtr] = paperAuthors[i];
		fname[fnamePtr] = paperAuthors[i];
		
		namePtr++;
		fnamePtr++;
		i++;
	}
	
	
	name[namePtr] = '\0';
	lname[lnamePtr] = '\0';
	fname[fnamePtr] = '\0';
	
	return &(paperAuthors[i]);
}

void Paper(char *paperAuthors){
	char name[LONG_NAME], lname[SHORT_NAME], fname[SHORT_NAME];
	Author *authors[MAX_PAPER_AUTHORS];
	int authorsIndex = 0;
	
	while (paperAuthors[0] != '\0') {
		paperAuthors = explodeName(paperAuthors, name, fname, lname);
		
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

void freeMemory(){
	delete globalqueueA;
	delete globalqueueB;
	globalqueueA = NULL;
	globalqueueB = NULL;
	clearAuhtors();
}


int main(int argc, char **argv){
	int scenarios, papers, names;
	int scenario, paper, nameInd;
	
	scanf("%d", &scenarios);
	for (scenario = 1; scenario <= scenarios; scenario++){
		scanf("%d %d\n", &papers, &names);
		
		for (paper = 1; paper <= papers ; paper++){
			char paperAuthors[MAX_PAPER_AUTHORS*LONG_NAME];
			
			scanf("%[^:]s\n", paperAuthors);
			while ( getchar() != '\n');
			
			Paper(paperAuthors);
			
		}
		
		printf("Scenario %d\n", scenario);
		for (nameInd = 1; nameInd <= names; nameInd++){
			char name[LONG_NAME], lname[SHORT_NAME], fname[SHORT_NAME], bigname[LONG_NAME];
			Author *a;
			scanf("%[^\n]s\n", bigname);
			while ( getchar() != '\n');
			explodeName(bigname, name, fname, lname);
			
			a = findAuthor(fname, lname);
			if (a == NULL){
				printf("%s infinity\n", name);
			} else {
				int d = a->erdos();
				if (d < 0){
					printf("%s infinity\n", name);
				} else {
					printf("%s %d\n", name, d);
				}
			}
		}
		
		freeMemory();
	}
	
	return 0;
}
