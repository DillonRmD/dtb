#include "SDL/SDL.h"
#include "dtb_gl.h"

#include <assert.h>

bool running;

#include <windows.h>


void poll_events()
{
	SDL_Event e;
	
	SDL_PollEvent(&e);
	
	if(e.type == SDL_QUIT)
	{
		running = false;
	}
}


float vertices[] = 
{
	-0.5f, -0.5f,
	0.5f, 0.5f,
	0.0f, 0.5f,
};

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_Window *window = SDL_CreateWindow("Title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL);
	
	assert(window);
	
	SDL_GLContext context = SDL_GL_CreateContext(window);
	
	SDL_GL_MakeCurrent(window, context);
	
	int check = dtbgl_init(dtbgl_win32_grab_gl_address);
	
	assert(check);
	
	
	
	
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	
	
	running = true;
	while(running == true)
	{
		poll_events();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		SDL_GL_SwapWindow(window);
	}
	
	
	return 0;
}
