#ifndef _LINKEDLIST
#define _LINKEDLIST
#include<iostream>
using namespace std;
#include "Node.h"
#include"Process.h"
template <typename T>
class LinkedList
{
private:
	Node<T>* Head;
	Node<T>* Tail;
	int count;
public:
	LinkedList()
	{
		Head = nullptr;
		Tail = nullptr;
		count = 0;
	}
	~LinkedList()
	{
		DeleteAll();
	}
	void InsertBeg(const T& data)
	{
		Node<T>* R = new Node<T>(data);
		R->setNext(Head);
		Head = R;
		if (!Head->getNext())
			Tail = Head;
		count++;
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
		count = 0;
	}
	void InsertEnd(const T& data)
	{
		Node<T>* newnode = new Node<T>;
		newnode->setItem(data);
		newnode->setNext(nullptr);
		if (!Head)
		{
			Head = newnode;
			Tail = Head;
		}
		else
		{
			Tail->setNext(newnode);
			Tail = newnode;
		}
		count++;
	}
	bool Remove(T item)
	{
		Node<T>* ptr = Head->getNext();
		Node<T>* prev = Head;
		if (prev->getItem() == item)
		{
			Head = Head->getNext();
			delete prev;
			count--;
			return true;
		}
		else
			while (ptr)
			{
				if (ptr->getItem() == item)
				{
					prev->setNext(ptr->getNext());
					delete ptr;
					count--;
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
	Node<T>* RemoveFirst()
	{
		if (Head != nullptr)
		{
			Node<T>* temp = Head;
			Head = Head->getNext();
			count--;
			return temp;
		}
		return nullptr;
	}
	void PrintList()    const
	{
		Node<T>* p = Head;
		while (p)
		{
			cout << *(p->getItem());
			p = p->getNext();
			if (p)
				cout << " ";
		}
	}
	int get_count()
	{
		return count;
	}
	T SearchbyID(int id)
	{
		Node<T>* pre = nullptr;
		Node<T>* ptr = Head;
		while (ptr)
		{
			if (*(ptr->getItem()) == id)
			{
				break;
			}
			pre = ptr;
			ptr = ptr->getNext();
		}
		if (ptr)
		{
			if (ptr == Head)
			{
				Head = Head->getNext();
			}
			else
			pre->setNext(ptr->getNext());
			return ptr->getItem();
		}
		return 0;
	}
	T getHead()
	{
		if (!Head)
			return nullptr;
		return Head->getItem();
	}
};
#endif
