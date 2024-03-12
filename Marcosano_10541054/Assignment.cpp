/*
* Assignment 1 of OOP _ 
* program takes converts the txt file containing a dictionary into a vecotr dictionary
* each word is inserted in the dictionary in order for the vector to be searched
* furthermore, the user is promped to enter a word to search and abianry search is performed on the vector
* 
* Author: Andrea Marcosano 
* Student ID: 10541054
*/


#include<iostream>
#include<String>//use strings in program, library
#include<fstream>//use txt files in the program 
#include<vector>//use vectors in this program 

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
	cout << "insert the name of your file, with its .txt extention " << endl;
	getline(cin,filename,'\n');
	return filename;
}
//function to make the user enter the word to search
void enterWord(string& idiom) {
	cout << "Insert the word to search in dictionary" << endl;
	getline(cin, idiom, '\n');
}

//function to print the information of the word if found
void print(Word idiom)
{
	cout << "Word:" << idiom.name << endl;
	cout << "Type:" << idiom.type << endl;
	cout << "Definition:" << idiom.definition << endl;
}

int main() {
	//create vector of words which will correspond to the dictionary 
	vector<Word> Dictionary;
	//initialise auxiliary variable for word so that it can be insered into the vector
	Word word;

	//auxiliary variables 
	string type,definition,name; 

	int linesRead = 0;

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

	linesRead = 0;
	while(linesRead<8)
	//while (!file.eof())
	{
		word.type = getInfo(file, type);  //read type of current word
		word.definition = getInfo(file, definition);//read definition of current word
		word.name = getInfo(file, name);//read word

		Dictionary.push_back(word); //insert new idiom into dictionary 

		linesRead++;
	}
	file.close();
	cout << "-------------------------------------------------" << endl;//separator
	//algorithm to ask for a word to user
	string idiom;
	enterWord(idiom);//passed by reference
	
	//algorithm to find word
	//implmenting binary search as the dictionary is sorted alphabetically

	int left = 0;//initialise start of vector
	int right = Dictionary.size();  //initialise right value to the size of the dictionary
	int middle; //middle avlue to facilitate binary search

	bool found=false; //bool variable to identify if word was found or not

	while (left < right) {
		middle = (left - right) / 2; //find middle element
		if (Dictionary[middle].name == idiom)
		{
			cout << "The word "<< idiom <<"was found"<< endl;
			print(Dictionary[middle]); //call function to print values on screen
			found = true;
		}
		else
		{
			if (idiom < Dictionary[middle].name)
			{
				right = middle - 1;  //if word is a bigger word than the middle value
			}
			else
			{
				left = middle + 1; //if word is smaller than the one at middle value
			}
		}
	}
	if (!found) {//scenario - word not found
		cout << "Unfortunately the word you entered could not be found in the dictionary " << endl;
	}




	return 0;

}