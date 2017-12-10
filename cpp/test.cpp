/*************************************
 > File Name: test.cpp
 > Author: xhx1993
 > Created Time: 六  4/15 21:15:29 2017
**************************************/

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <stack>
using namespace std;


int main() {
	list<int> a={1,2,3,4,5};
	vector<int> vec(a.begin(),a.end());

	list<string> names;
	vector<const char *> oldstyle;
	names.assign(oldstyle.cbegin(), oldstyle.cend());

	vector<int> vec1(10,1);
	vector<int> vec2(8,2);
	swap(vec1,vec2);
	cout << "vec1.size():" << vec1.size() << endl;
	cout << "vec2.size():" << vec2.size() << endl;

	stack<int> intStack;
	for (size_t ix = 0; ix != 10; ++ix)
		intStack.push(ix);
	while (!intStack.empty()) {
		int value = intStack.top();
		cout << "Value:" << value << endl;
		intStack.pop();
	}
	
	int i = 1;
	const int &r3 = i * 42;
	return 0;
}
