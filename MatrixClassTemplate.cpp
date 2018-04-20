/*
编写人：李鹤鹏
编写日期：2018/04/20
功能：矩阵模板
*/

#include <iostream>
#include <iomanip>
using namespace std;


template<class T>
class Matrix
{
public:
	Matrix();
	Matrix(int rowNew, int colNew);
	Matrix(T listNew[], int rowNew, int colNew);
	Matrix(const Matrix<T>& rhs);
	friend ostream& operator<< (ostream& out, const Matrix<T>& rhs)
	{
		for(int i=0; i<rhs.row; i++)
		{
			for(int j=0; j<rhs.col; j++)
			{
				cout<<setw(4)<<rhs.list[i * rhs.col + j];
					//输出并对齐
			}
			out<<endl;
		}
		return out;
	}
	friend istream& operator>> (istream& in, Matrix<T>& rhs)
	{
		int rowNew, colNew;
		in>>rowNew>>colNew;
		rhs.row = rowNew;
		rhs.col = colNew;
		if(rhs.list != NULL)
			delete[] rhs.list;	//不为空就释放内存
		rhs.list = new T[rhs.row * rhs.col];
		for(int i=0; i<rhs.row; i++)
			for(int j=0; j<rhs.col; j++)
				in>>rhs.list[i * rhs.col + j];
				//先输入行数以及列数再依次输入数据
		return in;
	}

	T* operator[](int number)
	{
		return list + number * col;
		//重载[]返回移动几行的指针，实现二维数组形式访问
	}
	~Matrix(){delete[] list;};
private:
	int row;	//行数
	int col;	//列数
	T* list;	//矩阵指针
};

template<class T>
Matrix<T>::Matrix()
{
	row = 0;
	col = 0;
	list = NULL;
}

template<class T>
Matrix<T>::Matrix(int rowNew, int colNew)
{
	row = rowNew;
	col = colNew;
	list = NULL;	//默认指向空
}

template<class T>
Matrix<T>::Matrix(T listNew[], int rowNew, int colNew)
{
	row = rowNew;
	col = colNew;
	list = new T[row * col];
	for(int i=0; i<row * col; i++)
	{
		listNew[i] = list[i];	//分配空间并且一一复制
	}
}

template<class T>
Matrix<T>::Matrix(const Matrix<T>& rhs)
{
	row = rhs.row;
	col = rhs.col;
	list = new T[row * col];
	for(int i=0; i<row * col; i++)
	{
		list[i] = rhs.list[i];	//分配空间并且一一复制
	}
}

int main()
{
	Matrix<int> mat1;
	cin>>mat1;
	cout<<mat1;
	cout<<mat1[1][2];
	return 0;
}