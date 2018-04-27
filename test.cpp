#include <iostream>

using namespace std;

template <class T>
class CArray
{
  private:
    T *data;      // 数据区首地址
    int size;       // 数组元素个数
  public:
    CArray(int n=100);   //构造函数
    CArray(const CArray &v);  //拷贝构造函数
    ~CArray() { delete []data; }  //析构函数
    void copy(const CArray &v);   //数组复制
    T &operator[](int i);  //为CArray类重载[]运算符
    void show();  //输出数组元素
};

template<class T>
CArray<T>::CArray(int n)
{
	size = n;
	data = new T[size];
	for(int i=0; i<size; i++)
		data[i] = 0;
}

template<class T>
CArray<T>::CArray(const CArray<T> &v)
{
	data = new T[v.size];
	for(int i=0; i<v.size; i++)
		data[i] = v.data[i];
	size = v.size;
}

template<class T>
void CArray<T>::copy(const CArray<T> &v)
{
	if(NULL != data)
		delete[] data;
	data = new T[v.size];
	for(int i=0; i<v.size; i++)
		data[i] = v.data[i];
	size = v.size;
}

template<class T>
T & CArray<T>::operator[](int i)
{
	return data[i];
}

template<class T>
void CArray<T>::show()
{
	for(int i=0; i<size; i++)
	{
		cout<<data[i];
		if(i != size - 1)
			cout<<' ';
	}
	cout<<endl;
}

//T是类型参数，补充完成各成员函数的定义，主函数设计如下：
int main()
{
  CArray<int> a(10);
  CArray<int>b(a);
  CArray<int>c;
  int i;
    for(i=0; i<10; i++) a[i]=1000+i;  //重载的[]
    a.show();  //输出数组a中的每个元素
    b.show();
    c.copy(a);  //将a复制给c
    c.show();
    return 0;
}