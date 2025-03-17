#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include<cctype> //check if char is letter or number 

using namespace std;

/*
 *  PLAN
 * First go through the text and identify unique words
 * Create columns and rows of the matrix with each unique word
 *
 * For each word, go through the whole text and count the number of times a given  word comes after it. Possibly in vector of a class with a name and count as members. 
 * Do this for all words of the matrix.
 * Create a matrix of the number of times each new word appears
 * Do this for each input text
 * Create a matrix with the probabilities
 */



void removePunct(string& s) {
	while (!isalnum(s.back())) {
		s.pop_back();	
	}
}

bool isSame(string& wordOne, string& wordTwo) {
	removePunct(wordOne);
	removePunct(wordTwo);

	if (wordOne.length() != wordTwo.length()) {
		return false;
	}

	for (size_t i = 0; i < wordOne.length(); i++) {
		if (tolower(wordOne[i]) != tolower(wordTwo[i])) {
			return false;
		}
	}

	return true;
}

//generates columns of matrix. should ignore case and punctuation
void generateWordOrder (istream& input, vector<string>& wordOrder) {
	string tempWord;
	while (input) {
		input >> tempWord;

		removePunct(tempWord);

		for (int i=0 ; i<tempWord.length(); i++) {
			tempWord[i]=tolower(tempWord[i]);
		}	

		//search for tempWord in vector 
		bool newWord{true};
		for (int i =0 ; i<wordOrder.size() ; i++ ) {
			if (isSame(tempWord,wordOrder[i])) {
				newWord = false;
				break;
			}
		}
		if (newWord == true) wordOrder.push_back(tempWord);

	}
}

//generates a matrix row before adding counts to entries 
vector<int> generateRow(const vector<string>& wordOrder) {
    vector<int> v(wordOrder.size(), 0);
    return v;
}



void generateCounts(const vector<string>& wordOrder) {
    for (const string& word : wordOrder) {
    	   // search for the word with a separate function for skipping (input.ignore() until word
	   // add one to count for each next word (i already wrote operator++
    }
}

int main () {
	vector<string> wordOrder;

	ifstream ist{"sample.txt"};

	generateWordOrder(ist, wordOrder);

	for (int i=0; i<wordOrder.size(); i++) {
		cout << wordOrder[i] << endl;
	}
	

	return 0;
}
