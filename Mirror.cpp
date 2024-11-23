#include "Mirror.h"

/*
Mirror
This overload constructor creates a Board object with a given size, along with a seperate newBoard for copying, and a mirrorBoard to implement boundary rules (with an extra two columns and rows)
@param item: int rows, int cols
*/
Mirror::Mirror(int rows, int cols) {
	gameBoard = new Board(rows, cols);
	newBoard = new Board(gameBoard->returnRows() + 1, gameBoard->returnCols() + 1);
	mirrorBoard = new Board(gameBoard->returnRows() + 3, gameBoard->returnCols() + 3);
}

/*
Mirror
This constructor creates a Board object with a given size and mapping (from a text file), along with a seperate newBoard for copying, and a mirrorBoard to implement boundary rules (with an extra two columns and rows)
@param item: string fileInput
*/
Mirror::Mirror(string fileInput) {
	ifstream file_input;
	file_input.open(fileInput);
	int rows, cols;
	string line;

	file_input >> rows;
	file_input >> cols;
	gameBoard = new Board(rows, cols);
	getline(file_input, line);
	for (int i = 0; i <= gameBoard->returnRows(); i++) {
		getline(file_input, line);
		for (int j = 0; j <= gameBoard->returnCols(); j++) {
			gameBoard->changeUnit(i, j, line[j]);
		}
	}

	newBoard = new Board(gameBoard->returnRows() + 1, gameBoard->returnCols() + 1);
	mirrorBoard = new Board(gameBoard->returnRows() + 3, gameBoard->returnCols() + 3);
	mirrorCreation();
}

/*
~Mirror
The destructor has no need to make any calls or functions since the Board objects automatically call their own destructors
*/
Mirror::~Mirror() {}

/*
mirrorCreation
This function goes through every position in the mirrorBoard, making each out-of-bound unit reflect off its respective nearby unit
@return return: void
*/
void Mirror::mirrorCreation() {
	mirrorBoard->changeUnit(0, 0, gameBoard->returnChar(0, 0));
	mirrorBoard->changeUnit(0, mirrorBoard->returnCols(), gameBoard->returnChar(0, gameBoard->returnCols()));
	mirrorBoard->changeUnit(mirrorBoard->returnRows(), 0, gameBoard->returnChar(gameBoard->returnRows(), 0));
	mirrorBoard->changeUnit(mirrorBoard->returnRows(), mirrorBoard->returnCols(), gameBoard->returnChar(gameBoard->returnRows(), gameBoard->returnCols()));

	for (int i = 0; i <= gameBoard->returnRows(); i++) {
		for (int j = 0; j <= gameBoard->returnCols(); j++) {
			mirrorBoard->changeUnit(i + 1, j + 1, gameBoard->returnChar(i, j));
		}
	}
	for (int i = 0; i <= gameBoard->returnRows(); i++) {
		mirrorBoard->changeUnit(i + 1, 0, gameBoard->returnChar(i, 0));
		mirrorBoard->changeUnit(i + 1, mirrorBoard->returnCols(), gameBoard->returnChar(i, gameBoard->returnCols()));
	}
	for (int i = 0; i <= gameBoard->returnCols(); i++) {
		mirrorBoard->changeUnit(0, i + 1, gameBoard->returnChar(0, i));
		mirrorBoard->changeUnit(mirrorBoard->returnRows(), i+1, gameBoard->returnChar(gameBoard->returnRows(), i));
	}
}

/*
Cycle
This function iterates through the mirrorBoard (within gameBoard boundary) and calls the neighborCheck function. neighborCheck returns an int that tells the function to adjust the newBoard accordingly.
@return return: void
*/
void Mirror::Cycle() {
	for (int i = 1; i < mirrorBoard->returnRows(); i++) {
		for (int j = 1; j < mirrorBoard->returnCols(); j++) {
			int val = neighborCheck(i, j);
			if (val <= 1) {
				newBoard->changeUnit(i - 1, j - 1, '-');
			}
			else if (val == 2) {
				if (gameBoard->returnChar(i - 1, j - 1) == 'X')
					newBoard->changeUnit(i - 1, j - 1, 'X');
				else
					newBoard->changeUnit(i - 1, j - 1, '-');
			}
			else if (val == 3) {
				newBoard->changeUnit(i - 1, j - 1, 'X');
			}
			else if (val >= 4) {
				newBoard->changeUnit(i - 1, j - 1, '-');
			}
		}
	}
}

/*
neighborCheck
This function takes two int values as a row and column location, then iterates around the index and returns an int of how many X characters surround the given unit
@param item : int row, int column
@return return: int
*/
int Mirror::neighborCheck(int row, int column) {
	int cnt = 0;

	for (int i = row - 1; i <= row + 1; i++) {
		for (int j = column - 1; j <= column + 1; j++) {
			if ((i == row) && (j == column)) {
				continue;
			}
			else if (mirrorBoard->returnChar(i, j) == 'X') {
				cnt += 1;
			}
			else {
				continue;
			}
		}
	}
	return cnt;
}

/*
playDelay
This function has the aforementioned Cycle function called consecutive times (with a short delay in between) until an exit check is called.
@return return: void
*/
void Mirror::playDelay() {
	int check = 2;
	int count = 1;
	
	int empty = 0;
	int total = (gameBoard->returnRows() + 1) * (gameBoard->returnCols() + 1);
	for (int i = 0; i <= gameBoard->returnRows(); i++) {
		for (int j = 0; j <= gameBoard->returnCols(); j++) {
			if (gameBoard->returnChar(i, j) == 'X') {
				break;
			}
			else {
				empty += 1;
			}
		}
	}
	if (empty == total) {
		gameBoard->boardSetup();
	}
	mirrorCreation();
	
	cout << "Gen 0" << endl;
	gameBoard->print();
	cout << endl;

	while (check == 2) {
		int empty = 0;
		int same = 0;

		Cycle();

		cout << "Gen " << count << endl;
		newBoard->print();

		for (int i = 0; i <= gameBoard->returnRows(); i++) {
			for (int j = 0; j <= gameBoard->returnCols(); j++) {
				if (gameBoard->returnChar(i, j) == newBoard->returnChar(i, j)) {
					same += 1;
				}
				if (newBoard->returnChar(i, j) == '-') {
					empty += 1;

				}
			}
		}

		for (int i = 0; i <= gameBoard->returnRows(); i++) {
			for (int j = 0; j <= gameBoard->returnCols(); j++) {
				gameBoard->changeUnit(i, j, newBoard->returnChar(i, j));
			}
		}

		mirrorCreation();

		if (empty == total) {
			cout << "Board is Empty" << endl;
			break;
		}
		else if (same == total) {
			cout << "Stability Achieved" << endl;
			break;
		}

		cout << endl;
		count++;
		usleep(1000000);
	}
}

/*
playPause
This function has the aforementioned Cycle function called consecutive times (requiring the user to press enter to continue to the next cycle) until an exit check is called.
@return return: void
*/
void Mirror::playPause() {
	int check = 2;
	int count = 1;
	
	int empty = 0;
	int total = (gameBoard->returnRows() + 1) * (gameBoard->returnCols() + 1);
	for (int i = 0; i <= gameBoard->returnRows(); i++) {
		for (int j = 0; j <= gameBoard->returnCols(); j++) {
			if (gameBoard->returnChar(i, j) == 'X') {
				break;
			}
			else {
				empty += 1;
			}
		}
	}
	if (empty == total) {
		gameBoard->boardSetup();
	}
	mirrorCreation();

	cout << "Press Enter to proceed to the next generation" << endl;;

	cout << "Gen 0" << endl;
	gameBoard->print();
	cout << endl;

	cin.get();

	while (check == 2) {
		int empty = 0;
		int same = 0;

		Cycle();

		cout << "Gen " << count << endl;
		newBoard->print();

		for (int i = 0; i <= gameBoard->returnRows(); i++) {
			for (int j = 0; j <= gameBoard->returnCols(); j++) {
				if (gameBoard->returnChar(i, j) == newBoard->returnChar(i, j)) {
					same += 1;
				}
				if (newBoard->returnChar(i, j) == '-') {
					empty += 1;

				}
			}
		}

		for (int i = 0; i <= gameBoard->returnRows(); i++) {
			for (int j = 0; j <= gameBoard->returnCols(); j++) {
				gameBoard->changeUnit(i, j, newBoard->returnChar(i, j));
			}
		}

		mirrorCreation();

		if (empty == total) {
			cout << "Board is Empty" << endl;
			break;
		}
		else if (same == total) {
			cout << "Stability Achieved" << endl;
			break;
		}

		count++;
		cin.get();
	}
}

/*
playFile
This function has the aforementioned Cycle function called consecutive times (outputting the generations to a seperate file) until an exit check is called.
@param item: string outputFile
@return return: void
*/
void Mirror::playFile(string outputFile) {
	int check = 2;
	int count = 1;

	int empty = 0;
	int total = (gameBoard->returnRows() + 1) * (gameBoard->returnCols() + 1);
	for (int i = 0; i <= gameBoard->returnRows(); i++) {
		for (int j = 0; j <= gameBoard->returnCols(); j++) {
			if (gameBoard->returnChar(i, j) == 'X') {
				break;
			}
			else {
				empty += 1;
			}
		}
	}
	if (empty == total) {
		gameBoard->boardSetup();
	}
	mirrorCreation();

	ofstream out_file;
	out_file.open(outputFile);

	out_file << "Gen 0" << endl;
	for (int i = 0; i < gameBoard->returnRows(); i++) {
		for (int j = 0; j < gameBoard->returnCols(); j++) {
			out_file << gameBoard->returnChar(i, j);
		}
		out_file << endl;
	}
	out_file << endl;

	while (check == 2) {

		int empty = 0;
		int same = 0;

		Cycle();

		out_file << "Gen " << count << endl;
		for (int i = 0; i < newBoard->returnRows(); i++) {
			for (int j = 0; j < newBoard->returnCols(); j++) {
				out_file << newBoard->returnChar(i, j);
			}
			out_file << endl;
		}

		for (int i = 0; i <= gameBoard->returnRows(); i++) {
			for (int j = 0; j <= gameBoard->returnCols(); j++) {
				if (gameBoard->returnChar(i, j) == newBoard->returnChar(i, j)) {
					same += 1;
				}
				if (newBoard->returnChar(i, j) == '-') {
					empty += 1;

				}
			}
		}

		for (int i = 0; i <= gameBoard->returnRows(); i++) {
			for (int j = 0; j <= gameBoard->returnCols(); j++) {
				gameBoard->changeUnit(i, j, newBoard->returnChar(i, j));
			}
		}

		mirrorCreation();

		if (empty == total) {
			out_file << "Board is Empty" << endl;
			break;
		}
		else if (same == total) {
			out_file << "Stability Achieved" << endl;
			break;
		}

		out_file << endl;
		count++;
	}
}
