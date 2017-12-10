/**************************************
 > File Name: copyctrl.cpp
 > Author: xhx1993
 > Created Time: 三  5/ 3 22:58:10 2017
**************************************/

#include <iostream>
#include <string>
using namespace std;

class Sales_data {
public:
	Sales_data():bookNo(""),units_sold(0),revenue(0)
	{
		cout << "Sales_data Default Constructor" << endl;
	}
	Sales_data(const Sales_data&);
	Sales_data& operator=(const Sales_data &rhs)
	{
		cout << "Sales_data == Operator " << endl;
		bookNo = rhs.bookNo;
		units_sold = rhs.units_sold;
		revenue = rhs.revenue;
		return *this;
	}

	~Sales_data()
	{
		cout << "Sales_data Destructor" << endl;
	}

private:
	std::string bookNo;
	int units_sold = 0;
	double revenue = 0.0;
};

Sales_data::Sales_data(const Sales_data &orig):
	bookNo(orig.bookNo), units_sold(orig.units_sold), revenue(orig.revenue) 
{
	cout << "Sales_data Copy Constructor" << endl;
}

Sales_data& test1(Sales_data &data)
{
	return data;
}

int main()
{
	/*
	Sales_data item;
	Sales_data item2=item;
	Sales_data item3(item);
	Sales_data item4;
	item4=item;
	*/
	Sales_data item;
	Sales_data item2;
	item2=test1(item);
	return 0;
}
