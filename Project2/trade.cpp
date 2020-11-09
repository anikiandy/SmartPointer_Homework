#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

void readPrice(string s, string &d, string &p);

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

struct user
{
	string name;
	int day, shares;

	string user2string()
	{
		string s, bs;
		if (shares <= 0) bs = "BUY";
		else bs = "SELL";
		s = to_string(day) + "|" + name + "|" + bs + "|" + to_string(abs(shares));
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
			if (checker->day <= d && (checker->next->day > d || checker->next->next ==nullptr)) return checker->price;
			checker = checker->next;
		}return 0;
	}

	bool didPricechange(int d) //check if this is a price change day
	{
		priceNode *checker = HEAD;
		while (checker != nullptr)
		{
			if (checker->day == d) return true;
			else checker = checker->next;
		} return false;
	}
};

void inspectTransaction(string s, user &inspect)
{
	int pipeCount = 0; 
	string name, day, shares, type;
	for (char c : s)
	{
		if (c == '|')//if pipe incrememnt pipecount and continue
		{
			pipeCount++;
			continue;
		}

		if (pipeCount == 0) day = day + c;
		else if (pipeCount == 1)name = name + c;
		else if (pipeCount == 2) type = type + c;
		else if (pipeCount == 3) shares = shares + c;
	}
	if (type == "BUY") shares.insert(0, "-");
	inspect.name = name;
	inspect.day = stoi(day);
	inspect.shares = stoi(shares);

}

vector<string> findPotentialBadTraders(vector<string> v)
{
	stockPrices prices = stockPrices(); //list of price changes
	user inspectUser = user(); // use to inspect transaction
	vector<string>transactions;
	int countPipes;//use to determine which data structure to read into
	string name, day, price, shares; //store data 

	//read stock prices into stockPrices list
	for (string s : v) //populates stockPrices list
	{
		countPipes = 0; //set pipecount to 0
		for (char c : s) //count pipes to determine what kind of string it is
		{
			if (c == '|') countPipes++;
		}
		if (countPipes == 3) //line is a transaction just continue
		{
			transactions.emplace_back(s);
		}
		else if (countPipes == 1) //line is a date
		{
			readPrice(s, day, price);
			prices.priceChange(stoi(day), stoi(price));
			name.clear();
			shares.clear();
			day.clear();
			price.clear();
			continue;
		}
	}
	//analyze transaction
	vector<string>::iterator it = transactions.begin();
	bool sketchy ;
	while (it != transactions.end())
	{
		sketchy = false;
		inspectTransaction(*it, inspectUser); //convert to user
		if (inspectUser.shares <= 0)//this is a BUY
		{
			int buyCost = prices.dayPrice(inspectUser.day) * inspectUser.shares;
			//int newCost;
			//need to know if price changed in the next 3 days
			for (int i = inspectUser.day + 1; i <= inspectUser.day + 3; i++) //check for price changes in next 3 days
			{
				if (prices.didPricechange(i)) //price changed. check if it gains money 
				{
					//check if sketchy
					if ((buyCost - (prices.dayPrice(i) * inspectUser.shares)) > 500000)
					{
						sketchy = true;
					}
				}
			}
		}
		else //this is a Sell
		{
			int sellIncome = prices.dayPrice(inspectUser.day) * inspectUser.shares;
			for (int i = inspectUser.day + 1; i <= inspectUser.day + 3; i++) //check if price changes in the next 3 days
			{
				if (prices.didPricechange(i))
				{
					if ((sellIncome - (prices.dayPrice(i) * inspectUser.shares)) > 500000)
					{
						sketchy = true;
					}
				}
			}
		}
		if (sketchy == false)
		{
			it = transactions.erase(it);
		
		}
		else it++;
	}
	v.swap(transactions); //swap input vector with transactions vector

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