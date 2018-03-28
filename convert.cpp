/*
编写人：李鹤鹏
编写时间：2018/03/23
功能：实现自定义类（以英尺为例）与基本类型的转换

*/

#include <iostream>

using namespace std;

class Foot
{
public:
	Foot();
	Foot(int ft, double ih);
	Foot(double meter = 0.0);
		//用构造函数实现从基本类型到自定义类型的转换
		//其实这里最好应该再重载一个参数是int的函数
	Foot(const Foot& foot);
	void showFeet();	//打印显示
	double operator + (const Foot& foot);
		//利用运算符重载实现从自定义类型到基本类型的转换
		//（当'+'左边是自定义类型，右边也是自定义类型时)
	double operator + (double meter);
		//（当'+'左边是自定义类型，右边是基本类型时
	~Foot(){};
private:
	int feet;		//英尺
	double inch;	//英寸
};

Foot::Foot()
{
	feet = 0;
	inch = 0.0;
}

Foot::Foot(int ft, double ih)
{
	feet = ft;
	inch = ih;
}

Foot::Foot(double meter)
{
	feet = (int)(meter * 3.28);
	inch = (meter - feet / 3.28) * 39.37;
		//转换的具体实现
}

Foot::Foot(const Foot& foot)
{
	feet = foot.feet;
	inch = foot.inch;
}

void Foot::showFeet()
{
	cout<<feet<<" feet "<<inch<<" inches"<<endl;
}

double Foot::operator + (const Foot& foot)
	//运算符重载，foo1+foot2相当于foot1.operator+(foot2)
	//所以也就是说如果不加前缀默认的是foot1的成员，
	//但是foot2是传参传进来的所以要加前缀foot2
{
	double meter = (feet + foot.feet) / 3.28 
				 	+ (inch + foot.inch) / 39.37;
		//先转换成米再转化成英尺来处理 进位
	return meter;
}

double Foot::operator + (double meter)
{
	meter += feet / 3.28 + inch / 39.37;
	return meter;
}

int main()
{
	Foot foot1(2.26);
	foot1.showFeet();
	Foot foot2(1.0);
	foot2.showFeet();
	cout<<foot1 + foot2<<endl;
		//测试左右都是自定义类型的'+'是否重载成功
	cout<<foot1 + 1<<endl;
		//测试左边自定义类型右边基本类型的'+'是否重载成功
		//并且这里基本类型用的是int,而实际函数形参是double
		//所以印证了int向double的隐式转换
	cout<<foot1 + 0.0<<endl;
		//只是加0实现的是把一个自定义类型转换成基本类型
	Foot foot3(foot1 + foot2);
		//先用重载计算两个自定义类型的基本类型和
		//再用返回的基本类型调用构造函数给新自定义类型初始化
		//这样子可以实现两个对象直接相加
		//之前想过在写一个函数直接返回对象
		//但是想起来只是返回值类型不同不能成功重载
	foot3.showFeet();
	return 0;
}