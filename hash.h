#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <vector> // vector
#include "student.h" // student

class HashTable {
private:
	int poolSize = 10;
	Student*** table; // array of array pointers containing data pointers

	void expand();

public:
    HashTable() {
    	std::cout << "=== Hashtable ===\n";
    	std::cout << "Started: HashTable()\n";
		HashTable::table = (Student***)std::malloc(HashTable::poolSize); // Allocate memory for array (of array pointers containing data pointers)
		std::cout << "Value (Table): " << HashTable::table << '\n';
		for (int i=0; i<HashTable::poolSize; i++) {
			HashTable::table[i] = (Student**)std::malloc(3);
			std::cout << "Value Table["<<i<<"]: " << HashTable::table[i] << '\n';
			for (int j=0; j<3; j++) {
				HashTable::table[i][j] = (Student*)nullptr;
				std::cout << "Value Table["<<i<<"]["<<j<<"]: " << HashTable::table[i][j] << '\n';
			}
		}
		//std::cout << HashTable::table[0][0]->id << "\n";
		//std::free(HashTable::table[0]);
	}
	//~HashTable(); // Delete list and all nodes

	void add(Student* student);
	bool del(unsigned int id);
	Student* get(unsigned int id);
	void print();

	int size() { std::cout << "=== Size ===\n"; return poolSize; } // get size
	
	unsigned int hash(unsigned int input, int size) {
		std::cout << "=== Hash ===\n";
		//unsigned int out = 0;
		//for (int j = 0; input[j]; j++) out += input[j]; // Ends on null terminator
		//out += input;
		//out += (input << 2)*3;
		//out += (input << 4)*5;
		//out += (input << 6)*7;
		//return out % size; //HashTable::poolSize;
		unsigned int x = input;
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = (x >> 16) ^ x;
		//std::cout << "Size: " << size << "  ";
		//std::cout << "X: " << x << "  ";
		//std::cout << "Hash: " << x % size << "\n";
		return x % size;
	}

    // Overloading [] operator to access elements in array style
    Student* operator[](unsigned int id) {
		std::cout << "=== Operator[] ===\n";
		//std::cout << "Value Table[0][0]: " << HashTable::table[0][0] << '\n';
		return HashTable::get(id);
	}

};

#endif // HASH_H