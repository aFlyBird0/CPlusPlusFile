
#include <iostream>
#include <iomanip>

using namespace std;

class Time
{
public:
	Time(int newHour, int newMinute, int newSecond=0);
		//构造函数，初始化为0秒
	Time(int totalSecond);
	//Time(Time& time){}
	void setTime(int newHour, int newMinute, int newSecond);
	Time operator + (const Time& time);
	friend ostream& operator <<(ostream& out, const Time& time);
		//输出重载
	friend istream& operator >>(istream& in, Time& time);
		//输入重载

	//~Time(){}


private:
	int hour, minute, second;
};

Time::Time(int newHour, int newMinute, int newSecond)
{
	hour = newHour;
	minute = newMinute;
	second = newSecond;
}

Time::Time(int totalSecond)
{
	hour = totalSecond / 3600;
	minute = (totalSecond - 3600 * hour) / 60;
	second = totalSecond - hour *3600 - minute * 60;
		//利用整除实现用秒数与构造函数初始化对象
}

void Time::setTime(int newHour, int newMinute, int newSecond)
{
	hour = newHour;
	minute = newMinute;
	second = newSecond;
}

Time Time::operator + (const Time& time)
{
	int time1Second = hour * 3600 + minute * 60 + second;
	int time2Second = time.hour * 3600 +
				time.minute * 60 + time.second;
				//分别折算成秒数
	return Time(time1Second + time2Second);
}

ostream& operator <<(ostream& out, const Time& time)
{
	out<<setfill('0')<<setw(2)<<time.hour<<":";
	out<<setfill('0')<<setw(2)<<time.minute<<":";
	out<<setfill('0')<<setw(2)<<time.second<<endl;
		//输出重载,setfill设置用0填充,setw设置宽度至少两格
	return out;
}

istream& operator >>(istream& in, Time& time)
{
	char ch;
	in>>time.hour>>ch>>time.minute>>ch>>time.second;
	//用一个字符来吸收':'
	return in;
}

int main()
{
	Time time1(0, 0, 0);
	Time time2(0, 0, 0);
	cin>>time1>>time2;
	cout<<time1+time2;
	return 0;
}
