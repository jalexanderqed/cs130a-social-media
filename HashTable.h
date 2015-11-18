#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include "HashTableNode.h"
#include <iostream>

using namespace std;

template <class T>
class HashTable {
 private:
  LinkedListNavigator<HashTableNode<T>>** map;
  size_t capacity;
  size_t size;
  const double FILL_FACTOR = .75;
  size_t iteratorPos;

 public:
  HashTable(int c) {
    map = new LinkedListNavigator<HashTableNode<T>>*[c];
    capacity = (c < 10) ? 10 : c;
    size = 0;

    for (int i = 0; i < capacity; i++) {
      map[i] = new LinkedListNavigator<HashTableNode<T>>();
    }
  }

  ~HashTable() {
    if (map != NULL) {
      for (int i = 0; i < capacity; i++) {
	if (map[i] != NULL) {
	  map[i]->DeleteList();
	  delete map[i];
	}
      }

      delete[] map;
    }
  }

  inline size_t Capacity() { return capacity; }
  inline size_t Size() { return size; }

  void PrintDebug() {
    cout << "HASH TABLE CAPACITY: " << capacity << endl;
    cout << "HASH TABLE SIZE: " << size << "\n\n" << endl;

    for (int i = 0; i < capacity; i++) {
      cout << "HASH TABLE NODE " << i << endl;
      map[i]->PrintDebug();
    }
  }

  void Rehash() {
    size_t nc = (capacity + 1) * 2 + 1;
    nc = (nc < 10) ? 10 : nc;
    HashTable<T>* newMap = new HashTable<T>(nc);

    int pos = 0;
    map[pos]->GoToHead();
    while (pos < capacity && map[pos]->GetCurrent() == NULL) {
      pos++;
      if (pos < capacity) map[pos]->GoToHead();
    }

    while (pos < capacity) {
      while (pos < capacity && map[pos]->GetCurrent() == NULL) {
	pos++;
	if (pos < capacity) map[pos]->GoToHead();
      }
      if (pos < capacity) {
	do {
	  HashTableNode<T>* n = map[pos]->GetCurrent();
	  newMap->Add(n);
	  map[pos]->GetCurrentNode()->SetValue(NULL);
	} while (map[pos]->Next());
      }
    }
    for (int i = 0; i < capacity; i++) {
      map[i]->DeleteList();
      delete map[i];
      map[i] = NULL;
    }

    delete[] map;

    capacity = nc;
    map = newMap->map;
    newMap->map = NULL;
    delete newMap;
  }

  T* NextIterator() {
    if (iteratorPos >= capacity) return NULL;
    if (map[iteratorPos]->GetCurrent() != NULL) {
      HashTableNode<T>* temp = map[iteratorPos]->GetCurrent();
      if (!(map[iteratorPos]->Next())) {
	while (map[iteratorPos]->GetCurrent() == NULL) {
	  iteratorPos++;
	  if (iteratorPos >= capacity) break;
	  map[iteratorPos]->GoToHead();
	}
      }
      return temp->GetValue();
    }
    else {
      while (map[iteratorPos]->GetCurrent() == NULL) {
	iteratorPos++;
	if (iteratorPos >= capacity) return NULL;
	map[iteratorPos]->GoToHead();
      }
      HashTableNode<T>* temp = map[iteratorPos]->GetCurrent();
      if (!(map[iteratorPos]->Next())) {
	while (map[iteratorPos]->GetCurrent() == NULL) {
	  iteratorPos++;
	  if (iteratorPos >= capacity) break;
	  map[iteratorPos]->GoToHead();
	}
      }
      return temp->GetValue();
    }
  }

  void StartIterator() {
    iteratorPos = 0;
    map[0]->GoToHead();
  }

  bool Add(HashTableNode<T>* n) {
    if (size + 1 > FILL_FACTOR * capacity) Rehash();
    size_t location = n->GetHash() % capacity;
    LinkedListNavigator<HashTableNode<T>>* l = map[location];

    l->GoToHead();
    if (l->GetCurrent() != NULL) {
      do {
	if (l->GetCurrent()->GetKey() == n->GetKey()) return false;
      } while (l->Next());
    }
    l->AddHead(n);
    size++;
    return true;
  }

  bool Add(string key, T* value) {
    HashTableNode<T>* n = new HashTableNode<T>(value, key);
    Add(n);
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
	  DLinkedListNode<HashTableNode<T>>* n = l->RemoveCurrent();
	  T* temp = n->GetValue()->GetValue();
	  n->GetValue()->SetValue(NULL);
	  delete n;
	  size--;
	  return temp;
	}
      } while (l->Next());
    }

    return NULL;
  }
};

#endif
