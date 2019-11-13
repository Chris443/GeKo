
#include <iostream>

#include "Applications/K_Application/K_App.h"


#include <Windows.h>

void printMat(float mat[4][4]) {
	for (int x = 0; x < 4; ++x) {
		for (int y = 0; y < 4; ++y) {
			std::cout << mat[x][y] << " ";
		}
		std::cout << std::endl;
	}
}

int main()
{
	K_App app;
	app.run();
}

