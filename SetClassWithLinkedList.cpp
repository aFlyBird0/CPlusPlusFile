/*

编写人：李鹤鹏
编写时间：2018/05/18
功能：链表集合类(链表中组合节点类，集合继承链表类，并且使用类模板)
		1.有序（从小到大）
		2.插入
		3.不重复
		4.输出重载
		5.交并集,差集
		6.删除指定值，pop最后一个值
		7.下标重载，支持负数下标


想法：关于模板与友元的结合还是有些问题，所以只能写在类内

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
	Set(const Set<T>& set);
	~Set(){LinkedList<T>::ClearList();};
	void Insert(const T item);	//有序插入且不重复
	void Remove(const T item);	//删除值为item的元素
	T Pop();	//弹出最后一个元素
	friend ostream& operator <<(ostream& out, Set<T>& set)	//输出重载
	{
		set.Reset();
		if(set.ListEmpty())
		{
			out<<"Te set is empty!"<<endl;
			return out;
		}
		out<<"The set is {";
		int i = 0;
		while(!set.EndOfList())
		{
			out<<set.Data();
			if(i < set.ListSize() - 1)
				out<<',';
			set.Next();
			i++;
		}
		out<<'}'<<endl;
	return out;
	}
	void ShowSize();	//显示元素个数
	Set operator + (Set<T>& set);	//并集
	Set operator * (Set<T>& set);	//交集
	Set operator - (Set<T>& set);	//差集
	T operator [] (const int pos);		//下标重载，支持负数索引
};

template <class T>
Set<T>::Set(const Set<T>& set)
{
	this->front = this->rear = NULL;
  	this->prevPtr = this->currPtr = NULL;
  	this->size = 0;
  	this->position = -1;
  	this->CopyList(set);
}

template <class T>
void Set<T>::Insert(const T item)
{
	cout<<"Inserting "<<item<<" to the set"<<endl;
	bool done = 0;	//插入是否完成
	if(this->ListEmpty())
	{
		this->InsertFront(item);
		done = 1;
	}
	else
	{
		this->Reset();
		while(!this->EndOfList())
		{
			if(this->Data()<item)
			{
				this->Next();	//如果节点值比新插入的小就将指针后移
			}
			else if(this->Data()==item)
			{
				cout<<"This item is repeated with an element of the set."<<endl;
				this->Reset();
				return;
			}
			else
			{
				this->InsertAt(item);	//否则就在当前节点之前插入
				this->Reset();	//指针归位s
				done = 1;
				break;
			}
		}
	}
	if( done == 0)//如果还没插入说明没有比带插入数据更大的数
	{
		this->InsertRear(item);	//插入到末尾
	}
	this->Reset();
	cout<<item<<" has been insert successfully"<<endl;
}
template<class T>
void Set<T>::Remove(const T item)
{
	this->Reset();
	while(!this->EndOfList())
	{
		if(item == this->Data())
		{
			this->DeleteAt();
			this->Reset();
			return;
		}
		this->Next();
	}
}

template<class T>
T Set<T>::Pop()
{
	this->Reset();
	int pos;
	for(pos=0; pos<(this->ListSize()-1); pos++)
		this->Next();
	T data = this->Data();
	this->DeleteAt();
	this->Reset();
	return data;
}

template <class T>
void Set<T>::ShowSize()
{
	cout<<"The set has "<<this->ListSize()<<" items"<<endl;
}

template <class T>
Set<T> Set<T>::operator + (Set<T>& set)
{
  	Set setNew(*this);
  	//cout<<"setNew"<<setNew<<endl;
	while(!set.EndOfList())
	{
		setNew.Insert(set.Data());
		//把右集合元素一个个插入到左集合里面
		set.Next();
	}
	this->Reset();
	set.Reset();
	setNew.Reset();
	return setNew;
}

template <class T>
Set<T> Set<T>::operator * (Set<T>& set)
{
  	Set setNew;
  	//cout<<"setNew"<<setNew<<endl;
	while(!this->EndOfList())
	{
		while(!set.EndOfList())
		{
			if(this->Data() == set.Data())
			{
				setNew.Insert(this->Data());
				//如果遇到两个集合都有的元素就插入新集合
				break;
			}
			set.Next();
		}
		this->Next();
	}
	this->Reset();
	set.Reset();
	setNew.Reset();
	return setNew;
}

template <class T>
Set<T> Set<T>::operator - (Set<T>& set)
{
  	Set setNew(*this);
  	//cout<<"setNew"<<setNew<<endl;
	while(!set.EndOfList())
	{
		while(!this->EndOfList())
		{
			if(this->Data() == set.Data())
			{
				setNew.Remove(this->Data());
				this->Reset();
				break;
			}
			this->Next();
		}
		set.Next();
		this->Reset();
	}
	this->Reset();
	set.Reset();
	setNew.Reset();
	return setNew;
}

template<class T>
T Set<T>::operator [](const int pos)
{
	this->Reset();
	if(pos > (this->ListSize() -1)|| (pos + this->ListSize()) < 0)
	{
		cout<<"Out of index"<<endl;
		exit(1);
	}
	if(pos >=0)
	{
		for(int i=0; i < pos; i++)
			this->Next();
		return this->Data();
	}
	else
	{
		for(int i=0; i<(pos+(this->ListSize())); i++)
			this->Next();
		return this->Data();
	}
}

int main()
{
	Set<int> set1;
	int item1 = 3;
	set1.Insert(item1);
	//cout<<set1.Data();
	//cout<<set1.ListSize();
	set1.Insert(1);
	set1.Insert(2);
	set1.Insert(3);
	set1.Insert(4);
	cout<<set1;
	set1.ShowSize();
	Set<int> set2;
	set2.Insert(6);
	set2.Insert(1);
	set2.Insert(2);
	set2.Insert(5);
	Set<int> set3(set1+set2);
	//cout<<(set1+set2)<<endl;
	cout<<set3;
	//set1+set2;
	Set<int> set4(set1*set2);
	cout<<set4;
	set3.Remove(4);
	cout<<set3;
	Set<int> set5(set1-set2);
	cout<<set5;
	set5.Pop();
	cout<<set5;
	cout<<set1[3]<<endl;
	cout<<set1[-1]<<endl;
	return 0;
}