/**************************************
 > File Name: template.cpp
 > Author: xhx1993
 > Created Time: 二  5/ 9 08:01:59 2017
**************************************/

#include <iostream>
#include <vector>
#include <list>
using namespace std;

template <typename T, typename Iter>
Iter myfind(Iter pBeg, Iter pEnd, T v)
{
	for (Iter pIter = pBeg; pIter != pEnd; pIter++)
	{
		if (*pIter == v)
			return pIter;
	}
	return pEnd;
}

int main()
{
	vector<int> vecInt = {1,2,3,4,5};
	auto p = myfind(vecInt.begin(), vecInt.end(), 5);
	cout << "Find: " << *p << endl;
	list<int> listInt = {1,2,3,4,5};
	auto pp = myfind(listInt.begin(),listInt.end(), 3);
	cout << "Find: " << *pp << endl;
	return 0;
}
