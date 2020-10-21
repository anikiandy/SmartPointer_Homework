#include <iostream>
#include "smart_ptr.h"
#include <string>
using namespace std;
typedef string theThing; 

int main()
{
	theThing* p{ new theThing { "hotdogs" } };
	//int *x;

	//makes test smart pointer based on raw pointer p
	smart_ptr <theThing> test = smart_ptr<theThing>(p);

	std::cout << "p: " << *p << std::endl; //prints out int p
	std::cout << "test: " << test.getVal() << std::endl; //value of test smart_pointer
	std::cout << "refcount: " << test.ref_count() << std::endl; //ref count for test (should be 1)

	smart_ptr <theThing> test2 = std::move(test);//test 2 pointer should replace test smart ptr

	std::cout << "p: " << *p << std::endl; //prints out theThing p
	std::cout << "test2: " << test2.getVal() << std::endl; //value of test smart_pointer
	std::cout << "refcount2: " << test2.ref_count() << std::endl; //ref count for test (should be 1)
	
	smart_ptr <theThing> steal = smart_ptr<theThing>(std::move(test2));
	std::cout << "steal refcount: " << steal.ref_count() << std::endl;
	std::cout << "test refcount: " << test.ref_count() << std::endl;

	smart_ptr<theThing> second = smart_ptr<theThing>();
	second = steal;
	test = second;
	test2 = test;
	test2.clone();

	test2.~smart_ptr(); //destruct clones ptr

	try {
		std::cout << "value: " << *test2 << std::endl;
	}
	catch (null_ptr_exception &e)
	{
		std::cout << "caught exception: " << e.what() << endl;
	}
	std::cout << "test dereference operator overload *test: " << *test << endl;

	
	return 0;
}