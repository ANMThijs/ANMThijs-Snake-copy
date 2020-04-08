#include "GameEngine.h"

GameEngine::GameEngine() {

}

GameEngine::~GameEngine() {

}

void GameEngine::Init() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, SCRWidth, SCRHeight, 0.0f, 1.0f, -1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(SCRWidth / 2.0f, SCRHeight / 2.0f, 0.0f);

	this->snake.Init();
	this->apple.Init(15, 10);

	this->score = 0;
	this->ticks = 0;
	this->dir = 1;

	this->running = false;
	this->applegotten = false;
}

void GameEngine::Reset() {
	this->snake.Init();
	this->apple.Init(15, 10);

	this->score = 0;
	this->ticks = 0;
	this->dir = 1;

	this->applegotten = false;
}

void GameEngine::OnTimer() {
	this->ticks++;

	if (applegotten == true) {
		applegotten = false;
		this->snake.AddLength(this->tempapple.x, this->tempapple.y);
	}

	this->snake.Move(this->dir);

	if (snake.selfcoll == true) {
		this->running = false;
	}

	if ((this->snake.cubes[0].x == this->apple.x) && (this->snake.cubes[0].y == this->apple.y)) {
		this->applegotten = true;
		this->tempapple.x = this->apple.x;
		this->tempapple.y = this->apple.y;
		this->apple.Init();
		for (int i = 0; i < this->snake.length; i++) {
			if ((this->snake.cubes[i].x == this->apple.x) && (this->snake.cubes[i].y == this->apple.y)) {
				this->apple.Init();
			}
		}
	}

	this->Render();
}

void GameEngine::Render() {
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(SCRWidth / 2.0f, SCRHeight / 2.0f, 0.0f);

	this->apple.Render();
	this->snake.Render();
}

void GameEngine::Onkey() {
	if (GetKeyState(VK_UP) & 0x8000) {
		this->dir = 0;
	} 
	else if (GetKeyState(VK_RIGHT) & 0x8000) {
		this->dir = 1;
	}
	else if (GetKeyState(VK_DOWN) & 0x8000) {
		this->dir = 2;
	}
	else if (GetKeyState(VK_LEFT) & 0x8000) {
		this->dir = 3;
	}
}

void GameEngine::Destroy() {

}