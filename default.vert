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
layout (location = 3) in uint colorIndex;

//output color to frag shader
out vec4 color;

uniform mat4 camMatrix;
uniform mat4 meshMatrix;
uniform int palette[256];

void main()
{
	gl_Position = camMatrix * meshMatrix * vec4(float(x), float(y), float(z), 1.0);

	//base color on index from vertices
	int colorData = palette[colorIndex];

	//extract the rgba from the data
	float a = float(colorData & 255);
	float b = float((colorData >> 8) & 255);
	float g = float((colorData >> 16) & 255);
	float r = float((colorData >> 24) & 255);

	//pass into frag shader
	color = vec4(r / 255.0, g / 255.0, b / 255.0, a / 255.0);
}