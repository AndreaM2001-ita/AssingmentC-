#ifndef DICTIONARY_H
#define DICTIONARY_H

#include<vector>
#include "Word.h"

using namespace std;

class Dictionary {
protected:
	vector <Word> Dictionary;
	int upper_boud = 1;//varibale for upper bound of menu to make menu dynamic

	string toLowercase(string);  //method to make input lower case, to avoid sensitive case errors
	void clearDictionary() { this->Dictionary.clear(); }  //function to clear dictionary once a new word has been inserted
	void enterWord(string&); //function to enter word from user 
public:
	//getter and setter for upper bound of menu
	void setUpperBound(int bound) { this->upper_boud = bound; }
	int getUpperBound() { return this->upper_boud; }
	void close() { this->clearDictionary(); }
	//generic functions
	void load();
	void search();
	void menu();
};

#endif // DICTIONARY_H