#include<stack>
#include<iostream>
#include<string>
#include<stdlib.h>
#include<cctype>

using namespace std;

int getPriority(char ch)//获取运算符优先级  
{	
	if (ch == '(') return 1;
	else if (ch == '+' || ch == '-') return 2;
	else if (ch == '*' || ch == '/') return 3;
	else return 4;
}

void calculate(stack<double> &mynum, char operation)//两个数字的计算方法
{
	double num1,num2,num3;
	num2= mynum.top();
	mynum.pop();
	num1 = mynum.top();
	mynum.pop();
	switch (operation)
	{
	case '+':num3 = num1 + num2; break;
	case '-':num3 = num1 - num2; break;
	case '*':num3 = num1 * num2; break;
	case '/':num3 = num1 / num2; break;
	default:break;
	}
	mynum.push(num3);
}

double calculator(string str)//计算中缀表达式（不考虑非法输入）
{
	int i = 0, j;
	stack<double> stackNum;
	stack<char> stackOperation;
	int size = str.length();
	char tempOperation;
	string tempNum;
	while (i < size)
	{
		if (isdigit(str[i]))//取出数字
		{
			j = i;
			while (j < size && (isdigit(str[j]) || str[j] == '.')) 
				j++;
			tempNum = str.substr(i, j - i);
			stackNum.push(atof(tempNum.c_str()));//将字符串形式的数字转化为double型
			i = j;
		}
		else if (str[i] == ' ')
		{
			i++;//忽略空格
		}
		else if(str[i] == '+'|| str[i] == '-'|| str[i] == '*'|| str[i] == '/')//基础运算
		{
			if (stackOperation.empty()) 
				stackOperation.push(str[i]);
			else 
			{
				while (!stackOperation.empty() )
				{
					tempOperation = stackOperation.top();//比较栈顶与当前运算符的优先级
					if (getPriority(tempOperation) >= getPriority(str[i]))
					{
						calculate(stackNum, tempOperation);//当前运算符优先级低，则弹出前两个数字和一个运算符，进行运算
						stackOperation.pop();
					}
					else break;
				}
				stackOperation.push(str[i]);//运算结束后压入当前运算符
			}
			i++;//（运算光标）向后
		}
		else if (str[i] == '(' || str[i] == ')')//括号
		{
			if (str[i] == '(') stackOperation.push(str[i]);
			else 
			{
				while (stackOperation.top() != '(')
				{
					tempOperation = stackOperation.top();
					calculate(stackNum, tempOperation);//进行运算
					stackOperation.pop();
				}
				stackOperation.pop();//括号内部计算完毕后删除左括号
			}
			i++;//（运算光标）向后
		}
	}
	while (!stackOperation.empty()) //遍历完后计算容器里剩余的数字
		{
			tempOperation = stackOperation.top();
			calculate(stackNum, tempOperation);//进行运算
			stackOperation.pop();
		}
	return stackNum.top();
}
int main()
{	
	string a;
	double result;
	a = " 7 * 8 - ( 2 + 3 )";
	result = calculator(a);
	cout << "例子 \" 7 * 8 - (2 + 3)\"的值为:" << result << endl;
	a = "1.2 + (3.3 * 5 + 2.5) / 1.2";
	result = calculator(a);
	cout << "例子 \"1.2 + (3.3 * 5 + 2.5) / 1.2\"的值为:" << result << endl;
	cout << "请输入你想计算的的中缀表达式（运算符需要英文格式）\n输入\"##\"停止计算\n";
	while (getline(cin,a) && a != "##")
	{
		result = calculator(a);
		cout << "计算结果为：" << result << endl;
	}

}