#include "Classic.h"

/*
Classic
This constructor creates and sets up a Board object with a given size, along with a seperate newBoard for copying
*/
Classic::Classic(int rows, int cols) {
	gameBoard = new Board(rows, cols);
	newBoard = new Board(gameBoard->returnRows() + 1, gameBoard->returnCols() + 1);
}

/*
Classic
This constructor creates a Board object with a given size and mapping (from a text file), along with a seperate newBoard for copying
*/
Classic::Classic(string fileInput) {
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
}

/*
~Classic
The destructor has no need to make any calls or functions since the Board objects automatically call their own destructors
*/
Classic::~Classic() {}

/*
Cycle
This function iterates through the gameBoard and calls neighborCheck on each index. neighborCheck returns an int that tells the function to adjust the newBoard accordingly.
@return return: void
*/
void Classic::Cycle() {
	for (int i = 0; i <= gameBoard->returnRows(); i++) {
		for (int j = 0; j <= gameBoard->returnCols(); j++) {
            int val = neighborCheck(i, j);
			if (val <= 1) {
				newBoard->changeUnit(i, j, '-');
			}
			else if (val == 2) {
				if (gameBoard->returnChar(i, j) == 'X')
					newBoard->changeUnit(i, j, 'X');
				else
					newBoard->changeUnit(i, j, '-');
			}
			else if (val == 3) {
				newBoard->changeUnit(i, j, 'X');
			}
			else if (val >= 4) {
				newBoard->changeUnit(i, j, '-');
			}
		}
	}
}

/*
neighborCheck
This function takes two int values as a row and column location, then iterates when available (within the board) around the index and returns an int of how many X characters surround the given unit
@param item : int row, int column
@return return: int
*/
int Classic::neighborCheck(int row, int column) {
	int cnt = 0;
	if (row == 0) {
		if (column == 0) {
			for (int i = row; i <= row + 1; i++) {
				for (int j = column; j <= column + 1; j++) {
					if ((i == row) && (j == column)) {
						continue;
					}
					else if (gameBoard->returnChar(i, j) == 'X') {
						cnt += 1;
					}
					else {
						continue;
					}
				}
			}
		}
		else if (column == gameBoard->returnCols()) {
			for (int i = row; i <= row + 1; i++) {
				for (int j = column - 1; j <= column; j++) {
					if ((i == row) && (j == column)) {
						continue;
					}
					else if (gameBoard->returnChar(i, j) == 'X') {
						cnt += 1;
					}
					else {
						continue;
					}
				}
			}
		}
		else {
			for (int i = row; i <= row + 1; i++) {
				for (int j = column - 1; j <= column + 1; j++) {
					if ((i == row) && (j == column)) {
						continue;
					}
					else if (gameBoard->returnChar(i, j) == 'X') {
						cnt += 1;
					}
					else {
						continue;
					}
				}
			}
		}
	}

	else if (row == gameBoard->returnRows()) {
		if (column == 0) {
			for (int i = row - 1; i <= row; i++) {
				for (int j = column; j <= column + 1; j++) {
					if ((i == row) && (j == column)) {
						continue;
					}
					else if (gameBoard->returnChar(i, j) == 'X') {
						cnt += 1;
					}
					else {
						continue;
					}
				}
			}
		}
		else if (column == gameBoard->returnCols()) {
			for (int i = row - 1; i <= row; i++) {
				for (int j = column - 1; j <= column; j++) {
					if ((i == row) && (j == column)) {
						continue;
					}
					else if (gameBoard->returnChar(i, j) == 'X') {
						cnt += 1;
					}
					else {
						continue;
					}
				}
			}
		}
		else {
			for (int i = row - 1; i <= row; i++) {
				for (int j = column - 1; j <= column + 1; j++) {
					if ((i == row) && (j == column)) {
						continue;
					}
					else if (gameBoard->returnChar(i, j) == 'X') {
						cnt += 1;
					}
					else {
						continue;
					}
				}
			}
		}
	}

	else {
		if (column == 0) {
			for (int i = row - 1; i <= row + 1; i++) {
				for (int j = column; j <= column + 1; j++) {
					if ((i == row) && (j == column)) {
						continue;
					}
					else if (gameBoard->returnChar(i, j) == 'X') {
						cnt += 1;
					}
					else {
						continue;
					}
				}
			}
		}
		else if (column == gameBoard->returnCols()) {
			for (int i = row - 1; i <= row + 1; i++) {
				for (int j = column - 1; j <= column; j++) {
					if ((i == row) && (j == column)) {
						continue;
					}
					else if (gameBoard->returnChar(i, j) == 'X') {
						cnt += 1;
					}
					else {
						continue;
					}
				}
			}
		}
		else {
			for (int i = row - 1; i <= row + 1; i++) {
				for (int j = column - 1; j <= column + 1; j++) {
					if ((i == row) && (j == column)) {
						continue;
					}
					else if (gameBoard->returnChar(i, j) == 'X') {
						cnt += 1;
					}
					else {
						continue;
					}
				}
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
void Classic::playDelay() {
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
void Classic::playPause() {
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


	cout << "Press Enter to proceed to the next generation" << endl;
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
void Classic::playFile(string outputFile) {
	int total = (gameBoard->returnRows() + 1) * (gameBoard->returnCols() + 1);
	int empty = 0;

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
	
	int check = 2;
	int count = 1;

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
		for (int i = 0; i <= newBoard->returnRows(); i++) {
			for (int j = 0; j <= newBoard->returnCols(); j++) {
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

