#pragma once

#include <GL\glew.h>
#include <string>
#include "Common.h"


class Texture
{
public:
	Texture();
	Texture(const char* filepath);

	bool loadTexture(); // loading a texture from file and checking if should be alpha or not
	bool loadTextureA();

	void useTexture(); // use the texture loaded
	void clearTexture();

	~Texture();

private:
	GLuint textureID; // texture id 
	int width, height, numComponents; // int values for the dimentions 
	const char* filePath;
};


