#ifndef node
#define node
#include "Node.h"
#include<iostream>
using namespace std;
template <class T>
class LinkedQueue
{
private:
	Node<T>* backPtr;
	Node<T>* frontPtr;
	int count;
public:
	LinkedQueue()
	{
		backPtr = nullptr;
		frontPtr = nullptr;
		count = 0;
	}
	bool isEmpty() const
	{
		return (count==0);
	}
	bool enqueue(const T& newEntry)
	{
		Node<T>* newNodePtr = new Node<T>;
		newNodePtr->setItem(newEntry);
		// Insert the new node
		if (isEmpty())	//special case if this is the first node to insert
			frontPtr = newNodePtr; // The queue is empty
		else
			backPtr->setNext(newNodePtr); // The queue was not empty

		backPtr = newNodePtr;
		count++;
		// New node is the last node now
		return true;
	}
	bool dequeue(T& frntEntry)
	{
		if (isEmpty())
		{
			frntEntry = 0;
			return false;
		}

		Node<T>* nodeToDeletePtr = frontPtr;
		frntEntry = frontPtr->getItem();
		frontPtr = frontPtr->getNext();
		// Queue is not empty; remove front
		if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
			backPtr = nullptr;

		// Free memory reserved for the dequeued node
		delete nodeToDeletePtr;
		count--;
		return true;
	}
		bool peek(T & frntEntry)  const
		{
			if (isEmpty())
			{
				frntEntry = 0;
				return false;
			}
			frntEntry = frontPtr->getItem();
			return true;
		}
		~LinkedQueue()
		{
			T temp;

			//Free (Dequeue) all nodes in the queue
			while (dequeue(temp));
		}
		LinkedQueue(const LinkedQueue<T>&LQ)
		{
			Node<T>* NodePtr = LQ.frontPtr;
			if (!NodePtr) //LQ is empty
			{
				frontPtr = backPtr = nullptr;
				return;
			}

			//insert the first node
			Node<T>* ptr = new Node<T>(NodePtr->getItem());
			frontPtr = backPtr = ptr;
			NodePtr = NodePtr->getNext();

			//insert remaining nodes
			while (NodePtr)
			{
				Node<T>* ptr = new Node<T>(NodePtr->getItem());
				backPtr->setNext(ptr);
				backPtr = ptr;
				NodePtr = NodePtr->getNext();
			}
		}
		int get_count()
		{
			return count;
		}
		void print()
		{
			if (frontPtr == nullptr)
				return;
			else
			{
				Node<T>*ptr = frontPtr;
				while (ptr)
				{

					cout << *(ptr->getItem()) << " , ";
					ptr = ptr->getNext();
				}

			}
		}
};
#endif
