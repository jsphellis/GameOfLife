
#include "Board.h"

/*
Board
This constructor creates a 2D array of pointers to char objects with a default 5 rows and 7 columns
*/
Board::Board() {
	rows = 5;
	cols = 7;
	board = new char* [rows];

	for (int i = 0; i < rows; i++) {
		board[i] = new char[cols];
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			board[i][j] = '-';
		}
	}
}


/*
Board
This overload constructor creates a 2D array of pointers to char objects with a given value for rows and columns
@param item: int m_rows, int m_cols
*/
Board::Board(int m_rows, int m_cols) {
	rows = m_rows;
	cols = m_cols;
	board = new char* [rows];
	for (int i = 0; i < rows; i++) {
		board[i] = new char[cols];
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			board[i][j] = '-';
		}
	}
}

/*
~Board
The destructor for the Board class iterates through and deletes each row in the array before deleting the array entirely
*/
Board::~Board() {
	for (int i = 0; i < rows; i++) {
		delete[] board[i];
	}

	delete[] board;
}

/*
returnRows
This function returns the amount of rows (in array format because row 1 is 0)
@return return: int
*/
int Board::returnRows() {
	return rows - 1;
}

/*
returnCols
This function returns the amount of columns (in array format because column 1 is 0)
@return return: int
*/
int Board::returnCols() {
	return cols - 1;
}

/*
returnChar
This function takes in a row and column int to return the char at that index in the board
@param item: int row, int col
@return return: char
*/
char Board::returnChar(int row, int col) {
	return board[row][col];
}

/*
changeUnit
This function takes in a row, column, and char to change the index of a board to a given char (in this case X or -)
@param item: int row, int col, char c
@return return: void
*/
void Board::changeUnit(int row, int col, char c) {
	board[row][col] = c;
}

/*
print
This function simply iterates through the board and prints its contents
@return return: void
*/
void Board::print() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << board[i][j];
		}
		cout << endl;
	}
}

/*
boardSetup
This function takes in a user decimal, using it as a population density to populate the board.
@param item: int choice
@return return: void
*/
void Board::boardSetup() {
	int var;
	cout << "Please enter a decimal between 0 and 1 to represent your board 'X' density." << endl;
	float temp;
	cin >> temp;
	while ((temp > 1)) {
		cout << "Please enter a decimal between 0 and 1" << endl;
		cin >> temp;
	}
	var = temp * 100;
	
	int num;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			num = rand() % 100;
			if (num < var) {
				board[i][j] = 'X';
			}
			else {
				continue;
			}
		}
	}
}





