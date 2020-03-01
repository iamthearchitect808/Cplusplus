#include "Oviparous.h"

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;


Oviparous::Oviparous() {
	numEggs = 0;
}

Oviparous::Oviparous(string trackNum, string name, string type, string subType, int eggs) {
	SetData(trackNum, name, type, subType, eggs);
}

void Oviparous::SetData(string trackNum, string name, string type, string subType, int eggs) {
    trackRfid = trackNum;
    animalName = name;
    animalType = type;
    animalSubType = subType;
    numEggs = eggs;
}

void Oviparous::PrintItem() {
	cout << setw(10) << left << trackRfid << setw(15) << left << animalName
		 << setw(15) << left << animalType << setw(15) << left << animalSubType
		 << setw(6) << left << numEggs << setw(6) << left << 0 << endl;
}

void Oviparous::FilePrint(ofstream &oFS) {

	oFS << setw(10) << left << trackRfid << setw(15) << left << animalName
		 << setw(15) << left << animalType << setw(15) << left << animalSubType << endl;
}

int Oviparous::GetEggs() {
	return numEggs;
}
