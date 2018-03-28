/* 
编写人：李鹤鹏
编写日期：2018/03/14
功能：引用练习，
		随机生成随机数并且找出最大最小值
备注：由于这个太简单所以不做过多描述，
		主要把精力放在下一个上面
*/


#include <iostream>
#include <cstdlib>
#include <ctime>

#define LENGTH 20

using namespace std;

void fun(int number[], int length, int &max, int &min);
		//传入数组以及长度，找出数组最大值与最小值

int main()
{
	int number[LENGTH], max, min;
	srand((unsigned)time(NULL));
	for(int i=0; i<LENGTH; i++)
		number[i] = rand()%100 + 1;	//随机生成随机数,范围1-100
	for(int i=0; i<LENGTH; i++)
		cout<<number[i]<<' ';	//遍历打印以检测
	cout<<endl;
	fun(number, LENGTH, max, min);
	cout<<"max:"<<max<<'\n'<<"min:"<<min<<endl;
	return 0;
}

void fun(int number[], int length, int &max, int &min)
{
	max = min = number[0];
	for(int i=0; i<length; i++)
	{
		max = (max>number[i] ? max : number[i]);
		min = (min<number[i] ? min : number[i]);
	}
}