#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>
#include "Object.h"

/// <summary>
/// Vertex Buffer Object.
/// </summary>
class VBO
	: public Object
{
public:
	GLuint ID;
	VBO(GLuint* vertices, GLsizeiptr size);

	void bind();
	void unbind();
	void deleteVBO();
};

#endif
