#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include "List.h"
#include "LinkedListNode.h"


#include <iostream>
using namespace std;

template <class S>
class LinkedList : virtual public List<S> {
private:
	LinkedListNode<S>* head;

public:
	bool Insert(int pos, S item) {
		if (pos > this->size || pos < 0)
			return false;

		if (pos == 0) {
			LinkedListNode<S>* newNode = new LinkedListNode<S>(item);
			newNode->SetNext(head);
			head = newNode;
			this->size++;
			return true;
		}

		int currentP = 0;
		LinkedListNode<S>* current = head;

		while (pos - 1 > currentP) {
			current = current->GetNext();
			currentP++;
		}

		LinkedListNode<S>* newNode = new LinkedListNode<S>(item);
		newNode->SetNext(current->GetNext());
		current->SetNext(newNode);
		this->size++;
		return true;
	}

	bool Remove(int pos) {
		if (pos > this->size || pos < 0)
			return false;

		if (pos == 0) {
			LinkedListNode<S>* temp = head;
			head = head->GetNext();
			delete temp;
			this->size--;
			return true;
		}

		int currentP = 0;
		LinkedListNode<S>* current = head;

		while (pos - 1 > currentP) {
			current = current->GetNext();
			currentP++;
		}

		LinkedListNode<S>* temp = current->GetNext();
		current->SetNext(temp->GetNext());
		delete temp;
		this->size--;
		return true;
	}

	bool Set(int pos, S item) {		if (pos > this->size || pos < 0)
			return false;

		int currentP = 0;
		LinkedListNode<S>* current = head;

		while (pos != currentP) {
			current = current->GetNext();
			currentP++;
		}

		current->Set(item);
		return true;	}	S Get(int pos) {
		if (pos > this->size || pos < 0)
			return *(new S());

		int currentP = 0;
		LinkedListNode<S>* current = head;

		while (pos != currentP) {
			current = current->GetNext();
			currentP++;
		}

		return current->Get();
	}
};

#endif