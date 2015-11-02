#ifndef __LINKED_LIST_NODE_H__
#define __LINKED_LIST_NODE_H__

#include <cstddef>

template <class T>
class LinkedListNode {
private:
	T value;
	LinkedListNode<T>* next;

public:
	LinkedListNode(const T& v) {
		next = NULL;
		value = v;
	}

	void SetNext(LinkedListNode<T>* n) { next = n; }
	LinkedListNode<T>* GetNext() { return next; }

	void Set(const T& v) { value = v; }
	T Get() { return value; }
};

#endif