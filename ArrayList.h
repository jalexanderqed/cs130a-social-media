#ifndef __ARRAY_LIST_H__
#define __ARRAY_LIST_H__

#include "List.h"
#include "LinkedListNode.h"


#include <iostream>
using namespace std;

template <class S>
class ArrayList : virtual public List<S> {
private:
	int capacity;
	S* contents;

public:
	ArrayList() {
		capacity = 10;
		contents = new S[10];
	}

	~ArrayList() {
		delete[] contents;
	}

	void Resize() {
		int newSize = 2 * capacity;

		S* temp = new S[newSize];
		for (int i = 0; i < this->size; i++) {
			temp[i] = contents[i];
			contents[i] = NULL;
		}

		delete[] contents;
		contents = temp;
		capacity = newSize;
	}

	bool Insert(int pos, S item) {
		if (pos > this->size || pos < 0)
			return false;

		if (this->size + 1 > capacity) {
			Resize();
		}

		for (int i = this->size; i > pos; i--) {
			contents[i] = contents[i - 1];
		}

		contents[pos] = item;
		this->size++;

		return true;
	}

	bool Remove(int pos) {
		if (pos > this->size || pos < 0)
			return false;

		for (int i = pos; i < this->size - 1; i++) {
			contents[i] = contents[i + 1];
		}

		this->size--;

		return true;
	}

	bool Set(int pos, S item) {		if (pos > this->size || pos < 0)
			return false;		contents[pos] = item;
		return true;	}	S Get(int pos) {
		if (pos > this->size || pos < 0)
			return *(new S());

		return contents[pos];
	}
};

#endif