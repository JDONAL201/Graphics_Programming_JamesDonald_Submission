#include "GameWindow.h"



GameWindow::GameWindow()
{
	sdlWindow = nullptr; //initialise to generate null access violation for debugging. 
	screenWidth = 1024.0f; // set sceen width
	screenHeight = 768.0f; // set screen height
	
}

float GameWindow::getWidth() { return screenWidth; } // getters to obtain screen width value
float GameWindow::getHeight() { return screenHeight; } // same but for height

void GameWindow::errorChecking(std::string errorString) // used for displaying errors
{
	std::cout << errorString << std::endl; // write the string to console window
	std::cout << "press any  key to quit..."; // write string for action
	int in; // hold int for any input
	std::cin >> in; // any input will quit out of application
	SDL_Quit(); // quit
}

void GameWindow::swapBuffer()
{
	SDL_GL_SwapWindow(sdlWindow); //swap buffers
}
void GameWindow::displayCleanup(float r, float g, float b, float a)
{
	glClearDepth(1.0); // clears the depth
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear both the color and the deepth buffers
}
void GameWindow::initWindow()
{
	SDL_Init(SDL_INIT_EVERYTHING); //initalise everything

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); //Min no of bits used to diplay colour
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // set up double buffer   

	sdlWindow = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)screenWidth, (int)screenHeight, SDL_WINDOW_OPENGL); // create window, cast the float values to ints

	if (sdlWindow == nullptr) // check window created properly 
	{
		errorChecking("window failed to create"); //output error message
	}

	glContext = SDL_GL_CreateContext(sdlWindow);

	if (glContext == nullptr)
	{
		errorChecking("SDL_GL context failed to create");//output error message
	}

	GLenum error = glewInit(); //initialise glew
	if (error != GLEW_OK)//check glew initialised correctly 
	{
		errorChecking("GLEW failed to initialise");//output error message
	}
	///ENABLE Z BUFFERING AND FACE CULLING
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // clear colour
}

GameWindow::~GameWindow() // deconstructer to clean up SDL and Context.
{
	SDL_GL_DeleteContext(glContext); // delete the context from the heap
	SDL_DestroyWindow(sdlWindow); // destroy the window from the heap
	SDL_Quit();  //quit using SDL
}