#include<iostream>
#include<string>

using namespace std;

template<typename T>
T Max(T *array,int size = 0)
{
	if(size ==0)
		return 0;
 	T max = array[0];
	for(int i=1; i<size; i++)
	if(max < array[i])
		max = array[i];
	//max = array[i] > max ? array[i] : max;
	return max;
}

int main()
{
	int size = 0;
	cin>>size;
	if(size >=3 && size<=20)
	{
		int array1[size];
		for(int i=0; i<size; i++)
		cin>>array1[i];
		cout<<Max<int>(array1, size);
	}

	cin>>size;
	if(size >=3 && size<=20)
	{
		double array2[size];
		for(int i=0; i<size; i++)
		cin>>array2[i];
		cout<<Max<double>(array2, size);
	}
	cin>>size;
	if(size >=3 && size<=20)
	{

		string array3[size];
		for(int i=0; i<size; i++)
			cin>>array3[i];
		cout<<Max<string>(array3, size);

	}
	return 0;
}

/*

5
78 96 -12 52 856
6
3.2 5.6 89.2 -3.2 46.2 63.47
5
hello world example virtual char

*/