#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct priceChange
{
	int day; 
	int price;
	priceChange *next;
	priceChange *last; 
};

struct transaction
{
	int day;
	int shares; 
	transaction *next;

	transaction()
	{
		next = nullptr;
		day = 0;
		shares = 0;
	}

	transaction(int d, int s)
	{
		shares = s;
		day = d;
		next = nullptr;

	}
};

struct person
{
	string name;
	transaction *t;
	person *next;
	person()
	{
		name = "NONE";
		t = nullptr;
		next = nullptr;
	}

	person(string n)
	{
		name = n; 
		t = nullptr;
		next = nullptr;
	}
};

class users
{
private:
	person *HEAD;
public:
	users()//construct empty users list
	{
		HEAD = nullptr;
	}

	~users() //destructor
	{

	}

	bool isUser(string n)
	{
		person *checker = HEAD;
		while (checker != nullptr)
		{
			if (checker->name == n) return true;
			else checker = checker->next;
		}
		return false;
	}

	void addLine(string n, int d, int s) //function to add new line. accepts all arguments in input text file
	{
		//make transaction
		transaction *add = new transaction(d, s);
		person *checkPerson = HEAD;
		transaction *checkTransaction = nullptr;

		if (isUser(n)) //person exists 
		{
			while (checkPerson != nullptr) //advance checkperson until find name
			{
				if (checkPerson->name == n) //found matching person
				{
					checkTransaction = checkPerson->t; //point to the first transaction 
					while (checkTransaction != nullptr) //loop to find the last transaction
					{
						if (checkTransaction->next == nullptr) //insert new transaction here
						{
							checkTransaction->next = add; //point to added transaction
							return;
						}
						checkTransaction = checkTransaction->next; //advance down transaction list
					} //end of transaction progress loop
				}
				else checkPerson = checkPerson->next; //go to next person
			} // end of checkPerson loop
		}
		else //person doesn exist
		{
			//need to create a new person and insert into users list
			person *newPerson = new person(n); //make a new person with name n
			newPerson->t = add; //point persons t pointer to the new transaction 
			newPerson->next = HEAD; //insert person at HEAD
			HEAD = newPerson; //point HEAD to new person
		}
	}
};

vector<string> findPotentialBadTraders(vector<string> v)
{
	users input = users();

	input.addLine("andy", 0, 10);
	input.addLine("andy", 1, 120);
	input.addLine("andy", 3, 10);

	input.addLine("bolo", 23, 20);
	input.addLine("jeanne", 0, 10);
	for (string s : v) // iterate each string in v
	{
		for (char c : s)
		{
			
		}
	}

	//person x = person("andy", 5, -13);
	return v; // This compiles, but is not correct
}

int main() {

	ifstream in("input.txt");
	string str;

	if (!in) {
		cerr << "No input file" << endl;
		exit(0);
	}

	vector<string> inputVec;
	while (getline(in, str)) {
		inputVec.push_back(str);
	}
	vector<string> resV = findPotentialBadTraders(inputVec);
	for (const string& r : resV) {
		cout << r << endl;;
	}
	return 0;
}