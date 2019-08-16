#pragma once

#include <iostream>
#include "../../GeKo/window.h"
#include "../../Math/mat4x4.h"

class K_App {
public:
	K_App();
	void run();
private:
	void init();
	void step();

	gke::window w;
};