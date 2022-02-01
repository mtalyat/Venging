#include "Mesh.h"

Mesh::Mesh()
{
	//GLfloat vertices[] =
	//{
	//	//	coordinates				colors
	//	-0.5f, 0.0f, 0.5f,		0.83f, 0.70f, 0.44f,	//bottom left forward
	//	-0.5f, 0.0f, -0.5f,		0.83f, 0.70f, 0.44f,	//bottom left backward
	//	0.5f, 0.0f, -0.5f,		0.83f, 0.70f, 0.44f,	//bottom right backward
	//	0.5f, 0.0f, 0.5f,		0.83f, 0.70f, 0.44f,	//bottom right forward
	//	0.0f, 0.8f, 0.0f,		0.92f, 0.86f, 0.76f,	//top
	//};

	////triangles' indices for the vertices
	//GLuint indices[] =
	//{
	//	0, 1, 2,
	//	0, 2, 3,
	//	0, 4, 1,
	//	1, 4, 2,
	//	2, 4, 3,
	//	3, 4, 0,
	//};

	//vertices = nullptr;
	//vertexCount = 0;
	//triangles = nullptr;
	//triangleCount = 0;

	int vTemp[] =
	{
	//	X  Y  Z   R    G    B
		0, 0, 2, 212, 176, 112,
		0, 0, 0, 212, 176, 112,
		2, 0, 0, 212, 176, 112,
		2, 0, 2, 212, 176, 112,
		1, 2, 1, 212, 176, 112
	};
	int tTemp[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 4, 1,
		1, 4, 2,
		2, 4, 3,
		3, 4, 0,
	};

	setVertices(vTemp, 30);
	setTriangles(tTemp, 18);

	//Create VAO
	vao = new VAO();
	vao->bind();

	vbo = new VBO(vertices, sizeof(int) * vertexCount);
	ebo = new EBO(triangles, sizeof(int) * triangleCount);

	//https://stackoverflow.com/questions/18919927/passing-uint-attribute-to-glsl
	
	//TEMP
	//link X, Y, Z, R, G, B
	//int i = 0;
	//for (; i < 6; i++)
	//{
	//	vao->linkAttribute(*vbo, i, 1, GL_UNSIGNED_INT, 6 * sizeof(unsigned int), (void*)(i * 1 * sizeof(unsigned int)));
	//}
	vao->linkAttribute(*vbo, 0, 1, GL_UNSIGNED_INT, 6 * sizeof(int), (void*)0);
	vao->linkAttribute(*vbo, 1, 1, GL_UNSIGNED_INT, 6 * sizeof(int), (void*)(1 * sizeof(int)));
	vao->linkAttribute(*vbo, 2, 1, GL_UNSIGNED_INT, 6 * sizeof(int), (void*)(2 * sizeof(int)));
	vao->linkAttribute(*vbo, 3, 1, GL_UNSIGNED_INT, 6 * sizeof(int), (void*)(3 * sizeof(int)));
	vao->linkAttribute(*vbo, 4, 1, GL_UNSIGNED_INT, 6 * sizeof(int), (void*)(4 * sizeof(int)));
	vao->linkAttribute(*vbo, 5, 1, GL_UNSIGNED_INT, 6 * sizeof(int), (void*)(5 * sizeof(int)));

	//OLD
	////link vertices to vec3 in shader
	//vao->linkAttribute(*vbo, 0, 3, GL_UNSIGNED_INT, 6 * sizeof(unsigned int), (void*)0);
	////link colors to vec3 in shader
	//vao->linkAttribute(*vbo, 1, 3, GL_UNSIGNED_INT, 6 * sizeof(unsigned int), (void*)(3 * sizeof(unsigned int)));

	//all done with VAO, VBO and EBO
	vao->unbind();
	vbo->unbind();
	ebo->unbind();
}

Mesh::~Mesh()
{
	vao->deleteVAO();
	vbo->deleteVBO();
	ebo->deleteEBO();

	delete(vao);
	delete(vbo);
	delete(ebo);

	if(vertices != nullptr)
		delete[] vertices;
	if(triangles != nullptr)
		delete[] triangles;
}

void Mesh::render(Shader* shaderProgram)
{
	//update matrices
	//update uniforms

	//use this shader
	shaderProgram->use();

	//bind this mesh for the shader
	vao->bind();

	//then render it
	glDrawElements(GL_TRIANGLES, triangleCount, GL_UNSIGNED_INT, 0);

	//close
	//vao->unbind();
}

void Mesh::setVertices(int* verts, int amount)
{
	if (vertices != nullptr)
	{
		delete[] vertices;
	}

	vertexCount = amount;
	vertices = new GLuint[amount];

	int i = 0;
	for (; i < amount; i++)
	{
		vertices[i] = (GLuint)verts[i];
	}
}

void Mesh::setTriangles(int* tris, int amount)
{
	if (triangles != nullptr)
	{
		delete[] triangles;
	}

	triangleCount = amount;
	triangles = new GLuint[amount];

	int i = 0;
	for (; i < amount; i++)
	{
		triangles[i] = (GLuint)tris[i];
	}
}
