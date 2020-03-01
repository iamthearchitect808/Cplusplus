#ifndef MAMMAL_H
#define MAMMAL_H

#include <fstream>
#include "Animal.h"
#include <iostream>
#include <string>
using namespace std;

class Mammal : public Animal {  //inherits from Animal base class
    public:
	    Mammal();  //default constructor
	    Mammal(string trackNum, string name, string type, string subType, int nurse);  //parameterized constructor
	    void SetData(string trackNum, string name, string type, string subType, int nurse);  //set values to object variables
	    void PrintItem();  //print data to screen
	    void FilePrint(ofstream &oFS);  //write data to text file
	    int GetNurse();  //retrieve nurse variable
    private:
	    int numNurse; //visible only to this class
};

#endif
