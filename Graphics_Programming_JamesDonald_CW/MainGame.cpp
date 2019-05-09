#include "MainGame.h"

MainGame::MainGame()
{
	gameState = GameStates::PLAY; // set game state
	GameWindow* gameWindow = new GameWindow(); //new display
	Shader* shader();
	Shader* shaderReflect();
	Shader* shaderExplode();
	Shader* holoShader();

	const char* message = ("Student name :James Donald \nStudent ID: S1229955 \nModule: Graphics Programming \n \n Custom shader is a combination of effects that when combined \n produce a holographic scanning effect on the object \n");
	printf(message);


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void MainGame::initModels()
{
	spiderman = Model();
	spiderman.loadModel("..//Resources//models//Spiderman//Amazing Spidey.obj","Spiderman");
	spiderman.transform.SetPos(glm::vec3(180.0f, 20.0f, 80.0f));
	spiderman.transform.SetRot(glm::vec3(0.0f, -10.0f, 0.0f));
	spiderman.transform.SetScale(glm::vec3(1.0f, 1.0f, 1.0f));

	r2d2 = Model();
	r2d2.loadModel("..//Resources//models//r2d2//r2-d2.obj", "r2d2");
	r2d2.transform.SetPos(glm::vec3(180.0, 20.0, -15.0));
	r2d2.transform.SetRot(glm::vec3(0.0f, 5.0f, 0.0f));
	r2d2.transform.SetScale(glm::vec3(0.6f, 0.6f, 0.6f));

	policeCar = Model();
	policeCar.loadModel("..//Resources//models//PoliceCar//PoliceCar.obj", "PoliceCar");
	policeCar.transform.SetPos(glm::vec3(280.0f, 20.0f, -185.0f));
	policeCar.transform.SetRot(glm::vec3(0.0f, 10.0f, 0.0f));
	policeCar.transform.SetScale(glm::vec3(0.04f, 0.04f, 0.04f));


	ballHolo = Model();
	ballHolo.loadModel("..//Resources//models//sphere//only_quad_sphere.obj", "");
	ballHolo.transform.SetPos(glm::vec3(100.0, 0.0, -15.0));
	ballHolo.transform.SetRot(glm::vec3(0.0f, 5.0f, 0.0f));
	ballHolo.transform.SetScale(glm::vec3(15.3f, 15.3f, 15.3f));

	ballReflect = Model();
	ballReflect.loadModel("..//Resources//models//sphere//only_quad_sphere.obj", "");
	ballReflect.transform.SetPos(glm::vec3(100.0f, 0.0f, -95.0f));
	ballReflect.transform.SetRot(glm::vec3(0.0f, 10.0f, 0.0f));
	ballReflect.transform.SetScale(glm::vec3(15.3f, 15.3f, 15.3f));

	ballExplode = Model();
	ballExplode.loadModel("..//Resources//models//sphere//only_quad_sphere.obj", "");
	ballExplode.transform.SetPos(glm::vec3(100.0, 0.0, 70.0));
	ballExplode.transform.SetRot(glm::vec3(0.0f, 5.0f, 0.0f));
	ballExplode.transform.SetScale(glm::vec3(15.3f, 15.3f, 15.3f));


}
void MainGame::initSkybox()
{	// populate the list of strings to hold the faces of the skybox
	skyboxFaces.push_back("..\\Resources\\textures\\Skybox\\right.jpg"); 
	skyboxFaces.push_back("..\\Resources\\textures\\Skybox\\left.jpg");
	skyboxFaces.push_back("..\\Resources\\textures\\Skybox\\up.jpg");
	skyboxFaces.push_back("..\\Resources\\textures\\Skybox\\down.jpg");
	skyboxFaces.push_back("..\\Resources\\textures\\Skybox\\front.jpg");
	skyboxFaces.push_back("..\\Resources\\textures\\Skybox\\back.jpg");

	skybox = Skybox(skyboxFaces);
	
}
void MainGame::initShaders() 
{
	std::string empty = "";
	shader.createShader("..\\Resources\\shaders\\Shader_Lighting\\shader.vert","..\\Resources\\shaders\\Shader_Lighting\\shader.frag",empty); // create the shader from the file locations given if no geomerty shader input empty string
	shaderReflect.createShader("..\\Resources\\shaders\\Shader_Reflection\\reflectionShader.vert", "..\\Resources\\shaders\\Shader_Reflection\\reflectionShader.frag",empty);
	shaderExplode.createShader("..\\Resources\\shaders\\Shader_Explode\\explodeShader.vert", "..\\Resources\\shaders\\Shader_Explode\\explodeShader.frag", "..\\Resources\\shaders\\Shader_Explode\\explodeShader.geom");
	holoShader.createShader("..\\Resources\\shaders\\Shader_Custom\\holographicShader.vert", "..\\Resources\\shaders\\Shader_Custom\\holographicShader.frag", empty);

}
void MainGame::run() 
{
	initSystems();
	gameLoop();
}
void MainGame::initInput() 
{
	SDL_SetRelativeMouseMode(SDL_TRUE); // mouse relative to game window

	//all keys are up so set all to false
	for (size_t i = 0; i < 1024; i++)
	{
		keysDown[i] = 0;
	}
}

void MainGame::initSystems() 
{
	gameWindow.initWindow(); //initalise game window 

	initInput();
	initShaders();
	initSkybox();
	initModels();

	camera = Camera(glm::vec3(-70.0f, 50.0f, -10.0f), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f,
		(float)gameWindow.getWidth() / gameWindow.getHeight(), 0.1f, 1000.0f, 0.0f, 0.0f, 80.0f, 0.1f);	 // create the camera



	counter = 1.0f;
	deltaTime = 0.0f;
	lastTimeCheck = 0.0f;
}
void MainGame::processTime()
{
	// used to calculate delta time
	lastTimeCheck = currentTime; 
	currentTime = SDL_GetPerformanceCounter();
	deltaTime =(double) ((currentTime - lastTimeCheck) /(double) SDL_GetPerformanceFrequency());

}
void MainGame::gameLoop()
{
	while (gameState != GameStates::EXIT) // while gamestate not exit , update these methods
	{
		processTime(); 
		draw();
		processInput();
		camera.cameraControl(deltaTime, keysDown);
	}
}
void MainGame::setReflectionShader(Transform transform) 
{
	
	shaderReflect.setMat4("model", transform.GetModel());
	shaderReflect.setMat4("view", camera.getView());
	shaderReflect.setMat4("projection", camera.getProjection());
	
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(transform.GetModel()));
	shaderReflect.setMat3("normalMatrix", normalMatrix);

	shaderReflect.setVec3("cameraPos", *camera.getPos());

}
void MainGame::setLights(Transform input) 
{

	shader.setMat4("model", input.GetModel());
	shader.setMat4("view", camera.getView());
	shader.setMat4("projection", camera.getProjection());

	shader.setVec3("directionalLight.colour", glm::vec3(0.0f,1.0f,1.0f));
	shader.setVec3("directionalLight.colourDiff", glm::vec3(1.0f,1.0f,1.0f));
	shader.setVec3("directionalLight.direction", glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setFloat("directionalLight.ambientIntensity", 0.1f);
	shader.setFloat("directionalLight.diffuseIntensity", 0.1f);

}

void MainGame::setShaderExplode(Transform input)
{	
	shaderExplode.setFloat("time", 1.0f * counter);
	shaderExplode.setMat4("model", input.GetModel());
	shaderExplode.setMat4("view", camera.getView());
	shaderExplode.setMat4("projection", camera.getProjection());


}
void MainGame::setHolographicShader(Transform input, glm::vec3 effectDirection,glm::vec4 holoColor, glm::vec4 holoRimColor, 
					float glowSpeed, float glowSpacing, float scanSpeed,float scanSpacing, float rimIntensity, float glitchSpeed, float glitchIntensity, float flickerSpeed, float overallIntensity)
{

	holoShader.setMat4("model", input.GetModel()); // Set the model matrix 
	holoShader.setMat4("view", camera.getView()); // set the view matrix
	holoShader.setMat4("projection", camera.getProjection()); // set the projection matrix
	glm::mat3 normalMatrix = glm::transpose(input.GetModel()* camera.getView()); // get the normal matrix outside of the shader, less expensive.
	holoShader.setMat3("normalMatrix", normalMatrix); // set the normal matrix

	holoShader.setVec3("camPos", *camera.getPos());
	//direction
	holoShader.setVec3("dir", effectDirection);
	//Colour of the shader effect
	holoShader.setVec4("holoColor", holoColor);

	//Glitching offset effect
	holoShader.setFloat("glitchSpeed", glitchSpeed);
	holoShader.setFloat("glitchIntensity", glitchIntensity);
	holoShader.setFloat("time", 1.0f * counter);


	//The rim colour & intensity
	holoShader.setVec4("rimGlowColor", holoRimColor);
	holoShader.setFloat("rimInensity", rimIntensity);

	//The strobing glow effect
	holoShader.setFloat("glowSpeed", glowSpeed); 
	holoShader.setFloat("glowSpace", glowSpacing); 

	// The holographic bars speed and spacing
	holoShader.setFloat("scanSpeed", scanSpeed);
	holoShader.setFloat("scanSpace", scanSpacing);

	// Flickering light speed
	holoShader.setFloat("flickerSpeed", 1.0);

	// overall intensity ( texture blending not working to make tranparent ? )
	holoShader.setFloat("alphaIntensity", overallIntensity);


}
void MainGame::draw()
{

	gameWindow.displayCleanup(0.0f, 0.0f, 0.0f, 1.0f);

	modelRenderer();

	counter = counter + 0.1f;
	
	glUseProgram(0);

	gameWindow.swapBuffer();
}
void MainGame::modelRenderer() 
{
	skybox.renderSkybox(camera);

	shaderExplode.useShader();
	setShaderExplode(spiderman.transform);
	spiderman.renderModel();
	
	setShaderExplode(ballExplode.transform);
	ballExplode.renderModel();

	shaderReflect.useShader();
	setReflectionShader(policeCar.transform);
	policeCar.renderModel();

	setReflectionShader(ballReflect.transform);
	ballReflect.renderModel();

	holoShader.useShader();
	setHolographicShader(r2d2.transform,posY, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f),0.1f,0.03f,1.0f,1.5f,0.0f,0.5f,10.0f,1.0f,0.7f);
	r2d2.renderModel();

	setHolographicShader(ballHolo.transform, negY, glm::vec4(1.0f, 0.6f, 0.0f, 1.0f), glm::vec4(0.0f, 0.6f, 0.0f, 1.0f), 0.05f, 0.05f, 0.7f, 1.4f, 0.2f, 1.1f, 10.0f, 1.0f, 0.7f);
	ballHolo.renderModel();


}

void MainGame::processInput()
{
	SDL_Event event;


	while (SDL_PollEvent(&event) != 0) //get and process events
	{
		if(event.type == SDL_MOUSEMOTION)
		{

			GLfloat x, y;

			x = event.motion.xrel; // x equal to the relative x mouse motion
			y = event.motion.yrel; // y "" """

			if (firstMove) // check if initial move
			{
				lastXpos = x; // last pos = to start x pos
				lastYpos = y; // """ y pos
				firstMove = false; // initalised first move
			}
			changeInX = x - lastXpos; // change in motion is set to the x value minus last position
			changeInY = y - lastYpos;// "" "" y value ""
			camera.mouseMotion(changeInX, changeInY); // send to camera mouse motion to use to rotate the camera relative to the mouse position
		}
		else if (event.type == SDL_KEYDOWN)  // check for when a key event down has occurred
		{
			switch (event.key.keysym.sym) // switch through the keys
			{
			case SDLK_w: // W down
				keysDown[SDLK_w] = true; // set the enum for w in the keydown array to true to allow for cont movement/press down
				break;
			case SDLK_a:
				keysDown[SDLK_a] = true; // ""
				break;
			case SDLK_s:
				keysDown[SDLK_s] = true; // ""
				break;
			case SDLK_d:
				keysDown[SDLK_d] = true;//""
				break;
		
			case SDLK_ESCAPE:
				gameState = GameStates::EXIT; // change the game state to exit which will call SDL QUIT and exit the application
				break;
			}
		}
		else if (event.type == SDL_KEYUP) 
		{
			switch (event.key.keysym.sym) 
			{
			case SDLK_w:
				keysDown[SDLK_w] = false; // same as above but checking for keys been up and returning the bool to false.
				break;
			case SDLK_a:
				keysDown[SDLK_a] = false;
				break;
			case SDLK_s:
				keysDown[SDLK_s] = false;
				break;
			case SDLK_d:
				keysDown[SDLK_d] = false;
				break;
			}

		}
	}
}
MainGame::~MainGame()
{
}
