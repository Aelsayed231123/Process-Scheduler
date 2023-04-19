#ifndef queue
#define queue
#include"pair.h"
template<class T>
class Node
{
private:
	T item; // A data item
	Node<T>* next; // Pointer to next node
public:
	Node()
	{
		next = nullptr;
	}
	Node(const T& r_Item)
	{
		item = r_Item;
		next = nullptr;
	}
	Node(const T& r_Item, Node<T>* nextNodePtr)
	{
		item = r_Item;
		next = nextNodePtr;
	}
	void setItem(const T& r_Item)
	{
		item = r_Item;
	}

	void setNext(Node<T>* nextNodePtr)
	{
		next = nextNodePtr;
	}
	T & getItem() 
	{
		return item;
	}
	Node<T>* getNext() const
	{
		return next;
	}
};
#endif

