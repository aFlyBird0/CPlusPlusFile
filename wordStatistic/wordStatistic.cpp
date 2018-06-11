/*

编写人：李鹤鹏
编写时间：2018/06/11 ~ 2018/06/
功能：1.逐个拆分单词
	  2.统计词频并显示

*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <list>
#include <string>

using namespace std;

class Word
{
public:
	Word(){word = ""; time = 0;};
	Word(char *w, int t):word(w),time(t){};
	~Word(){};

protected:
	string word;
	int time;
};

int main()
{
	list<Word> statistic;	//用来统计单个单词
	list<string> article;	//用来存放文章每个分离的单词
	list<string> ignore;	//用来存放忽略单词
	ifstream fRead;
	fRead.open("input.txt");
	char ch = fRead.get();
	int flag = 0;
	ostringstream word;
	while( ch != EOF)
	{
		if(flag == 0)
		{
			if(ch >= 'A' && ch <= 'Z')
			{
				flag = 1;
				word<<char(ch - 'A' + 'a');	//转换成小写存入字符流
			}
			else if(ch >= 'a' && ch <= 'z')
			{
				flag = 1;
				word<<ch;
			}
		}
		else
		{
			if(ch >= 'A' && ch <= 'Z')
			{
				flag = 1;
				word<<char(ch - 'A' + 'a');	//转换成小写存入字符流
			}
			else if(ch >= 'a' && ch <= 'z')
			{
				flag = 1;
				word<<ch;
			}
			else
				//遇到非字母，单词结束
			{
				flag = 0;
				article.push_back(word.str());	//存入链表
				word.flush();
			}
		}
		ch = fRead.get();
	}
	fRead.close();
	copy(article.begin(), article.end(), ostream_iterator<string>(cout, " "));
		cout<<endl;
	return 0;
}