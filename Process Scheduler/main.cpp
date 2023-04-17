#include <iostream>
#include"PriorityQueue.h"
using namespace std;
template<class T>
void PrintQueue(PriorityQueue<T> Q)
{
	T K;
	while (Q.dequeue(K))
	{
		cout << K;
		if (!Q.isEmpty())
			cout << " ";
	}
	cout << endl;
}
int main()
{
	PriorityQueue<int>P;
	int val;
	cin >> val;
	while (val != -1)
	{
		P.enqueue(val,val);
		cin >> val;
	}
	PrintQueue(P);
   return 0;
}