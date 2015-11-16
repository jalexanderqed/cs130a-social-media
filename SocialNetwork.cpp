#include "HashTable.h"
#include "Interface.h"
#include <iostream>
#include <time.h>
#include <string>

using namespace std;

int main(int argc, char** argv) {
	HashTable<string>* h = new HashTable<string>(10);

	string* first = new string("first");

	cout << (h->Add("first", first) ? "Added successfully" : "Could not add") << endl;

	string* res = h->Get("first");

	cout << "Got response." << endl;

	if (res == NULL) {
		cout << "Returned null" << endl;
	}
	else {
		cout << *res << endl;
	}

	return 0;

	return RunInterface();
}