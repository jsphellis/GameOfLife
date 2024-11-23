
#if !defined(BOARD_H)
#define BOARD_H

#include <string>
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

class Board {
private:
	int rows, cols;
	char** board;
public:
	Board();
	Board(int m_rows, int m_cols);
	~Board();
	void print();
	int returnRows();
	int returnCols();
	void changeUnit(int row, int col, char c);
	char returnChar(int row, int col);
	void boardSetup();
};

#endif
