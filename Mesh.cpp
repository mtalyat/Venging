#include "Mesh.h"

Mesh::Mesh()
{
	vao = nullptr;
	vbo = nullptr;
	ebo = nullptr;

	vertices = nullptr;
	vertexCount = 0;
	triangles = nullptr;
	triangleCount = 0;
}

Mesh::~Mesh()
{
	if (vao != nullptr)
	{
		vao->deleteVAO();
		vbo->deleteVBO();
		ebo->deleteEBO();

		delete(vao);
		delete(vbo);
		delete(ebo);
	}

	if(vertices != nullptr)
		delete[] vertices;
	if(triangles != nullptr)
		delete[] triangles;
}

void Mesh::render(Transform* transform, Shader* shaderProgram)
{
	//if nothing to render, do nothing
	if (triangleCount == 0) return;

	//update matrices
	//update uniforms
	matrix(transform, shaderProgram);

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

void Mesh::rebuild()
{
	//Create VAO
	vao = new VAO();
	vao->bind();

	vbo = new VBO(vertices, sizeof(int) * vertexCount);
	ebo = new EBO(triangles, sizeof(int) * triangleCount);

	//vertex info
	vao->linkAttribute(*vbo, 0, 1, GL_UNSIGNED_INT, 1 * sizeof(int), (void*)0);
	//lighting info
	//vao->linkAttribute(*vbo, 0, 1, GL_UNSIGNED_INT, 1 * sizeof(int), (void*)0); etc

	//all done with VAO, VBO and EBO
	vao->unbind();
	vbo->unbind();
	ebo->unbind();
}

void Mesh::matrix(Transform* transform, Shader* shaderProgram)
{
	//TODO: if no change from last time, do not do anything

	//get values from transform
	glm::vec3 pos = transform->getPosition().toVec3();
	glm::vec3 origin(0.0f);//temp
	glm::vec3 rotation(0.0f);//temp
	glm::vec3 scale = transform->getScale().toVec3();

	//modify matrix
	glm::mat4 meshMatrix(1.0f);
	meshMatrix = glm::translate(meshMatrix, origin);
	meshMatrix = glm::rotate(meshMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	meshMatrix = glm::rotate(meshMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	meshMatrix = glm::rotate(meshMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	meshMatrix = glm::translate(meshMatrix, pos - origin);
	meshMatrix = glm::scale(meshMatrix, scale);

	//set in shader
	shaderProgram->setMatrix4(meshMatrix, "meshMatrix");

	//glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID, "meshMatrix"), 1, GL_FALSE, glm::value_ptr(projection * view));
}
