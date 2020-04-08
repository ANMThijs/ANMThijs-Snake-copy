#include "Window.h"

int main() {
	HWND hwnd = CreateWin(10, 10, 1000, 1000, L"ANMThijs' Snake copy");

	MSGLoop();

	return 0;
}