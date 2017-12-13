/**************************************
 > File Name: Quote.cpp
 > Author: xhx1993
 > Created Time: 日  5/ 7 23:17:46 2017
**************************************/

#include <iostream>
using namespace std;


class Quote
{
public:
	Quote() = default;
	Quote(const std::string &book, double sales_price):
		bookNo(book), price(sales_price) {}
	std::string isbn() const { return bookNo; }

	virtual double net_price(std::size_t n) const
	{
		return n * price;
	}
	virtual ~Quote(){
	}
	virtual void Test() {
		cout << "Base Test" << endl;
	}
private:
	std::string bookNo;

protected:
	double price = 0.0;
};

class Bulk_quote: public Quote
{
public:
	Bulk_quote() = default;
	Bulk_quote(const std::string&, double, std::size_t, double);
	double net_price(std::size_t) const override {return 0.0;}
	~Bulk_quote() {
		cout << "Bulk_quote Destructor" << endl;
	}
	void Test() override {
		cout << "Bulk_quote Test" << endl;
	}
private:
	std::size_t min_qty = 0;
	double discount = 0.0;
};

class Dirved_quote: public Bulk_quote
{
public:
	~Dirved_quote() {
		cout << "Dirved_quote Destructor" << endl;
		this->Test();
	}
	double net_price(std::size_t) const override {return 0.0;}
	void Test() override {
		cout << "Dirved_quote Test" << endl;
	}
};

int main()
{
	//析构时，先执行继承类最底层的析构，然后在往父类上
	Quote *p=nullptr;
	{
		p = new Dirved_quote;
		delete p;
	}
	cout << "------------" << endl;
	{
		p = new Bulk_quote;
		delete p;
	}
	cout << "------------" << endl;
	return 0;
}

