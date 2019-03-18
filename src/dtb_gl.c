#include "dtb_gl.h"

void dtbgl_extension_init(void*(*glGetProcAddr)(const char* proc)) 
{
	sui_gl_GetProcAddress = glGetProcAddr;
}

void *dtbgl_extension_get_addr(const char* proc) 
{
	if (sui_gl_GetProcAddress == NULL) 
	{
		return NULL;
	}
	else 
	{
		return sui_gl_GetProcAddress(proc);
	}
}

int dtbgl_buffer_init()
{
	glBindBuffer = dtbgl_extension_get_addr("glBindBuffer");
	if(glBindBuffer == NULL)
	{
		return -1;
	}
	
	return 1;
}


#include <assert.h>

int dtbgl_init(void*(*glGetProcAddr)(const char* proc))
{
	int (APIENTRY *SwapInterval)(int interval) = NULL;
	float fov = 9.0f / 16.0f;
	
	dtbgl_extension_init(glGetProcAddr);
	
	if(dtbgl_buffer_init() < 0)
	{
		assert(!"Failed here");
	}
	
	//Buffer
	//SwapInterval
	//Shaders
	//FrameBuffer
	//array
	
	return -1;
}