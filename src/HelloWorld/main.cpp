// The linking could be done in the project too.
#pragma comment (lib, "OpenGL32.lib")

#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <SDL.h>
#include <SDL_opengl.h>

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600
#define WINDOW_TITLE	"SDL2 OpenGL Hello World"

// Output the message and pause the console if necessary.
void PrintError(const char* str);

int main(int argc, char *argv[])
{
	SDL_Window *window;
	SDL_GLContext context;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != NULL)
	{
		PrintError(SDL_GetError());
		return EXIT_FAILURE;
	}

	// Set the desired OpenGL version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	// Create the window using SDL
	window = SDL_CreateWindow(WINDOW_TITLE,
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

	if (window == NULL)
	{
		PrintError(SDL_GetError());
		return EXIT_FAILURE;
	}

	// Create the OpenGL context for the window using SDL
	context = SDL_GL_CreateContext(window);
	if (context == NULL)
	{
		PrintError(SDL_GetError());
		return EXIT_FAILURE;
	}

	// Enable glew experimental, this enables some more OpenGL extensions.
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		PrintError("Failed to initialize GLEW");
		return EXIT_FAILURE;
	}

	// Application Variables
	bool isRunning = true;

	// Set some OpenGL settings
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);

	SDL_Event event;
	while (isRunning)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT: 
				isRunning = false;
				break;
			}
		}

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     
    // ....


		// Swap the OpenGL window buffers
		SDL_GL_SwapWindow(window);
	}

	// Release resources
	SDL_GL_DeleteContext(context);
	SDL_Quit();

	return EXIT_SUCCESS;
}

void PrintError(const char* str)
{
	std::cout << str << '\n';

#ifdef _DEBUG
	std::cin.get();
#endif
}
