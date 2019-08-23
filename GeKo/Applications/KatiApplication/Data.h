#pragma once
#include <vector>

//Data for a Cube

float vertices[] = {
	//Front
	//positions			//colors
	 0.5f,  0.5f, 0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f,// top right
	 0.5f, -0.5f, 0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,// bottom right
	-0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,// bottom left
	-0.5f,  0.5f, 0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f,// top left 
	//Back											 ,
	 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f,// top right
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,// bottom right
	- 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,// bottom left
	- 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f// top left 



};
std::vector<unsigned int> indices = { 
	0, 1, 2,    
	3, 0, 2,    
			    
	 4,5,6,
	 7,4,6,

	7,3,2,
	2,6,7,

	0,1,5,
	5,4,0,

	1,2,5,
	2,5,6,

	3,7,4,
	4,0,3
};