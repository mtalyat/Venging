#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include "Object.h"

std::string get_file_contents(const char* filename);

/// <summary>
/// An interface for vertex and fragment shaders.
/// </summary>
class Shader
	: public Object
{
public:
	GLuint ID;
	Shader(const char* vertexFile, const char* fragmentFile);

	void activate();
	void close();

private:
	// Checks if the different Shaders have compiled properly
	void compileErrors(unsigned int shader, const char* type);
};

#endif