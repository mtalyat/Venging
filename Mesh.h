#ifndef MESH_H
#define MESH_H

#include <GLFW/glfw3.h>
#include <cstdbool>
#include "Object.h"
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Mesh :
    public Object
{
public:
    Mesh();
    ~Mesh();

    void render(Shader* shaderProgram);

    void setVertices(int* verts, int amount);
    void setTriangles(int* tris, int amount);

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
};

#endif
