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

using namespace std;

string MAINFILE= "dictionary_2024S1.txt";
//struct to contain the information of each word
struct Word {
	string type;
	string definition;
	string name;
};

//function to get the parameter off the dictionary, eliminate useless characters
string getInfo(ifstream& file, string parameter) {
	getline(file, parameter, ':');  //read line only after : simbol
	file.ignore(1); //ignore one empty space
	getline(file, parameter); //read rest of the line
	//cout << parameter << endl; //testline
	return parameter;
}
//function to ask for file name to open
string askFileName()
{
	string filename;
	cout << "Insert the name of your file, with its .txt extention " << endl;
	cin.clear();
	getline(cin,filename,'\n');
	return filename;
}
//function to make the user enter the word to search
void enterWord(string& idiom) {
	cout << "Insert the word to search in dictionary" << endl;
	cin.clear();
	getline(cin, idiom);
	
}
//function to replace - with ~ as looking up woirds would return erranous results as ASCII of '-' is llower than the other characters
//therefore is was substituted with a character with higher ASII which is '~'
void replaceByreference(string& word) {
	string result;
	// Iterate through each character in the input string
	for (char c : word) {
		// If the character is '-', replace it with '~', otherwise keep it as it is
		if (c == '-') {
			result += '~';
		}
		else {
			result += c;
		}
	}
	word = result;
}

//function to ask the user if they want to look for another word
void queryUser(char& response) {
	do {
		cout << "Do you want to look up another word?? (Y/N)" << endl;
		cin >> response;
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer to avoid issues with it
		response = toupper(response); //convert to uppercase in case user forget sensitive case
	} while (response != 'N' && response != 'Y');
}

//function to print the information of the word if found
void print(Word idiom)
{
	cout << "-------------------------------------------------" << endl;//separator
	cout << "Word:" << idiom.name << endl;
	cout << "Type:" << idiom.type << endl;
	cout << "Definition:" << idiom.definition << endl;
	cout << "-------------------------------------------------" << endl;//separator
}

int main() {
	//create vector of words which will correspond to the dictionary 
	vector<Word> Dictionary;
	//initialise auxiliary variable for word so that it can be insered into the vector
	Word word;

	//auxiliary variables 
	string type,definition,name; 


	string filename=askFileName();
	//string filename = "dictionary_2024S1.txt"; //file of the assignment with dictionary DEPRECATED

	cout << "Attempting to read text file..."<<endl; //communicating to user that the porgram is attemption to read file 
	ifstream f(filename);//auxiliary file named f to verify if file exists 
	if (!f.is_open())
	{
		cout << "Unable to open file..."<<endl;
		cout << "Opening file " << MAINFILE << endl;
		filename = MAINFILE;
	}
	f.close();
	ifstream file(filename); //open main file if file not found
	//regardless of what file the user tries to open a file will always be opened 

	while (!file.eof())
	{
		word.type = getInfo(file, type);  //read type of current word
		word.definition = getInfo(file, definition);//read definition of current word
		word.name = getInfo(file, name);//read word

		if (word.name.find('-') != string::npos) { //verify that '-'is in word so the program does not have to call the fucntion for each word 
			replaceByreference(word.name);//call function to check that the word does not contain - 
		}

		Dictionary.push_back(word); //insert new idiom into dictionary 

	}
	file.close();
	cout << "-------------------------------------------------" << endl;//separator

	//declaration of variable useful for binary search
	char response = ' ';
	int left, right, middle;
	string idiom;
	do
	{
		//algorithm to ask for a word to user
		idiom=" ";
		enterWord(idiom);//passed by reference

		//algorithm to find word
		//implmenting binary search as the dictionary is sorted alphabetically

		left = 0;//initialise start of vector
		right = Dictionary.size();  //initialise right value to the size of the dictionary
		middle = 0; //middle avlue to facilitate binary search

		bool found = false; //bool variable to identify if word was found or not

		while (left <= right) {
			middle = left + floor((right - left) / 2); //find middle element
			string word=Dictionary[middle].name;  //auxiliary string variable to conatin the word
			if (word.at(0) == '-') word.erase(0,1); //erase first character if it is - 
			if (word == idiom)
			{
				cout << "The word " << idiom << " was found" << endl;
				print(Dictionary[middle]); //call function to print values on screen
				found = true;
				break;
			}
			else
			{
				if (idiom < word)right = middle - 1;  //if word is a bigger word than the middle value
				else left = middle + 1; //if word is smaller than the one at middle value
			}
		}
		if (!found) {//scenario - word not found
			cout << "word not found " << endl;
		}

		queryUser(response);//reponse passed by reference
	} while (response != 'N');

	cout << "Program is exiting..." << endl;

	return 0;

}