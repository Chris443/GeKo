#pragma once

#include <iostream>
#include "../../Core/window.h"

class K_App {
public:
	K_App();
	void run();
private:
	void init();

	gke::window w;
};