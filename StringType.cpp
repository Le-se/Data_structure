#include<iostream>
#include<assert.h>
#include<string.h>
using namespace std;
class StringType {
private:
	char*  myStorage; //存放字符串的空间的起始位置,动态数组
	unsigned Storlen;  //空间大小
public:
	//构造
	StringType();    //空串
	StringType(unsigned); //指定长度串（无值）
	StringType(char c);//指定字符
	StringType(const char * initstr);//给定字符数组
	StringType(const StringType&); //给定值串-StringType类型的字符串

	void operator = (const StringType& right); //赋值
	void operator +=(const StringType& right); //连接
	int compare(const StringType& right) const; //比较
	int find(const StringType& pattern);
	char& operator[ ](unsigned index) const;//下标访问
	unsigned length() const;  //求串长
	istream& getline(istream&); //按行读入
	operator const char* () const; //转换成C/C++表示的字符串
	~StringType();  //  析构
};
//-------------------------------------------------------作业
StringType::StringType(const StringType& c)
{
	Storlen = c.length()+1;
	myStorage = new char[Storlen];
	strcpy(myStorage, c.myStorage);
}
void StringType::operator=(const StringType& right)
{
	if (this == &right) return;
	delete[] myStorage;
	Storlen = right.length()+1;
	myStorage = new char[Storlen];
	strcpy(myStorage, right.myStorage);
}
void StringType::operator +=(const StringType& right)
{
	int sumLen = length() + right.length() ;
	char* temStr = new char[sumLen + 1];
	int i = 0, j = 0;
	for (; i < length(); i++)
		temStr[i] = myStorage[i];
	for (; j < right.length; i++,j++)
		temStr[i] = right.myStorage[j];
	temStr[i] = '\0';
	delete[] myStorage;
	myStorage = new char[sumLen + 1];
	strcpy(myStorage, temStr);
	Storlen = sumLen + 1;
	delete[] temStr;
}
char& StringType::operator[ ](unsigned index) const 
{
	if (index > Storlen - 1) return myStorage[Storlen - 1];
	return myStorage[index];
}
int StringType::compare(const StringType& right) const
{
	return strcmp(myStorage, right.myStorage);
}
istream& StringType::getline(istream& in)
{
	int i = 0, count = 10;
	char* temp1 = new char[count];
	while (in >> temp1[i])
	{
		if (temp1[i] == '\n') break;
		if (i + 1 == count)
		{
			count *= 2;
			char* temp2 = new char[count];
			strcpy(temp2,temp1);
			delete[] temp1;
			temp1 = new char[count];
			strcpy(temp1, temp2);
			delete[] temp2;
		}
		i++;
	}
	temp1[i] = '\0';
	myStorage = new char[i+1];
	strcpy(myStorage, temp1);
	delete[] temp1;
	Storlen = i+1;
	return in;
}

StringType::~StringType()
{
	delete[] myStorage;
	Storlen = 0;
}
StringType::operator const char* () const
{
	return myStorage;
}
//-------------------------------------------------------作业
int operator<=(const StringType &left, const StringType & right);//比较
StringType::StringType()
{
	int Storlen = 1;
	myStorage = new char[Storlen];
	assert(myStorage != 0); //  # include<assert.h>
	myStorage[0] = '\0';
}   //空串
StringType::StringType(unsigned size)
{
	int Storlen = size;
	myStorage = new char[size];
	assert(myStorage != 0); //  # include<assert.h>
	for (unsigned i = 0; i<Storlen; i++)  myStorage[i] = '\0';
}   //给定长度的串
StringType::StringType(char c)
{
	int Storlen = 2;
	myStorage = new char[Storlen];
	assert(myStorage != 0); //  # include<assert.h>
	myStorage[0] = c;
	myStorage[1] = '\0';
}   //给定值的串-字符
StringType::StringType(const char * initstr)
{
	unsigned i = 0;
	int Storlen = 1 + strlen(initstr);
	myStorage = new char[Storlen];
	assert(myStorage != 0); //  # include<assert.h>
	for (; i<Storlen - 1; i++)  myStorage[i] = initstr[i];
	myStorage[i] = '\0';
}   //给定值的串-c/c++表示
unsigned StringType::length() const
{
	unsigned len = 0;
	for (; myStorage[len] != '\0'; len++);
	return len;
}   //求C++表示的字符串的字面长度。
int operator<=(const StringType&left, const StringType& right)
{
	return left.compare(right) <= 0;
}
int StringType::find(const StringType& pattern)
{
	int patlen = pattern.length();
	int last =this->length() - patlen; //最后一个可能匹配位置  
	int pos = 0;
	for (; pos <= last; pos++)
	{
		StringType t(myStorage, pos, patlen);
		if (pattern == t) return pos;
	} //找到匹配位置返回
	pos = -1; // 找不到匹配位置
	return pos;
}
