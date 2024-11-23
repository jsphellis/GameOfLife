#if !defined(USER_H)
#define USER_H

#include "Classic.h"
#include "Doughnut.h"
#include "Mirror.h"
#include <iostream>

class User {
private:
	Classic* classic;
	Doughnut* doughnut;
	Mirror* mirror;
public:
	User(int choice);
	~User();
	void Play();
};

#endif