#ifndef __DLINKEDLISTNODE_H__
#define __DLINKEDLISTNODE_H__

/* Template node class for use with DLinkedList (doubly linked list).
 * Containes basic initializer, getter, and setter methods.
 */
template <class T>
class DLinkedListNode {
 private:
  DLinkedListNode<T>* prev;
  DLinkedListNode<T>* next;
  T* value;

 public:
 DLinkedListNode(T* val) :
  value{ val },
    prev{ NULL },
      next{ NULL }
      { }

 DLinkedListNode(T* val, DLinkedListNode<T>* p, DLinkedListNode<T>* n) :
      value{ val },
	prev{ p },
	  next{ n }
	  { }

	  ~DLinkedListNode() {
	    if (value != NULL){
	      delete value;
	    }
	  }

	  inline void SetNext(DLinkedListNode<T>* n) { next = n; }

	  inline void SetPrev(DLinkedListNode<T>* p) { prev = p; }

	  inline DLinkedListNode<T>* GetNext() { return next; }

	  inline DLinkedListNode<T>* GetPrev() { return prev; }

	  inline T* GetValue() { return value; }

	  inline void SetValue(T* v) { value = v; }
};

#endif
