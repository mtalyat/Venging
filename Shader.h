#ifndef SHADER_H
#define SHADER_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include "Object.h"
#include "Helper.h"
#include "ColorPalette.h"
#include "Color.h"

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

	void setInt(GLint value, const GLchar* name);
	void setFloat(GLfloat value, const GLchar* name);
	void setVector2(glm::fvec2 value, const GLchar* name);
	void setVector3(glm::fvec3 value, const GLchar* name);
	void setVector4(glm::fvec4 value, const GLchar* name);
	void setMatrix3(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE);
	void setMatrix4(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE);
	void setPalette(ColorPalette* palette, const GLchar* name);
private:
	// Checks if the different Shaders have compiled properly
	void compileErrors(unsigned int shader, const char* type);
};

#endif