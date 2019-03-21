#include "dtb_gl.h"

#include <assert.h>

void *(*sui_gl_GetProcAddress)(const char* proc) = NULL;

#ifdef _WIN32
void *dtbgl_win32_grab_gl_address(const char *name)
{
	void *p = (void *)wglGetProcAddress(name);
	if(p == 0 || (p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) || (p == (void*)-1) )
	{
		HMODULE module = LoadLibraryA("opengl32.dll");
		p = (void *)GetProcAddress(module, name);
	}
	
	return p;
}
#endif

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

bool dtbgl_buffer_init()
{
	glBindVertexArray = dtbgl_extension_get_addr("glBindVertexArray");
	if(glBindVertexArray == NULL)
	{
		return false;
	}
	glGenVertexArrays = dtbgl_extension_get_addr("glGenVertexArrays");
	if(glGenVertexArrays == NULL)
	{
		return false;
	}
	glBindBuffer = dtbgl_extension_get_addr("glBindBuffer");
	if(glBindBuffer == NULL)
	{
		return false;
	}
	glGenBuffers = dtbgl_extension_get_addr("glGenBuffers");
	if(glGenBuffers == NULL)
	{
		return false;
	}
	glBufferData = dtbgl_extension_get_addr("glBufferData");
	if(glBufferData == NULL)
	{
		return false;
	}
	glEnableVertexAttribArray = dtbgl_extension_get_addr("glEnableVertexAttribArray");
	if(glEnableVertexAttribArray == NULL)
	{
		return false;
	}
	glDisableVertexAttribArray = dtbgl_extension_get_addr("glDisableVertexAttribArray");
	if(glDisableVertexAttribArray == NULL)
	{
		return false;
	}
	glVertexAttribPointer = dtbgl_extension_get_addr("glVertexAttribPointer");
	if(glVertexAttribPointer == NULL)
	{
		return false;
	}
	glBufferSubData = dtbgl_extension_get_addr("glBufferSubData");
	if(glBufferSubData == NULL)
	{
		return false;
	}
	
	return true;
}

bool dtbgl_shader_init()
{
	glCreateShader = dtbgl_extension_get_addr("glCreateShader");
	if(glCreateShader == NULL)
	{
		return false;
	}
	glShaderSource = dtbgl_extension_get_addr("glShaderSource");
	if(glShaderSource == NULL)
	{
		return false;
	}
	glCompileShader = dtbgl_extension_get_addr("glCompileShader");
	if(glCompileShader == NULL)
	{
		return false;
	}
	glGetShaderiv = dtbgl_extension_get_addr("glGetShaderiv");
	if(glGetShaderiv == NULL)
	{
		return false;
	}
	glGetShaderInfoLog = dtbgl_extension_get_addr("glGetShaderInfoLog");
	if(glGetShaderInfoLog == NULL)
	{
		return false;
	}
	glDeleteShader = dtbgl_extension_get_addr("glDeleteShader");
	if(glDeleteShader == NULL)
	{
		return false;
	}
	glCreateProgram = dtbgl_extension_get_addr("glCreateProgram");
	if(glCreateProgram == NULL)
	{
		return false;
	}
	glAttachShader = dtbgl_extension_get_addr("glAttachShader");
	if(glAttachShader == NULL)
	{
		return false;
	}
	glLinkProgram = dtbgl_extension_get_addr("glLinkProgram");
	if(glLinkProgram == NULL)
	{
		return false;
	}
	glGetProgramiv = dtbgl_extension_get_addr("glGetProgramiv");
	if(glGetProgramiv == NULL)
	{
		return false;
	}
	glDeleteProgram = dtbgl_extension_get_addr("glDeleteProgram");
	if(glDeleteProgram == NULL)
	{
		return false;
	}
	glDetachShader = dtbgl_extension_get_addr("glDetachShader");
	if(glDetachShader == NULL)
	{
		return false;
	}
	glGetProgramInfoLog = dtbgl_extension_get_addr("glGetProgramInfoLog");
	if(glGetProgramInfoLog == NULL)
	{
		return false;
	}
	glUseProgram = dtbgl_extension_get_addr("glUseProgram");
	if(glUseProgram == NULL)
	{
		return false;
	}
	glGetUniformLocation = dtbgl_extension_get_addr("glGetUniformLocation");
	if(glGetUniformLocation == NULL)
	{
		return false;
	}
	glUniform1f = dtbgl_extension_get_addr("glUniform1f");
	if(glUniform1f == NULL)
	{
		return false;
	}
	glUniform2f = dtbgl_extension_get_addr("glUniform1f");
	if(glUniform1f == NULL)
	{
		return false;
	}
	glUniform3f = dtbgl_extension_get_addr("glUniform1f");
	if(glUniform1f == NULL)
	{
		return false;
	}
	glUniform4f = dtbgl_extension_get_addr("glUniform1f");
	if(glUniform1f == NULL)
	{
		return false;
	}
	glUniform1i = dtbgl_extension_get_addr("glUniform1i");
	if(glUniform1i == NULL)
	{
		return false;
	}
	glUniform2i = dtbgl_extension_get_addr("glUniform2i");
	if(glUniform2i == NULL)
	{
		return false;
	}
	glUniform3i = dtbgl_extension_get_addr("glUniform3i");
	if(glUniform3i == NULL)
	{
		return false;
	}
	glUniform4i = dtbgl_extension_get_addr("glUniform4i");
	if(glUniform4i == NULL)
	{
		return false;
	}
	glUniform1ui = dtbgl_extension_get_addr("glUniform1ui");
	if(glUniform1ui == NULL)
	{
		return false;
	}
	glUniform2ui = dtbgl_extension_get_addr("glUniform2ui");
	if(glUniform2ui == NULL)
	{
		return false;
	}
	glUniform3ui = dtbgl_extension_get_addr("glUniform3ui");
	if(glUniform3ui == NULL)
	{
		return false;
	}
	glUniform4ui = dtbgl_extension_get_addr("glUniform4ui");
	if(glUniform4ui == NULL)
	{
		return false;
	}
	glUniform1fv = dtbgl_extension_get_addr("glUniform1fv");
	if(glUniform1fv == NULL)
	{
		return false;
	}
	glUniform2fv = dtbgl_extension_get_addr("glUniform2fv");
	if(glUniform2fv == NULL)
	{
		return false;
	}
	glUniform3fv = dtbgl_extension_get_addr("glUniform3fv");
	if(glUniform3fv == NULL)
	{
		return false;
	}
	glUniform4fv = dtbgl_extension_get_addr("glUniform4fv");
	if(glUniform4fv == NULL)
	{
		return false;
	}
	glUniform1iv = dtbgl_extension_get_addr("glUniform1iv");
	if(glUniform1iv == NULL)
	{
		return false;
	}
	glUniform2iv = dtbgl_extension_get_addr("glUniform2iv");
	if(glUniform2iv == NULL)
	{
		return false;
	}
	glUniform3iv = dtbgl_extension_get_addr("glUniform3iv");
	if(glUniform3iv == NULL)
	{
		return false;
	}
	glUniform4iv = dtbgl_extension_get_addr("glUniform4iv");
	if(glUniform4iv == NULL)
	{
		return false;
	}
	glUniform1uiv = dtbgl_extension_get_addr("glUniform1uiv");
	if(glUniform1uiv == NULL)
	{
		return false;
	}
	glUniform2uiv = dtbgl_extension_get_addr("glUniform2uiv");
	if(glUniform2uiv == NULL)
	{
		return false;
	}
	glUniform3uiv = dtbgl_extension_get_addr("glUniform3uiv");
	if(glUniform3uiv == NULL)
	{
		return false;
	}
	glUniform4uiv = dtbgl_extension_get_addr("glUniform4uiv");
	if(glUniform4uiv == NULL)
	{
		return false;
	}
	glUniformMatrix2fv = dtbgl_extension_get_addr("glUniformMatrix2fv");
	if(glUniformMatrix2fv == NULL)
	{
		return false;
	}
	glUniformMatrix3fv = dtbgl_extension_get_addr("glUniformMatrix3fv");
	if(glUniformMatrix3fv == NULL)
	{
		return false;
	}
	glUniformMatrix4fv = dtbgl_extension_get_addr("glUniformMatrix4fv");
	if(glUniformMatrix4fv == NULL)
	{
		return false;
	}
	glUniformMatrix2x3fv = dtbgl_extension_get_addr("glUniformMatrix2x3fv");
	if(glUniformMatrix2x3fv == NULL)
	{
		return false;
	}
	glUniformMatrix3x2fv = dtbgl_extension_get_addr("glUniformMatrix3x2fv");
	if(glUniformMatrix3x2fv == NULL)
	{
		return false;
	}
	glUniformMatrix2x4fv = dtbgl_extension_get_addr("glUniformMatrix2x4fv");
	if(glUniformMatrix2x4fv == NULL)
	{
		return false;
	}
	glUniformMatrix4x2fv = dtbgl_extension_get_addr("glUniformMatrix4x2fv");
	if(glUniformMatrix4x2fv == NULL)
	{
		return false;
	}
	glUniformMatrix3x4fv = dtbgl_extension_get_addr("glUniformMatrix3x4fv");
	if(glUniformMatrix3x4fv == NULL)
	{
		return false;
	}
	glUniformMatrix4x3fv = dtbgl_extension_get_addr("glUniformMatrix4x3fv");
	if(glUniformMatrix4x3fv == NULL)
	{
		return false;
	}
	return true;
}

// TODO(DILLON): Write this
void dtbgl_bind_buffer()
{
	
}

// TODO(DILLON): Write this
bool dtbgl_create_shaders()
{
	return true;
}

bool dtbgl_init(void*(*glGetProcAddr)(const char* proc))
{
	int (APIENTRY *SwapInterval)(int interval) = NULL;
	float fov = 9.0f / 16.0f;
	
	dtbgl_extension_init(glGetProcAddr);
	
	SwapInterval = dtbgl_extension_get_addr("wglSwapIntervalEXT");
	if (SwapInterval == NULL) 
	{
		SwapInterval = dtbgl_extension_get_addr("glXSwapIntervalEXT");
	}
	
	if(dtbgl_buffer_init() == false)
	{
		return false;
	}
	
	if(dtbgl_shader_init() == false)
	{
		return false;
	}
	
	//SwapInterval
	//FrameBuffer
	//array
	
	return true;
}