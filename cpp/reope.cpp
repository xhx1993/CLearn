/**************************************
 > File Name: reope.cpp
 > Author: xhx1993
 > Created Time: 四  5/ 4 23:25:13 2017
**************************************/

#include <iostream>
#include <functional>
#include <string>
#include <map>
using namespace std;

class CTest
{
friend ostream &operator<<(ostream&, const CTest &);
friend istream &operator>>(istream&, CTest &);
friend CTest operator+(const CTest &, const CTest &);
friend bool operator==(const CTest &, const CTest &);
public:
	CTest():a(0){}
	CTest(int aa):a(aa) {}
	void Print(){
		cout << a << endl;
	}
	CTest operator+=(const CTest &);
	int GetValue() const {
		return a;
	}
private:
	int a;
};

CTest operator+(const CTest &t1, const CTest &t2)
{
	CTest sum = t1;
	sum += t2;
	return sum;
}

bool operator==(const CTest &t1, const CTest &t2)
{
	return t1.a == t2.a;
}

bool operator!=(const CTest &t1, const CTest &t2)
{
	return !(t1==t2);
}

CTest CTest::operator+=(const CTest &t2)
{
	a+=t2.a;
	return *this;
}

ostream &operator<<(ostream &os, const CTest &t)
{
	os << "CTest << " << t.a;
	return os;
}

istream &operator>>(istream &is, CTest &t)
{
	int value;
	is >> value;
	if (is)
		t.a=value;
	return is;
}

int add(int a, int b)
{
	return a + b;
}

struct divide
{
	int operator()(int a, int b)
	{
		if (b == 0)
			return 0;
		return a / b;
	}
};

int main()
{
	CTest a(5);
	CTest b(5);
	CTest c(3);
	cout << (a == b) << endl;
//	cin >> c;
	cout << "Value: " << a + b + c << endl;
	cout << a << endl;

	auto mod = [](int i, int j) { return i % j; };
	map<string,function<int(int, int)>> binops = {
		{"+", add},
		{"-", std::minus<int>()},
		{"/", divide()},
		{"*", [](int i, int j) { return i * j; }},
		{"%", mod}
	};
	function<int(int, int)> f1 = add;
	function<int(int, int)> f2 = divide();
	function<int(int, int)> f3 = [](int i, int j) { return i * j; };

	cout << f1(4, 2) << endl;
	cout << f2(4, 2) << endl;
	cout << f3(4, 2) << endl;

	printf("----------------map<string,function<int(int, int)>>---------\n");
	cout << binops["+"](10, 5) << endl;
	cout << binops["-"](10, 5) << endl;
	cout << binops["/"](10, 5) << endl;
	cout << binops["*"](10, 5) << endl;
	cout << binops["%"](10, 5) << endl;
	
	return 0;
}
