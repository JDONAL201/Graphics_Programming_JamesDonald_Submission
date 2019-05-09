#pragma once
#include <iostream>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <vector>
#include "transform.h"

class Mesh
{
public:
	Mesh();

	void createMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void renderMesh();
	void clearMesh();
	Transform transform;
	~Mesh();
private:

	GLuint VAO, VBO, IBO;
	GLsizei drawCount;
};

