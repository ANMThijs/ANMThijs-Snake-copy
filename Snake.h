#pragma once
#include <gl/glew.h>
#include <gl/wglew.h>
#include <stdio.h>

#include "Apple.h"

//The color of the snake
#define SnakeCol 0.1f, 0.8f, 0.1f

//The cube class which are the cubes in the snake. They're actually rectangles
class Cube {
public:
	int x, y, dir;
};

class Snake
{
public:
	//The length of the snake
	int length;
	//The cubes in the snake
	Cube cubes[400];

	//Is true if the snake hits it's own body
	bool selfcoll;

	Snake();
	~Snake();

	//Set's the default snake settings
	void Init();

	//Function to add a rectangle after the snake reached an apple
	void AddLength(int x, int y);
	//Function to update the position of the snake cubes
	void Move(int dir);

	//Function to draw the snake
	void Render();
};