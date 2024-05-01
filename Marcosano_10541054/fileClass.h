#pragma once
#include <iostream>
#include<string>
#include<fstream>//use txt files in the program 
using namespace std;


// Define  class for file management
class fileClass {
private:
    string filename;
    const string MAINFILE = "dictionary_2024S1.txt";  //main variable for the name of main dictioanry 

public:
    
    // Constructor
    fileClass() {}
    //file name setter
    void setFilename(string filename) {
        this->filename = filename;
    }

    //getters
    //file name getter
    string getFilename() {
        return this->filename;
    }
    //get main filename(no setter)
    string getFilenameMain() {
        return this->MAINFILE;
    }

    //function to ask for file name to open
    string askFileName()
    {
        string filename;
        cout << "Insert the name of your file, with its .txt extention " << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        getline(cin, filename, '\n');

        if (filename.find(".txt") == string::npos) {// Add .txt extension if not provided
            filename += ".txt";
        }

        this->setFilename(filename);//setting the name of the current file to the value entered
        return filename;
    }

    //function to open file in input mode
    ifstream openFileInput() {
        cout << "Attempting to read text file..." << endl; //communicating to user that the porgram is attemption to read file 
        ifstream f(this->getFilename());
        try {
            if (!f.is_open()) {
                throw(string("Unable to open file..."));
            }
            f.close(); // Close the file when done
        }
        catch (string error) {
            cout << error << endl;
            cout << "Opening file " << MAINFILE << endl; // Open main file if file not found

            this->setFilename(MAINFILE);//if the file is not open, the code set the filename to the main file name
        }

        // Continue with file processing...

        ifstream file(this->getFilename()); //open main file if file not found
        return file;
    }
    //function to open file in outpuy mode
    ofstream openFileOutput() {
        cout << "Attempting to open text file..." << endl; //communicating to user that the porgram is attemption to read file 
        ofstream f(this->getFilename(), ofstream::trunc);  //open in output trunc mode  so that the content of the file it is already deleted or create a new file
        try {
            if (!f.is_open()) {
                throw(string("Unable to open file... file not created"));
            }
        }
        catch (string error) {
            cout << error << endl;
        }

        return f;
    }
};
