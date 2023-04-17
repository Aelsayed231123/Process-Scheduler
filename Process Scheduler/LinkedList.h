#ifndef _LINKEDLIST
#define _LINKEDLIST
#include<iostream>
using namespace std;
#include "Node.h"

template <typename T>
class LinkedList
{
private:
	Node<T>* Head;
public:
	LinkedList()
	{
		Head = nullptr;
	}
	~LinkedList()
	{
		DeleteAll();
	}
	void PrintList()	const
	{
		Node<T>* p = Head;
		while (p)
		{
			cout << p->getItem();
			p = p->getNext();
			if (p)
				cout << " ";

		}
		cout << "NULL\n";
	}
	void InsertBeg(const T& data)
	{
		Node<T>* R = new Node<T>(data);
		R->setNext(Head);
		Head = R;

	}
	void DeleteAll()
	{
		Node<T>* P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}
	void InsertEnd(const T& data)
	{
		Node<T>* newnode = new Node<T>;
		newnode->setItem(data);
		newnode->setNext(nullptr);
		if (Head == 0)
		{
			Head = newnode;
		}
		else
		{
			Node<T>* ptr = Head;
			while (ptr->getNext())
				ptr = ptr->getNext();
			ptr->setNext(newnode);

		}
	}
	bool Remove(T item)
	{
		Node<T>* ptr = Head->getNext();
		Node<T>* prev = Head;
		if (prev->getItem() == item)
		{
			Head = Head->getNext();
			delete prev;
			return true;
		}
		else
			while (ptr)
			{
				if (ptr->getItem() == item)
				{
					prev->setNext(ptr->getNext());
					delete ptr;
					return true;
				}
				prev = ptr;
				ptr = ptr->getNext();
			}
		return false;
	}
	Node<T>* GetFirst()
	{
		if (Head != nullptr)
		{
			Node<T>* temp = Head;
			Head = Head->getNext();
			return temp;
		}
	}
	bool isEmpty()
	{
		return(!Head);
	}
	Node<T>* get_head()
	{
		return Head;
	}
};

#endif
