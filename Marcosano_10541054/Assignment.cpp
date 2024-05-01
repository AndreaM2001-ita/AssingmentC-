/*
* Assignment 1 of OOP CSP2104 
* program takes converts the txt file containing a dictionary into a vecotr dictionary
* each word is inserted in the dictionary in order for the vector to be searched
* furthermore, the user is promped to enter a word to search and abianry search is performed on the vector
* 
* Author: Andrea Marcosano 
* Student ID: 10541054
*/


#include<iostream>
#include<string>//use strings in program, library
#include<fstream>//use txt files in the program 
#include<vector>//use vectors in this program 
#include <cmath> //floor function

#include "Word.h"
#include "Dictionary.h"
#include "ImprovedDictionary.h"

using namespace std;


int main() {

	ImprovedDictionary aDictionary;  //obj of imporved dictioanry 
	aDictionary.setUpperBound(1);  //set initial upper bound  for menu
	int selection ;
	do{
		do {
			try {
				
				aDictionary.menu();
				cout << "Select one option " << endl;
				cin >> selection;
				
				if (cin.fail()) { //if the user input a string the program will exit
					cin.clear();
					//cin.ignore(numeric_limits<streamsize>::max(), '\n');
					throw string("Invalid selection. Program will exit...");
				}
				//only valid selection output error
				if (selection < 0 || selection > aDictionary.getUpperBound()) {
					throw string("Invalid selection. Please enter a number within the range");
				}
			}
			catch (string error) {
				cout << "Error: " << error << endl;		
			}

		} while (selection < 0 || selection > aDictionary.getUpperBound()); //checking selection
		switch (selection) {
			//case 0: break;
			case 1: aDictionary.load();
				break;
			case 2:
				aDictionary.search();
				break;
			case 3: aDictionary.findPolindromes();
				break;
			case 4:aDictionary.findRhyming();
				break;
			case 5:aDictionary.game();
				break;
			case 6: aDictionary.addWord();
				aDictionary.setUpperBound(1); //this way user has to reload dictionary before reusing program so that new word is in dictionary vector
				break;
			default: break;

		}
	} while (selection != 0);
	aDictionary.close(); //close dictionary ...clean its content
	cout << "Program is exiting..." << endl;

	return 0;

}