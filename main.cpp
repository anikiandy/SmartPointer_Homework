#include <iostream>
#include "smart_ptr.h"
#include <string>
using namespace std;
typedef string theThing; 

int main()
{
	theThing* p{ new theThing { "hotdogs" } };
	//int *x;
	smart_ptr<int> empty_int;
	std::cout << "empty ref cnt: " << empty_int.ref_count() << std::endl;
	int *temp = new int; 
	*temp = 5;
	smart_ptr <int> smart_int (temp);
	std::cout << "smart int ref cnt : " << smart_int.ref_count() << std::endl;
	smart_ptr<int>another_int(smart_int);
	std::cout << "smart int ref cnt : " << smart_int.ref_count() << std::endl;
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

	//empty_int = steal;

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

	struct Point { int x = 2; int y = -5; };

		smart_ptr<Point> sp{ new Point };
		cout << sp->x << " " << sp->y << endl; // prints 2 -5

		smart_ptr<double> dsp1{ new double {3.14} };
		smart_ptr<double> dsp2, dsp3;
		dsp3 = dsp2 = dsp1;
		cout << dsp1.ref_count() << " " << dsp2.ref_count() << " "
			<< dsp3.ref_count() << endl; // prints 3 3 3
			// prints 3.14 3.14 3.14
		cout << *dsp1 << " " << *dsp2 << " " << *dsp3 << endl;
		dsp1.clone(); // returns true
		cout << dsp1.ref_count() << " " << dsp2.ref_count() << " "
			<< dsp3.ref_count() << endl; // prints 1 2 2
			// prints 3.14 3.14 3.14
		cout << *dsp1 << " " << *dsp2 << " " << *dsp3 << endl;
	
	return 0;
}