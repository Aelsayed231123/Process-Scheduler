#include"Node.h"
template<class T>
class PriorityQueue
{
private:
	Node<T>* frontPtr;
	Node<T>* backPtr;
public:
	PriorityQueue()
	{
		frontPtr = nullptr;
		backPtr = nullptr;
	}
	void enqueue(const T& newEntry)
	{
		Node<T>* temp = new Node<T>(newEntry);
		if (isEmpty())
		{
			frontPtr = temp;
			backPtr = temp;
		}
		else
		{
			Node<T>* pre = nullptr;
			Node<T>* ptr = frontPtr;
			while (ptr)
			{
				if (temp->getItem() <= ptr->getItem())
				{
					if (!pre)
					{
						temp->setNext(ptr);
						frontPtr = temp;
						backPtr = ptr;
						break;
					}
					else
					{
						temp->setNext(ptr);
						pre->setNext(temp);
						break;
					}
				}
				pre = ptr;
				ptr = ptr->getNext();
			}
		}
	}
	bool isEmpty() const
	{
		return (frontPtr == nullptr);
	}
	bool dequeue(T& frntEntry)
	{
		if (isEmpty())
			return false;

		Node<T>* nodeToDeletePtr = frontPtr;
		frntEntry = frontPtr->getItem();
		frontPtr = frontPtr->getNext();
		// Queue is not empty; remove front
		if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
			backPtr = nullptr;

		// Free memory reserved for the dequeued node
		delete nodeToDeletePtr;

		return true;
	}
	bool peek(T& frntEntry)  const
	{
		if (isEmpty())
			return false;

		frntEntry = frontPtr->getItem();
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
};

