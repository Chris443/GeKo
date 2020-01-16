#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormals;

uniform mat4 mat;
uniform mat4 view;
uniform mat4 proj;

out vec2 texCoord;

void main()
{
	gl_Position = proj * view * mat * vec4(aPos , 1.0);
	texCoord = aTexCoord;
}
