#include "Mammal.h"

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

Mammal::Mammal() {
	numNurse = 0;
}

Mammal::Mammal(string trackNum, string name, string type, string subType, int nurse) {
	SetData(trackNum, name, type, subType, nurse);
	numNurse = nurse;
}

void Mammal::SetData(string trackNum, string name, string type, string subType, int nurse) {
    trackRfid = trackNum;
    animalName = name;
    animalType = type;
    animalSubType = subType;
    numNurse = nurse;
}

void Mammal::PrintItem() {
	cout << setw(10) << left << trackRfid << setw(15) << left << animalName
		 << setw(15) << left << animalType << setw(15) << left << animalSubType
		 << setw(6) << left << 0 << setw(6) << left << numNurse << endl;
}

void Mammal::FilePrint(ofstream &oFS) {

	oFS << setw(10) << left << trackRfid << setw(15) << left << animalName
		 << setw(15) << left << animalType << setw(15) << left << animalSubType << endl;
}

int Mammal::GetNurse() {
	return numNurse;
}
