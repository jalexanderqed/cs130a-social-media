#ifndef __HASH_TABLE_NODE_H__
#define __HASH_TABLE_NODE_H__

#include <string>
#include "LinkedListNavigator.h"

template <class T>
class HashTableNode {
 private:
  T* value;
  std::string* key;

  inline size_t HashInt(int a) {
    a = (a ^ 61) ^ (a >> 16);
    a = a + (a << 3);
    a = a ^ (a >> 4);
    a = a * 0x27d4eb2d;
    a = a ^ (a >> 15);
    return (size_t)a;
  }

 public:
  HashTableNode(T* val, std::string k) {
    value = val;
    key = new string(k);
  }

  ~HashTableNode() {
    if (value != NULL)
      delete value;
    if (key != NULL)
      delete key;
  }

  inline T* GetValue() {
    return value;
  }

  inline std::string GetKey() const {
    return *key;
  }

  inline std::string PrintKey() const {
    cout << "Key in print: " << *key << endl;
  }

  inline void SetValue(T* v) {
    value = v;
  }

  inline size_t GetHash() {
    size_t seed = 131;
    size_t hash = 0;

    for (size_t i = 0; i < key->length(); i++) {
      hash = (hash * seed) + (*key)[i];
    }

    return (hash & 0x7FFFFFFF);
  }
};

#endif
