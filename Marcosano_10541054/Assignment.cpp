#include<iostream>
#include<String>//use strings in program, library
#include<fstream>

using namespace std;

int main() {

	string filename = "dictionary_2024S1.txt"; //file of the assignment with dictionary 

	//auxiliary variables 
	string type,definition,word; 

	int linesRead = 0;

	cout << "Attempting to read text file...\n"; //communicating to user that the porgram is attemption to read file 
	ifstream file(filename);
	if (file.is_open())
	{
		linesRead = 0;
		while (linesRead<3)
		{

			getline(file, type, ':');
			file.ignore(1);
			getline(file, type);
			cout << type << endl;

			// Read definition of word
			getline(file, definition, ':');
			// Remove space after ':'
			
			getline(file, definition);
			cout << definition << endl;

			// Read word
			getline(file, word, ':');
			// Remove space after ':'
			file.ignore(1);
			getline(file, word);
			cout << word<<endl;


			linesRead++;
		}
		file.close();
	}
	else cout << "Unable to open file";
	return 0;

}