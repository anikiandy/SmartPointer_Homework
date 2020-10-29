#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

vector<string> findPotentialBadTraders(vector<string> v)
{
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