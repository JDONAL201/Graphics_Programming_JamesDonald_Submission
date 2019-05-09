#pragma once

#include <vector>
#include <string>

#include <GL\glew.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Common.h"

#include "Mesh.h"
#include "Shader.h"

class Skybox
{
public:
	Skybox();

	Skybox(std::vector<std::string> faceLocations); // get the face locations from file to create skybox

	void renderSkybox(Camera camera); // render the skybox
	void createCube(); // the cube to texture
	~Skybox();

private:
	Mesh* skyCube; // the mesh to texture
	Shader* skyboxShader;// the shader for the skybox

	GLuint textureID;// the id 
	GLuint uniformProjection, uniformView; // uniform location
};

