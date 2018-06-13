
/*

编写人：李鹤鹏
编写时间：2018/06/11 ~ 2018/06/
功能：1.逐个拆分单词
	  2.统计词频并显示,简单可视化

*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <iterator>
#include <list>
#include <map>
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
	map<string, int> statistic;	//用来统计单词词频
	list<string> article;	//用来存放文章每个分离的单词
	list<string> ignore;	//用来存放忽略单词
	ifstream fRead;
	fRead.open("input.txt");
	char ch = fRead.get();
	int flag = 0;
	string word = "";
	while( ch != EOF)
	{
		if(flag == 0)
		{
			if(ch >= 'A' && ch <= 'Z')
			{
				flag = 1;
				word = word + char(ch - 'A' + 'a');	//统一转换成小写
			}
			else if(ch >= 'a' && ch <= 'z')
			{
				flag = 1;
				word = word + ch;
			}
		}
		else
		{
			if(ch >= 'A' && ch <= 'Z')
			{
				flag = 1;
				word= word+char(ch - 'A' + 'a');
			}
			else if(ch >= 'a' && ch <= 'z')
			{
				flag = 1;
				word = word + ch;
			}
			else
				//遇到非字母，单词结束
			{
				flag = 0;
				article.push_back(word);	//存入链表
				word= "";
			}
		}
		ch = fRead.get();
	}
	fRead.close();
	//copy(article.begin(), article.end(), ostream_iterator<string>(cout, " "));
	//cout<<endl;
    fRead.open("ignore.txt");
	word = "";
	while( fRead>>word )
	{
		for(unsigned int i=0; i<word.size(); i++)
		{
			if(word[i]>='A' && word[i]<='Z')
				word[i] = word[i] - 'A' + 'a';	//全部转换成小写
		}
		ignore.push_back(word);
	}
	fRead.close();
	//copy(ignore.begin(), ignore.end(), ostream_iterator<string>(cout, " "));
	//cout<<endl;
	list<string>::iterator articleIterator;
	list<string>::iterator ignoreIterator;
	map<string,int>::iterator statisticIterator;
	bool isInIgnore = false;
	for(articleIterator = article.begin(); articleIterator!=article.end(); articleIterator++)
	{
		isInIgnore = false;
		for(ignoreIterator = ignore.begin(); ignoreIterator!=ignore.end(); ignoreIterator++ )
		{
			if(*articleIterator == *ignoreIterator)
			{
				isInIgnore = true;
				break;	//如果ignore里面有这个单词就忽略
			}
		}
		if(isInIgnore == false)
		{
			if(statistic.count(*articleIterator) == true)	//存在这个单词
				statistic[*articleIterator] += 1;
			else	//不存在这个单词
				statistic.insert(make_pair(*articleIterator,1));
					//不存在就新添加
		}

	}
	/*
	for(statisticIterator=statistic.begin();statisticIterator!=statistic.end();statisticIterator++)
	{
		cout<<statisticIterator->first<<"\t\t\t"<<statisticIterator->second<<endl;
	}
	*/
	multimap<int, string>multiStatistic;
	//因为没办法直接用sort通过value排序，map默认通过key排序，所以将key与value互换
	for(statisticIterator = statistic.begin();statisticIterator!=statistic.end();statisticIterator++)
	{
	    multiStatistic.insert(pair<int,string>(statisticIterator->second,statisticIterator->first));
	}
	multimap<int, string>::reverse_iterator msi;
		//原来顺序是从低到高，所以用反向迭代器
	for(msi=multiStatistic.rbegin(); msi!=multiStatistic.rend(); msi++)
	{
		cout<<left<<setw(20)<<msi->second<<msi->first<<'\t';
			//因为键值互换，所以先输出了值
		for(int i=0; i<msi->first; i++)
			cout<<"■";
		cout<<endl;
		//出现几次就输出几个方框，简单可视化
	}
		return 0;
	}
