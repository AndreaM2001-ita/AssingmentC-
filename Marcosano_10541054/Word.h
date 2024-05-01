#pragma once
#include <iostream>
#include<string>
using namespace std;

// Define the class of word
class Word {
private:
       string type;
       string definition;
       string name;

public:
    Word() {}
    // Constructor
    Word(string type, string definition, string name) {
        this->type = type;
        this->definition = definition;
        this->name = name;
    }
    //setters
    //type setter
    void setType(string type) {
        this->type = type;
    }
    //definition setter
    void setDefinition(string definition) {
        this->definition = definition;
    }
    //name setter
    void setName(string name) {
        this->name = name;
    }
    //getters
    //type getter
    string getType() {
        return this->type;
    }
    //definition getter
    string getDefinition() {
        return this->definition;
    }

    //name getter
    string getName() {
        return this->name;
    }

    //print word
    void printDefinition() {
        cout << "-------------------------------------------------" << endl;//separator
        cout << "Word:" << getName() << endl;
        cout << "Type:" << getType() << endl;
        cout << "Definition:" << getDefinition() << endl;
        cout << "-------------------------------------------------" << endl;//separator
    } 
};

