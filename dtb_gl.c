#include "dtb_gl.h"

void *(*sui_gl_GetProcAddress)(const char* proc) = NULL;

char* dtbgl_check_gl_error()
{
    GLenum err;
    while( !(err = glGetError()) ){
        return (char*)err;
    }
	
	return NULL;
}

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

GLuint dtbgl_create_buffer(size_t size, const void* data, GLenum target, GLenum usage_hint)
{
    GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(target, buffer);
	glBufferData(target, size, data, usage_hint);
	
	return buffer;
}

GLuint dtbgl_create_ibo(size_t size, const void* data, GLenum usage_hint)
{
	return dtbgl_create_buffer(size, data, GL_ELEMENT_ARRAY_BUFFER, usage_hint);
}

GLuint dtbgl_create_vbo(size_t size, const void* data, GLenum usage_hint)
{
	return dtbgl_create_buffer(size, data, GL_ARRAY_BUFFER, usage_hint);
}

GLuint dtbgl_create_shaders(char* header_code, char* vert_shader, char* frag_shader)
{
	char info_log[512];
	int success;
	int code_lengths[] = {-1, -1, -1, -1, -1, -1};
	
	char* vert_code[] =
	{
		header_code,
		vert_shader,
	};
	
	GLuint vert_shader_id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert_shader_id,
				   sizeof(vert_code) / sizeof(vert_code[0]),
				   vert_code,
				   code_lengths);
	
	glCompileShader(vert_shader_id);
	glGetShaderiv(vert_shader_id, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vert_shader_id, 512, 0, info_log);
		printf("%s\n", info_log);
	}
	
	
	char* frag_code[] =
	{
		header_code,
		frag_shader,
	};
	
	GLuint frag_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag_shader_id,
				   sizeof(frag_code) / sizeof(frag_code[0]),
				   frag_code,
				   code_lengths);
	
	
	glCompileShader(frag_shader_id);
	glGetShaderiv(frag_shader_id, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(frag_shader_id, 512, 0, info_log);
		printf("%s\n", info_log);
	}
	
	
    GLuint program_id = glCreateProgram();
	glAttachShader(program_id, vert_shader_id);
	glAttachShader(program_id, frag_shader_id);
	
	glLinkProgram(program_id);
	
	glGetProgramiv(program_id, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(program_id, 512, NULL, info_log);
		printf("%s\n", info_log);
	}
	
	return program_id;
}

bool dtbgl_init()
{
	dtbgl_extension_init(dtbgl_win32_grab_gl_address);
	
	glGenerateMipmap = dtbgl_extension_get_addr("glGenerateMipmap");
	if(glGenerateMipmap == NULL)
	{
		return false;
	}
	glActiveTexture = dtbgl_extension_get_addr("glActiveTexture");
    if(glActiveTexture == NULL)
    {
        return false;
    }
	glGetStringi = dtbgl_extension_get_addr("glGetStringi");
	if(glGetStringi == NULL)
	{
		return false;
	}
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
    glGetUniformfv = dtbgl_extension_get_addr("glGetUniformfv");
    if(glGetUniformfv == NULL)
	{
		return false;
	}
    
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
	glDeleteVertexArrays = dtbgl_extension_get_addr("glDeleteVertexArrays");
    if(glDeleteVertexArrays == NULL)
    {
        return false;
    }
    glDeleteBuffers = dtbgl_extension_get_addr("glDeleteBuffers");
    if(glDeleteBuffers == NULL)
    {
        return false;
    }
    glBindAttribLocation = dtbgl_extension_get_addr("glBindAttribLocation");
    if(glBindAttribLocation == NULL)
    {
        return false;
    }
    glBindFragDataLocation = dtbgl_extension_get_addr("glBindFragDataLocation");
    if(glBindFragDataLocation == NULL)
    {
        return false;
    }
    
    
	return true;
}