#include <iostream>
#include <cmath>

using namespace std;

class Rec;
class Point
{
public:
	friend Rec;
	Point(int newX=0, int newY=0):x(newX),y(newY){};
	friend ostream& operator<<(ostream& out, Rec& rec);	//输出重载
	friend istream& operator>>(istream& in, Point& point);	//输入重载
private:
	double x;
	double y;
};

istream& operator>>(istream& in, Point& point)	//输入重载
{
	cin>>point.x>>point.y;
	return in;
}
class Rec
{
public:
	Rec(Point p1, Point p2):point1(p1),point2(p2){};
	int calculate()	//计算面积
	{
		return abs(point1.x - point2.x) * abs(point1.y - point2.y);
			//abs取绝对值
	}
	friend ostream& operator<<(ostream& out, Rec& rec);	//输出重载
	~Rec(){};
private:
	Point point1;
	Point point2;
};

ostream& operator<<(ostream& out, Rec& rec)
{
	cout<<rec.point1.x<<rec.point1.y<<rec.point2.x<<rec.point2.y<<endl;
		//这里格式自己改一下
	cout<<rec.calculate()<<endl;
	return out;
}

int main()
{
	Point p1, p2;
	cin>>p1>>p2;	//输入两个点
	Rec rec(p1, p2);
	cout<<rec;	//输出长方形数据
	return 0;
}