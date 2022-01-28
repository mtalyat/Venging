#version 330 core
//position
layout (location = 0) in vec3 aPos;
//colors
layout (location = 1) in vec3 aColor;

//output color to frag shader
out vec3 color;

uniform mat4 camMatrix;

void main()
{
	gl_Position = camMatrix * vec4(aPos, 1.0);

	color = aColor;
}