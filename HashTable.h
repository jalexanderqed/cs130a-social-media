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
    capacity = c;
    size = 0;

    for (int i = 0; i < capacity; i++) {
      map[i] = new LinkedListNavigator<HashTableNode<T>>();
    }
  }

  ~HashTable() {
    if(map != NULL){
      for (int i = 0; i < size; i++) {
	if(map[i] != NULL){
	  map[i]->DeleteList();
	  delete map[i];
	}
      }
      
      delete[] map;
    }
  }

  void PrintDebug(){
    cout << "HASH TABLE CAPACITY: " << capacity << endl;
    cout << "HASH TABLE SIZE: " << size << "\n\n" << endl;
    
    for(int i = 0; i < capacity; i++){
      cout << "HASH TABLE NODE " << i << endl;
      map[i]->PrintDebug();
    }
  }

  void Rehash(){
    size_t nc = (capacity + 1) * 2 + 1;
    
    HashTable<T>* newMap = new HashTable<T>(nc);

    StartIterator();

    HashTableNode<T>* n;
    while((n = NextIterator()) != NULL){
      newMap->Add(n->GetKey(), n->GetValue());
      n->SetValue(NULL);
      delete n;
    }

    for (int i = 0; i < size; i++) {
      map[i]->DeleteList();
      delete map[i];
      map[i] = NULL;
    }

    delete[] map;

    capacity = nc;
    map = newMap->map;
    newMap->map = NULL;
    delete newMap;
    PrintDebug();
  }

  HashTableNode<T>* NextIterator(){
    if(iteratorPos >= capacity) return NULL;
    if(map[iteratorPos]->GetCurrent() != NULL){
      HashTableNode<T>* temp = map[iteratorPos]->GetCurrent();
      if(!(map[iteratorPos]->Next())){
	while(map[iteratorPos]->GetCurrent() == NULL){
	  iteratorPos++;
	  if(iteratorPos >= capacity) break;
	  map[iteratorPos]->GoToHead();
	}
      }
      return temp;
    }
    else{
      while(map[iteratorPos]->GetCurrent() == NULL){
	iteratorPos++;
	if(iteratorPos >= capacity) return NULL;
	map[iteratorPos]->GoToHead();
      }
      HashTableNode<T>* temp = map[iteratorPos]->GetCurrent();
      if(!(map[iteratorPos]->Next())){
	while(map[iteratorPos]->GetCurrent() == NULL){
	  iteratorPos++;
	  if(iteratorPos >= capacity) break;
	  map[iteratorPos]->GoToHead();
	}
      }
      return temp;
    }
  }

  void StartIterator(){
    iteratorPos = 0;
    map[0]->GoToHead();
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
    if(size > FILL_FACTOR * capacity) Rehash();
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
