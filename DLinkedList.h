#ifndef __DLINKEDLIST_CPP__
#define __DLINKEDLIST_CPP__

#include "DLinkedListNode.h"

template <class T>
class DLinkedList {
 private:
  DLinkedListNode<T>* head;
  DLinkedListNode<T>* tail;

  void DeleteNodes(DLinkedListNode<T>* n) {
    if(n != NULL){
      DLinkedListNode<T>* temp;
      if ((temp = n->GetNext()) != NULL)
	DeleteNodes(temp);
      delete n;
    }
  }

 public:
 DLinkedList() : head{ NULL }, tail{ NULL } { }

  ~DLinkedList() {
    if (head != NULL)
      DeleteNodes(head);
  }

  inline void AddHead(DLinkedListNode<T>* n) {
    if (head == NULL && tail == NULL) {
      head = n;
      tail = n;
      n->SetNext(NULL);
      n->SetPrev(NULL);
    }
    else {
      head->SetPrev(n);
      n->SetNext(head);
      n->SetPrev(NULL);
      head = n;
    }
  }

  inline void AddTail(DLinkedListNode<T>* n) {
    if (head == NULL && tail == NULL) {
      head = n;
      tail = n;
      n->SetNext(NULL);
      n->SetPrev(NULL);
    }
    else {
      tail->SetNext(n);
      n->SetPrev(tail);
      n->SetNext(NULL);
      tail = n;
    }
  }

  inline DLinkedListNode<T>* RemoveHead() {
    DLinkedListNode<T>* n;
    if ((n = head) == NULL) return head;

    if (n->GetNext() != NULL) {
      n->GetNext()->SetPrev(NULL);
      head = n->GetNext();
      return n;
    }
    else {
      tail = NULL;
      head = NULL;
      return n;
    }
  }

  inline DLinkedListNode<T>* RemoveTail() {
    DLinkedListNode<T>* n;
    if ((n = tail) == NULL) return tail;

    if (n->GetPrev() != NULL) {
      n->GetPrev()->SetNext(NULL);
      tail = n->GetPrev();
      return n;
    }
    else {
      tail = NULL;
      head = NULL;
      return n;
    }
  }

  inline DLinkedListNode<T>* GetHead() { return head; }
  inline DLinkedListNode<T>* GetTail() { return tail; }
};

#endif
