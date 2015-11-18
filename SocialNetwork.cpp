#include "HashTable.h"
#include "Interface.h"
#include <iostream>
#include <time.h>
#include <string>
#include <cstdlib>

using namespace std;

inline char* GetRandString(int length) {
	char* str = new char[length + 1];
	str[length] = '\0';
	for (int i = 0; i < length; i++) {
		str[i] = (rand() % 26) + 65;
	}
	return str;
}

int main(int argc, char** argv) {
	/*int testSize = 1000;
	HashTable<string>* h = new HashTable<string>(10);
	string** stored = new string*[testSize];
	srand((int)time(NULL));

	for (int i = 0; i < testSize; i++) {
		stored[i] = NULL;
		char* cstr = GetRandString(8);
		string* str = new string(cstr);
		delete[] cstr;
		if (h->Add(*str, str)) {
			stored[i] = str;
		}
	}

	int count = 0;
	h->StartIterator();
	HashTableNode<string>* n;
	while ((n = h->NextIterator()) != NULL) {
		count++;
	}
	cout << "Count: " << count << endl;

	for (int i = 0; i < testSize; i++) {
		if (stored[i] != NULL) {
			if (h->Remove(*stored[i]) == NULL)
				cout << "Could not remove " << *stored[i] << endl;
		}
	}

	delete h;
	delete[] stored;

	return 0;*/

	return RunInterface();
}
