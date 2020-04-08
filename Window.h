#pragma once
#include "GameEngine.h"
#include "StartScreen.h"

//Function to create the window. Returns the window handle
HWND CreateWin(int xpos, int ypos, int width, int height, LPCWSTR title);

//Function to process events. Get's called with every event
LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);

//Message loop. Get's all messages and sends them to the window procedure
void MSGLoop();

//Function to Create an Opengl Context for the window. Returns the context created.
HGLRC CreateGLContext(HDC hdc);