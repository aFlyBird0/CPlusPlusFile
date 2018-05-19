/*

编写人：李鹤鹏
编写时间：2018/05/18
功能：链表集合类(链表中组合节点类，集合继承链表类)

*/

#include <iostream>
#include "Link.h"

using namespace std;

template <class T>
class Set: public LinkedList<T>
{

protected:

public:
	Set(void):LinkedList<T>::LinkedList(){}	//构造函数
	~Set(){LinkedList<T>::ClearList();};
	void Insert(const T item);	//有序插入且不重复
};

template <class T>
void Set<T>::Insert(const T item)
{
	if(LinkedList<T>::ListEmpty())
		LinkedList<T>::InsertFront(item);
	else
	{
		while(!LinkedList<T>::EndOfList())
		{
			if(LinkedList<T>::Data()<item)
			{
				LinkedList<T>::Next();	//如果节点值比新插入的小就将指针后移
			}
			else
			{
				LinkedList<T>::InsertAt(item);	//否则就在当前节点之前插入
				LinkedList<T>::Reset();	//指针归位
			}
		}
	}
}

int main()
{
	Set <int> set1;
	int item1 = 3;
	set1.InsertRear(item1);
	cout<<set1.Data();
	cout<<set1.ListSize();
	return 0;
}