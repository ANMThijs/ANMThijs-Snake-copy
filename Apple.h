#pragma once
#include <gl/glew.h>
#include <gl/wglew.h>

#include "RandomInt.h"

//The apple color
#define AppleCol 0.9f, 0.2f, 0.2f

//The apple
class Apple
{
public:
	//Position
	int x, y;

	Apple();
	~Apple();

	//Init functions, the one without parameters generates a random position, the other one sets the 
	//parameters as the position, which is only used on the start of the game
	void Init();
	void Init(int x, int y);

	//Draw the apple
	void Render();
};