
/* 
 * Written by Eric Tuvesson
 *
 * The OpenGL rendering is based on NeHe's Tutorial '3D Shapes' 
 * which can be found here http://nehe.gamedev.net/tutorial/3d_shapes/10035/
 * 
 */

#include <iostream>

#include <GL/glew.h>
#include <glut.h>

#include <SDL.h>
#include <SDL_opengl.h>

int main(int argc, char *argv[])
{
	SDL_Window *window;
	SDL_GLContext context;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
	{ 
		std::cout << SDL_GetError() << std::endl; 
		return 1;
	}

	// Lets assume that the Client can run OpenGL 2.1
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	window = SDL_CreateWindow("SDL2 OpenGL 3D Shapes",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		800, 600, SDL_WINDOW_OPENGL);

	if (window == 0)
	{ 
		std::cout << SDL_GetError() << std::endl; 
		return 1;
	}

	context = SDL_GL_CreateContext(window);

	if (context == 0)  
	{ 
		std::cout << SDL_GetError() << std::endl; 
		return 1;
	}

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)  
	{ 
		std::cout << "Failed to initialize GLEW" << std::endl; 
		return 1;
	}

	// OpenGL & SDL2 Initialized

	GLfloat anglePyramid = 0.0f;
	GLfloat angleCube = 0.0f;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	GLfloat aspect = (GLfloat)800 / (GLfloat)600;
	glViewport(0, 0, 800, 600);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);

	// 

	bool isRunning = true;
	SDL_Event event;
	while (isRunning)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				isRunning = false;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();
		glTranslatef(1.5f, 0.0f, -7.0f);
		glRotatef(angleCube, 1.0f, 1.0f, 1.0f);

		glBegin(GL_QUADS);
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
		glEnd();

		glLoadIdentity();
		glTranslatef(-1.5f, 0.0f, -6.0f);
		glRotatef(anglePyramid, 1.0f, 1.0f, 0.0f);

		glBegin(GL_TRIANGLES);
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
		glEnd();

		SDL_GL_SwapWindow(window);

		anglePyramid += 0.2f;
		angleCube -= 0.15f;
	}

	return 0;
}