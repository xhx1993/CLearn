/**************************************
 > File Name: mapset.cpp
 > Author: xhx1993
 > Created Time: 一  5/ 1 21:03:32 2017
**************************************/

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;


int main()
{
	map<string, size_t> word_count;
	set<string> exclude = {"The", "But", "And"};
	string word;
	while (0 && cin >> word)
		//set find
		if (exclude.find(word) == exclude.end())
			++word_count[word];
	for (const auto &w: word_count)
		//map pair ==> first, second
		cout << w.first << " occurs " << w.second << ((w.second > 1) ? " times " : " time") << endl;


	vector<int> ivec;
	for (vector<int>::size_type i = 0; i != 10; ++i) {
		ivec.push_back(i);
		ivec.push_back(i);
	}
	set<int> iset(ivec.cbegin(), ivec.cend());
	multiset<int> miset(ivec.cbegin(), ivec.cend());
	cout << ivec.size() << endl;
	cout << iset.size() << endl;
	cout << miset.size() << endl;

	map<string,size_t> word_count1;
	while (0 && cin >> word)
	{
		auto ret = word_count1.insert({word, 1});
		if (!ret.second)
			++ret.first->second;
	}

	multimap<string, string> authors;
	authors.insert({"Barth, John", "Sot-Weed Factor"});
	authors.insert({"Barth, John", "Lost in the Funhouse"});

	//元素不存在，会自动生成一个
	map<string, size_t> word_count2;
	word_count2["Anna"] = 1;
	for (auto v : word_count2)
		cout << v.first << " --> " << v.second << endl;

	if (word_count2.find("Anna") == word_count2.end())
		cout << "foobar is not in the map" << endl;

	string search_item("Barth, John");
	auto entires = authors.count(search_item);
	auto iter = authors.find(search_item);
	while (entires) {
		cout << iter->second << endl;
		//多个相同关键字会相邻存储
		++iter;
		--entires;
	}

	//查找一个允许重复的容器内，某个关键字的所有元素
	for (auto beg = authors.lower_bound(search_item),
			end = authors.upper_bound(search_item);
			beg != end; ++beg)
		cout << beg->second << endl;

	cout << "-------------------------" << endl;
	for (auto pos = authors.equal_range(search_item);
			pos.first != pos.second; ++pos.first)
		cout << pos.first->second << endl;
	return 0;
}
