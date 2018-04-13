/***************************
编写人：李鹤鹏
编写时间：2018/04/13
功能：自然数集合类

***************************/

#include <iostream>
#include <algorithm>

using namespace std;

class Set
{
public:
	Set(int num[], int length);
		//传入一个数组与长度
	Set();	//无参数创建一个空集合
	Set(const Set& set);	//复制构造函数
	friend ostream& operator <<(ostream& out,
		const Set& set);	//输出重载
	~Set(){delete[] buf;};
private:
	int *buf;	//指向一个数组
	int count;	//元素的个数
};

int remove_repeat(int num[], int length);
	//数组去重

Set::Set(int num[], int length)
{
	int i, j = 0;
	count = remove_repeat(num, length);
		//利用去重函数返回有效个数
	buf = new int[count]();
		//分配空间并让buf指向
	for(i=0; i<length; i++)
	{
		if(num[i] != -1)
		{
			buf[j] = num[i];
			j++;
		}
		//只挑选不是-1的有效值
	}
}

Set::Set()
{
	buf = NULL;
	count = 0;
}

Set::Set(const Set& set)
{
	buf = new int[set.count]();
		//分配空间并让buf指向
	for(int i=0; i<set.count; i++)
		buf[i] = set.buf[i];
	count = set.count;
		//每个私有变量进行复制，深复制
}

ostream& operator <<(ostream& out, const Set& set)
{
	cout<<'{';
	int i;
	for(i=0; i<set.count-1; i++)
		cout<<set.buf[i]<<',';
	cout<<set.buf[i];
	cout<<'}'<<endl;
	return out;
}

int remove_repeat(int num[], int length)
	//数组去重
{
	int count = length;	//减去重复数字后的有效数字
	for(int i=0; i<length-1; i++)
	{
		for(int j=i+1; j<length; j++)
		{
			if(num[i] == num[j])
			{
				num[i] = -1;
				count -= 1;
			}
		}
	}
	return count;
}

int main()
{
	int num[] = {1,3,2,2,2,4};
	Set set1(num, sizeof(num)/4);
	cout<<set1;
	Set set2(set1);
	cout<<set2;
	return 0;
}

