#ifndef OVIPAROUS_H
#define OVIPAROUS_H

#include <fstream>
#include <iostream>
#include <string>
#include "Animal.h"
using namespace std;

class Oviparous : public Animal {  //inherits from Animal base class
    public:
	    Oviparous();  //default constructor
	    Oviparous(string trackNum, string name, string type, string subType, int eggs);  //parameterized constructor
	    void SetData(string trackNum, string name, string type, string subType, int eggs); //set values to object variables
	    void PrintItem();  //print data to screen
	    void FilePrint();  //write data to text file
	    int GetEggs();
    private:
	    int numEggs;  //visible only to this class
};

#endif
