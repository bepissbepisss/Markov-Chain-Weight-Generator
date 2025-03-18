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

void removeCaps(string& s) {
	for (int i=0 ; i<s.length(); i++) {
		s[i]=tolower(s[i]);
	}	
}

//remove caps and punctuation
void cleanWord(string& s) {
	removePunct(s);
	removeCaps(s);
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

void writeFirstRow(ofstream& output, vector<string>& wordOrder) {
	output << ",";
	for (const string& word : wordOrder) {
		output << word << ",	";
	}

}


//generates columns of matrix. should ignore case and punctuation
void generateWordOrder (istream& input, vector<string>& wordOrder) {
	string tempWord;
	while (input) {
		input >> tempWord;


		cleanWord(tempWord);
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

//generates a row of the matrix
vector<int> generateCounts(ifstream& ist, const vector<string>& wordOrder) {
	vector<int> row(wordOrder.size(),0);
	for (const string& word : wordOrder) {
		// use wordOrder and search for word in text 
	//	ist.seekg(0,std::ios::beg);
		string tempWord{"dany"};

		cout << "Looking for " << word << endl;

		ist.clear();
		ist.good();
		while (ist >> tempWord) {
			cout << "Got " << tempWord << endl;
			if (tempWord == word) {
			string nextWord{""};
			ist >> nextWord;
			for (int i=0; i<wordOrder.size(); i++ ) {
				string column = wordOrder[i];
				if (nextWord == column) {
					row[i]++;	
				}
			}

			}
		}
		ist.good();
			


		
	
		// make a new vector of ints that represents the counts of each next word
		//
		//look at next word and add one to its entry on the row


		// do for all words of wordOrder
	}
	return row;
}

// divide each entry by the sum of the entries
// output


int main () {
	vector<string> wordOrder;

	ifstream ist{"sample.txt"};

	generateWordOrder(ist, wordOrder);

	for (int i=0; i<wordOrder.size(); i++) {
		cout << wordOrder[i] << endl;
	}


	ofstream ost{"matrix.csv"};

	writeFirstRow(ost, wordOrder);

	vector<int> row = generateCounts(ist, wordOrder);

	for(int i : row ) {
		cout << i << endl;
	}



	return 0;
}
