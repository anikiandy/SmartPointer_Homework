#include <iostream>
#include "smart_ptr.h"

int main()
{
	int* p{ new int { 42 } };
	//int *x;

	smart_ptr <int> test = smart_ptr<int>(p);
	smart_ptr <int> test2 = test;
	std::cout << "p: " << *p << std::endl;
	std::cout << "test: " << test.getVal() << std::endl;
	std::cout << "refcount: " << test.ref_count() << std::endl;
	return 0;
}