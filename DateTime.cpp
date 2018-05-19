/*
名称：时间日期类（多继承）
编写人：李鹤鹏
编写时间：2018/05/11-2018/05/12
功能:1.时间日期自动初始化，修改，输出重载
	 2.日期倒计时（涉及到闰年判断等等）
	 3.时间倒计时（闹钟）
*/



#include <iostream>
#include <ctime>
#include <iomanip>
#include <cassert>
#include <windows.h>
using namespace std;

class Date
{
public:
	Date();	//无数值初始化为计算机系统时间
	Date(int y, int m, int d);
	Date(const Date& date);
	void set(int y, int m, int d);	//时间修改
	int isLeapyear();	//判断是否闰年
    int cal();	//计算一年第几天
    int minusDate(Date& date);	//计算两个日期相差天数
	friend ostream& operator <<(ostream& out, const Date& date);
	~Date(){};
protected:
	int year;
	int month;
	int day;
	static int days[12];	//一年的每月天数
};

Date::Date()
{
	time_t now;
	now = time(0);
	struct tm nowDate = *localtime(&now);
		//获得当前时间结构体
	year  = nowDate.tm_year + 1900;
	month = nowDate.tm_mon + 1;
	day   = nowDate.tm_mday;
	//时间初始化
}

Date::Date(int y, int m, int d)
{
	year  = y;
	month = m;
	day   = d;
}

Date::Date(const Date& date)
{
	year  = date.year;
	month = date.month;
	day   = date.day;
}

void Date::set(int y, int m, int d)
{
	year  = y;
	month = m;
	day   = d;
}

int Date::isLeapyear()
{
	if((year%100==0&&year%400==0)||(year%100!=0&&year%4==0))
		return 1;
	else
		return 0;
}

int Date::cal()
{
	int num = 0;	//第几天
	switch(month)
	{
		//如果是十二月那么应该加上前十一月天数
		case 12: num += days[10];
		case 11: num += days[9];
		case 10: num += days[8];
		case 9: num += days[7];
		case 8: num += days[6];
		case 7: num += days[5];
		case 6: num += days[4];
		case 5: num += days[3];
		case 4: num += days[2];
		case 3: {if(isLeapyear())
					num += (days[1]+1);	//闰年二月多加一天;
				else
					num += days[1];}
		case 2: num += days[0];
	}
	num += day;	//再加上日子数
	return num;
}

int Date::minusDate(Date& date)
{
	assert((date.year > year) ||
			(date.year == year && date.month > month) ||
			(date.year == year && date.month == month && date.day >= day));
	int minusDay = 0;
	if(year == date.year)
	{
		minusDay = date.cal() - cal();
	}
		//年份相同就直接将两个各自的第几天想减
	else
	{
		minusDay += (date.cal() + 365 + isLeapyear() - cal());
		//将前一个日期到年底的天数与后一个日期从一月一日开始的天数相加
		for(int i=year+1; i<date.year; i++)
		{
			minusDay += (365 + isLeapyear());
			//把中间的年份加上去
		}
	}
	return minusDay;
}

ostream& operator << (ostream& out, const Date& date)
{
	cout<<"The date is ";
	cout<<setfill('0')<<setw(4)<<date.year<<"/";
	cout<<setfill('0')<<setw(2)<<date.month<<"/";
	cout<<setfill('0')<<setw(2)<<date.day<<endl;
	return out;
}


class Time
{
public:
	Time();
	Time(int h, int m, int s);
	void set(int h, int m, int s);
	static int minusTime(Time& time1, Time& time2);	//两时间相减
	friend ostream& operator <<(ostream& out, const Time& time);//输出重载
	void alarmClock(int sleepTime);	//闹钟
	~Time(){};
protected:
	int hour;
	int minute;
	int second;
};

Time::Time()
{
	time_t now;
	now = time(0);
	struct tm nowTime = *localtime(&now);
		//获得当前时间结构体
	hour   = nowTime.tm_hour;
	minute = nowTime.tm_min;
	second = nowTime.tm_sec;
}

Time::Time(int h, int m, int s)
{
	hour   = h;
	minute = m;
	second = s;
}

void Time::set(int h, int m, int s)
{
	hour   = h;
	minute = m;
	second = s;
	cout<<*this;
}

int Time::minusTime(Time& time1, Time& time2)
{
	int time1Second = time1.hour * 3600 +
					time1.minute * 60 + time1.second;
	int time2Second = time2.hour * 3600 +
					time2.minute * 60 + time2.second;
	return time1Second - time2Second;
}


ostream& operator << (ostream& out, const Time& time)
{
	cout<<"The time is ";
	cout<<setfill('0')<<setw(2)<<time.hour<<":";
	cout<<setfill('0')<<setw(2)<<time.minute<<":";
	cout<<setfill('0')<<setw(2)<<time.second<<endl;
	return out;
}

void Time::alarmClock(int sleepTime)
{
	if(sleepTime > 0)
	{
		cout<<"The alarm clock is running !"<<endl;
		while(sleepTime != 0)
		{
			int restHour = sleepTime/3600;
			int restMinute = (sleepTime - restHour * 3600) / 60;
			int restSecond = sleepTime - restHour * 3600
										- restMinute * 60;
			cout<<'\r';	//移到行首，起到“刷新”效果
			cout<<setfill('0')<<setw(2)<<restHour<<"hour(s)";
			cout<<setfill('0')<<setw(2)<<restMinute<<"minute(s)";
			cout<<setfill('0')<<setw(2)<<restSecond<<"second(s)";
			cout<<"left";	//注意这里故意不换行是为了配合'\r'进行刷新
			Sleep(1000);	//延迟
			sleepTime --;
		}
		cout<<"\n\a\a\atime out!"<<endl;
	}
	else
		cout<<"Error, time set have passed!"<<endl;
}

class DateTime:public Date, public Time
{
public:
	DateTime(int y, int mon, int d, int h, int min, int s):Date(y, mon, d),Time(h, min, s){};//构造函数
	DateTime():Date(),Time(){};//无数值构造函数
	DateTime(const Date& date, const Time& time):Date(date),Time(time){};	//用基类初始化
	void set(int y, int mon, int d, int h, int min, int s);	//设置时间,修改基类函数
	friend ostream& operator <<(ostream& out, const DateTime dateTime);
	~DateTime(){};

};

void DateTime::set(int y, int mon, int d, int h, int min, int s)
{
	year  = y;
	month = mon;
	day   = d;
	hour   = h;
	minute = min;
	second = s;
	cout<<*this;
}


ostream& operator <<(ostream& out, const DateTime dateTime)
{
	cout<<"The dateTime is ";
	cout<<setfill('0')<<setw(4)<<dateTime.year<<"/";
	cout<<setfill('0')<<setw(2)<<dateTime.month<<"/";
	cout<<setfill('0')<<setw(2)<<dateTime.day<<"  ";
	cout<<setfill('0')<<setw(2)<<dateTime.hour<<":";
	cout<<setfill('0')<<setw(2)<<dateTime.minute<<":";
	cout<<setfill('0')<<setw(2)<<dateTime.second<<endl;
	return out;
}

int Date::days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


int main()
{
	Date date1;
	Date date2(2018, 6, 7);	//高考时间
	Time time1;
	cout<<date1<<time1;
	DateTime dateTime1(date1, time1);
	cout<<dateTime1;
	cout<<"There are "<<date1.minusDate(date2);
	cout<<" days before the college entrance examination."<<endl;
		//高考倒计时
	Sleep(3000);
	Time time2;
	dateTime1.alarmClock(Time::minusTime(time2, time1));
		//闹钟
	return 0;
}