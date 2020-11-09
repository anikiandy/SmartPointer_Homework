#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

using namespace std;
vector<int> destroyedOnes;
class Movie //Movie list and remove bad function
{
public:

	Movie(int r) : m_rating(r) {}
	~Movie() { destroyedOnes.push_back(m_rating); }
	int rating() const { return m_rating; }
private:
	int m_rating;
};
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


// Remove the movies in li with a rating below 50 and destroy
//them.
// It is acceptable if the order of the remaining movies is not
// the same as in the original list.
void removeBad(list<Movie*>& li) 
{
	//Create a new list of movie objects
	list<Movie*>temp;

	//interate through li. 

	for (std::list<Movie*>::iterator it = li.begin(); it != li.end(); it++)
	{
		Movie* mv = *it;
		
		if (mv->rating() > 50)temp.emplace_back(mv); //If movie is better than 50 add to temp list
	
		else mv->~Movie(); //else, it is less than or equal to 50, so destroy it
	}

	//swap lists
	li.swap(temp);
}

void removeBad(vector<Movie*>& v) //overload vector of movie pointers
{
	//Create a new list of movie objects
	vector<Movie*>temp;

	//interate through li. 

	for (std::vector<Movie*>::iterator it = v.begin(); it != v.end(); it++)
	{
		Movie* mv = *it;

		if (mv->rating() > 50)temp.emplace_back(mv); //If movie is better than 50 add to temp list

		else mv->~Movie(); //else, it is less than or equal to 50, so destroy it
	}

	//swap lists
	v.swap(temp);
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

void test3()
{
	int a[8] = { 85, 80, 30, 70, 20, 15, 90, 10 };
	list<Movie*> x;
	for (int k = 0; k < 8; k++)
		x.push_back(new Movie(a[k]));
	assert(x.size() == 8 && x.front()->rating() == 85 &&
		x.back()->rating() == 10);
	removeBad(x);
	assert(x.size() == 4 && destroyedOnes.size() == 4);
	vector<int> v;
	for (list<Movie*>::iterator p = x.begin(); p != x.end(); p++)
	{
		Movie* mp = *p;
		v.push_back(mp->rating());
	}
	sort(v.begin(), v.end());
	int expect[4] = { 70, 80, 85, 90 };
	for (int k = 0; k < 4; k++)
		assert(v[k] == expect[k]);
	sort(destroyedOnes.begin(), destroyedOnes.end());
	int expectGone[4] = { 10, 15, 20, 30 };
	for (int k = 0; k < 4; k++)
		assert(destroyedOnes[k] == expectGone[k]);
}

void test4() {
	int a[8] = { 85, 80, 30, 70, 20, 15, 90, 10 };
	vector<Movie*> x;
	for (int k = 0; k < 8; k++)
		x.push_back(new Movie(a[k]));
	assert(x.size() == 8 && x.front()->rating() == 85 &&
		x.back()->rating() == 10);
	removeBad(x);
	assert(x.size() == 4 && destroyedOnes.size() == 4);
	vector<int> v;
	for (int k = 0; k < 4; k++)
		v.push_back(x[k]->rating());
	sort(v.begin(), v.end());
	int expect[4] = { 70, 80, 85, 90 };
	for (int k = 0; k < 4; k++)
		assert(v[k] == expect[k]);
	sort(destroyedOnes.begin(), destroyedOnes.end());
	int expectGone[4] = { 10, 15, 20, 30 };
	for (int k = 0; k < 4; k++)
		assert(destroyedOnes[k] == expectGone[k]);
}

int main() {
	test();
	cout << "Passed test()" << endl;
	test2();
	cout << "Passed test2()" << endl;
	test3();
	cout << "Passed test3()" << endl;
	destroyedOnes.clear();//need to clear vector to run test 4
	test4();
	cout << " PAssed Test4()" << endl;
	return 0;
}