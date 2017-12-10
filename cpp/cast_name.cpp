/**************************************
 > File Name: test1.cpp
 > Author: xhx1993
 > Created Time: 一  4/10 22:21:24 2017
**************************************/

#include <iostream>
using namespace std;
/*
int main() {
	int ival = 3.541 + 3;
	printf("%d\n",ival);
	printf("%d\n",int(ival));
	return 0;
}
*/

class Base {
public:
	virtual int test1(){
		printf("test1\n");
		return 0;
	}
	int test2(){
		printf("test2\n");
		return 0;
	}
};

class Derived:public Base{
public:
	int test1() {
		printf("derived test1\n");
		return 0;
	}
	int test2() {
		printf("derived test2\n");
		return 0;
	}
};

int main(){
	int d = 10;
	void *p = &d;
	//任何具有明确定义的类型转换，只要不包含底层const，都可以使用static_cast
	double *dp = static_cast<double *>(p);
	double *dp2 = (double *)p;
	
	//const_cast只能改变运算对象的底层const(去掉const性质)
	const char *pc;
	char *p8 = const_cast<char *>(pc);
	
	//dynamic_cast 动态类型转换(RIIT);适用于没有虚函数，但是基类指针想使用派生类函数
	Base b =Base();
	Base *dpBase = &b;
	if (Derived *dp1 = dynamic_cast<Derived *>(dpBase))
	{
		dp1->test2();
	} else {
		dp1->test2();
	}

	//reinterpret_cast为运算对象的位模式提供较低层次上的重新解释
	int *ip;
	char *pcc = reinterpret_cast<char *>(ip);
	return 0;
}
