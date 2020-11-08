#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

void readPrice(string s, string &d, string &p);
void readTransaction(string s, string &n, string& d, string &shares);

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
		priceNode *del = HEAD;
		priceNode *lead = HEAD;
		while (lead != nullptr)
		{
			lead = lead->next;
			delete del;
			cout << "deleted price Node \n";
			del = lead;
		}
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
	void getChangeDays(vector<int>&v) //add days which have changes into vector v
	{
		priceNode *checker = HEAD;
		v.clear();
		while (checker != nullptr)
		{
			v.emplace_back(checker->day);
			checker = checker->next;
		}

	}

	int dayPrice(int d) //return stock price at given day
	{
		//int price = 0;
		priceNode *checker = HEAD;
		while (checker != nullptr)
		{
			if (checker->day <= d && (checker->next->day > d || checker->next ==nullptr) ) return checker->price;
			checker = checker->next;
		}return 0;
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
		person *leadPerson = HEAD;
		person *delPerson = HEAD;
		transaction *delTrans;
		transaction *leadTrans;
		while (leadPerson != nullptr)
		{
			delTrans = leadPerson->t;
			leadTrans = delTrans;
			while (leadTrans != nullptr)
			{
				leadTrans = leadTrans->next;
				delete delTrans;
				cout << "deleted transaction \n";
				delTrans = leadTrans;
			}// deleted all transaction
			leadPerson = leadPerson->next;
			delete delPerson;
			cout << "deleted person \n";
			delPerson = leadPerson;
		}//deleted all people
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
		//n--;
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
	users input = users(); //list of all users 
	stockPrices prices = stockPrices(); //list of price changes
	vector<string>people; //used to hold list of user names
	int countPipes, tNum;//use to determine which data structure to read into
	string name, day, price, shares; //store data 
	transaction tempTrans;
	
	//read data into data structure
	for (string s : v) //iterates through each line
	{
		countPipes = 0; //set pipecount to 0
		for (char c : s) //count pipes to determine what kind of string it is
		{
			if (c == '|') countPipes++;
		}
		if (countPipes == 3) //line is a transaction
		{
			readTransaction(s, name, day, shares);
			input.addLine(name, stoi(day), stoi(shares));
		}
		else if (countPipes == 1) //line is a date
		{
			readPrice(s, day, price);
			prices.priceChange(stoi(day), stoi(price));
		}
		//clear variables
		name.clear();
		shares.clear();
		day.clear();
		price.clear();
	}

	input.getUsers(people); //get all names in the 

	for (string s : people) //loops each user
	{
		tNum = input.transactionCount(s); //get number of transactions user has done
		for (int i = 0; i < tNum; i++) //pull each transaction 
		{
			input.getTransaction(s, i, tempTrans); //tempTrans populated with values from n transaction
			cout << s << "Transaction " << i + 1 << ": sharePrice: " << prices.dayPrice(tempTrans.day) << " : proffit: " << prices.dayPrice(tempTrans.day) * tempTrans.shares << endl;
		
		}
		
	}


	return v; // This compiles, but is not correct
}

void readPrice(string s, string &d, string &p) //reads stock price into variables necessary to make a priceNode
{
	int pipes = 0; 
	for (char c : s)
	{
		if (c == '|') //if we hit a pipe increment pipe count and continue loop
		{
			pipes++;
			continue;
		}
		if (pipes == 0)
		{
			d = d + c;
		}
		else if (pipes == 1)
		{
			p = p + c;
		}
	}
}

void readTransaction(string s, string &n, string& d, string &shares) //read transaction into variables needed to add to user datastruct
{
	int pipes = 0;
	string type;
	for (char c : s)
	{
		if (c == '|') //if we hit a pipe increment pipe count and continue loop
		{
			pipes++;
			if (type == "BUY") shares = shares + '-';
			continue;
		}
		if (pipes == 0)//this is the day
		{
			d = d + c;
		}
		else if (pipes == 1)//this is name
		{
			n = n + c;
		}
		else if (pipes == 2)//this is sale type
		{
			type = type + c;
		}

		else if (pipes == 3) //this is share number
		{
			shares = shares + c;
		}
	}//iterated through string

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
	users input = users();
	stockPrices prices = stockPrices();
	vector<string>people;
	transaction tranny;
	//check add lines
	input.addLine("andy", 0, 10);
	input.addLine("andy", 1, 120);
	input.addLine("andy", 3, 10);
	input.addLine("bolo", 23, 20);
	input.addLine("jeanne", 0, 10);

	int x = input.transactionCount("andy");
	input.getTransaction("andy", 2, tranny);
	input.getUsers(people);
	//check add priceNode
	prices.priceChange(0, 30);
	prices.priceChange(3, 20);
	prices.priceChange(4, 23);
	prices.priceChange(6, 240);

	x = prices.dayPrice(5);
	vector<int>daydos;
	prices.getChangeDays(daydos);
}