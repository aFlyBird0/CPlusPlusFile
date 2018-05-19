/*
编写人：李鹤鹏
编写日期：2018/03/14

功能：Time类：
			1.时间生成：自主生成时间，也可以通过获取系统时间自动生成，
			2.闹钟：功能不多说，且用到了老师要求的时间相减函数
					并且有倒计时功能，但是只能设定当天的闹钟
					如果忽略程序运行时间闹钟会比较准确，
					因为题意设定时间可以由用户指定，
					所以不能通过与系统时间进行实时比对增加精度
			3.老师你觉得时间增加我找不出什么很有用的实际意义，
				并且时间增加只是简单地进位，锻炼意义不大。

函数库使用说明:  1.iomanip 是为了设置输出填充'0'
				2.ctime 获取系统时间以及对时间的处理
				3.windows.h 用于Sleep()进行延迟

关于为什么用英语：因为我用sublime写的cpp,然后调用g++运行，
				cpp编码格式用的utf-8,但是一直有乱码，
				试了很多方法也解决不了，所以干错用英文了。
疑惑：我的闹钟方法和时间相减方法这么写总感觉有点怪，
		每次调用的时候都必须用一个类引出，比如必须用
		time1.alarmTime(sleeptime),很想不通过实例
		然后直接用类里面函数，不知道是否有可行的方法，
		总感觉这样很怪
*/



#include <iostream>
#include <iomanip>
#include <ctime>
#include <windows.h>

using namespace std;

class Time
{
public:
	Time(int newHour, int newMinute=0, int newSecond=0);
		//有数值初始化，并且设定分秒默认值为0，符合常理
	Time();	//没有数值的初始化， 获得系统时间初始化
	Time(Time& time);
	void showTime();
	void setTime(int newHour, int newMinute, int newSecond);
	int minusTime(Time& time1, Time& time2);
		//两时间相减，返回相差的秒数
	void alarmClock(int sleepTime);	//闹钟


private:
	int hour, minute, second;
};

Time::Time(int newHour, int newMinute, int newSecond)
{
	hour = newHour;
	minute = newMinute;
	second = newSecond;
}

Time::Time()
{
	time_t now;
	now = time(0);
	struct tm nowTime = *localtime(&now);
		//获得当前时间结构体
	hour = nowTime.tm_hour;
	minute = nowTime.tm_min;
	second = nowTime.tm_sec;
}

Time::Time(Time& time)
{
	hour = time.hour;
	minute = time.minute;
	second = time.second;
}

void Time::showTime()
{
	cout<<"The current time is:\n";
	cout<<setfill('0')<<setw(2)<<hour<<":";
	cout<<setfill('0')<<setw(2)<<minute<<":";
	cout<<setfill('0')<<setw(2)<<second<<endl;
}

void Time::setTime(int newHour, int newMinute, int newSecond)
{
	hour = newHour;
	minute = newMinute;
	second = newSecond;
}

int Time::minusTime(Time& time1, Time& time2)
{
	int time1Second = time1.hour * 3600 +
					time1.minute * 60 + time1.second;
	int time2Second = time2.hour * 3600 +
					time2.minute * 60 + time2.second;
	return time1Second - time2Second;
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

int main()
{
	Time timeCurrent;	//自动获取系统时间
	timeCurrent.showTime();
	Time time1(22, 39, 0);	//用数值进行初始化
	time1.showTime();	//显示时间
	time1.setTime(22,58,0);	//时间设定
	time1.showTime();
	Time time2(23);	//用默认值的初始化
	time2.showTime();
	time1.alarmClock(time1.minusTime(time2, time1));
		//闹铃函数，有瑕疵，见文档开头说明
	return 0;
}
