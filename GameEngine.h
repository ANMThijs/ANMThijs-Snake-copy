#pragma once
#include <gl/glew.h>
#include <gl/wglew.h>
#include <Windows.h>

#include "Snake.h"

const int SCRWidth = 1000;
const int SCRHeight = 1000;

const float RectSize = 50.0f;

//The game engine, which handles all the variables and game events
class GameEngine
{
private:
	//Game variables and classes
	int score, ticks, dir;
	Snake snake;
	Apple apple, tempapple;

	//Handles if the snake has reached an apple
	bool applegotten;

public:
	bool running;

	GameEngine();
	~GameEngine();

	//Main setup
	void Init();

	//Setup after failed game
	void Reset();

	//Events
	void OnTimer();
	void Render();
	void Onkey();

	//Delete the engine
	void Destroy();
};

