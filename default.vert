#version 330 core

layout (location = 0) in uint v;

//output color to frag shader
out vec4 color;

uniform mat4 camMatrix;
uniform mat4 meshMatrix;
uniform int palette[256];
uniform float faceShades[4];

void main()
{
	//extract data from the input v
	int i = int(v >> 4);

	int faceId = i & 3;//11
	i >>= 2;
	int x = i & 63;//111111
	i >>= 6;
	int y = i & 63;
	i >>= 6;
	int z = i & 63;
	i >>= 6;
	int colorIndex = i & 255;//11111111

	//set position now that we have the x y z
	gl_Position = camMatrix * meshMatrix * vec4(float(x), float(y), float(z), 1.0);

	//base color on index from vertices
	int colorData = palette[colorIndex];

	//extract the rgba from the data
	float a = float(colorData & 255);
	float b = float((colorData >> 8) & 255);
	float g = float((colorData >> 16) & 255);
	float r = float((colorData >> 24) & 255);
	
	//multiply all colors (not alpha) by face value
	float f = faceShades[faceId];

	//pass into frag shader
	color = vec4(r * f / 255.0, g * f / 255.0, b * f / 255.0, a / 255.0);
}