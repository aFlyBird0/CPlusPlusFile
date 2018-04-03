#include <iostream>

using namespace std;

class Date
{
public:
    Date(int Year=2000,int Month=1, int Day=1);
    //Date(const Class& date);
    void set(int Year, int Month, int Day);
    int isLeapyear();	//判断是否闰年
    static int cal(const Date& date);
    	//计算第几天
    void Show();
    friend void test(const Date& date);
    ~Date(){};

private:
	int year;
	int month;
	int day;
	static int days[12];
};

Date::Date(int Year,int Month, int Day)
{
	year = Year;
	month = Month;
	day = Day;
}

void Date::set(int Year, int Month, int Day)
{
	year = Year;
	month = Month;
	day = Day;
	if(isLeapyear())
		days[1] = 29;
	else
		days[1] = 28;
}

int Date::isLeapyear()
{
	if((year%100==0&&year%400==0)||(year%100!=0&&year%4==0))
		return 1;
	else
		return 0;
}

int Date::cal(const Date& date)
{
	int num = 0;	//第几天
	switch(date.month)
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
		case 3: num += days[1];
		case 2: num += days[0];
	}
	num += date.day;	//再加上日子数
	return num;
}

void Date::Show()
{
	cout<<year<<"年"<<month<<"月"<<day<<"日"<<endl;

}

void test(const Date& date)
{
	cout<<"是"<<date.year<<"年的第"<<Date::cal(date)<<"天"<<endl;
}

int Date::days[] = {31,28,31,30,31,30,31,31,30,31,30,31};

int main()
{
	Date date;
	int Year, Month, Day;
	while(cin>>Year>>Month>>Day)
		//读取到文件末尾返回eof结束读取
	{
		date.set(Year, Month, Day);
		test(date);	//用外部函数进行计算与输出
	}
    return 0;
}
