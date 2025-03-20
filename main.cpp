#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include <algorithm>

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
	s.erase(remove_if(s.begin(), s.end(), [](char c) {
		return !isalnum(c);
	}), s.end());
}

void removeCaps(string& s) {
	for (int i=0 ; i<s.length(); i++) {
		s[i]=tolower(s[i]);
	}	
}

//remove caps and punctuation
void cleanWord(string& s) {
	if (s == "") {
		return;
	}
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
	output << endl;

}


//generates columns of matrix. should ignore case and punctuation
void generateWordOrder (istream& input, vector<string>& wordOrder) {
	string tempWord;
	while (input) {
		input >> tempWord;
//		cout << "Got tempword: " << tempWord << endl;



		cleanWord(tempWord);
		if (tempWord == "") {
			cout << "Empty string";
			continue;
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

//generates a row of the matrix
vector<double> generateCounts(ifstream& ist, const vector<string>& wordOrder, int r) {
	vector<double> row(wordOrder.size(),0);
	string temp;
	cout << "row is of size " << row.size() << endl;


	ist.clear();
	ist.seekg(0,std::ios::beg);

//	cout << "Current word is " << wordOrder[r] << endl;

	while (ist>>temp) {
		cleanWord(temp);
//		cout << "Current read is " << temp << endl;
		if (temp != wordOrder[r]) {
			continue;
		} else {
			cout << "Found it ";
			ist >> temp; // gets next word
			cleanWord(temp);
			cout << "Following word is " << temp << endl;
			int i =0;
			cout << "i should be zero. i is " << i << endl;
			for (string nextWord : wordOrder) { // find next word's index
				if (nextWord == temp) {
					cout << "Index of next word is " << i << endl;
					break;

				} else {i++;}
			}
			cout << "i is " << i << endl;
			row[i] = row[i] + 1;	
			cout << "++'d the entry. Count is now " << row[i] << endl;
		}
	} 
	// divide by total count
	double total;
	for (double count : row)  {
		total +=count;
	}
	cout << "Total is " << total << endl;

	for (int i =0; i<row.size(); i++ ) {
		row[i]=row[i]/total;
	}



	return row;
}



// divide each entry by the sum of the entries
// output


int main() {
	vector<string> wordOrder;

	ifstream ist{"kafka.txt"};
	cout << "Got great gatsby" << endl;

	generateWordOrder(ist, wordOrder);
	cout << "Generated word order" << endl;

	for (int i=0; i<wordOrder.size(); i++) {
		cout << wordOrder[i] << endl;
	}


	ofstream ost{"matrix.csv"};

	writeFirstRow(ost, wordOrder);

	vector<double> row = generateCounts(ist, wordOrder, 0);


	for (int i=0 ; i<row.size(); i++) {
		cout << row[i] << endl;
	}

	for (int i=0; i<wordOrder.size(); i++) {
		ost << wordOrder[i] << ", ";
		cout << "Generating row" << i << endl;
		row = generateCounts(ist, wordOrder, i);
		cout << "Generated row " << i << endl;
		for (int j=0; j<row.size( ); j++) {
			ost << row[j] << ", ";
		}
		ost << endl;


	}



	return 0;
}
