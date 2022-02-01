#ifndef MESH_H
#define MESH_H

#include <GLFW/glfw3.h>
#include <cstdbool>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include "Object.h"
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Transform.h"

class Mesh :
    public Object
{
public:
    Mesh();
    ~Mesh();

    void render(Transform* transform, Shader* shaderProgram);

    void setVertices(int* verts, int amount);
    void setTriangles(int* tris, int amount);
    void rebuild();

private:
    //shader stuff
    VAO* vao;
    VBO* vbo;
    EBO* ebo;

    bool redrawNextFrame;

    GLuint* vertices;
    int vertexCount;
    GLuint* triangles;
    int triangleCount;

    void matrix(Transform* transform, Shader* shaderProgram);
};

#endif
