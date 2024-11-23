#if !defined(DOUGHNUT_H)
#define DOUGHNUT_H

#include <string>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <fstream>
#include "Board.h"

class Doughnut {
private:
	Board* gameBoard;
	Board* newBoard;
	Board* doughnutBoard;
public:
	Doughnut(int rows, int cols);
	Doughnut(string fileInput);
	~Doughnut();
	void Cycle();
	void doughnutCreation();
	int neighborCheck(int row, int column);
	void playDelay();
	void playPause();
	void playFile(string outputFile);
};

#endif