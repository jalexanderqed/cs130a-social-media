#ifndef __LINKEDLISTNAVIGATOR_H__
#define __LINKEDLISTNAVIGATOR_H__

#include "DLinkedList.h"
#include <iostream>

using namespace std;

/* Class for navigating over the elements of a DLinkedList object.
 * Contains methods for inserting and removing nodes, adding to the
 * beginning and end of the list, and moving through the list.
 * The current position in the list is stored as a pointer to a
 * DLinkedListNoed object, and the user can move backwards and forwards
 * over the entire list, as well as jumping to the start or end.
 * This class can either be used as a complete wrapper around a
 * DLinkedList (its default constructor constructs a DLinkedList)
 * object, or it can be attached to an existing list using the "attach"
 * method.
*/
template <class T>
class LinkedListNavigator {
private:
	DLinkedList<T>* list;
	DLinkedListNode<T>* current;

public:
	// Causes the Navigator object to set its current position to the
	// start of the DLinkedList passed as an argument
	void Attach(DLinkedList<T>* l) {
		list = l;
		current = list->GetHead();
	}

	LinkedListNavigator(DLinkedList<T>* l) {
		attach(l);
	}

	// Creates a new DLinkedList associated with this Navigator object.
	// (For when the LinkedListNavigator is used as a wrapper around a list.)
	LinkedListNavigator() {
		DLinkedList<T>* l = new DLinkedList<T>();
		Attach(l);
	}

	// Destructor does nothing, as both the list and the current node pointer
	// belong to the list itself. Deleting the list case would create a
	// bug when using the Navigator to iterate over an existing list.
	~LinkedListNavigator() { }

	// Deletes the attached list object, including all of its nodes.
	void DeleteList() {
		delete list;
	}

	inline int Length() {
		DLinkedListNode<T>* c = list->GetHead();
		int count = 0;
		while (c != NULL) {
			count++;
			c = c->GetNext();
		}
		return count;
	}

	// Prints debug information for all nodes in the list, including
	// the next and previous nodes they point to.
	// Not optimized, so should only be used for testing.
	inline void PrintDebug() {
		DLinkedListNode<T>* c = list->GetHead();
		while (c != NULL) {
			cout << "\t\tcurrent:" << c;
			cout << "\t\tprev:" << c->GetPrev();
			cout << "\t\tnext:" << c->GetNext() << endl;
			c = c->GetNext();
		}
		cout << "\nList Length:" << Length() << endl;
		cout << "head:" << list->GetHead() << endl;
		cout << "tail:" << list->GetTail() << endl;
		cout << "current:" << current << endl << endl;
	}

	inline void AddHead(DLinkedListNode<T>* n) {
		if (current == NULL)
			current = n;
		list->AddHead(n);
	}

	inline void AddTail(DLinkedListNode<T>* n) {
		if (current == NULL)
			current = n;
		list->AddTail(n);
	}

	inline void AddAfter(DLinkedListNode<T>* n) {
		if (current == NULL || current == list->GetTail())
			AddTail(n);
		else {
			n->SetPrev(current);
			n->SetNext(current->GetNext());
			n->GetNext()->SetPrev(n);
			current->SetNext(n);
		}
	}

	inline void AddBefore(DLinkedListNode<T>* n) {
		if (current == NULL || current == list->GetHead())
			AddHead(n);
		else {
			n->SetNext(current);
			n->SetPrev(current->GetPrev());
			n->GetPrev()->SetNext(n);
			current->SetPrev(n);
		}
	}

	inline DLinkedListNode<T>* RemoveHead() {
		DLinkedListNode<T>* n = list->RemoveHead();
		if (n == current) {
			current = list->GetHead();
		}
		return n;
	}

	inline DLinkedListNode<T>* RemoveTail() {
		DLinkedListNode<T>* n = list->RemoveTail();
		if (n == current) {
			current = list->GetTail();
		}
		return n;
	}

	inline DLinkedListNode<T>* RemoveAfter() {
		DLinkedListNode<T>* n;
		if (current == NULL || (n = current->GetNext()) == NULL)
			return NULL;
		else if (n == list->GetTail()) {
			return RemoveTail();
		}
		else {
			current->SetNext(n->GetNext());
			current->GetNext()->SetPrev(current);
			return n;
		}
	}

	inline DLinkedListNode<T>* RemoveBefore() {
		DLinkedListNode<T>* n;
		if (current == NULL || (n = current->GetPrev()) == NULL)
			return NULL;
		else if (n == list->GetHead()) {
			return RemoveHead();
		}
		else {
			current->SetPrev(n->GetPrev());
			current->GetPrev()->SetNext(current);
			return n;
		}
	}

	// Removes the current list and goes to the head of the list
	inline DLinkedListNode<T>* RemoveCurrent() {
		if (current == NULL)
			return NULL;
		else if (current == list->GetHead()) {
			DLinkedListNode<T>* n = RemoveHead();
			GoToHead();
			return n;
		}
		else if (current == list->GetTail()) {
			DLinkedListNode<T>* n = RemoveTail();
			GoToHead();
			return n;
		}
		else {
			DLinkedListNode<T>* n = current;
			n->GetPrev()->SetNext(n->GetNext());
			n->GetNext()->SetPrev(n->GetPrev());
			return n;
		}
	}

	inline void AddHead(T* v) {
		AddHead(new DLinkedListNode<T>(v));
	}

	inline void AddTail(T* v) {
		AddTail(new DLinkedListNode<T>(v));
	}

	inline void AddAfter(T* v) {
		AddAfter(new DLinkedListNode<T>(v));
	}

	inline void AddBefore(T* v) {
		AddBefore(new DLinkedListNode<T>(v));
	}

	inline bool Next() {
		if (current == NULL) return false;

		DLinkedListNode<T>* temp;
		if ((temp = current->GetNext()) != NULL) {
			current = temp;
			return true;
		}
		else {
			return false;
		}
	}

	inline bool Prev() {
		if (current == NULL) return false;

		DLinkedListNode<T>* temp;
		if ((temp = current->GetPrev()) != NULL) {
			current = temp;
			return true;
		}
		else {
			return false;
		}
	}

	inline void GoToHead() { current = list->GetHead(); }

	inline void GoToTail() { current = list->GetTail(); }

	inline T* GetCurrent() {
		if (current != NULL)
			return current->GetValue();
		else
			return NULL;
	}
};

#endif
