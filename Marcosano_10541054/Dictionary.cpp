#include<iostream>
#include<vector>
#include<string>
#include<fstream>//use txt files in the program 
#include"Dictionary.h"
#include"Word.h"
#include"fileClass.h"
using namespace std;

//function to get the parameter off the dictionary, eliminate useless characters
string getInfo(ifstream& file, string parameter) {
	getline(file, parameter, ':');  //read line only after : simbol
	file.ignore(1); //ignore one empty space
	getline(file, parameter); //read rest of the line
	//cout << parameter << endl; //testline
	return parameter;
}
//function to replace - with ~ as looking up woirds would return erranous results as ASCII of '-' is llower than the other characters
//therefore is was substituted with a character with higher ASII which is '~'
string replaceByreference(string& word) {
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
	return result;
}
/*
* initial menu 
* input: 
* output:  menu on screen
* author: Andrea Marcosano date 25/04/2024
*/
void Dictionary::menu() {

	cout << "===========MENU============" << endl;
	cout << endl;
	cout << "0. Exit the Program" << endl;
	cout << "1. Load Your Dictionary " << endl;
	if (!this->Dictionary.empty()) {
		cout << "2. Search your Dictionary " << endl;
		this->upper_boud = 2;
	}
}

/*
* fucntion to transform input word to lower case
* input:  word 
* output:  lower case version of word
* author: Andrea Marcosano date 25/04/2024
*/
string Dictionary::toLowercase(string string) {
	for (char& character : string) {
		character = tolower(character);
	}
	return string;
}

/*
* function to make the user enter the word to search
* input:  word in reference mode
* output:  lower case version of word
* author: Andrea Marcosano date 25/04/2024
*/
void Dictionary::enterWord(string& idiom) {
	cout << "Insert the word to search in dictionary" << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer to avoid issues with it

	getline(cin, idiom);
	idiom = toLowercase(idiom);//make sure it is lower case/ avoid sensitive case errors
}

/*
* function to load content of file in dictioanry obj
* input:  file of dictionary 
* output:  dictionary obj
* author: Andrea Marcosano date 25/04/2024
*/
void Dictionary::load() {

	fileClass f;
	string filename = f.askFileName();

	//auxiliary variables 
	string type, definition, name;

	ifstream file=f.openFileInput();//open file in input mode 

	while (!file.eof())
	{
		//get current word parameters
		type = getInfo(file, type);
		definition = getInfo(file, definition);
		name = getInfo(file, name);
		
		if (type.find_first_not_of("\r\n") != string::npos) { //function to avoid storing empty values in dictionary 
			Word word;

			word.setType(type);//read type of current word
			word.setDefinition(definition);//read definition of current word
			word.setName(name);//read word

			name = word.getName();
			if (name.find('-') != string::npos) { //verify that '-'is in word so the program does not have to call the fucntion for each word 
				name = replaceByreference(name);//call function to check that the word does not contain - 
				word.setName(name);
			}

			Dictionary.push_back(word); //insert new idiom into dictionary 
		}
	}
	file.close();
	cout << "-------------------------------------------------" << endl;//separator
}

/*
* function to search for word within dictioanry 
* input:  word to search
* output:  name, type and defintion of the word, if found
* author: Andrea Marcosano date 25/04/2024
*/
void Dictionary::search() {
	
	string idiom = " ";
	this->enterWord(idiom);//passed by reference

	bool found = false; //bool variable to identify if word was found or not

	//linear search algorithm
	for (Word& word : Dictionary) {
		if (word.getName().at(0) == '-') word.getName().erase(0, 1); //erase first character if it is -
		if (word.getName() == idiom) {
			cout << "The word " << idiom << " was found" << endl;
			word.printDefinition(); //call function to print values on screen
			found = true;
			break;
		}
	}

	if (!found) {//scenario - word not found
		cout << "-->Word not found " << endl;
	}

	//DEPRECATED
	/*
	* //declaration of variable useful for binary search
	algorithm to find word
	implmenting binary search as the dictionary is sorted alphabetically
	int left,right,middle
	left = 0;//initialise start of vector
	right = this->Dictionary.size()-1;  //initialise right value to the size of the dictionary
	middle = 0; //middle avlue to facilitate binary search
	while (left <= right) {
		middle = floor((right + left) / 2); //find middle element
		string word= this->Dictionary[middle].getName();  //auxiliary string variable to conatin the word
		if (word.at(0) == '-') word.erase(0,1); //erase first character if it is -
		if (word == idiom)
		{
			cout << "The word " << idiom << " was found" << endl;
			Word idiom = this->Dictionary[middle];
			idiom.printDefinition(); //call function to print values on screen
			found = true;
			break;
		}
		else
		{
			if (idiom < word)right = middle - 1;  //if word is a bigger word than the middle value
			else left = middle + 1; //if word is smaller than the one at middle value
		}
	}
	*/

}

