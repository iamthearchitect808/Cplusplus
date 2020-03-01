#ifndef ANIMAL_H
#define ANIMAL_H

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class Animal {
    public:
	    Animal();  //default constructor
	    Animal(int trackNum, string name, string type, string subType); //parameterized constructor
	    virtual ~Animal(); //destructor
	    void SetData(int trackNum, string name, string type, string subType);  //to set all parent class values to object
	    void SetTrackNum(int trackNum);
	    void SetName(string name);
	    void SetType(string type);
	    void SetSubType(string subType);
	    virtual void PrintItem();  //for printing data to screen depending on vector element subclass type Mammal or Oviparous
	    virtual void FilePrint(); //for writing data to text file depending on vector element subclass type Mammal or Oviparous
	    string GetTrackNum();  //accessors for other functions
	    string GetName();
	    string GetType();
	    string GetSubType();
    protected:  //all variables usable by child classes
	    string trackRfid;
	    string animalName;
	    string animalType;
	    string animalSubType;
};

#endif
