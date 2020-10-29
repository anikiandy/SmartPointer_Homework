#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <vector>
using namespace std;

const int MAXRESULTS   = 20;    // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in

int loadDictionary(istream &dictfile, vector<string>& dict)
{
	return -1; // This compiles, but this is incorrect
}

int permute(string word, vector<string>& dict, vector<string>& results)
{
	return -1; // This compiles, but this is incorrect
}

void display(vector<string>& results)
{
	return; // This compiles, but this is incorrect
}

int main()
{
    vector<string> results(MAXRESULTS);
    vector<string> dict(MAXDICTWORDS);
    ifstream dictfile;         // file containing the list of words
    int nwords;                // number of words read from dictionary
    string word;

    dictfile.open("words.txt");
    if (!dictfile) {
        cout << "File not found!" << endl;
        return (1);
    }

    nwords = loadDictionary(dictfile, dict);

    dictfile.close();

    cout << "Please enter a string for an anagram: ";
    cin >> word;

    int numMatches = permute(word, dict, results);
    if (!numMatches)
        cout << "No matches found" << endl;
    else
        display(results);

	return 0;
}
