/**************************************
 > File Name: algorithm.cpp
 > Author: xhx1993
 > Created Time: 三  4/26 22:38:11 2017
**************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <numeric>
#include <iterator>
#include <functional>
using namespace std;
using namespace std::placeholders;

void PrintVec(vector<int> &);
void PrintVecStr(vector<string> &);
void PrintList(list<int> &);
void elimDups(vector<string> &words);
bool isShorter(const string &s1, const string &s2);
bool check_size(const string &s, string::size_type sz);

int main()
{
	vector<int> vec={1,4,2,-3,4,5};
	int val = 4;
	//result 是一个迭代器
	auto result = find(vec.cbegin(), vec.cend(), val);
	cout << "The value " << val
		<< (result == vec.cend() ? " is not present" : " is present") << endl;

	auto num1 = count(vec.cbegin(), vec.cend(), val);
	cout << num1 << " " << val << " in vec" << endl;

	int sum = accumulate(vec.cbegin(), vec.cend(), 0);
	cout << "Sum: " << sum << endl;
	
	list<int> list1={1,4};
	auto bEqual=equal(list1.cbegin(), list1.cend(), vec.cbegin());
	cout << (bEqual == true ? "Equal" : "Not Equal") << endl;

//	fill(vec.begin(), vec.end(), 0);
//	fill_n(vec.begin(), vec.size(), 1);
	PrintVec(vec);

	//插入迭代器
	vector<int> vec2;
	fill_n(back_inserter(vec2), 3, 8);
	PrintVec(vec2);
int a1[] = {0, 1, 2, 3, 4}; int a2[sizeof(a1)/sizeof(*a1)]; auto ret = copy(begin(a1), end(a1), a2); list<int> list2={1,2,3,4};
	replace(list2.begin(), list2.end(), 1, 42);
	PrintList(list2);
	vector<int> replace_result;
	cout << "-------------------" << endl;
	replace_copy(list2.cbegin(), list2.cend(), back_inserter(replace_result), 42, 1);
	PrintVec(replace_result);
	cout << "-------------------" << endl;

	vector<string> words = {"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};
	elimDups(words);

	stable_sort(words.begin(), words.end(),
			[] (const string &a, const string &b)
			{ return a.size() < b.size(); });

	int sz = 9;
	auto f = [sz] (const string &a) { return a.size() >= sz; };
	cout << f("hello") << endl;

	transform(vec.begin(), vec.end(), vec.begin(),
			[](int i) { if (i < 0) return -i; else return i; });
	PrintVec(vec);
	
	//类似Functor
	auto check6 = bind(check_size, _1, 6);
	//remove并不会真的删除
	remove(vec.begin(),vec.end(), 3);
	remove_if(vec.begin(), vec.end(),[](int value) { return value%2; });
	reverse(vec.begin(),vec.end());
	PrintVec(vec);

	list<int> lTest = {2, 1, 3, 4, 5, 6, 7};
	list<int> lTest2 = {1, 8, 9};
	lTest.merge(lTest2,[](int a, int b){ return a>b;});
//	lTest.remove(1);
//	lTest.remove_if([](int a) { return a%2; });
	lTest.reverse();
	lTest.sort();
	lTest.unique();
	for (auto v: lTest)
		cout << v << " ";
	cout << endl;
	return 0;
}

bool check_size(const string &s, string::size_type sz)
{
	return s.size() >= sz;
}

void elimDups(vector<string> &words)
{
	PrintVecStr(words);
	sort(words.begin(), words.end());
	PrintVecStr(words);
	auto end_unique = unique(words.begin(), words.end());
	words.erase(end_unique, words.end());
	PrintVecStr(words);
	stable_sort(words.begin(), words.end(), isShorter);
	PrintVecStr(words);
}

bool isShorter(const string &s1, const string &s2)
{
	return s1.size() < s2.size();
}

#define PRINT \
	for (auto value: vec) \
		cout << value << " "; \
	cout << endl;

void PrintList(list<int> &vec)
{
	PRINT
}

void PrintVecStr(vector<string> &vec)
{
	PRINT
}

void PrintVec(vector<int> &vec)
{
	PRINT
}

void biggies(vector<string> &words, vector<string>::size_type sz)
{
	elimDups(words);
	stable_sort(words.begin(), words.end(),
			[](const string &a, const string &b)
			{ return a.size() < b.size();});
	auto wc = find_if(words.begin(), words.end(),
			[sz](const string &a) 
			{ return a.size() >= sz; });
	auto count = words.end() - wc;
	cout << count << " " << "wrods of length " << sz << " or longer" << endl;
	for_each(wc, words.end(),
			[](const string &a) { cout << a << " ";} );
	cout << endl;
}
