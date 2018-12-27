#include<iostream>
#include<cmath>
#include<string>
using namespace std;
class Fraction
{
public:
	Fraction(int a, int b=1);
	void print() ;
	Fraction operator+(const Fraction& a) ;		//重载+
	Fraction operator-(const Fraction& a) ;		//重载-
	Fraction operator/(const Fraction& a) ;		//重载/
	Fraction operator*(const Fraction& a) ;		//重载*
	bool operator<(const Fraction& a) ;			//重载<
	bool operator<=(const Fraction& a) ;		//重载<=
	bool operator>(const Fraction& a) ;			//重载>
	bool operator>=(const Fraction& a) ;		//重载>=
	bool operator==(const Fraction& a) ;		//重载==
	void fractionReduction();						//约分（R)
	Fraction reciprocal() ;						//倒数（I）
	int minAllDr(const Fraction& x);			//最小公分母（L）
	int maxSlef();								//最大公因子（G）
	void vulgarFraction();						//化为带分数（M）
private:
	int numerator;  //分子
	int denominator;//分母
	int maxFactor(int nr,int dr);				//最大公约数
};

Fraction::Fraction(int a, int b)
{
	if ((a >= 0 && b>0) || (a <= 0 && b<0)) 
	{
		numerator = abs(a);		
		denominator = abs(b);
	}
	else 
	{ 
		numerator = -abs(a);
		denominator = abs(b);
	}
}
void Fraction::print() 
{
	if (denominator == 1) cout << numerator<<endl;
	else cout << numerator << '/' << denominator << endl;
}
int Fraction::maxFactor(int nr,int br)
{
	int a, b;
	nr > br ? (a = nr, b = br) : (a = br, b = nr);
	if (a%b == 0)return b;
	else return maxFactor(b, a%b);
}
void Fraction::fractionReduction()
{
	int a = maxFactor(abs(numerator),abs(denominator));
	if (a > 1)
	{
		numerator /= a;
		denominator /= a;
	}
}
Fraction Fraction::operator+(const Fraction& x) 
{
	Fraction a = Fraction(numerator*x.denominator + denominator * x.numerator, denominator*x.denominator);
	a.fractionReduction();
	return a;
}
Fraction Fraction::operator-(const Fraction& x) 
{
	Fraction a = Fraction(numerator*x.denominator - denominator * x.numerator, denominator*x.denominator);
	a.fractionReduction();
	return a;
}
Fraction Fraction::operator*(const Fraction& x) 
{
	Fraction a = Fraction(numerator*x.numerator, denominator*x.denominator);
	a.fractionReduction();
	return a;
}
Fraction Fraction::operator/(const Fraction& x) 
{
	Fraction a = Fraction(numerator*x.denominator, denominator*x.numerator);
	a.fractionReduction();
	return a;
}
Fraction Fraction::reciprocal()
{
	Fraction a = Fraction(denominator, numerator);
	return a;
} 
bool Fraction::operator<(const Fraction& x)
{
	return(numerator*x.denominator < denominator*x.numerator);
}
bool Fraction::operator<=(const Fraction& x)
{
	return(numerator*x.denominator <= denominator*x.numerator);
}
bool Fraction::operator>(const Fraction& x)
{
	return(numerator*x.denominator >= denominator*x.numerator);
}
bool Fraction::operator>=(const Fraction& x)
{
	return(numerator*x.denominator >= denominator*x.numerator);
}
bool Fraction::operator==(const Fraction& x)
{
	return(numerator*x.denominator == denominator*x.numerator);
}
int Fraction::minAllDr(const Fraction& x)
{
	int a = denominator, b = x.denominator;
	return maxFactor(a, b);
}
int Fraction::maxSlef()
{
	int a = maxFactor(abs(numerator), abs(denominator));
	return a;
}
void Fraction::vulgarFraction()
{	int a = numerator / denominator;
	int b = numerator - denominator * a;
	if (numerator == 0) cout << 0 << endl;
	else if(abs(numerator)<denominator) this->print();
	else if (b == 0) cout << a << endl;
	else cout << a << '+' << b << '/' << denominator << endl;
}
int main()
{
	int a[6];
	char b[5];
	while (cin >> a[0]>>b[0]>>a[1]>>b[1])
	{
		Fraction num1(a[0], a[1]);
		switch (b[1])
		{
		case'I':num1.reciprocal().print(); break;
		case'M':num1.vulgarFraction(); break;
		case'R':num1.fractionReduction(); num1.print(); break;
		case'G':cout<<num1.maxSlef(); break;
		case'L': {cin >> a[2] >> b[2] >> a[3];
			Fraction num2(a[2], a[3]);
			cout << num2.minAllDr(num1); }break;
		case'+': {cin >> a[2] >> b[2] >> a[3];
			Fraction num2(a[2], a[3]);
			(num1 + num2).print(); } break;
		case'-': {cin >> a[2] >> b[2] >> a[3];
			Fraction num2(a[2], a[3]);
			(num1 - num2).print(); }break;
		case'*': {cin >> a[2] >> b[2] >> a[3];
			Fraction num2(a[2], a[3]);
			(num1 * num2).print(); }break;
		case'/': {cin >> a[2] >> b[2] >> a[3];
			Fraction num2(a[2], a[3]);
			(num1 / num2).print(); } break;
		case'>': {cin >> a[2] >> b[2] >> a[3];
			Fraction num2(a[2], a[3]);
			cout << (num1 > num2); } break;
		case'<': {cin >> a[2] >> b[2] >> a[3];
			Fraction num2(a[2], a[3]);
			cout << (num1 < num2); }break;
		case'=': {cin >> a[2] >> b[2] >> a[3];
			Fraction num2(a[2], a[3]);
			cout << (num1 == num2); }break;
		}
	}
}