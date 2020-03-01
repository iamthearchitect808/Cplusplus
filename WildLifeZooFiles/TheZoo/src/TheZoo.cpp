#include <iostream>
#include <jni.h>
#include <vector>
#include "Animal.h"
#include "Mammal.h"
#include "Oviparous.h"
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>
using namespace std;

void GenerateData()               //DO NOT TOUCH CODE IN THIS METHOD
{
     JavaVM *jvm;                      // Pointer to the JVM (Java Virtual Machine)
     JNIEnv *env;                      // Pointer to native interface
                                                              //================== prepare loading of Java VM ============================
     JavaVMInitArgs vm_args;                        // Initialization arguments
     JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
     options[0].optionString = (char*) "-Djava.class.path=";   // where to find java .class
     vm_args.version = JNI_VERSION_1_6;             // minimum Java version
     vm_args.nOptions = 1;                          // number of options
     vm_args.options = options;
     vm_args.ignoreUnrecognized = false;     // invalid options make the JVM init fail
                                                                          //=============== load and initialize Java VM and JNI interface =============
     jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);  // YES !!
     delete options;    // we then no longer need the initialisation options.
     if (rc != JNI_OK) {
            // TO DO: error processing...
            cin.get();
            exit(EXIT_FAILURE);
     }
     //=============== Display JVM version =======================================
     cout << "JVM load succeeded: Version ";
     jint ver = env->GetVersion();
     cout << ((ver >> 16) & 0x0f) << "." << (ver & 0x0f) << endl;

     jclass cls2 = env->FindClass("ZooFileWriter");  // try to find the class
     if (cls2 == nullptr) {
            cerr << "ERROR: class not found !";
     }
     else {                                  // if class found, continue
            cout << "Class MyTest found" << endl;
            jmethodID mid = env->GetStaticMethodID(cls2, "createZooFile", "()V");  // find method
            if (mid == nullptr)
                   cerr << "ERROR: method void createZooFile() not found !" << endl;
            else {
                   env->CallStaticVoidMethod(cls2, mid);                      // call method
                   cout << endl;
            }
     }


     jvm->DestroyJavaVM();
     cin.get();
}

void AddAnimal(vector<Animal*> &animalVector) //function to add new animal object pointer to vector
{
	Oviparous* oviparousPtr = nullptr; //declaring all variables
	Mammal* mammalPtr = nullptr;
	string trackingNum;
	string name;
	string type;
	string subType;
	string response;
	int eggs;
	int nurse;

	cout << "Enter tracking number:" << endl;
	cin >> trackingNum;
	if (trackingNum.length() > 6) { //recognizes error in tracking number length, prompts to re-enter
		cout << "Error: tracking number more than six digits." << endl;
		cout << "Enter tracking number:" << endl;
		cin >> trackingNum;
	}

	cout << "Enter animal name:" << endl;
	cin >> name;
	if (name.length() > 15) { //recognizes error in animal name length, prompts to re-enter
		cout << "Error: name more than 15 characters." << endl;
		cout << "Enter name:" << endl;
		cin >> name;
	}

	cout << "Enter animal type: Oviparous or Mammal:" << endl;
	cin >> type;
	if (type.length() > 15) { //recognizes error in type length, prompts to re-enter
		cout << "Error: type more than 15 characters." << endl;
		cout << "Enter type:" << endl;
		cin >> type;
	}

	cout << "Enter animal sub-type:" << endl;
	cin >> subType;
	if (subType.length() > 15) { //recognizes error in sub-type length, prompts to re-enter
		cout << "Error: sub-type more than 15 characters." << endl;
	    cout << "Enter sub-type:" << endl;
	    cin >> subType;
	}

	cout << "Save new animal? Y/N" << endl;
	cin >> response;

	if (response == "Y" || response == "y") {  //loop runs only if response is Y or y
		if (type == "Mammal" || type == "mammal") {  //will create new vector element pointer of subclass Mammal
			eggs = 0;
			cout << "Enter number nursing, 0 if none:" << endl;
			cin >> nurse;
			mammalPtr = new Mammal; //initialize new subclass pointer
			mammalPtr->SetData(trackingNum, name, type, subType, nurse);  //set values to subclass object pointer
			animalVector.push_back(mammalPtr); //add to back of vector
		}
		else if (type == "Oviparous" || type == "oviparous") { //will create new vector element pointer of subclass Oviparous
			nurse = 0;
			cout << "Enter number of eggs, 0 if none:" << endl;
			cin >> eggs;
			oviparousPtr = new Oviparous; //initialize new subclass pointer
			oviparousPtr->SetData(trackingNum, name, type, subType, eggs); //set values to subclass object pointer
			animalVector.push_back(oviparousPtr);  //add to back of vector
		}
	}
}

void RemoveAnimal(vector<Animal*> &animalVector)  //function to delete vector element
{
    unsigned int i = 0;  //declaring all variables
	string searchId = "";
	string choice = "";
	cout << "Enter animal tracking ID:" << endl;
    cin >> searchId;
    if (searchId.length() > 6) {  //recognizes error if tracking ID is too long, prompts for re-entry
    	cout << "Error: tracking ID more than 6 digits." << endl;
    	cout << "Enter animal tracking ID:" << endl;
    	cin >> searchId;
    }
    else {
		for (i = 0; i < animalVector.size(); ++i) {
			if(animalVector.at(i)->GetTrackNum() == searchId) {  //matches if search parameter matches tracking ID in vector
				cout << "Tracking ID: " << animalVector.at(i)->GetTrackNum() << endl;  //displays some info for user to check if it's the correct animal
				cout << "Name: " << animalVector.at(i)->GetName() << endl;
				cout << "Type: " << animalVector.at(i)->GetType() << endl;
				cout << "Sub-Type: " << animalVector.at(i)->GetSubType() << endl;
				cout << "Delete animal? Y/N:" << endl;
				cin >> choice;
				if (choice == "Y" || choice == "y") {  //vector element is erased if choice is Y or y
					animalVector.erase (animalVector.begin() + i);
					cout << "Animal successfully deleted." << endl;
				}
			}
		}
    }
}

void LoadDataFromFile(vector<Animal*> &animalVector) //loads text file information into vector
{
	ifstream inFS; //declaring all variables
	Oviparous* oviparousPtr = nullptr;
	Mammal* mammalPtr = nullptr;
	string trackingNum;
	string name;
	string type;
	string subType;
	int eggs;
	int nurse;
    unsigned int i = 0;
    cout << "Opening file" << endl;
	inFS.open("zoodata.txt");  //opening text file for reading
	if (!inFS.is_open()) {
		cout << "Could not open file zoodata.txt." << endl;  //if file is not open

	}
	//read first string from file, assign to variable, do same for next five strings
    while (!inFS.eof()) {
    	while (i < 6) {
			inFS >> trackingNum;
			i++;
			inFS >> name;
			i++;
			inFS >> type;
			i++;
			inFS >> subType;
			i++;
			inFS >> eggs;
			i++;
			inFS >> nurse;
			if (type == "Oviparous" || type == "oviparous") { //if third string is Oviparous
				oviparousPtr = new Oviparous;   //new object pointer
				oviparousPtr->SetData(trackingNum, name, type, subType, eggs); //sets variables to new object pointer
				animalVector.push_back(oviparousPtr); //adds element to back of vector
			}
			else {
				mammalPtr = new Mammal; //new object pointer
				mammalPtr->SetData(trackingNum, name, type, subType, nurse);  //sets variables to new object pointer
				animalVector.push_back(mammalPtr); //adds element to back of vector
			}
			i++;
    	}
    	i = 0;
    }
	cout << "Closing file" << endl;
	inFS.close();  //close file after reading is complete
}

void DisplayAnimalData(vector<Animal*> &animalVector)  //print all vector information to user screen
{
	unsigned int i = 0;
	cout << "Track #   " << "Name           " << "Type           "
	<< "Sub-Type       " << "Eggs  " << "Nurse " << endl;
	for (i = 0; i < animalVector.size(); ++i) {  //calls subclass object printItem function for each iteration of i
		animalVector.at(i)->PrintItem();
	}
}

void SaveDataToFile(vector<Animal*> &animalVector)  //replace file contents with vector contents
{
    ofstream outFS;
    unsigned int i = 0;

    outFS.open("zoodata.txt", ios::out | ios::trunc);  //open file for overwriting by truncating previous data

    if (!outFS.is_open()) {
    	cout << "Could not open file zoodata.txt." << endl;
    }

    outFS << "Track #   " << "Name           " << "Type           "
        << "Sub-Type       " << "Eggs  " << "Nurse " << endl;

    for (i = 0; i < animalVector.size(); ++i) {
    	animalVector.at(i)->FilePrint(outFS);
    }
    cout << "Save successfully completed." << endl;
    cout << "Closing file" << endl;
    outFS.close();
}

void DisplayMenu()
{
	vector<Animal*> animalVector; //vector of animal object pointers
	char choice;
	bool Quit = false;  //menu displayed until quit is set to true

	while (!Quit) {
		cout << "(L)oad Animal Data" << endl;
		cout << "(G)enerate File" << endl;
		cout << "(D)isplay Animal Data" << endl;
		cout << "D(e)lete Animal Record" << endl;
		cout << "(A)dd Animal Record" << endl;
		cout << "(S)ave Animal Data to File" << endl;
		cout << "(Q)uit Program" << endl;
		cout << "Make selection:" << endl;

        cin >> choice;
		switch (choice) {  //switch depending on what user choice is
			case 'q':
			case 'Q':
				cout << "Quitting program" << endl;
				Quit = true;
				break;
			case 'L':
			case 'l':
				system("CLS");  //clear screen before displaying choice data
				cout << "Choice: Load Animal Data:" << endl;
				LoadDataFromFile(animalVector);  //call function on data in vector
				break;
			case 'G':
			case 'g':
				system("CLS");
				cout << "Choice: Generate data from file" << endl;
				GenerateData();
				break;
			case 'D':
			case 'd':
				system("CLS");
				cout << "Choice: Display animal data" << endl;
				DisplayAnimalData(animalVector);
				break;
			case 'A':
			case 'a':
				system("CLS");
				cout << "Choice: Add Animal Record" << endl;
				AddAnimal(animalVector);
				break;
			case 'E':
			case 'e':
				system("CLS");
				cout << "Choice: Delete Animal Record" << endl;
				RemoveAnimal(animalVector);
				break;
			case 'S':
			case 's':
				system("CLS");
				cout << "Choice: Save Animal Data to File" << endl;
				SaveDataToFile(animalVector);
				break;
			default:
				cout << "Invalid choice. Try again." << endl;
				break;
	    }
	}
}

int main()
{
	DisplayMenu(); //display menu runs until user choice is to quit
	return 0; //program ends when user choice is to quit
}
