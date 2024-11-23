#include "User.h"
#include <iostream>
using namespace std;

/*
main
main is where the aforementioned purpose of the mainprogram.cpp file is found. The user is asked for a row and column value, then a User object is created with given values
@return return: int
*/
int main() {
	int choice;
	cout << "Would you like a random configuration of the map or would you like a pre-made board setup to be used?" << endl;
	cout << "Enter 1 for random and 2 for a file input" << endl;
	cin >> choice;
	while ((choice != 1) && (choice != 2)) {
		cout << "Enter 1 for random and 2 for a file input" << endl;
		cin >> choice;
	}
	cout << endl;
	User user(choice);
	user.Play();

	return 0;
}