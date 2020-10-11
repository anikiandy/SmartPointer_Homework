#include <iostream>
#include "smart_ptr.h"

int main()
{
	int* p{ new int { 42 } };
	//int *x;

	//makes test smart pointer based on raw pointer p
	smart_ptr <int> test = smart_ptr<int>(p);

	std::cout << "p: " << *p << std::endl; //prints out int p
	std::cout << "test: " << test.getVal() << std::endl; //value of test smart_pointer
	std::cout << "refcount: " << test.ref_count() << std::endl; //ref count for test (should be 1)

	smart_ptr <int> test2 = std::move(test);//test 2 pointer should replace test smart ptr

	std::cout << "p: " << *p << std::endl; //prints out int p
	std::cout << "test2: " << test2.getVal() << std::endl; //value of test smart_pointer
	std::cout << "refcount2: " << test2.ref_count() << std::endl; //ref count for test (should be 1)
	
	smart_ptr <int> steal = smart_ptr<int>(std::move(test2));
	std::cout << "steal refcount: " << steal.ref_count() << std::endl;
	std::cout << "test refcount: " << test.ref_count() << std::endl;

	smart_ptr<int> second = smart_ptr<int>();
	second = steal;
	test = second;
	test2 = test;

	return 0;
}