#pragma once
template<class T,class M>
struct mypair
{
	T first;
	M second;
	mypair(T f=0, M s=0)
	{
		set_pair(f, s);
	}
	void set_pair(T f,M s)
	{
		first = f;
		second = s;
	}
	void set_first(T f)
	{
		first = f;
	}
	void set_second(M s)
	{
		second = s;
	}
};


