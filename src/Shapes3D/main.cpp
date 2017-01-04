
/*
 * The OpenGL rendering is based on NeHe's Tutorial '3D Shapes'
 * which can be found here http://nehe.gamedev.net/tutorial/3d_shapes/10035/
 */

#include <iostream>

#include <GL/glew.h>
#include <GL/glut.h>

#include <SDL.h>
#include <SDL_opengl.h>

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600
#define WINDOW_TITLE	"SDL2 OpenGL 3D Shapes"

#define OPENGL_MAJOR	2
#define OPENGL_MINOR	1

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
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OPENGL_MAJOR);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OPENGL_MINOR);

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
	GLfloat anglePyramid = 0.0f;
	GLfloat angleCube = 0.0f;
	bool isRunning = true;

	// Set some OpenGL settings
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	GLfloat aspect = (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT;
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);

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

		// Rotate the shapes
		anglePyramid += 0.2f;
		angleCube -= 0.15f;

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);

		// Reset the current transform
		glLoadIdentity();

		// Set the cube location
		glTranslatef(1.5f, 0.0f, -7.0f);
		glRotatef(angleCube, 1.0f, 1.0f, 1.0f);

		// Draw the cube
		glBegin(GL_QUADS);
		{
			// Top face (y = 1.0f)
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(1.0f, 1.0f, -1.0f);
			glVertex3f(-1.0f, 1.0f, -1.0f);
			glVertex3f(-1.0f, 1.0f, 1.0f);
			glVertex3f(1.0f, 1.0f, 1.0f);

			// Bottom face (y = -1.0f)
			glColor3f(1.0f, 0.5f, 0.0f);
			glVertex3f(1.0f, -1.0f, 1.0f);
			glVertex3f(-1.0f, -1.0f, 1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(1.0f, -1.0f, -1.0f);

			// Front face  (z = 1.0f)
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(1.0f, 1.0f, 1.0f);
			glVertex3f(-1.0f, 1.0f, 1.0f);
			glVertex3f(-1.0f, -1.0f, 1.0f);
			glVertex3f(1.0f, -1.0f, 1.0f);

			// Back face (z = -1.0f)
			glColor3f(1.0f, 1.0f, 0.0f);
			glVertex3f(1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, 1.0f, -1.0f);
			glVertex3f(1.0f, 1.0f, -1.0f);

			// Left face (x = -1.0f)
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(-1.0f, 1.0f, 1.0f);
			glVertex3f(-1.0f, 1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, 1.0f);

			// Right face (x = 1.0f)
			glColor3f(1.0f, 0.0f, 1.0f);
			glVertex3f(1.0f, 1.0f, -1.0f);
			glVertex3f(1.0f, 1.0f, 1.0f);
			glVertex3f(1.0f, -1.0f, 1.0f);
			glVertex3f(1.0f, -1.0f, -1.0f);
		}
		glEnd();

		// Reset the current transform
		glLoadIdentity();

		// Set the pyramid location
		glTranslatef(-1.5f, 0.0f, -6.0f);
		glRotatef(anglePyramid, 1.0f, 1.0f, 0.0f);

		// Draw the pyramid
		glBegin(GL_TRIANGLES);
		{
			// Front
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 1.0f, 0.0f);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-1.0f, -1.0f, 1.0f);
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(1.0f, -1.0f, 1.0f);

			// Right
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 1.0f, 0.0f);
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(1.0f, -1.0f, 1.0f);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(1.0f, -1.0f, -1.0f);

			// Back
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 1.0f, 0.0f);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(1.0f, -1.0f, -1.0f);
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);

			// Left
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 1.0f, 0.0f);
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-1.0f, -1.0f, 1.0f);
		}
		glEnd();

		// Swap the OpenGL window buffers
		SDL_GL_SwapWindow(window);
	}

	// Release resources

	return EXIT_SUCCESS;
}

void PrintError(const char* str)
{
	std::cout << str << '\n';

#ifdef _DEBUG
	std::cin.get();
#endif
}
