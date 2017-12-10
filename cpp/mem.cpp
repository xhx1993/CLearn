/**************************************
 > File Name: mem.cpp
 > Author: xhx1993
 > Created Time: 二  5/ 2 22:54:27 2017
**************************************/

#include <iostream>
#include <memory>
#include <vector>
#include <string>
using namespace std;


class StrBlob {
public:
	typedef std::vector<std::string>::size_type size_type;
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }

	void push_back(const std::string &t) {
		data->push_back(t);
	}
	void pop_back();

	std::string& front();
	std::string& back();

private:
	std::shared_ptr<vector<string>> data;
	void check(size_type i, const string &msg) const;
};

StrBlob::StrBlob(): data(make_shared<vector<string>>()) {}
StrBlob::StrBlob(initializer_list<string> il):
	data(make_shared<vector<string>>(il)) {}

void StrBlob::check(size_type i, const string &msg) const
{
	if (i >= data->size())
		throw out_of_range(msg);
}

string& StrBlob::front()
{
	check(0, "front on empty StrBlob");
	return data->front();
}

string& StrBlob::back()
{
	check(0, "back on empty StrBlob");
	return data->back();
}

void StrBlob::pop_back()
{
	check(0, "pop_back on empty StrBlob");
	data->pop_back();
}


int main()
{
	shared_ptr<int> p1 = make_shared<int>(42);
	shared_ptr<string> p2 = make_shared<string>(10, '9');
	shared_ptr<int> p5 = make_shared<int>();

	auto p6 = make_shared<vector<string>>();
	
//	指定回调函数，在异常时也可以释放资源
//	connection c = connection(&d);
//	shared_ptr<connection> p(&c, end_connection);

	vector<int> vi(10,20);
	allocator<int> alloc;
	auto p = alloc.allocate(vi.size() * 2);
	auto q = uninitialized_copy(vi.begin(), vi.end(), p);
	uninitialized_fill_n(q, vi.size(), 42);
	for (int i = 0; i < vi.size() * 2; i++)
		cout << p[i] << endl;
}
