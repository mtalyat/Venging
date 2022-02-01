#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include "Object.h"
#include "Helper.h"

/// <summary>
/// An interface for vertex and fragment shaders.
/// </summary>
class Shader
	: public Object
{
public:
	GLuint ID;
	Shader(const char* vertexFile, const char* fragmentFile);

	void use();
	void close();
	void deleteProgram();

private:
	// Checks if the different Shaders have compiled properly
	void compileErrors(unsigned int shader, const char* type);
};

#endif