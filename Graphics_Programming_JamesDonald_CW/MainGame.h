#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <vector>
#include "GameWindow.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Skybox.h"
#include "Model.h"
#include <Assimp/Importer.hpp>
enum class GameStates { PLAY, EXIT };
class MainGame
{
public:
	MainGame();
	~MainGame();
	void run();
	
	GLfloat deltaTime,lastTimeCheck;


private:

	void processInput();
	void gameLoop();
	void draw();
	void processTime();
	void modelRenderer();

	//INITIALISE
	void initShaders();
	void initModels();
	void initInput();
	void initSkybox();
	void initSystems();
	
	//setting shaders
	void setLights(Transform input);
	void setReflectionShader(Transform input);
	void setShaderExplode(Transform input);
	void setHolographicShader(Transform input, glm::vec3 effectDirection, 
											glm::vec4 holoColor, glm::vec4 holoRimColor, float glowSpeed, float glowSpacing, float scanSpeed, 
																	float scanSpacing, float rimIntensity, float glitchSpeed, float glitchIntensity, float flickerSpeed, float overallIntensity);
	//INPUT
	bool keysDown[1024];
	bool firstMove;

	//FOR TIME
	GLfloat currentTime = SDL_GetPerformanceCounter();
	GLfloat lastXpos,lastYpos,changeInX,changeInY;

	//SHADERS
	Shader shader,shaderReflect,shaderExplode,holoShader;

	Skybox skybox;
	std::vector<std::string> skyboxFaces;
	
	Camera camera;

	//WINDOW
	GameWindow gameWindow;
	GameStates gameState;

	Model spiderman;
	Model teapot;
	Model r2d2;
	Model ballHolo;
	Model ballReflect;
	Model ballExplode;
	Model silverSurfer;
	Model policeCar;

	// direction vectors
	glm::vec3 posX = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 posY = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 posZ = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 negX = glm::vec3(-1.0f, 0.0f, 0.0f);
	glm::vec3 negY = glm::vec3(0.0f, -1.0f, 0.0f);
	glm::vec3 negZ = glm::vec3(0.0f, 0.0f, -1.0f);

	float counter = 0;
	bool moveUp = false, moveRight = false;
};

