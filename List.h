#ifndef __LIST_H__
#define __LIST_H__

template <class T>
class List {
protected:
	int size = 0;

public:
	virtual bool Insert(int pos, T item) = 0;
	virtual bool Remove(int pos) = 0;
	virtual bool Set(int pos, T item) = 0;	virtual T Get(int pos) = 0;
	int GetSize() { return size; }
};

#endif