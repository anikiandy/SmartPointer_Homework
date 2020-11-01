#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std;
// Remove the odd integers from li.
// It is acceptable if the order of the remaining even integers
//is not
// the same as in the original list.
void removeOdds(list<int>& li) //overload list int
{
	for (std::list<int>::iterator it = li.begin(); it != li.end(); it++) //iterate through list
	{
		if (*it % 2 != 0)
		{
			*it = 3;//change all odd integers to 3
		}
	}
	li.remove(3); //remove all elements == 3
}

// Remove the odd integers from v.
// It is acceptable if the order of the remaining even integers
//is not
// the same as in the original vector.
void removeOdds(vector<int>& v)//overload vector int
{
	vector<int>::iterator ptr; //iterator for vector
	vector<int>temp; //temporary vector 
	for (ptr = v.begin(); ptr < v.end(); ptr++)
	{
		if (*ptr % 2 == 0) temp.emplace_back(*ptr);//use emplaceback to add even ints to temp vector
	}
	v.swap(temp); //swap vector 
}
void test()//test for list
{
	int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
	//constructor take a start memory location and and end a is the start of the array a+8 ==std::end(a)
	list<int> x(a, a+8); // construct x from the array

	assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
	removeOdds(x);
	assert(x.size() == 4);
	vector<int> v(x.begin(), x.end()); // construct v from x
	sort(v.begin(), v.end());
	int expect[4] = { 2, 4, 6, 8 };
	for (int k = 0; k < 4; k++)
		assert(v[k] == expect[k]);
}

void test2() //test for vector
{
	int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
	vector<int> x(a, a + 8); // construct x from the array
	assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
	removeOdds(x);
	assert(x.size() == 4);
	sort(x.begin(), x.end());
	int expect[4] = { 2, 4, 6, 8 };
	for (int k = 0; k < 4; k++)
		assert(x[k] == expect[k]);
}
int main() {
	test();
	cout << "Passed test()" << endl;
	test2();
	cout << "Passed test2()" << endl;
	return 0;
}