#include<iostream>
#include<String>//use strings in program, library
#include<fstream>
#include<vector>

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
	ifstream file(filename);
	if (!file.is_open())
	{
		cout << "Unable to open file..."<<endl;
		cout << "Opening file " << MAINFILE << endl;
		ifstream file(MAINFILE); //open main file if file not found
	}
	//regardless of what file the user tries to oipen a file will always be opened 
	//while(true)
	linesRead = 0;
	while (!file.eof())
	{
		word.type = getInfo(file, type);  //read type of current word
		word.definition = getInfo(file, definition);//read definition of current word
		word.name = getInfo(file, name);//read word

		Dictionary.push_back(word); //insert new idiom into dictionary 

		linesRead++;
	}
	file.close();
	cout << "-------------------------------------------------" << endl;
	//algorithm to ask for a word to user
	string idiom;
	enterWord(idiom);//passed by reference
	
	//algorithm to find word
	//implmenting binary search as the dictionary is sorted alphabetically

	int left = 0;
	int right = Dictionary.size() - 1;
	int middle;

	bool found=false;

	while (left < right) {
		middle = (left - right) / 2; //find middle element
		if (Dictionary[middle].name == idiom)
		{
			cout << "The word "<< idiom <<"was found"<< endl;
			print(Dictionary[middle]);
			found = true;
		}
		else
		{
			if (idiom < Dictionary[middle].name)
			{
				right = middle - 1;
			}
			else
			{
				left = middle + 1;
			}
		}
	}
	if (!found) {
		cout << "Unfortunately the word you entered could not be found in the dictionary " << endl;
	}




	return 0;

}