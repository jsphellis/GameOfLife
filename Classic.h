
#if !defined(CLASSIC_H)
#define CLASSIC_H

#include <string>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include "Board.h"
#include <fstream>

class Classic{
private:
	Board* gameBoard;
	Board* newBoard;
public:
	Classic(int rows, int cols);
	Classic(string fileInput);
	~Classic();
	void Cycle();
	int neighborCheck(int row, int column);
	void playDelay();
	void playPause();
	void playFile(string outputFile);
};

#endif