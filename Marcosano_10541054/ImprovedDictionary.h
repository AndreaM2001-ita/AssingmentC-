#pragma once
#ifndef IMPROVEDDICTIONARY_H
#define IMPROVEDDICTIONARY_H

#include "Dictionary.h"

using namespace std;

class ImprovedDictionary : public Dictionary{
private:
	int score;  //variable to keep the score 
	int highestScore=10;  //to store best player result
public:
	
	void menu();   //menu when dictioanry is loaded 
	void setScore(int score);  //setter of score 
	void resetScore();
	int getScore();  //getter of score

	void setHighestScore(int score);  //setter of score 
	int getHighestScore();  //getter of score

	void findPolindromes();  //task 3
	void findRhyming(); //task 4
	void game();//task 5
	void addWord(); //task 6
	
};

#endif // DICTIONARY_H