/*
编写人：李鹤鹏
编写日期：2018/04/20
功能：矩阵模板
	1.用一维数组进行矩阵初始化
	2.矩阵相加，相减，相乘
	3.利用重载实现类似于二维数组访问效果
	4.实现矩阵转置
	5.矩阵初等行变换:a.交换两行
					b.某一行乘不为0的数
					c.某一行乘k加到另一行上去
*/

#include <iostream>
#include <iomanip>
#include <cassert>
using namespace std;


template<class T>
class Matrix
{
public:
	Matrix();
	Matrix(int rowNew, int colNew);
	Matrix(T listNew[], int rowNew, int colNew);
	Matrix(const Matrix<T>& rhs);
	Matrix<T>& operator = (const Matrix<T>& rhs);//赋值重载
	Matrix<T> transpose()const;	//矩阵转置
	friend ostream& operator<< (ostream& out, const Matrix<T>& rhs)
	{
		for(int i=0; i<rhs.row; i++)
		{
			for(int j=0; j<rhs.col; j++)
			{
				cout<<setw(4)<<rhs.list[i * rhs.col + j];
					//输出并对齐
			}
			out<<'\n';
		}
		cout<<endl;
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

	Matrix<T> operator + (const Matrix<T>& rhs);//矩阵加法
	Matrix<T> operator - (const Matrix<T>& rhs);//矩阵减法
	Matrix<T> operator * (const Matrix<T>& rhs);//矩阵乘法

	T* operator[](int number)
	{
		return list + number * col;
		//重载[]返回移动几行的指针，实现二维数组形式访问
	}
	Matrix<T>& swapRow(int row1, int row2);	//交换row1与row2行
	Matrix<T>& multiplyRow(int rowNew, T k);	//row1行乘k倍
	Matrix<T>& multiplyAddRow(int row1, int row2, T k);
											//把row2行乘k加到row1上
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
		list[i] = listNew[i];	//分配空间并且一一复制
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

template<class T>
Matrix<T>& Matrix<T>::operator = (const Matrix<T>& rhs)
{
	if(list == rhs.list)
		return *this
	assert(rhs.row == row && rhs.col == col);
	if(NULL == list)
		list = new T[row * col];
		//因为两个数组长度应该是一样的，所以直接覆盖或新建
	for(int i=0; i<row * col; i++)
		list[i] = rhs.list[i];
	return *this;
}

template<class T>
Matrix<T> Matrix<T>::transpose()const
{
	T listNew[row * col];
	for(int i=0; i<row; i++)
	{
		for(int j=0; j<col; j++)
		{
			listNew[j*row+i] = list[i*col+j];
		}
	}
	return Matrix(listNew, col, row);
}

template<class T>
Matrix<T> Matrix<T>::operator + (const Matrix<T>& rhs)
{
	assert(rhs.row == row && rhs.col == col);
	T listNew[row * col];
	for(int i=0; i<row * col; i++)
		listNew[i] = list[i] + rhs.list[i];
	return Matrix<T>(listNew, row, col);
		//新建数组，一一赋值，返回无名对象
}

template<class T>
Matrix<T> Matrix<T>::operator - (const Matrix<T>& rhs)
{
	assert(rhs.row == row && rhs.col == col);
	T listNew[row * col];
	for(int i=0; i<row * col; i++)
		listNew[i] = list[i] - rhs.list[i];
	return Matrix<T>(listNew, row, col);
		//新建数组，一一赋值，返回无名对象
}

template<class T>
Matrix<T> Matrix<T>::operator * (const Matrix<T>& rhs)
{
	assert(col == rhs.row);	//左矩阵列数与右矩阵行数必须相等
	T listNew[row * rhs.col];
	for(int i=0; i<row; i++)
	{
		for(int j=0; j<rhs.col; j++)
		{
			listNew[i * rhs.col + j] = 0;
			//设初始值为0
			for(int k=0; k<col; k++)
			{
				listNew[i*rhs.col+j] +=
					(list[i*col+k] * rhs.list[k*rhs.col+j]);
					//逐渐累加
			}
		}
	}
	return Matrix(listNew, row, rhs.col);
}

template<class T>
Matrix<T>& Matrix<T>::swapRow(int row1, int row2)
{
	assert(row1>=0 && row1<row && row2>=0 && row2<row);
	int temp;
	for(int i=0; i<col; i++)
	{
		temp = list[row1*col+i];
		list[row1*col+i] = list[row2*col+i];
		list[row2*col+i] = temp;
	}
	return *this;
}

template<class T>
Matrix<T>& Matrix<T>::multiplyRow(int rowNew, T k)
{
	for(int i=0; i<col; i++)
	{
		list[rowNew*col+i] *= k;
	}
	return *this;
}

template<class T>
Matrix<T>& Matrix<T>::multiplyAddRow(int row1, int row2, T k)
{
	for(int i=0; i<col; i++)
	{
		list[row1*col+i] += list[row2*col+i] * k;
	}
	return *this;
}

int main()
{
	Matrix<int> mat1;
	cin>>mat1;
	/*
	3 4
	1 2 3 4
	5 6 7 8
	9 1 2 3
	*/
	Matrix<int> mat2(mat1);
	cout<<mat1;
	cout<<mat2;
	cout<<mat1[1][2]<<endl;
	int listNew[20] = {1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7,8,9,1,2};
	Matrix<int> mat3(listNew, 4, 5);//一维数组初始化
	cout<<mat1 + mat2;	//矩阵相加
	cout<<mat3<<endl;
	cout<<mat1 - mat2;	//矩阵相减
	cout<<mat1 * mat3;	//矩阵相乘
	cout<<mat3.transpose();	//矩阵转置
	cout<<mat3.swapRow(1,2);	//交换第二行与第三行位置
	cout<<mat3.multiplyRow(0,3);	//第一行乘3
	cout<<mat3.multiplyAddRow(0,1,2);//第二行乘2加到第一行
	return 0;
}