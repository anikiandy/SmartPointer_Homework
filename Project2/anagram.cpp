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
    dict.clear();
    string word;
    while (getline(dictfile, word))
    {
        dict.emplace_back(word);
    }
    
    return dict.size();
}

int permute(string word, vector<string>& dict, vector<string>& results)
{
	results.clear();
	int matches = 0; 
	bool match;
	string check; 
	//iterate through dictionary vector
	for (std::vector<string>::iterator it = dict.begin(); it != dict.end(); it++)
	{
		if (it->length() == word.length())//if string lengths match then check if chars are in word
		{
			//copy word into temp vector
			check = word; //use check string as a temporary string object to manipulate during checks
			//iterate through chars in dictionary word with string iterator
			for (std::string::iterator ch = it->begin(); ch != it->end(); ++ch)
			{
				//iterate through check word chars 
				for (std::string::iterator l = check.begin(); l != check.end(); l++)
				{
					if (*l == *ch) // found a matching char
					{
						*l = ' '; //replace matching char in check with white space
						break;
					}
				}//iterate one letter of dict word through check word
			}//finished iterating all letters of word
			//check if check is all whitespace
			match = true; //set match flag to true
			for (std::string::iterator ch = check.begin(); ch != check.end(); ch++)
			{
				if (*ch != ' ') //found non whitespace meaning the word didnt match
				{
					match = false;
				}
			}
			if (match == true)
			{
				matches++; //found a match so increment matches 
				results.emplace_back(*it); //eadd it word to results
			}
		}

	}
	return matches; // Return count of matches
	
}

void display(vector<string>& results)
{
	for (std::vector<string>::iterator it = results.begin(); it != results.end(); it++)
	{
		cout << "Match: " << *it << endl;
	}
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
