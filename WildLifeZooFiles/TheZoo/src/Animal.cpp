#include <iostream>
#include <string>
#include <iomanip>
#include "Animal.h"
#include <fstream>
using namespace std;

Animal::Animal() {  //for function explanations, see header file
	trackRfid = "";
	animalName = "";
	animalType = "";
	animalSubType = "";
}

Animal::~Animal() {
	//delete *trackRfid;
	//delete *animalName;
	//delete *animalType;
	//delete *animalSubType;
}

Animal::Animal(int trackNum, string name, string type, string subType) {
	SetData(trackNum, name, type, subType);
}

void Animal::SetData(int trackNum, string name, string type, string subType) {
	trackRfid = trackNum;
	animalName = name;
	animalType = type;
	animalSubType = subType;
}

void Animal::PrintItem() {   //to print data to screen
	cout << setw(10) << left << trackRfid << setw(15) << left << animalName
		 << setw(15) << left << animalType << setw(15) << left << animalSubType << endl;
}

void Animal::FilePrint(ofstream &oFS) { //print data to file

	oFS << setw(10) << left << trackRfid << setw(15) << left << animalName
		 << setw(15) << left << animalType << setw(15) << left << animalSubType << endl;
}

void Animal::SetTrackNum(int trackNum) {
	trackRfid = trackNum;
}

void Animal::SetName(string name) {
	animalName = name;
}

void Animal::SetType(string type) {
	animalType = type;
}

void Animal::SetSubType(string subType) {
	animalSubType = subType;
}

string Animal::GetTrackNum() {
	return trackRfid;
}

string Animal::GetName() {
	return animalName;
}

string Animal::GetType() {
	return animalType;
}

string Animal::GetSubType() {
	return animalSubType;
}

