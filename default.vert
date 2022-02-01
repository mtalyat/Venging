#version 330 core
//OLD
//position
//layout (location = 0) in vec3 aPos;
//colors
//layout (location = 1) in vec3 aColor;

//TEMP
layout (location = 0) in uint x;
layout (location = 1) in uint y;
layout (location = 2) in uint z;
layout (location = 3) in uint r;
layout (location = 4) in uint g;
layout (location = 5) in uint b;

//output color to frag shader
out vec3 color;

uniform mat4 camMatrix;
uniform mat4 meshMatrix;
//uniform uint palette[256];

void main()
{
	gl_Position = camMatrix * meshMatrix * vec4(float(x), float(y), float(z), 1.0);

	//base color on index from vertices
	color = vec3(float(r) / 255.0, float(g) / 255.0, float(b) / 255.0);
}