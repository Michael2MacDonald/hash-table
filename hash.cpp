#include "hash.h"
#include "student.h"

#include <cstring>
//#include <climits>


//#define CAPACITY 50000 // Size of the HashTable.

//unsigned long hash_function(char* str) {
//    unsigned long i = 0;
//
//    for (int j = 0; str[j]; j++)
//        i += str[j];
//
//    return i % CAPACITY;
//}


void HashTable::expand() {
	std::cout << "=== Expand ===\n";
	//std::cout << "========== EXPANDING! ===========\n";
	// todo
	int newPoolSize = poolSize;
	Student*** newtable;// = (Student***)std::malloc(newPoolSize);
	while(1) {
		std::cout << "========== EXPANDING! ===========\n";
		newPoolSize = newPoolSize*2;
		newtable = (Student***)std::malloc(newPoolSize);
		for (int i=0; i<newPoolSize; i++) {
			std::cout << "Value Table[]: " << table[i] << '\n';
			newtable[i] = (Student**)std::malloc(3);
			for (int j=0; j<3; j++) newtable[i][j] = nullptr;
		}
		//std::free(newtable[1]);
		bool br = 1;
		for (int i=0; i<HashTable::poolSize && br; i++) {
			//std::cout << "test 2\n";
			for(int j=0; j<3 && br; j++) {
				if (HashTable::table[i][j] != nullptr) {
					//std::cout << "Pointer: " << HashTable::table[i][j] << "\n";
					Student* student = HashTable::table[i][j];
					std::cout << "Student ID:" << student->id << "\n";
					int hash = HashTable::hash(student->id, newPoolSize);
					int full = 0;
					for (int k=0; k<3; k++) { if (newtable[hash][k] != nullptr) full++; }
					if (full >= 3) {
						br = 0;
						//std::cout << "test HH\n";
						//for (int d=0; d<newPoolSize; d++) { std::cout << d << "\n"; delete[] newtable[d]; }
						for (int d=0; d<newPoolSize; d++) {
							
							std::cout << "Addr: " << newtable[d] << "\n";
							std::free(newtable[d]);
							
						}
						//std::cout << "test x\n";
						std::free(newtable);
						//delete[] newtable;
						
						std::cout << "test 2\n";
					} else { // add if not full
						newtable[hash][full] = student;
					}
				}
			}
		}
		if (br) break;
	}
//	for (HashTable::poolSize)
//		delete HashTable::table[][];
	//for (int i=0; i<HashTable::poolSize; i++) { std::cout << i << "\n"; delete[] HashTable::table[i]; }
	std::free(HashTable::table);
	HashTable::table = newtable;
	std::cout << "==== DONE! ====\n";
}


Student* HashTable::get(unsigned int id) {
	std::cout << "=== Get ===\n";
	unsigned int i = HashTable::hash(id, HashTable::poolSize);
	//std::cout << UINT_MAX << "\n";
	for (int j=0; j<3; j++) {
		//return nullptr;
		if (HashTable::table[i][j] != nullptr) {
			if (HashTable::table[i][j]->id == id) return HashTable::table[i][j];
		}
	}
	return nullptr;
}


void HashTable::add(Student* student) {
	std::cout << "=== Add ===\n";
	std::cout << "Adding student: " << student->id << "  ";
	// Check if a student with that ID exists
	if (HashTable::get(student->id) != nullptr) { /**ERROR_DUP_STUDENT**/
		std::cout << "==== ERROR_DUP_STUDENT_ID! ====\n";
		return;
	}
	//return;
	// else
	unsigned int index;
	while (true) { // keep expanding until collitions are low enough
		index = HashTable::hash((unsigned int)student->id, HashTable::poolSize); // get index
		std::cout << "Hash: " << index;// << "\n";
		// Check if the index is already full
		int full = 0;
		for (int i=0; i<3; i++) { if (HashTable::table[index][i] != nullptr) full++; }
		std::cout << "  Full: " << full << "\n";
		if (full >= 3) {
			HashTable::expand();
		} else { // add if not full
			//HashTable::table[index]->push_back(student);
			HashTable::table[index][full] = student;
			break;
		}
	}

}


bool HashTable::del(unsigned int id) {
	std::cout << "=== Del ===\n";
	unsigned int i = HashTable::hash(id, HashTable::poolSize);
	for (int j=0; j<3; j++) {
		if (HashTable::table[i][j] == nullptr) continue;
		if (HashTable::table[i][j]->id == id) {
			// delete
			delete HashTable::table[i][j];
			HashTable::table[i][j] = nullptr;
			return 0;
		}
	}
	return 1;
}



void HashTable::print() {
	std::cout << "=== Print ===\n";
	std::cout << "Value Table[0][0]: " << HashTable::table[0][0] << '\n';
	//if (Students->getStart() == nullptr) {
	//  std::cout << "- No Students -\n";
	//  return;
	//}
	std::cout << "\n";
	bool hehe = 1;
	for (int i=0; i<HashTable::poolSize; i++) {
		//std::cout << "test 2\n";
		for(int j=0; j<3; j++) {
			std::cout << "i: " << i << " j: " << j << '\n';
			std::cout << "Value: " << HashTable::table[i][j] << '\n';
			std::cout << "Value: " << table[i][j] << '\n';
			//continue;
			if (HashTable::table[i][j] != nullptr) {
				hehe=0;
				Student* student = (HashTable::table[i][j]);
				std::cout << "-----------------------\n";
				std::cout << "ID: " << student->id << '\n';
				std::cout << "First Name: ";
				for (int k=0; k < strlen(student->firstName); k++) { std::cout << (student->firstName)[k]; }
				std::cout << '\n';
				std::cout << "Last Name: ";
				for (int k=0; k < strlen(student->lastName); k++) { std::cout << (student->lastName)[k]; }
				std::cout << '\n';
				std::cout << "GPA: " << student->gpa << '\n';
			}
		}
	}
	if (hehe) std::cout << "- No Students -\n\n";
}


