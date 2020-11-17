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
