#include<iostream>
using namespace std;

class Term
{
public:
	Term(double a = 0, int b = 0, Term* c = NULL)
	{
		ceof = a;
		expn = b;
		next = c;
	}
private:
	double ceof;//多项式系数
	int expn;//多项式次数
	Term* next;//下一项
	friend class Polynominal;
};

class Polynominal
{
public:
	Polynominal();//构造
	~Polynominal();//析构
	Polynominal(const Polynominal& c);//拷贝构造
	void InputPoly(istream& in);//输入多项式的每一项
	void OutputPoly(ostream& out);//输出多项式的每一项
	bool foundExpn(int exp,Term* &prev);//找这个次数是否存在
	Polynominal operator *(const Polynominal& right);//多项式乘法
	

private:
	Term* first;//多项式首项
};

Polynominal::Polynominal()//构造
{
	 first = new Term();
}
Polynominal::~Polynominal()//析构
{
	while (first->next != NULL)
	{
		Term* temp = first;
		first = first->next;
		delete temp;
	}
	delete first;
	first = NULL;
}
Polynominal::Polynominal(const Polynominal& c)//拷贝构造
{
	if (c.first != NULL)
	{
		Term* p = c.first;
		first = new Term(c.first->ceof,c.first->expn);
		p = p->next;
		Term* pp = first;
		while (p) {
			pp->next = new Term(p->ceof,p->expn);
			p = p->next;
			pp = pp->next;
		}
	}
	else
		first = NULL;
}
void Polynominal::InputPoly(istream& in)//输入
{
	cout << "请依次输入系数和指数的次数，系数和次数同时为0时停止输入。\n";
	Term* prev = first;
	Term* newptr = NULL;
	double ceo;//系数
	int exp;//次数
	for(;;)
	{
		in >> ceo >> exp;		
		if (ceo == 0 && exp == 0)
			break;
		newptr = new Term(ceo, exp);
		prev->next = newptr;
		prev = newptr;

	}
	
}
void Polynominal::OutputPoly(ostream& out)//输出
{
	Term* ptr = first->next;
	if (first->ceof == 0 && first->expn == 0 && first->next == NULL)
	{
		out << 0 << endl;
		return;
	}
	while (ptr != NULL )
	{ 
		out << ptr->ceof<<'x';    
		if (ptr->expn >= 2)      
			out << '^' << ptr->expn;    
		if (ptr->next != 0)      
			out << " + ";    
		ptr = ptr->next; 
	}  
	out << endl;
}
bool Polynominal::foundExpn(int exp,Term* &prev)//找这个次数是否存在
{
	Term* ptr = first->next;
	prev = first;
	while (ptr != NULL && ptr->expn < exp)
	{
		prev = ptr;
		ptr = ptr->next;	
	}
	return(ptr != NULL && ptr->expn == exp);
}
Polynominal Polynominal::operator*(const Polynominal& right)//多项式乘法
{
	Polynominal multPoly;
	Term* ptrleft = first->next;
	Term* ptrright;
	Term* ptrmult = multPoly.first;
	Term* prev = NULL;
	double multceof;//乘出的系数
	int multexpn;//乘出的次数
	while (ptrleft != NULL)
	{
		ptrright = right.first->next;
		while (ptrright != NULL)
		{
			multceof = ptrleft->ceof * ptrright->ceof;
			multexpn = ptrleft->expn + ptrright->expn;
			if (multPoly.foundExpn(multexpn,prev))
			{
				ptrmult = prev->next;
				double addceof = ptrmult->ceof + multceof;
				if (addceof != 0)//系数不为0
					ptrmult->ceof = addceof;
				else
				{
					prev->next = ptrmult->next;
					delete ptrmult;//删除系数为0项
				}
			}
			else
			{
				ptrmult = new Term(multceof, multexpn);
				ptrmult->next = prev->next;
				prev->next = ptrmult;
			}
			ptrright = ptrright->next;
		}
		ptrleft = ptrleft->next;
	}
	return multPoly;
}
int main()
{
	Polynominal left;
	Polynominal right;
	left.InputPoly(cin);
	cout << "您输入的是：";
	left.OutputPoly(cout);
	right.InputPoly(cin);
	cout << "您输入的是：";
	right.OutputPoly(cout);
	cout << "结果是：";
	(left * right).OutputPoly(cout);
}