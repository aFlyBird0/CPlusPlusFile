/*
编写人：李鹤鹏
编写日期：2018/03/23

功能：Cat类
目的：练习静态数据成员和静态成员函数
意外收获：1.类外定义static要省去
		 2.复制构造函数最后要加上猫的总数加一，
		 	这样子用已有对象初始化的时候数量才会加，
		 	但这样又出现了一个问题，
		 	形参与实参结合和返回对象的时候会调用复制构造函数，
		 	这个时候数量也会加一，所以这两种情况要加一句数量减一，
		 	（这两种情况本程序中未出现，但是想到了就写了下来）

*/

#include <iostream>
#include <string>

using namespace std;

class Cat
{
public:
	Cat(string catName = "Kitty", 
		string catKind = "ordinary", 
		int catAge = 0);
	Cat(const Cat& cat);	//常引用，防止原对象被恶意修改
	void showCat();
	void changeNmae(string newName)	{name = newName;};//改名字
	void changekind(string newKind) {kind = newKind;};//改种类
	void changeAge(int newAge)   {age = newAge;}	 //改年龄
	static int getNumOfCats();
	~Cat(){ numOfCats--;};	//析构函数，对象消亡时猫的数量减一

private:
	static int numOfCats;	//猫总数，静态数据成员声明
	string name;	//猫的名字
	string kind;	//猫的种类
	int age;		//猫的年龄
};

Cat::Cat(string catName, string catKind, int catAge)
{
	name = catName;
	kind = catKind;
	age  = catAge;
	numOfCats++;	//创建对象时猫的数量增加
}

Cat::Cat(const Cat& cat)
{
	name = cat.name;
	kind = cat.kind;
	age  = cat.age;
	numOfCats++;
}

void Cat::showCat()
{
	cout<<"catName:"<<name<<endl;
	cout<<"catKind:"<<kind<<endl;
	cout<<"catAge:"<<age<<'\n'<<endl;
}

int Cat::getNumOfCats()
		//!!!注意在类外定义的时候的时候不需要再加static
		//如static int Cat::getNumofCats()是错误的
{
	cout<<"There are "<<numOfCats<<" cat(s) in tatal.\n"<<endl;
	return numOfCats;
}

int Cat::numOfCats = 0; //初始化静态数据成员
						//注意初始化的时候不需要再次用static

int main()
{
	Cat cat1("cat1", "kind1", 1);
	cat1.showCat();
	Cat cat2(cat1);	//用一个初始化另一个数量也会增加
	cat2.changeNmae("cat2");
	cat2.changekind("kind2");
	cat2.changeAge(2);
	cat2.showCat();
	Cat::getNumOfCats();
	Cat cat3("cat3", "kind3", 3);
	cat3.showCat();
	Cat::getNumOfCats();
	return 0;
}

