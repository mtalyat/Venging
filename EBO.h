#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>
#include "Object.h"

/// <summary>
/// Elements Buffer Object.
/// </summary>
class EBO
	: public Object
{
public:
	// ID reference of Elements Buffer Object
	GLuint ID;
	// Constructor that generates a Elements Buffer Object and links it to indices
	EBO(GLuint* indices, GLsizeiptr size);

	// Binds the EBO
	void bind();
	// Unbinds the EBO
	void unbind();
	// Deletes the EBO
	void deleteEBO();
};

#endif