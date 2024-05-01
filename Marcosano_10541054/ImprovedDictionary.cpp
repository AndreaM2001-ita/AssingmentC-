#include<iostream>
#include<vector>
#include<string>
#include<fstream>//use txt files in the program 
#include "ImprovedDictionary.h"
#include "Dictionary.h"
#include"fileClass.h"
#include "Word.h"
#include <time.h>   //library for time needed in seed generator
#include<random> //library for default_random_engine
#include <algorithm>  //library to sort out vecotr as i am using a binary search algortihm
using namespace std;


//function to check if word is polindrome
bool checkPolindrome(string idiom) {

	if (idiom.size() == 1) return false;  //a word composed by one letter is not polindrome
	// Check if the word is a palindrome
	int lowerbound = 0;
	int upperbound= idiom.size() - 1;
	while (lowerbound < upperbound) {
		if (idiom[lowerbound] != idiom[upperbound]) {  //check if character in word correspond
			return false; // char do not match
		}
		++lowerbound;  //increment start
		--upperbound;  //decremement end
	}
	return true; // All corresponding characters match-> polindrome
}

//function to find if the count of the words of the defintion is greater than 4
bool countWords(string Definition) {
	int words = 0;
	int lenOfDefinitio = Definition.size();

	for (int index = 0; index < lenOfDefinitio; index++)
	{
		// check if current character is a space
		if (Definition[index] == ' ' and Definition[index+1]!=' ')  //count start after space of word, plus aboid cases of double space in that position
		{
			words++;
			if (words == 4) { return true; }  //stop counting if the word has more than 4 words as per assignment script
		}
	}
	return false;
}
//function to make the user enter a word for gess
void enterWordtoRhyme(string& idiom) {
	cout << "Insert the word to look for its rhymes " << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer to avoid issues with it

	getline(cin, idiom);
	
}

//function to print instructions of the game
void printInstructions() {
	cout << "--------------------" << endl;
	cout << "WELCOME TO GUESS THE WORD" << endl;
	cout << "You will be presented with a random word and definintion " << endl;
	cout << "Although, the fourth word of the definition will be replced by _____" << endl;
	cout << "GUESS THE MISSING WORD!!" << endl;
	cout << endl;
}
//function to get the fouth word of a string
string getFourthWord(string definition) {

	int words = 1;
	int lenOfDefinition = definition.size();
	bool first = false;

	string fourthWord; //store the 4th word

	for (int i = 0; i < lenOfDefinition; i++)
	{
		if (definition[i] == ' ')  //coutn spaces to find the fourth word
		{
			words++;
		}
		if (words == 4) {  //when the fourth word in defintion is found
			if (first) {
				fourthWord = fourthWord + definition[i];
			}
			first = true;
		}
		if (words == 5) { break; }
	}
	return fourthWord;
}
//function to modify the defintion by deleting the fourth word
string modifyDefinition(string definition) {

	int wordsCount = 1;

	int lenOfDefinition = definition.size();  //length of definiton
	bool first = false;

	for (int index = 0; index < lenOfDefinition; index++)
	{
		if (definition[index] == ' ')
		{
			wordsCount++;
		}
		if (wordsCount == 4) {		//if it is the  4th word substitut it 
			if (first) {		//used mechanism to make sure that the first space is not replaced as well
				definition[index] = '_';
			}
			first = true;  //strat inserting -
		}
		if (wordsCount == 5) { break; } //when it gets to 5th word exit loop

	}
	return definition;
}
//function to enter parameters of new word
void enterParameter(string typeParameter, string& parameter) {
	//cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Enter the " << typeParameter << " you want to insert : ";

	getline(cin, parameter, '\n');

}

//function to verify uniqueness of name
bool verifyuniqueness(string name, vector<Word> Dict) {
	for (Word word : Dict) {
		if (name == word.getName()) {
			cout << "Error... " << name << " exists in the dictionary, elevated priviledges required to edit existing words" << endl;
			return true;
		}
	}
	return false;
}

//function to verify if the tyope insertwed exist
bool correctType(string& type) {
	vector<string> acceptableTypes = { "v","n","adv","adj","prep","pn","n_and_v","misc" };
	for (string& currentType : acceptableTypes) {
		if (currentType == type) {
			return false;
		}
	}
	cout << "Error... " << type << " is not an acceptable type" << endl;
	return true;
}

//function to ask user a yes or no question
void queryUser(char& response) {

	do {
		cout << "Do you want to overwrite the original file? (Y/N)" << endl;
		cin >> response;
		//cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer to avoid issues with it
		response = toupper(response); //convert to uppercase in case user forget sensitive case
	} while (response != 'N' && response != 'Y');

}


/*
* set the value of score by adding it to its previous value
* input: the score
* output: if the current score is highesr that the highest score, let user know
* author: Andrea Marcosano date 24/04/2024
*/
void ImprovedDictionary::setScore(int score) {
	this->score += score;  //add to current score

	if (this->score > getHighestScore()) {
		cout << endl;
		cout << "CONGRATULATIONS!! you have beaten your previous record!" << endl;
		cout << endl;
	}
}


/*
* get the value of the current score
* input: 
* output: return the value of the score 
* author: Andrea Marcosano date 24/04/2024
*/
int ImprovedDictionary::getScore() {
	return this->score;
}
/*
*  reset the current value to zero to let user replay a second time starting from 0
* input:
* output:
* author: Andrea Marcosano date 24/04/2024
*/
void ImprovedDictionary::resetScore() {
	this->score = 0;
}
/*
* set teh highest score to the current score only if the current score is higher than th eprevious one 
* input:  the highest score value
* output: newest score is updated only if the new one is higher than the previous one
* author: Andrea Marcosano date 24/04/2024
*/
void ImprovedDictionary::setHighestScore(int highestScore)  //setter of score 
{
	if (highestScore > getHighestScore()) {
		this->highestScore = highestScore;
	}
}
/*
*  getter for highest score
* input:
* output: return highest score
* author: Andrea Marcosano date 24/04/2024
*/
int ImprovedDictionary::getHighestScore()  //getter of score
{
	return this->highestScore;
}
/*
*  prints out the menu for improved dictionary and its advanced features 
* input:
* output:
* author: Andrea Marcosano date 24/04/2024
*/
void ImprovedDictionary::menu() {
	this->Dictionary::menu();

	if (Dictionary::Dictionary.size()!=0) {
		cout << "3. Find Polindromes " << endl;
		cout << "4. Find Rhyming words " << endl;
		cout << "5. Game - Guess the fourth word " << endl;
		cout << "6. Add word to Dictionary " << endl;
		this->upper_boud = 6;
	}
	cout << "--------------------" << endl;

}
/*
* the function goes throguh the entirety of the dictioanry and verifies if a word is polindrome
* input:  take dictioanry from class
* output: prints out polindrom
* author: Andrea Marcosano date 25/04/2024
*/
void ImprovedDictionary::findPolindromes() {

	cout << "---List of Polindromes in Dictionary---" << endl;

	vector<Word> Dict = Dictionary::Dictionary;
	string idiom;

	int count = 0;
	for (Word word : Dict) {//go through dictionary 
		idiom=word.getName();//get the words one by one
		if (checkPolindrome(idiom)) {  //check polindrome
			count++;
			cout << count << ". " << word.getName() << endl;  //if they are print them on screen
		}
	}
}
/*
* the fucntion finds the words that rhyme with a word entered by user
* input:  take dictioanry from class + enteterd word
* output: prints all the rhyming words with the word entered by user
* author: Andrea Marcosano date 25/04/2024
*/
void ImprovedDictionary::findRhyming() {
	string aWord;
	vector<Word> Dict = Dictionary::Dictionary;
	enterWordtoRhyme(aWord);// ask the user for the word to rhyme
	cout << "---List of Rhyming words for "<< aWord<<endl;
	aWord=toLowercase(aWord); //make word to lower case to avoid sensitive case errors
	int lastThree = aWord.length() - 3;  //initialise the last three letter of the owrd entered
	int count = 0;
	for (Word word : Dict) {
		string idiom = word.getName();

		if (idiom.length() > 3) {  //only if word is longer than 3
			if (aWord.substr(lastThree) == idiom.substr(idiom.length() - 3)) {
				count++;
				cout << count << ". " << idiom << endl;
			}
		}
	}
}
/*
* the game fucntion makes the user play a game of guessing the fourth word of a defintion of a ranom word within the dictioanry and keeps track of results with a scoring system
* input:  take dictioanry from class + guess from user
* output:  output results of game wining or losing
* author: Andrea Marcosano date 26/04/2024
*/
void ImprovedDictionary::game() {
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer to avoid issues with it
	printInstructions(); //print the rules of the game
	while (true) {
		vector<Word> Dict = Dictionary::Dictionary;
		int length = Dict.size();  //find total length of dictioanry

		Word randomWord;
		do {
			//srand(time(0));
			//int randomPosition = rand() % length; //find random position --deprecated

			const int min = 0;
			const int max = length;
			std::default_random_engine random_engine(time(0));  //initializes a random number generator using the current
			std::uniform_int_distribution<int> distribution(min, max);//uniform distribution creationg, generates random numebrs between 0 and the length of dictionary
			int randomPosition = distribution(random_engine);  //generate random int based on distribution 
			//cout << randomPosition << endl;
			randomWord = Dict[randomPosition];//find random word

		} while (!countWords(randomWord.getDefinition()));//count numbr of words in definition)

		cout << "Your score is " << this->getScore() << endl; //retriveing score

		string fourthWord = getFourthWord(randomWord.getDefinition());
		string newDefintion = modifyDefinition(randomWord.getDefinition()); //eliminate 4th word


		//printing word to guess
		cout << "-------------------------------------------------" << endl;//separator
		cout << "Word: " << randomWord.getName() << endl;
		cout << "Definition: " << newDefintion << endl;
		cout << "-------------------------------------------------" << endl;//separator
		//print instructions and prompt user to enter guess
		string guess;
		cout << "Now it is your turn to guess the word!..." << endl;
		cout << "Enter your guess " << endl;
		cout << "Solution: " << fourthWord << endl;  //decomment to see solution
		cout << "-------------------------------------------------" << endl;//separator
		cout << endl;
		getline(cin, guess);

		guess = Dictionary::toLowercase(guess);//avoid sensitive case error
		//solution
		if (guess == fourthWord) {
			cout << "CONGRATULATION, you won this round " << endl;
			this->setScore(10);//setting score to +10
		}
		else {
			cout << "OH NO!!! INCORRECT GUESS" << endl;
			cout << "The correct word was " << fourthWord << endl;
			cout << "The game is Exiting ..." << endl;
			this->setHighestScore(getScore());
			this->resetScore();
			return;
		}
	}
}

/*
* the function isnerts a new word within the dictionary by asking user a name a type and a definition. furthermore, it verifies that the new word is not present within the current dictionary
* once the new word is entereed the fucntion can either create a new diuctionary file and save the words there or resave everyhting (current dictioanry + new word) in the old dictionary file
* input:  take dictioanry from class + new word(name,type, definition)
* output:  renewed file with new dictionary 
* author: Andrea Marcosano date 27/04/2024
*/
void ImprovedDictionary::addWord() {
	string name, type, definition;
	vector<Word> Dict = Dictionary::Dictionary;
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); //coming from a cin input

	//checks for word
	do {
		enterParameter("Word",name);
		name = Dictionary::toLowercase(name);
	} while (verifyuniqueness(name, Dict));//control of uniqueness of name
	//checks for type
	do {
		enterParameter("Type",type);
		type= Dictionary::toLowercase(type);
	} while (correctType(type));
	//get definiton from user
	enterParameter("Definition",definition);
	definition = Dictionary::toLowercase(definition);

	Word newWord;

	//setting parameters of new word
	newWord.setName(name);
	newWord.setType(type);
	newWord.setDefinition(definition);

	Dict.push_back(newWord); //adding new word to dictionary 
	// Sorting the vector
	//sortVector(Dict);

	char response;
	queryUser(response);//about if they want to ovverride current file

	fileClass f;
	if (response == 'Y') {  //use same file
		f.setFilename(f.getFilenameMain());
	}
	else {  //create new file
		string filename = f.askFileName();
		
		f.setFilename(filename);
	}

	ofstream file = f.openFileOutput();//open file in output mode
	for (Word word : Dict)  //writing on file
	{
		//rewriting whole dictionary 
		file << endl;
		file << "Type: " + word.getType() << endl;
		file << "Definition: " + word.getDefinition() << endl;
		file << "Word: " + word.getName() << endl;
		
	}
	//eliminate the content of vector so that user is forced to reload it
	Dictionary:clearDictionary();//clears current dictioanry so it can be repopulated if needed 
	file.close();
	cout << "Operation Completed with success" << endl;
}