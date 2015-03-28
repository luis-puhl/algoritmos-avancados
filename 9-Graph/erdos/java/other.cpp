#include <stdio.h>

#include <thread>         // std::thread
#include <mutex>          // std::mutex
#include <string>          // std::string
#include <iostream>

#define DD(msg) std::cout << "\t" << msg << "\n"

using namespace std;

class Object{
	static Object **garbage;
	static long int garbageSize;
	static std::mutex garbageMutex;
	static void remove(Object *ptr){
		garbageMutex.lock();
		for (int i = 0; i < Object::garbageSize; i++){
			if (Object::garbage[i] == ptr){
				Object::garbage[i] = NULL;
				break;
			}
		}
		garbageMutex.unlock();
	}
	static void add(Object *ptr){
		garbageMutex.lock();
		if (Object::garbage == NULL){
			Object::garbage = (Object **) malloc(100 * sizeof(Object *));
			Object::garbageSize = 100;
			Object::garbage[0] = ptr;
			Object::garbage[1] = 0;
		} else {
			int i;
			for (i = 0; i < Object::garbageSize; i++){
				if (Object::garbage[i] == NULL){
					Object::garbage[i] = ptr;
					if (i+1 < Object::garbageSize){
						Object::garbage[i+1] = 0;
					}
					break;
				}
			}
			if (i == Object::garbageSize){
				Object::garbage = (Object **) realloc( Object::garbage, sizeof(Object *) * (100 + Object::garbageSize) );
				Object::garbage[Object::garbageSize] = ptr;
				Object::garbage[Object::garbageSize+1] = 0;
				Object::garbageSize += 100;
			}
		}
		garbageMutex.unlock();
	}
	public:
	Object(){
		std::thread (add, this).detach();
	}
	~Object(){
		std::thread (remove, this).detach();
	}
};
std::mutex Object::garbageMutex;
Object **Object::garbage;
long int Object::garbageSize;

class String : public string, Object{};

class Scanner : public Object{
	bool hasNextName_flag = true;
	bool hasNextChar_flag = true;
	char getchar(){
		//~ DD("\tin getchar");
		char ch;
		if (hasNextChar_flag){
			ch = std::getchar();
		} else {
			DD("\tout getchar by null");
			return '\0';
		}
		if ( ch == EOF ){
			hasNextChar_flag = false;
		}
		//~ DD("out getchar");
		return ch;
	}
	public:
	int nextInt(){
		//~ DD("in nextInt");
		int i;
		char ch;
		do { ch = getchar(); } while( ch <= '0' || ch >= '9' );
		i = ch - '0';
		ch = getchar();
		while( ch >= '0' && ch <= '9' ) {
			i = i * 10 + (ch - '0');
			ch = getchar();
		}
		//~ DD("\tout nextInt");
		return i;
	}
	String *nextName(){
		//~ DD("in nextName");
		char ch =  ' ';
		string s;
		
		cin >> s;
		
		cout << "\tIgnoring '";
		while( ch <= '!' || ch >= '~' ){
			cout << ch;
			ch = getchar(); 
		}
		cout << "'\n";
		
		if (ch == ':' || ch == '\n' || ch == '\0'){
			DD("out nextName empty");
			hasNextName_flag = false;
			return new String();
		}
		
		String *s = new String();
		s->append(1, ch);
		ch = getchar();
		while( (ch >= '!' && ch <= '~') && ch != ',' && ch != ':' ){
			s->append(1, ch);
			ch = getchar();
		}
		if (ch == ':' || ch == '\n' || ch == '\0'){
			hasNextName_flag = false;
		}
		//~ DD("out nextName");
		//~ DD(*s);
		return s;
	}
	void getLineEnd(){
		char ch;
		do { ch = getchar(); } while( ch != '\n' );
		hasNextName_flag = true;
	}
	bool hasNextName(){
		return hasNextName_flag;
	}
	bool hasNextChar(){
		return hasNextChar_flag;
	}
};

void UvaErdo(){
	int scenarios, papers, names;
	int scenario, paper, name;
	Scanner sca;
	
	if (sca.hasNextChar()){
		scenarios = sca.nextInt();
	}
	for (scenario = 1; scenario <= scenarios; scenario++){
		printf("Scenario %d\n", scenario);
		papers = sca.nextInt();
		names = sca.nextInt();
		
		printf("\t%dpapers and %d names\n", papers, names);
		
		for (paper = 1; paper <= papers ; paper++){
			printf("paper #%d\n", paper);
			String *s;
			
			while (sca.hasNextName()){
				if (sca.hasNextName()){
					s = sca.nextName();
					printf("\t'%s', ", s->c_str());
				}
				if (sca.hasNextName()){
					s = sca.nextName();
					printf("'%s'\n", s->c_str());
				}
			}
			sca.getLineEnd();
			fflush(stdout);
		}
		
		for (name = 1; name <= names ; name++){
			printf("name #%d\n", name);
			String *s;
			
			if (!sca.hasNextName()){
				sca.getLineEnd();
			}
			if (sca.hasNextName()){
				s = sca.nextName();
				printf("\t'%s', ", s->c_str());
			}
			if (sca.hasNextName()){
				s = sca.nextName();
				printf("'%s'\n", s->c_str());
			}
			//~ sca.getLineEnd();
			fflush(stdout);
		}
	}
	
	return;
}

int main(int argc, char **argv){
	
	UvaErdo();
	
	printf("\nEND PROG\n");
	if (argc == 0){
		getchar();
	}
	
	return 0;
}
