#if !defined(MIRROR_H)
#define MIRROR_H

#include <string>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include "Board.h"
#include <fstream>

class Mirror : public Board {
private:
	Board* gameBoard;
	Board* newBoard;
	Board* mirrorBoard;
public:
	Mirror(int rows, int cols);
	Mirror(string fileInput);
	~Mirror();
	void Cycle();
	void mirrorCreation();
	int neighborCheck(int row, int column);
	void playDelay();
	void playPause();
	void playFile(string outputFile);
};

#endif