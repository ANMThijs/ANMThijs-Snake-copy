#include "Snake.h"

Snake::Snake() {

}

Snake::~Snake() {

}

void Snake::Init() {
	//Default variables
	this->length = 1;

	this->cubes[0].x = 5;
	this->cubes[0].y = 10;

	this->selfcoll = false;
}

void Snake::AddLength(int x, int y) {
	this->length++;

	this->cubes[this->length - 1].x = x;
	this->cubes[this->length - 1].y = y;
}

void Snake::Move(int dir) {
	//Move the cube to the position of the next cube. It start's at the back, otherwise the cubes would
	//get the same positions
	for (int i = 1; i < this->length; i++) {
		int j = this->length - i;
		this->cubes[j].x = this->cubes[j - 1].x;
		this->cubes[j].y = this->cubes[j - 1].y;
	}

	//The direction handling
	switch (dir) {
	case 0: //Up
		this->cubes[0].y -= 1;
		break;
	case 1: //Right
		this->cubes[0].x += 1;
		break;
	case 2: //Down
		this->cubes[0].y += 1;
		break;
	case 3: //Left
		this->cubes[0].x -= 1;
		break;
	}

	//If the snake reached the border of the screen, it 'teleports' to the other side of the screen
	if (this->cubes[0].x == -1) {
		this->cubes[0].x = 19;
	}
	else if (this->cubes[0].x == 20) {
		this->cubes[0].x = 0;
	}
	else if (this->cubes[0].y == -1) {
		this->cubes[0].y = 19;
	}
	else if (this->cubes[0].y == 20) {
		this->cubes[0].y = 0;
	}

	//Self collision check
	for (int i = 1; i < this->length; i++) {
		if ((this->cubes[0].x == this->cubes[i].x) && (this->cubes[0].y == this->cubes[i].y)) {
			this->selfcoll = true;
		}
	}
}

void Snake::Render() {
	//Loop through the cubes and draw them
	for (int i = 0; i < this->length; i++) {
		float x = -500.0f + this->cubes[i].x * 50.0f;
		float y = -500.0f + this->cubes[i].y * 50.0f;

		glBegin(GL_TRIANGLES);
		
		glColor3f(SnakeCol);
		glVertex2f(x + 48.0f, y + 48.0f);
		glVertex2f(x		, y + 48.0f);
		glVertex2f(x		, y);

		glVertex2f(x + 48.0f, y + 48.0f);
		glVertex2f(x		, y);
		glVertex2f(x + 48.0f, y);

		glEnd();
	}
}