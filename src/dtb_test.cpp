#include "SDL/SDL.h"
#include "dtb_gl.h"

#include <windows.h>
#include <assert.h>

bool running;

void *GetAnyGLFuncAddress(const char *name)
{
	void *p = (void *)wglGetProcAddress(name);
	if(p == 0 ||
	   (p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) ||
	   (p == (void*)-1) )
	{
		HMODULE module = LoadLibraryA("opengl32.dll");
		p = (void *)GetProcAddress(module, name);
	}
	
	return p;
}

void poll_events()
{
	SDL_Event e;
	
	SDL_PollEvent(&e);
	
	if(e.type == SDL_QUIT)
	{
		running = false;
	}
}


int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_Window *window = SDL_CreateWindow("Title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL);
	
	assert(window);
	
	SDL_GLContext context = SDL_GL_CreateContext(window);
	
	SDL_GL_MakeCurrent(window, context);
	
	int check = dtbgl_init(GetAnyGLFuncAddress);
	
	assert(check);
	
	running = true;
	while(running == true)
	{
		poll_events();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//SimpleLight(1, 250, , -0.5f, -1.0f);
		
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		
		SDL_GL_SwapWindow(window);
	}
	
	
	return 0;
}
