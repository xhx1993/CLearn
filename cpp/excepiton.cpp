/**************************************
 > File Name: excepiton.cpp
 > Author: xhx1993
 > Created Time: 一  4/10 23:23:43 2017
**************************************/

#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
	int i,j;
	while (cin >> i >> j) {
		try {
			if (i == j) {
				throw runtime_error("i Equal to j");
			} else {
				printf("%d != %d",i,j);
			}
		} catch (runtime_error err) {
			cout << err.what()
				<< "\nTry Again? Enter y or n" << endl;
			char c;
			cin >> c;
			if (!cin || c == 'n')
				break;
		}
	}
	return 0;
}
