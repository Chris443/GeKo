#version 330 core
layout (location = 0)

in vec3 aPos;
uniform vec3 pos;

void main()
{
	gl_Position = vec4(aPos + pos, 1.0);
}
