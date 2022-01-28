#include "pch.h"
#include"VBO.h"

// Constructor that generates a Vertex Buffer Object and links it to vertices
VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	//store in buffer array, size of bytes, data itself, and...
//STREAM -> vertices modified once and used a few times
//STATIC -> vertices modified once and used many times
//DYNAMIC -> vertices modified many times and used many times
//  ...
//DRAW -> vertices modified and used to draw to screen
//READ
//COPY

	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

// Binds the VBO
void VBO::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// Unbinds the VBO
void VBO::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Deletes the VBO
void VBO::close()
{
	glDeleteBuffers(1, &ID);
}