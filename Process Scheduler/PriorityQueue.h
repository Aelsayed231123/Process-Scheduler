#ifndef PRIORITYQUEUE
#define PRIORITYQUEUE
#pragma once
#include"Node.h"
#include"pair.h"
#include<iostream>
using namespace std;
template<class T>
class PriorityQueue
{
private:
	Node<mypair<T,int>>* frontPtr;
	Node<mypair<T,int>>* backPtr;
	int count;
public:
	PriorityQueue()
	{
		frontPtr = nullptr;
		backPtr = nullptr;
		count = 0;
	}
	void enqueue(const T& newEntry,int priority)
	{
		Node <mypair<T,int>>* temp = new Node<mypair<T,int>>;
		temp->getItem().set_first(newEntry);
		temp->getItem().set_second(priority);

		if (isEmpty())
		{
			frontPtr = temp;
			backPtr = temp;
		}
		else
		{
			Node<mypair<T,int>>* pre = nullptr;
			Node<mypair<T,int>>* ptr = frontPtr;
			while (ptr)
			{
				if ((temp->getItem()).second<=(ptr->getItem()).second)
				{
					break;
				}
				pre = ptr;
				ptr = ptr->getNext();
			}
			if (!pre)
			{
				temp->setNext(ptr);
				frontPtr = temp;
				backPtr = ptr;
			}
			else
			{
				temp->setNext(ptr);
				pre->setNext(temp);
				if (!ptr)
					backPtr = temp;
			}
		}
		count++;
	}
	bool isEmpty() const
	{
		return (frontPtr == nullptr);
	}
	bool dequeue(T& frntEntry)
	{
		if (isEmpty())
		{
			frntEntry = 0;
			return false;
		}

		Node<mypair<T,int>>* nodeToDeletePtr = frontPtr;
		frntEntry = (frontPtr->getItem()).first;
		frontPtr = frontPtr->getNext();
		// Queue is not empty; remove front
		if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
			backPtr = nullptr;

		// Free memory reserved for the dequeued node
		delete nodeToDeletePtr;
		count--;
		return true;
	}
	bool peek(T& frntEntry)  const
	{
		if (isEmpty())
		{
			frntEntry = 0;
			return false;
		}

		frntEntry = frontPtr->getItem().first;
		return true;
	}
	~PriorityQueue()
	{
		T temp;

		//Free (Dequeue) all nodes in the queue
		while (dequeue(temp));
	}
	PriorityQueue(const PriorityQueue<T>& LQ)
	{
		Node<mypair<T,int>>* NodePtr = LQ.frontPtr;
		if (!NodePtr) //LQ is empty
		{
			frontPtr = backPtr = nullptr;
			return;
		}

		//insert the first node
		Node<mypair<T,int>>* ptr = new Node<mypair<T,int>>;
		ptr->getItem().set_first(NodePtr->getItem().first);
		ptr->getItem().set_second(NodePtr->getItem().second);
		frontPtr = backPtr = ptr;
		NodePtr = NodePtr->getNext();

		//insert remaining nodes
		while (NodePtr)
		{
			Node<mypair<T,int>>* ptr = new Node<mypair<T,int>>;
			ptr->getItem().set_first(NodePtr->getItem().first);
			ptr->getItem().set_second(NodePtr->getItem().second);
			backPtr->setNext(ptr);
			backPtr = ptr;
			NodePtr = NodePtr->getNext();
		}
	}
	void print()
	{
		if (frontPtr == nullptr)
			return;
		else
		{
			Node<mypair<T, int>>*ptr = frontPtr;
			while (ptr)
			{
				cout << *(ptr->getItem().first) << " , ";
				ptr = ptr->getNext();
			}
			cout << "\n";
		}
	}
	int get_count()
	{
		return count;
	}
};
#endif
