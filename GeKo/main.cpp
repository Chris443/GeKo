#include <glad/glad.h>
#include "GLFW/glfw3.h"


#include <iostream>
 
#include "Applications/KatiApplication/K_App.h"
#include "Applications/GebertApplication/G_App.h"

#include "Math/vec3.h"


int main()
{
	gkm::vec3 v1(1, 2, 3);
	gkm::vec3 v2(4, 5, 6);

	gkm::vec3 t = gkm::cross(v1, v2);
	std::cout << gkm::dot(v1, v2) << std::endl;
	std::cout << t.x << "," <<t.y << "," << t.z << std::endl;



}