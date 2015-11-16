#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include "HashTableNode.h"


template <class T>
class HashTable {
private:
	LinkedListNavigator<HashTableNode<T>>** map;
	size_t capacity;
	size_t size;
	const double FILL_FACTOR = .75;

public:
	HashTable(int c) {
		map = new LinkedListNavigator<HashTableNode<T>>*[c];
		capacity = c;
		size = 0;

		for (int i = 0; i < capacity; i++) {
			map[i] = new LinkedListNavigator<HashTableNode<T>>();
		}
	}

	~HashTable() {
		for (int i = 0; i < size; i++) {
			map[i]->DeleteList();
			delete map[i];
		}

		delete[] map;
	}

	bool Add(string key, T* value) {
		HashTableNode<T>* n = new HashTableNode<T>(value, key);
		uint32_t index = n->GetHash();

		size_t location = index % capacity;
		LinkedListNavigator<HashTableNode<T>>* l = map[location];

		l->GoToHead();
		if (l->GetCurrent() != NULL) {
			do {
				if (l->GetCurrent()->GetKey() == key) return false;
			} while (l->Next());
		}
		l->AddHead(n);
		size++;
		return true;
	}

	T* Get(string key) {
		HashTableNode<T>* n = new HashTableNode<T>(NULL, key);
		uint32_t index = n->GetHash();
		size_t location = index % capacity;
		LinkedListNavigator<HashTableNode<T>>* l = map[location];
		delete n;

		l->GoToHead();

		if (l->GetCurrent() != NULL) {
			do {
				if (l->GetCurrent()->GetKey() == key) return l->GetCurrent()->GetValue();
			} while (l->Next());
		}

		return NULL;
	}

	T* Remove(string key) {
		HashTableNode<T>* n = new HashTableNode<T>(NULL, key);
		uint32_t index = n->GetHash();
		size_t location = index % capacity;
		LinkedListNavigator<HashTableNode<T>>* l = map[location];
		delete n;

		l->GoToHead();

		if (l->GetCurrent() != NULL) {
			do {
				if (l->GetCurrent()->GetKey() == key) {
					DLinkedListNode* n = l->RemoveCurrent();

					return l->RemoveCurrent();
				}
			} while (l->Next());
		}

		return NULL;
	}
};

#endif