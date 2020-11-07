#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct priceNode
{
	int day; 
	int price;
	priceNode *next;
	priceNode *last; 
	priceNode(int d, int p)
	{
		day = d;
		price = p; 
		next = nullptr;
		last = nullptr;
	}
	priceNode()
	{
		day = 0, price = 0, next = nullptr, last = nullptr;
	}
};

class stockPrices
{
private:
	priceNode * HEAD;
public:
	stockPrices() //create empty stockPrice object 
	{
		HEAD = nullptr;
	}
	
	~stockPrices()
	{

	}
	void priceChange(int d, int p)
	{
		priceNode *newData = new priceNode(d, p); //create new priceNode
		if (HEAD == nullptr)HEAD = newData; //if head is at nullptr then the list is empty-> add first datapoint
		else
		{
			priceNode *checkNode = HEAD; 
			while (checkNode != nullptr)
			{
				if (checkNode->next == nullptr)
				{
					checkNode->next = newData;
					return;
				}
				checkNode = checkNode->next;
			}
		}
	}
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

	void getUsers(vector<string> &v) //function which takes a vector argument and populates it with all names in the list
	{
		v.clear();
		person *checker = HEAD;
		
		while (checker != nullptr)
		{
			v.emplace_back(checker->name);
			checker = checker->next;
		}
		
		
	}

	bool getTransaction(string name, int n, transaction &t) //takes name, number, and transaction address. copies information from number transaction to transaction t. returns true if transaction exists
	{
		person *checkPerson = HEAD;
		transaction *checkT = nullptr;
		if (n < 0) return false; 
		while (checkPerson != nullptr)// loop through users
		{
			if (checkPerson->name == name) //check name matches user
			{
				checkT = checkPerson->t; //go down transaction list
				for (int i = 0; i < n; i++)//go from first transaction to n transaction
				{
					if (checkT == nullptr) return false; //if checkT hits nullptr then n was greater than list
					checkT = checkT->next;
				}
				t.day = checkT->day;
				t.shares = checkT->shares;
				return true;
							}
			else checkPerson = checkPerson->next; //name doesnt match check next user
		}//finished looping through users didnt' find match
		return false;
	}

	int transactionCount(string n)
	{
		int count =0;
		person *check = HEAD;
		transaction *c;
		while (check != nullptr)
		{
			if (check->name == n)
			{
				c = check->t;
				
				while (c != nullptr)
				{
					count++; 
					c = c->next;
				}
				return count;
			}check = check->next;
		}return count;
	}
};

vector<string> findPotentialBadTraders(vector<string> v)
{
	users input = users();
	stockPrices prices = stockPrices();
	vector<string>people;

	//check add lines
	input.addLine("andy", 0, 10);
	input.addLine("andy", 1, 120);
	input.addLine("andy", 3, 10);
	input.addLine("bolo", 23, 20);
	input.addLine("jeanne", 0, 10);
	
	int x = input.transactionCount("andy");
	input.getUsers(people);
	//check add priceNode
	prices.priceChange(0, 30);
	prices.priceChange(3, 20);

	for (string s : v) // iterate each string in v
	{
		string name;
		int day, price, shares;
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