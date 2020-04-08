#include "Window.h"

HWND CreateWin(int xpos, int ypos, int width, int height, LPCWSTR title) {
	HINSTANCE hInst = GetModuleHandleW(NULL);

	WNDCLASS wc = {};

	wc.hInstance = hInst;
	wc.lpszClassName = L"Main class";
	wc.lpfnWndProc = WndProc;

	RegisterClassW(&wc);

	//Create the window
	HWND hwnd = CreateWindowExW(NULL, wc.lpszClassName, title,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		xpos, ypos, width, height,
		NULL, NULL, hInst, NULL);

	return hwnd;
}

//The engine which contains all the game variables and renders everything
GameEngine engine;

LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
	HDC hdc = NULL;
	HGLRC hrc = NULL;
	POINT Cursorpos;
	switch (umsg) {
	//Mouse clicked event. Nothing happens if the engine is running
	case WM_LBUTTONDOWN:
		if (engine.running == false) {
			GetCursorPos(&Cursorpos);
			//If mouse is in the square x350-x450 and y450-y550 (in pixels), start the game
			if ((Cursorpos.x > 350) && (Cursorpos.x < 450) && (Cursorpos.y > 450) && (Cursorpos.y < 550)) {
				engine.running = true;
				engine.Reset();
				SetTimer(hwnd, 101, 250, NULL);
			}
			//If mouse is in the square x550-x650 and y450-y550 (in pixels), close the game
			if ((Cursorpos.x > 550) && (Cursorpos.x < 650) && (Cursorpos.y > 450) && (Cursorpos.y < 550)) {
				DestroyWindow(hwnd);
			}
		}
		break;
		//Key pressed event. Nothing happens if the engine isn't running
	case WM_KEYDOWN:
		if (engine.running == true) {
			engine.Onkey();
		}
		break;
		//Timer. the timer is started by SetTimer in the Mouse click event. This timer is called every
		//250 milliseconds, which is the speed of the game
	case WM_TIMER:
		hdc = GetDC(hwnd);

		if (engine.running == true) {
			engine.OnTimer();
		}
		else if (engine.running == false) {
			KillTimer(hwnd, 101);
			DrawMainMenu();
		}

		SwapBuffers(hdc);
		break;
		//Drawing Event, is only called once at the start of the game. The other drawing is done in the
		//Timer event
	case WM_PAINT:
		hdc = GetDC(hwnd);

		if (engine.running == true) {
			engine.Render();
		}
		else if(engine.running == false){
			DrawMainMenu();
		}

		SwapBuffers(hdc);
		break;
		//Create window event. Get's called upon the window creation, before the drawing event.
		//This event set's up the OpenGL Context and the game engine.
	case WM_CREATE:
		hdc = GetDC(hwnd);
		hrc = CreateGLContext(hdc);
		wglMakeCurrent(hdc, hrc);

		engine.Init();
		break;
		//Destroy window event. Is called when the window is destroyed. It's used to delete the
		//OpenGL Context, to release the window Drawing context and to close the game.
	case WM_DESTROY:
		engine.Destroy();

		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hrc);
		ReleaseDC(hwnd, hdc);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProcW(hwnd, umsg, wparam, lparam);
}

void MSGLoop() {
	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
}

HGLRC CreateGLContext(HDC hdc) {
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
		PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
		32,                   // Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                   // Number of bits for the depthbuffer
		8,                    // Number of bits for the stencilbuffer
		0,                    // Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	int iPixFor = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, iPixFor, &pfd);

	//Create a temporary context, because you'll need Glew to create a good context, but to initialize
	//Glew, you'll need a context
	HGLRC tempc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, tempc);

	glewInit();

	//Context attributes. The OpenGL Version is 2.1
	int attribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 2,
		WGL_CONTEXT_MINOR_VERSION_ARB, 1,
		WGL_CONTEXT_FLAGS_ARB, 0,
		0
	};

	//Create the main context and delete the temporary context
	HGLRC hrc = wglCreateContextAttribsARB(hdc, 0, attribs);
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(tempc);

	return hrc;
}