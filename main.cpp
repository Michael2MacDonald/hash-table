#include <iostream>
#include <cstring>
#include <cctype> // tolower
#include <cstdlib> // rand
#include <fstream> // file
#include <chrono> // time

#include "student.h"
#include "list.h"
#include "hash.h"

typedef List<Student> StudentList;
typedef 
Node<Student> StudentNode;

unsigned long hash(char*, unsigned int);
void gen(int i, HashTable *Students);

void add(HashTable *Students);
void del(HashTable *Students);
//void print(HashTable *Students);


//Student* &Students;


int main() {
	//std::cout << "=== Main ===\n";
	//Student* tmp = new Student();
	//*tmp = { .id = 123456, .firstName = "John", .lastName = "Doe", .gpa = 3.817 };

	// List to hold all the students. List class is just a class that helps transverse nodes
	// Node class could be used without the List class but you will have to manually save the start node and transverse the node chain to do anything
	//StudentList *Students = new StudentList(new StudentNode(new Student()));
	//StudentList *Students = new StudentList(tmp);
	
	HashTable* Students = new HashTable();
	
	// Add first student
	// new StudentList(tmp)
	
	while(1) {
		// This will produce and error or unexpected behavior if the user enters more than 9 characters
		// To fix this we would have to implement some sort of "string" class with operator overloading or something
		// Because this is not a production, we can just ignore this
		char input[10] = {}; // zero-init the entire array
		std::cout << "===============\nType A Command:\n";
		std::cin >> input;
		
		// to lower case
		for (int i = 0; i < std::strlen(input); i++) {
			input[i] = std::tolower(input[i]);
		}
		
		if (!strcmp(input, "add")) {
			add(Students);
		} else if (!strcmp(input, "gen")) {
			int c = 0;
			std::cout << "How many:\n";
			std::cin >> c;
			gen(c, Students);
		} else if (!strcmp(input, "del")) {
			del(Students);
		} else if (!strcmp(input, "print")) {
			Students->print();
		} else if (!strcmp(input, "quit")) {
			return 0;
		} else { std::cout << "ERROR: Incorrect Command\n"; }
		//} else { std::cout << "========================\nERROR: Incorrect Command\n========================\n"; }

	}
	
	
	//Student* bob = Students->getStart()->getData();
	//bob->id = 123;
	//std::cout << bob->id << '\n';
	
	return 0;
}


//unsigned long hash(char* input, unsigned int tabLen) {
//	unsigned long out = 0;
//	for (int j = 0; input[j]; j++) out += input[j]; // Ends on null terminator
//	return out%tabLen;
//}

//new StudentList(tmp);



void add(HashTable *Students) {
	Student* student = new Student();
	
	// ID
	std::cout << "ID:\n";
	std::cin >> student->id;
	// First name
	char buf[128] = {};
	std::cout << "First Name:\n";
	//return;
	std::cin >> buf;
	char* firstName = (char*)malloc(strlen(buf)+1);
	strcpy(firstName, buf);
	student->firstName = firstName;
	// Last Name
	memset(buf, 0, strlen(buf)); // clear
	std::cout << "Last Name:\n";
	std::cin >> buf;
	char* lastName = (char*)malloc(strlen(buf)+1);
	strcpy(lastName, buf);
	student->lastName = lastName;
	// GPA
	std::cout << "GPA:\n";
	std::cin >> student->gpa;
	
	//StudentNode* node = new StudentNode(student);
	Students->add(student);
}

void del(HashTable *Students) {
	int id = 0;
	std::cout << "Enter The ID Of The Student You Want To Thanos Snap:\n";
	std::cin >> id;
	//std::cout << id << '\n';
	if (!Students->del(id)) return;
	std::cout << "Student does not exist!\n";
}

//void print(HashTable *Students) {
	//if (Students->getStart() == nullptr) {
	//	std::cout << "- No Students -\n";
	//	return;
	//}

	//for (int i=0; i<Students->size(); i++) {
	//	StudentNode* node = (*Students)[i];
	//	Student* student = node->getData();
	//	
	//	std::cout << "-----------------------\n";
	//	std::cout << "ID: " << student->id << '\n';
	//	std::cout << "First Name: ";
	//	for (int i=0; i < strlen(student->firstName); i++) { std::cout << (student->firstName)[i]; }
	//	std::cout << '\n';
	//	std::cout << "Last Name: ";
	//	for (int i=0; i < strlen(student->lastName); i++) { std::cout << (student->lastName)[i]; }
	//	std::cout << '\n';
	//	std::cout << "GPA: " << student->gpa << '\n';
	//}
//}




void gen(int i, HashTable *Students) {
	static int index = 0;
	int old = index;
	for (int j=index; (j-old)<i; j++) {
		index++;
		Student* student = new Student();
		// ID
		student->id = j;
		// First name
		char* raw;
		int len = 0;
		std::ifstream myfile; myfile.open("first.txt");
		int file_size = 0;
		if ( myfile.is_open() ) {
			if (myfile) {
				myfile.seekg(0, std::ios::end);
				file_size = myfile.tellg();
				//std::cout << "file size: " << file_size << "\n";
			}
			len = file_size+1;
			myfile.clear(); myfile.seekg(0);
			raw = (char*)std::malloc(file_size+1);
			for (int x=0; myfile && x<len; x++) {
				raw[x] = myfile.get();
				//std::cout << raw[x];
			}
		}
		int count = 0;
		for (int x=0; x<len; x++) {
			if (raw[x] == '\n') count++;
		}
		//std::cout << "name count: " << count << "\n";
		srand( (std::chrono::duration_cast<std::chrono::milliseconds>((std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now())).time_since_epoch())).count() );
		//srand((unsigned)time(NULL));
		//std::cout << "Time: " << time(NULL) << "\n";
		int nm = (std::rand() % (count+1));
		int k = 0;
		int c = 0;
		char buf[128] = {0};
		for (int x=0; x<len; x++){
			//std::cout << "test 6\n";
			if (raw[x] == '\n') {
				if (c==nm) break;
				for (int g=0; g<128; g++) buf[g]=0;
				c++; k=0;
			} else { buf[k] = raw[x]; k++; }
		}
		char* firstName = (char*)malloc(strlen(buf)+1);
		strcpy(firstName, buf);
		student->firstName = firstName;
		//std::cout << student->firstName << ".\n";
		// reset
		std::free(raw);
		len = 0;
		count = 0;
		nm = (std::rand() % (count+1));
		k = 0;
		c = 0;
		for (int g=0; g<128; g++) buf[g]=0;
		
		// ===================== Last Name ========================
        myfile.close();
        myfile.open("last.txt");
        if ( myfile.is_open() ) {
            int file_size = 0;
            if (myfile) {
                myfile.seekg(0, std::ios::end);
                file_size = myfile.tellg();
            }
            len = file_size+1;
            myfile.clear(); myfile.seekg(0);
            raw = (char*)std::malloc(len);
            for (int x=0; myfile && x<len; x++) {
                raw[x] = myfile.get();
                //std::cout << raw[x];
            }
        }
        //count = 0;
        for (int x=0; x<len; x++) {
            if (raw[x] == '\n') count++;
        }
        srand( (std::chrono::duration_cast<std::chrono::milliseconds>((std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now())).time_since_epoch())).count() );
        //srand((unsigned)time(NULL));
        //std::cout << "Time: " << time(NULL) << "\n";
        nm = (std::rand() % (count+1));
        //k = 0; 
        //buf[128] = {0};
        for (int x=0; x<len; x++) {
            if (raw[x] == '\n') {
                if (c==nm) break;
                for (int g=0; g<128; g++) buf[g]=0;
                c++; k=0;
            } else { buf[k] = raw[x]; k++; }
        }
		char* lastName = (char*)malloc(strlen(buf)+1);
		strcpy(lastName, buf);
		//std::cout << lastName;
		student->lastName = lastName;
		//std::cout << student->lastName << ".\n";
		// GPA
		//std::cout << "GPA:\n";
		//std::cin >> student->gpa;   
		srand( (std::chrono::duration_cast<std::chrono::milliseconds>((std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now())).time_since_epoch())).count() );
		student->gpa = ((std::rand()%301)*0.01)+1;
		
		
	    //StudentNode* node = new StudentNode(student);
	    Students->add(student);
		
	}
	
}


//template class List<int>;


