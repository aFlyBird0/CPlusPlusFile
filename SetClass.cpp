/***************************
编写人：李鹤鹏
编写时间：2018/04/13
功能：自然数集合类(无序):
		1.实现了Python中列表的部分功能：
			append,remove,pop,insert,
			负数索引
		2.并集，交集,补集
		3.输入输出重载

***************************/

#include <iostream>
#include <cassert>

using namespace std;

class Set
{
public:
	Set(int num[], int length);
		//传入一个数组与长度
	Set();	//无参数创建一个空集合
	Set(const Set& set);	//复制构造函数
	Set operator = (const Set& set);	//赋值重载
	int getCount(){return count;};	//得到元素个数
	bool isItIn(int number);	//某个数是否在集合中
	Set& append(int number);	//末未添加元素
	Set& remove(int number);	//删除指定值
	int pop();	//删除最后一个元素
	int pop(int index);	//删除指定下标元素
	Set& insert(int index, int number);
		//指定位置插入指定元素
	int operator [](int index);	//负数索引
	friend ostream& operator <<(ostream& out,
		const Set& set);	//输出重载
	friend istream& operator >>(istream& in, Set& set);
		//输入重载 输入-1结束
	Set operator * (const Set& set);	//求并集
	Set operator / (const Set& set);	//求交集
	Set operator - (const Set& set);	//求补集
	~Set(){delete[] buf;};
private:
	int *buf;	//指向一个数组
	int count;	//元素的个数
};

int remove_repeat(int num[], int length);
	//数组去重

Set::Set(int num[], int length)
{
	if(NULL != num)
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
	else
	{
		buf = NULL;
		count = 0;
	}

}

Set::Set()
{
	buf = NULL;
	count = 0;
}

Set::Set(const Set& set)
{
	//if(NULL != buf)
		//delete[] buf;
	//原来指向的是随机内存，不能删，否则会造成删掉不该删的东西
	buf = new int[set.count]();
		//分配空间并让buf指向
	for(int i=0; i<set.count; i++)
		buf[i] = set.buf[i];
	count = set.count;
		//每个私有变量进行复制，深复制

}

Set Set::operator = (const Set& set)
{
	if(NULL != buf)
		delete[] buf;
	if(set.buf == buf)
		return *this;
	buf = new int[set.count]();
		//分配空间并让buf指向
	for(int i=0; i<set.count; i++)
		buf[i] = set.buf[i];
	count = set.count;
		//每个私有变量进行复制，深复制
	return Set(set.buf, set.count);
}


bool Set::isItIn(int number)
{
	for(int i=0; i<count; i++)
	{
		if(number == buf[i])
			return 1;
	}
	return 0;
}
Set& Set::append(int number)
{
	if(NULL != buf)
	{
		int i;
		if(isItIn(number))
			return *this;	//如果有相同的值不做更改
		int *bufNew = new int[count+1];
		for(i=0; i<count; i++)
			bufNew[i] = buf[i];
		bufNew[i] = number;	//新建数组并赋值
		delete[] buf;	//释放内存
		buf = bufNew;	//重新指向
		count += 1;
	}
	else
	{
		buf = new int[1];
		buf[0] = number;
		//集合为空则新分配内存并赋值
	}
	return *this;
}

Set& Set::remove(int number)
{
	int i, j=0;
	int* bufNew = new int[count-1];
	for(i=0; i<count; i++)
	{
		if(number != buf[i])
		{
			bufNew[j] = buf[i];
			j++;
		}
	}
	count -= 1;
	return *this;
}

int Set::pop()
{
	int number = buf[count];	//最后一位
	if(NULL != buf)
	{
		int* bufNew = new int[count-1];
		for(int i=0; i<count-1; i++)
		{
			bufNew[i] = buf[i];
		}
		delete[] buf;
		buf = bufNew;
		count -= 1;
	}
	else
	{
		cout<<"The Set is empty"<<endl;
	}
	return number;

}

int Set::pop(int index)
{
	assert(index>=0 && index<count);
	int i, j = 0;
	int number = buf[index];
	if(NULL != buf)
	{
		int* bufNew = new int[count-1];
		for(i=0; i<count; i++)
		{
			if(i != index)
			{
				bufNew[j] = buf[i];
				j++;
			}
		}
		delete[] buf;
		buf = bufNew;
		count -= 1;
	}
	else
	{
		cout<<"The Set is empty"<<endl;
	}
	return number;

}

int Set::operator [](int index)
{
	if(index>=0)
		return buf[index];
	else
		return buf[count + index];
		//-1是倒数第一个，-2倒数第二个
}

Set& Set::insert(int index, int number)
{
	assert(index>=0 && index<count);
	int i, j = 0;
	if(NULL != buf)
	{
		int *bufNew = new int[count+1];
		for(i=0; i<count; i++)
		{
			if(j == index)
			{
				bufNew[j] = number;
				j++;
			}
			bufNew[j] = buf[i];
			j++;
		}
		delete[] buf;
		buf = bufNew;
		count += 1;
	}
	else
	{
		buf = new int[1];
		buf[0] = number;
	}
	return *this;
}

ostream& operator <<(ostream& out, const Set& set)
{
	if(NULL != set.buf)
	{
		cout<<'{';
		int i;
		for(i=0; i<set.count-1; i++)
			cout<<set.buf[i]<<',';
		cout<<set.buf[i];
		cout<<'}'<<endl;
	}
	else
		cout<<"The set is empty!"<<endl;
	return out;
}

istream& operator >>(istream& in, Set& set)
{
	if(NULL != set.buf)
		delete[] set.buf;
	else
	{
		int number[500], i = 0;
		cout<<"Please input no more than 500 numbers\n";
		cout<<"input -1 to end"<<endl;
		while((cin>>number[i], number[i]) != -1
			&& i<500)	//输入-1结束，最大500个
			i++;
		set = Set(number, i);
	}
	return in;
}

Set Set::operator * (const Set& set)
{
	int i, j;
	int countNew = count;
	for(i=0; i<set.count; i++)
		if(isItIn(set.buf[i])==0)
			countNew++;
		//对比数据算出有效数据总数
	//int* bufNew = new int[countNew];
	int bufNew[500];
	for(i=0; i<count; i++)
		bufNew[i] = buf[i];
			//先将左集合完全复制进来
	for(j=0; j<set.count; j++)
	{
		if(isItIn(set.buf[j]) == 0)
		{
			bufNew[i] = set.buf[j];
			i++;
		}
	}
	return Set(bufNew, countNew);
}

Set Set::operator / (const Set& set)
{
	int i, j = 0;
	int countNew = 0;
	for(i=0; i<set.count; i++)
		if(isItIn(set.buf[i])==1)
			countNew++;
		//对比数据算出有效数据总数
	//int* bufNew = new int[countNew];
	int bufNew[500];
	for(i=0; i<set.count; i++)
	{
		if(isItIn(set.buf[i]) == 1)
		{
			bufNew[j] = set.buf[i];
			j++;
			//如果右集合元素在左集合中存在就添加进新集合
		}
	}
	return Set(bufNew, countNew);
}

Set Set::operator - (const Set& set)
{
	for(int i=0; i<set.count; i++)
	{
		if(0 == isItIn(set.buf[i]))
		{
			cout<<"error"<<endl;
			return Set(NULL, 0);
		}
		//如果右集合不是左集合子集，报错，返回空集
	}
	int bufNew[count - set.count];
		//新集合元素为count - set.count个
	int k = 0, flag;
	for(int i=0; i<count; i++)
	{
		flag = 1;
		for(int j=0; j<set.count; j++)
		{
			if(buf[i] == set.buf[j])
			{
				flag = 0;
				break;
			}

		}
		if(1 == flag)
		{
			bufNew[k] = buf[i];
			k++;
		}
	}
	return Set(bufNew, count - set.count);
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
				//如果后面有一样的就置为-1
				break;
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
	//{1,3,2,4}
	Set set2(set1);
	cout<<set2;
	//{1,3,2,4}
	cout<<set1[-1]<<endl;	//负数索引
	//4
	cout<<set1[-2]<<endl;
	//3
	cout<<set1[-3]<<endl;
	//2
	cout<<set1[-4]<<endl;
	//1
	set2.append(5);	//末尾添加元素
	cout<<set2;
	//{1,3,2,4,5}
	set2.append(3);	//添加重复元素
	cout<<set2;
	//{1,3,2,4,5}
	set2.remove(2);	//删除值是2的元素
	cout<<set2;
	//{1,3,2,4}
	set2.pop();	//删除最后一个元素
	cout<<set2;
	//{1,3,2}
	set1.pop(2);	//删除索引是2的元素
	cout<<set1;
	//{1,3,4}
	set1.insert(1,5);	//在索引1的地方插入5,其余元素后移
	cout<<set1;
	//{1,5,3,4}
	cout<<set2;
	//{1,3,2}
	cout<<set1 * set2<<set1 / set2;	//求交并集
	//{1,5,3,4,2}
	//{1,3}
	cout<<(set1 * set2) - set2;	//求补集
	//{5,4}
	Set set3, set4;
	cin>>set3>>set4;
	/*
	1 4 6 8 -1 4 6 7 8 9 -1 3 5
	*/
	cout<<set3<<set4;
	/*
	Please input no more than 500 numbers
	input -1 to end
	1 4 6 8 -1 4 6 7 8 9 -1 3 5
	Please input no more than 500 numbers
	input -1 to end
	{1,4,6,8}
	{4,6,7,8,9}
	*/
	return 0;
}