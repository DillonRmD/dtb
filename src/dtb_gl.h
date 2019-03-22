/*  ============================================================================================
*  PROJECT:  Dillon's Tool Box OpenGL Wrapper Edition
*  AUTHOR:   Dillon Williams
*  LICENSE:  Do What The Fuck Ever license
*  LANGUAGE: C\C++
*
*  INFORMATION:
*  To implement into your code base include dtb_gl.h into main compilation unit i.e. main.c / main.cpp
*  Make sure to compile the compilation unit attached with dtb_gl.h (dtb_gl.c). This is neccessary for
*  the program to work. I couldn't find a work around to just use a single header file, this was the
*  comprimise.
*
*  IMPORTANT:
*  dtb_gl.h and dtb_gl.c are bundled together compile dtb_gl.c with your project while including dtb_gl.h!!!
*
*  EXAMPLE:
*  
  *  #include "dtb_gl.h"
  *  int main(int argc, char* argv[])
  *  {
  *      //Window Creation
  *      //OpenGL Context grabbing
  *      bool error = dtbgl_init(dtbgl_win32_grab_gl_address);
  *      if(error == false)
  *          //ERROR
  *      return 0;
  *  }
*
*  ============================================================================================
*/

#ifndef DTB_GL_H

#ifdef _WIN32
// NOTE(DILLON): Disables macro redefinition warning
#include <windows.h>
#pragma warning(disable : 4005)
#ifndef WINGDIAPI
#define CALLBACK    __stdcall
#define WINGDIAPI   __declspec(dllimport)
#define APIENTRY    __stdcall
#endif
#endif //_WIN32

#ifdef __cplusplus
#define DTB_EXTERN extern "C"
#else
#define DTB_EXTERN extern
typedef char bool;
#define true 1
#define false 0
#define NULL 0
#endif

#include <stddef.h>
#include <stdio.h>

#include <gl/gl.h>
#include <gl/glu.h>

typedef  char GLchar;
typedef unsigned int GLuint;
typedef int GLint;
typedef void GLvoid;



typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

#define GL_TEXTURE0_ARB								0x84C0

#define GL_FRAMEBUFFER_EXT                     0x8D40
#define GL_RENDERBUFFER_EXT                    0x8D41

#define GL_STENCIL_INDEX1_EXT                  0x8D46
#define GL_STENCIL_INDEX4_EXT                  0x8D47
#define GL_STENCIL_INDEX8_EXT                  0x8D48
#define GL_STENCIL_INDEX16_EXT                 0x8D49

#define GL_RENDERBUFFER_WIDTH_EXT              0x8D42
#define GL_RENDERBUFFER_HEIGHT_EXT             0x8D43
#define GL_RENDERBUFFER_INTERNAL_FORMAT_EXT    0x8D44
#define GL_RENDERBUFFER_RED_SIZE_EXT           0x8D50
#define GL_RENDERBUFFER_GREEN_SIZE_EXT         0x8D51
#define GL_RENDERBUFFER_BLUE_SIZE_EXT          0x8D52
#define GL_RENDERBUFFER_ALPHA_SIZE_EXT         0x8D53
#define GL_RENDERBUFFER_DEPTH_SIZE_EXT         0x8D54
#define GL_RENDERBUFFER_STENCIL_SIZE_EXT       0x8D55

#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_EXT            0x8CD0
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_EXT            0x8CD1
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_EXT          0x8CD2
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_EXT  0x8CD3
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_3D_ZOFFSET_EXT     0x8CD4

#define GL_COLOR_ATTACHMENT0_EXT                0x8CE0
#define GL_DEPTH_ATTACHMENT_EXT                 0x8D00
#define GL_STENCIL_ATTACHMENT_EXT               0x8D20

#define GL_FRAMEBUFFER_COMPLETE_EXT                          0x8CD5
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT             0x8CD6
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT     0x8CD7
#define GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT             0x8CD9
#define GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT                0x8CDA
#define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT            0x8CDB
#define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT            0x8CDC
#define GL_FRAMEBUFFER_UNSUPPORTED_EXT                       0x8CDD

#define GL_FRAMEBUFFER_BINDING_EXT             0x8CA6
#define GL_RENDERBUFFER_BINDING_EXT            0x8CA7
#define GL_MAX_COLOR_ATTACHMENTS_EXT           0x8CDF
#define GL_MAX_RENDERBUFFER_SIZE_EXT           0x84E8

#define GL_DEPTH_COMPONENT16				0x81A5
#define GL_DEPTH_COMPONENT24              0x81A6
#define GL_DEPTH_COMPONENT32              0x81A7
#define GL_STENCIL_INDEX8	             0x8D48
#define GL_CLAMP_TO_EDGE                  0x812F

#define GL_EXT_TEXTURE_CUBE_MAP		          1 
#define GL_NORMAL_MAP_EXT                   0x8511 
#define GL_REFLECTION_MAP_EXT               0x8512 
#define GL_TEXTURE_CUBE_MAP_EXT             0x8513 
#define GL_TEXTURE_BINDING_CUBE_MAP_EXT     0x8514 
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT  0x8515 
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X_EXT  0x8516 
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y_EXT  0x8517 
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_EXT  0x8518 
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z_EXT  0x8519 
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_EXT  0x851A 
#define GL_PROXY_TEXTURE_CUBE_MAP_EXT       0x851B 
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE_EXT    0x851C 

#define GL_VERTEX_SHADER_ARB				0x8B31
#define GL_FRAGMENT_SHADER_ARB				0x8B30
#define GL_GEOMETRY_SHADER_ARB				0x8DD9
#define GL_COMPILE_STATUS					0x8B81
#define GL_LINK_STATUS						0x8B82

#define GL_SAMPLE_ALPHA_TO_COVERAGE			0x809E

#define GL_UNIFORM_BUFFER                   0x8A11
#define GL_SHADER_STORAGE_BUFFER			0x90D2
#define GL_ARRAY_BUFFER_ARB                 0x8892
#define GL_ELEMENT_ARRAY_BUFFER_ARB			0x8893
#define GL_COPY_READ_BUFFER					0x8F36
#define GL_DYNAMIC_DRAW_ARB					0x88E8

#define GL_ARRAY_BUFFER                   0x8892 // Acquired from:
#define GL_ARRAY_BUFFER_BINDING           0x8894 // https://www.opengl.org/registry/api/GL/glext.h
#define GL_COLOR_ATTACHMENT0              0x8CE0
#define GL_COMPILE_STATUS                 0x8B81
#define GL_CURRENT_PROGRAM                0x8B8D
#define GL_DYNAMIC_DRAW                   0x88E8
#define GL_ELEMENT_ARRAY_BUFFER           0x8893
#define GL_ELEMENT_ARRAY_BUFFER_BINDING   0x8895
#define GL_FRAGMENT_SHADER                0x8B30
#define GL_FRAMEBUFFER                    0x8D40
#define GL_FRAMEBUFFER_COMPLETE           0x8CD5
#define GL_FUNC_ADD                       0x8006
#define GL_INVALID_FRAMEBUFFER_OPERATION  0x0506
#define GL_MAJOR_VERSION                  0x821B
#define GL_MINOR_VERSION                  0x821C
#define GL_STATIC_DRAW                    0x88E4
#define GL_STREAM_DRAW                    0x88E0
#define GL_TEXTURE0                       0x84C0
#define GL_VERTEX_SHADER                  0x8B31
#define GL_INFO_LOG_LENGTH				0x8B84

#ifdef __cplusplus
extern "C" {
#endif
	
	DTB_EXTERN char* dtbgl_check_gl_error();
	
#ifdef _WIN32
	// NOTE(DILLON): This is only Win32
	DTB_EXTERN void *dtbgl_win32_grab_gl_address(const char *name);
#endif
	
	// NOTE(DILLON): Initializes extensions
	DTB_EXTERN void dtbgl_extension_init(void*(*glGetProcAddr)(const char* proc));
	// NOTE(DILLON): Gets address of extensions
	DTB_EXTERN void *dtbgl_extension_get_addr(const char* proc);
	
	// NOTE(DILLON): Initilizers for the wrapper
	DTB_EXTERN bool dtbgl_buffer_init();
	DTB_EXTERN bool dtbgl_shader_init();
	
	// NOTE(DILLON): Is called by user and calls the other initializers
	DTB_EXTERN bool dtbgl_init(void*(*glGetProcAddr)(const char* proc));
	
	// NOTE(DILLON): Utility functions, not necessart for the wrapper to function
	DTB_EXTERN uint dtbgl_create_shaders(char* header_code, char* vert_shader, char* frag_shader);
	DTB_EXTERN uint dtbgl_create_buffer(size_t size, const void* data, GLenum target, GLenum usage_hint);
	
	DTB_EXTERN uint dtbgl_create_ibo(size_t size, const void* data, GLenum usage_hint);
	DTB_EXTERN uint dtbgl_create_vbo(size_t size, const void* data, GLenum usage_hint);
	
	DTB_EXTERN void dtbgl_draw_cube(float x, float y, float z, float edge_length);
	DTB_EXTERN void dtbgl_draw_primitive_rect(float x, float y, float width, float height, float r, float g, float b, float a);
	
	DTB_EXTERN void dtbgl_setup_view_2d(int width, int height);
	
	// NOTE(DILLON): GL Calls
	GLubyte *(APIENTRY *glGetStringi)(GLenum name, GLuint index);
	
	// NOTE(DILLON): Buffers
	void (APIENTRY *glBindVertexArray)(GLuint array);
	void (APIENTRY *glGenVertexArrays)(GLsizei n, GLuint * arrays);
	void (APIENTRY *glBindBuffer)(GLenum target, GLuint buffer);
	void (APIENTRY *glGenBuffers)(GLsizei n, GLuint * buffers);
	void (APIENTRY *glBufferData)(GLenum target, GLsizei size, const GLvoid * data, GLenum usage);
	void (APIENTRY *glEnableVertexAttribArray)(GLuint index);
	void (APIENTRY *glDisableVertexAttribArray)(GLuint index);
	void (APIENTRY *glVertexAttribPointer)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer);
	void (APIENTRY *glBufferSubData)(GLenum target, size_t offset, size_t size, const void *data);
	
	// NOTE(DILLON): Shaders
	GLuint(APIENTRY *glCreateShader)(GLenum shaderType);
	void (APIENTRY *glShaderSource)(GLuint shader, GLsizei count, const GLchar **string, const GLint *length);
	void (APIENTRY *glCompileShader)(GLenum shaderType);
	void (APIENTRY *glGetShaderiv)(GLuint shader, GLenum pname, GLint *params);
	void (APIENTRY *glGetShaderInfoLog)(GLuint shader, GLsizei max_length, GLsizei *length, GLchar *info_log);
	void (APIENTRY *glDeleteShader)(GLuint shader);
	GLuint(APIENTRY *glCreateProgram)();
	void (APIENTRY *glAttachShader)(GLuint program, GLuint shader);
	void (APIENTRY *glLinkProgram)(GLuint program);
	void (APIENTRY *glGetProgramiv)(GLuint program, GLenum pname, GLint *params);
	void (APIENTRY *glDeleteProgram)(GLuint program);
	void (APIENTRY *glDetachShader)(GLuint program, GLuint shader);
	void (APIENTRY *glGetProgramInfoLog)(GLuint program, GLsizei max_length, GLsizei *length, GLchar *info_log);
	void (APIENTRY *glUseProgram)(GLuint program);
	
	// NOTE(DILLON): Uniforms
	GLint (APIENTRY *glGetUniformLocation)(GLuint program, GLchar *name);
	
	void (APIENTRY *glUniform1f)(GLint location, GLfloat v0);
	void (APIENTRY *glUniform2f)(GLint location, GLfloat v0, GLfloat v1);
	void (APIENTRY *glUniform3f)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
	void (APIENTRY *glUniform4f)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
	
	void (APIENTRY *glUniform1i)(GLint location, GLint v0);
	void (APIENTRY *glUniform2i)(GLint location, GLint v0, GLint v1);
	void (APIENTRY *glUniform3i)(GLint location, GLint v0, GLint v1, GLint v2);
	void (APIENTRY *glUniform4i)(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
	
	void (APIENTRY *glUniform1ui)(GLint location, GLuint v0);
	void (APIENTRY *glUniform2ui)(GLint location, GLuint v0, GLuint v1);
	void (APIENTRY *glUniform3ui)(GLint location, GLuint v0, GLuint v1, GLuint v2);
	void (APIENTRY *glUniform4ui)(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
	
	void (APIENTRY *glUniform1fv)(GLint location, GLsizei count, const GLfloat *value);
	void (APIENTRY *glUniform2fv)(GLint location, GLsizei count, const GLfloat *value);
	void (APIENTRY *glUniform3fv)(GLint location, GLsizei count, const GLfloat *value);
	void (APIENTRY *glUniform4fv)(GLint location, GLsizei count, const GLfloat *value);
	
	void (APIENTRY *glUniform1iv)(GLint location, GLsizei count, const GLint *value);
	void (APIENTRY *glUniform2iv)(GLint location, GLsizei count, const GLint *value);
	void (APIENTRY *glUniform3iv)(GLint location, GLsizei count, const GLint *value);
	void (APIENTRY *glUniform4iv)(GLint location, GLsizei count, const GLint *value);
	
	void (APIENTRY *glUniform1uiv)(GLint location, GLsizei count, const GLuint *value);
	void (APIENTRY *glUniform2uiv)(GLint location, GLsizei count, const GLuint *value);
	void (APIENTRY *glUniform3uiv)(GLint location, GLsizei count, const GLuint *value);
	void (APIENTRY *glUniform4uiv)(GLint location, GLsizei count, const GLuint *value);
	
	void (APIENTRY *glUniformMatrix2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
	void (APIENTRY *glUniformMatrix3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
	void (APIENTRY *glUniformMatrix4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
	
	void (APIENTRY *glUniformMatrix2x3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
	void (APIENTRY *glUniformMatrix3x2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
	void (APIENTRY *glUniformMatrix2x4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
	void (APIENTRY *glUniformMatrix4x2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
	void (APIENTRY *glUniformMatrix3x4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
	void (APIENTRY *glUniformMatrix4x3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
	
#ifdef __cplusplus
}
#endif

#define DTB_GL_H
#endif