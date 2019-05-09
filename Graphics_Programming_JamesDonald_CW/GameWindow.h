#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>

class GameWindow
{
public:
	GameWindow(); // constructor
	~GameWindow(); // deconstructor
	void initWindow(); // create the window
	void swapBuffer(); // swap the buffers
	void displayCleanup(float r, float g, float b, float a); // clear the display 

	float getWidth();// return the width
	float getHeight(); //return height
	SDL_GLContext glContext; // context for window 

private:

	void errorChecking(std::string errorString); // error display

	SDL_Window* sdlWindow; //holds pointer to out window
	float screenWidth, screenHeight; // width and height of screen
};

