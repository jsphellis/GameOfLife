#include "User.h"

/*
User
The User constructor builds class objects with either a predefined board or random with given row and column amounts, based on an int choice received as an argument
@param item: int choice
*/
User::User(int choice) {
	int rows, cols;
	string fileName;

	if (choice == 1) {
		cout << "How many rows would you like your simulation to have?" << endl;
		cin >> rows;
		cout << "How many columns would you like your simulation to have?" << endl;
		cin >> cols;
		classic = new Classic(rows, cols);
		doughnut = new Doughnut(rows, cols);
		mirror = new Mirror(rows, cols);
	}
	else if (choice == 2) {
		cout << "Please provide the name of the file to read in from:" << endl;
		cin >> fileName;
		classic = new Classic(fileName);
		doughnut = new Doughnut(fileName);
		mirror = new Mirror(fileName);
	}

	cout << endl;
}

/*
~Mirror
The destructor has no need to make any calls or functions since the Board objects in their respective mode classes automatically call their own destructors
*/
User::~User() {}

/*
Play
The Play function asks the user to choose one of the modes, which type of output, then runs the simulation of their choosing
@return return: void
*/
void User::Play() {
	string choice;

	cout << "Classic mode runs the simulation without any regard for boxes outside of the grid." << endl;
	cout << endl;
	cout << "Doughnut mode wraps the grid around so one grid unit off to the left will be the respective unit on the right side." << endl;
	cout << endl;
	cout << "Mirror mode reflects the unit off the board back onto the corresponding unit next to it." << endl;
	cout << endl;
	cout << "Please write the name of the mode you wish the simulation to run:" << endl;
	cin >> choice;
	while ((choice != "Classic") && (choice != "Doughnut") && (choice != "Mirror")) {
		cout << "Please enter one of the options:" << endl;
		cout << "Classic          Doughnut          Mirror" << endl;
		cin >> choice;
	}
	cout << endl;

	int delayType;
	cout << "Would you like the simulation pause, require input before continuing to the next generation, or just output to a seperate text file" << endl;
	cout << endl;
	cout << "Enter 1 for delay, 2 for pause, or 3 for file output" << endl;
	cin >> delayType;
	while ((delayType != 1) && (delayType != 2) && (delayType != 3)) {
		cout << "Enter 1 for delay, 2 for pause, or 3 for file output" << endl;
		cin >> delayType;
	}
	cout << endl;

	string fileName;

	if (choice == "Classic") {
		if (delayType == 1) {
			classic->playDelay();
		}
		else if (delayType == 2) {
			classic->playPause();
		}
		else if (delayType == 3) {
			cout << "The text file you enter should end with .txt" << endl;
			cout << "Example: file.txt" << endl;
			cin >> fileName;
			classic->playFile(fileName);
		}
	}
	else if (choice == "Doughnut") {
		if (delayType == 1) {
			doughnut->playDelay();
		}
		else if (delayType == 2) {
			doughnut->playPause();
		}
		else if (delayType == 3) {
			cout << "The text file you enter should end with .txt" << endl;
			cout << "Example: file.txt" << endl;
			cin >> fileName;
			doughnut->playFile(fileName);
		}
	}
	else if (choice == "Mirror") {
		if (delayType == 1) {
			mirror->playDelay();
		}
		else if (delayType == 2) {
			mirror->playPause();
		}
		else if (delayType == 3) {
			cout << "The text file you enter should end with .txt" << endl;
			cout << "Example: file.txt" << endl;
			cin >> fileName;
			mirror->playFile(fileName);
		}
	}
	if ((delayType == 1) || (delayType == 3))
		cin.ignore();
	cout << "Press Enter to exit simulation" << endl;
	string myString = "";
	do {
		getline(cin, myString);
	} while (myString.length() != 0);
}