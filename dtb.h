/*  ============================================================================================
*  PROJECT:  Dillon's Tool Box
*  AUTHOR:   Dillon Williams
*  LICENSE:  Do What The Fuck Ever license
*  LANGUAGE: C\C++
*
*  INFORMATION:
*  Absolutely no warranty when using this. I made this for personal use, and is now in the
*  public domain....congrats! Use at your own risk, feel free to edit/revise any of the
*  code base. I have tried to make this code as cross platform as possible, feel free to help
*  contribute with cross-platform specifications! Do whatever you want to with this code. Feel 
*  free to help out on github, or what the fuck ever.
*
*  ============================================================================================
*/
#ifndef DTB_INCLUDE_GUARD
#ifdef DTB_IMPLEMENT

//Standard libs
#include <stdio.h>
#include <stdlib.h>

#ifndef DTB_WIN32_DEFINED
#if defined _WIN32
#pragma warning(disable:4996) //CRT
#pragma warning(disable:4244) //Float conversion
//Win32 bullshittery
#define NOMINMAX
#define NOCOMM
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef near
#undef far
#define DTB_WIN32_DEFINED
#endif // _WIN32
#endif //DTB_WIN32_DEFINED

//Regular types
typedef char unsigned u8;
typedef unsigned short u16;
typedef unsigned int u32;

#ifdef __cplusplus //C++
#define DTB_EXTERN extern "C"
#else //C
typedef unsigned char bool
#define true 1
#define false 0
#define DTB_EXTERN extern
#endif //__cplusplus

#ifdef __linux__
	//Sets terminal colors for linux
#define DTB_TERMINAL_NORMAL  	"\x1B[0m"
#define DTB_TERMINAL_RED 	    "\x1B[31m"
#define DTB_TERMINAL_GREEN	    "\x1B[32m"
#define DTB_TERMINAL_YELLOW	    "\x1B[33m"
#define DTB_TERMINAL_BLUE  	    "\x1B[34m"
#define DTB_TERMINAL_MAGENTA 	"\x1B[35m"
#define DTB_TERMINAL_CYAN  	    "\x1B[36m"
#define DTB_TERMINAL_WHITE  	"\x1B[37m"
#endif //__linux__

	//ZeroMemory
#define dtb_zm(data) memset(&data, 0, sizeof(data)) 

	//String helpers
	DTB_EXTERN size_t dtb_strlen(const char *s);
DTB_EXTERN size_t dtb_strnlen(const char *s, size_t max_len);
DTB_EXTERN char *dtb_strcpy(char *s, const char *ct);
DTB_EXTERN char *dtb_strncpy(char *s, const char *ct, size_t n);
DTB_EXTERN int dtb_strcmp(const char* s, const char *t);
DTB_EXTERN int dtb_strncmp(const char* s, const char *t, size_t n);

size_t dtb_strlen(const char *s)
{
	size_t sz = 0;
	while(*s++ != '\0')
	{
		++sz;
	}
	return sz;
}

size_t dtb_strnlen(const char *s, size_t max_len)
{
	size_t i;
	for(i = 0; (i < max_len) && s[i]; ++i);
	return i;
}

char *dtb_strcpy(char *s, const char *ct)
{
	size_t n = dtb_strlen(ct);
	char *saver = (char*)malloc(n + 1);
	saver = s;
	while(n--)
		*saver++ = *ct++;

	*saver = '\0';

	return s;
}

char *dtb_strncpy(char *s, const char *ct, size_t n) 
{
	char *saver = (char*)malloc(n + 1);
	saver = s;
	while(n--)
		*saver++ = *ct++;

	*saver = '\0';

	return s;
}

int dtb_strcmp(const char* s, const char *t)
{
	while(*s != '\0' && *t != '\0' && *s == *t)
	{
		s++;
		t++;
	}

	return (*s - *t);
}

int dtb_strncmp(const char *s, const char *t, size_t n) 
{
	for ( ; n--; ++s, ++t) 
	{
		if(*s != *t) 
		{
			return *s - *t;
		}
	}

	return 0;
}

//Memory helpers
DTB_EXTERN void dtb_memcpy(void *src, void *dest);
DTB_EXTERN void dtb_memncpy(void *src, void *dest, size_t n);
DTB_EXTERN void dtb_memmove(void *src, void *dest);
DTB_EXTERN void dtb_memnmove(void *src, void *dest, size_t n);

void dtb_memcpy(void *src, void *dest)
{
	int n = sizeof(src);

	char *p_src = (char *)src;
	char *p_dest = (char *)dest;

	for (int i = 0; i < n; i++) 
	{
		p_dest[i] = p_src[i];
	}

}

void dtb_memncpy(void *src, void *dest, size_t n) 
{
	char *p_src = (char *)src;
	char *p_dest = (char *)dest;

	for (size_t i = 0; i < n; i++)
	{
		p_dest[i] = p_src[i];
	}
}

// TODO(dillon): Make sure this works in pure C
void dtb_memmove(void *src, void *dest)
{
	int n = sizeof(src);

	char *csrc = (char *)src;
	char *cdest = (char *)dest;

	//NOTE(dillon): This is a fix for MS shitty compilers
#ifdef _MSC_VER 
	char *temp = new char[n];
#else
	char *temp[n];
#endif

	for (int i=0; i<n; i++)
		temp[i] = csrc[i];

	for (int i=0; i<n; i++)
		cdest[i] = temp[i];

	//TODO(dillon): Check for memory leaks here
	realloc(temp, 0);
}

void dtb_memnmove(void *src, void *dest, size_t n)
{
	char *p_src = (char *)src;
	char *p_dest = (char *)dest;

	//NOTE(dillon): Windows Shitty compiler
#ifdef _MSC_VER
	char *temp = new char[n];
#else
	char *temp[n];
#endif

	memset(&temp, 0, sizeof(temp));

	for (size_t i=0; i<n; i++)
		temp[i] = p_src[i];

	for (size_t i=0; i<n; i++)
		p_dest[i] = temp[i];

	//(TODO(dillon): Check for memory leaks here
	realloc(temp, 0);
}

// Get array length (or size)
#define dtb_arr_len(array_name)		sizeof(array_name)

// Custom Assertions
#define dtb_assert(expression) if(!expression) __dtb_assert(__FILE__, __LINE__)

//Linux definitions of custom assert function
#ifdef __linux__
void __dtb_assert(char* file, int line)
{
	printf("%sDTB_ASSERTION: %s:%d%s\n", DTB_TERMINAL_RED, file, line, DTB_TERMINAL_NORMAL);
	abort(); //exit
}
#endif //__linux__

//Win32 definitions of custom assert function
#ifdef _WIN32
void __dtb_assert(char* file, int line)
{
	HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	WORD saved_attributes;

	/* Save current attributes */
	GetConsoleScreenBufferInfo(console_handle, &consoleInfo);
	saved_attributes = consoleInfo.wAttributes;

	SetConsoleTextAttribute(console_handle, FOREGROUND_RED);	

	printf("DTB_ASSERTION: %s:%d\n", file, line);

	SetConsoleTextAttribute(console_handle, saved_attributes);

	abort(); //exit
}
#endif //_WIN32

//Alignment macros
#define DTB_ALIGN(num, alignment) (((size_t)(num) + alignment - 1) & -(alignment - 1)
#define DTB_ALIGN_4(num) (((size_t)(num) + 3) & ~3)
#define DTB_ALIGN_8(num) (((size_t)(num) + 7) & ~7)
#define DTB_ALIGN_16(num) (((size_t)(num) + 15) & ~15)
#define DTB_ALIGN_32(num) (((size_t)(num) + 31) & ~31)

//Easy loops - mainly for personal use
//TODO(dillon): Look at maybe deleting this 
#ifndef DTB_NO_LOOPS

#define dtb_for(val, start, end) for (int (val) = (start); (val) < (end); ++(val))
#define dtb_for64(val, start, end) for (i64 (val) = (start); (val) < (end); ++(val))

#define dtb_fz(val, end) for (int (val) = 0; (val) < (end); ++val)
#define dtb_fz64(val, end) for (i64 (val) = 0; (val) < (end); ++val)

#define dtb_fo(val, end) for (int (val) = 1; (val) < (end); ++val)
#define dtb_fo64(val, end) for (i64 (val) = 1; (val) < (end); ++val)

#define dtb_fi(start, end) for (int i = (start); i < (end); ++i)
#define dtb_fj(start, end) for (int j = (start); j < (end); ++j)
#define dtb_fk(start, end) for (int k = (start); k < (end); ++k)

#define dtb_fi64(start, end) for (i64 i = (start); i < (end); ++i)
#define dtb_fj64(start, end) for (i64 j = (start); j < (end); ++j)
#define dtb_fk64(start, end) for (i64 k = (start); k < (end); ++k)

#define dtb_fiz(end) for (int i = 0; i < (end); ++i)
#define dtb_fjz(end) for (int j = 0; j < (end); ++j)
#define dtb_fkz(end) for (int k = 0; k < (end); ++k)

#define dtb_fiz64(end) for (i64 i = 0; i < (end); ++i)
#define dtb_fjz64(end) for (i64 j = 0; j < (end); ++j)
#define dtb_fkz64(end) for (i64 k = 0; k < (end); ++k)

#define dtb_fio(end) for (int i = 1; i < (end); ++i)
#define dtb_fjo(end) for (int j = 1; j < (end); ++j)
#define dtb_fko(end) for (int k = 1; k < (end); ++k)

#define dtb_fio64(end) for (i64 i = 1; i < (end); ++i)
#define dtb_fjo64(end) for (i64 j = 1; j < (end); ++j)
#define dtb_fko64(end) for (i64 k = 1; k < (end); ++k)

//Array shit
#define dtb_fei(array_name) for (int i = 0; i < DTB_ARR_LEN(array_name); ++i)
#define dtb_fej(array_name) for (int j = 0; j < DTB_ARR_LEN(array_name); ++j)
#define dtb_fek(array_name) for (int k = 0; k < DTB_ARR_LEN(array_name); ++k)

#define dtb_fei64(array_name) for (i64 i = 0; i < DTB_ARR_LEN(array_name); ++i)
#define dtb_fej64(array_name) for (i64 j = 0; j < DTB_ARR_LEN(array_name); ++j)
#define dtb_fek64(array_name) for (i64 k = 0; k < DTB_ARR_LEN(array_name); ++k)

#define dtb_fei1(array_name) for (int i = 1; i < DTB_ARR_LEN(array_name); ++i)
#define dtb_fej1(array_name) for (int j = 1; j < DTB_ARR_LEN(array_name); ++j)
#define dtb_fek1(array_name) for (int k = 1; k < DTB_ARR_LEN(array_name); ++k)

#define dtb_fei164(array_name) for (i64 i = 1; i < DTB_ARR_LEN(array_name); ++i)
#define dtb_fej164(array_name) for (i64 j = 1; j < DTB_ARR_LEN(array_name); ++j)
#define dtb_fek164(array_name) for (i64 k = 1; k < DTB_ARR_LEN(array_name); ++k)
#define dtb_for_each(array_name, index_name)  for (int index_name = 0; index_name < DTB_ARR_LEN(array_name); ++index_name)
#endif //DTB_NO_LOOPS

//File management
typedef struct
{
	char* name;
	char* contents;
	size_t size;
}dtb_file;

DTB_EXTERN dtb_file dtb_read_file(char* file_name);
DTB_EXTERN dtb_file dtb_write_file(char* file_name, char* msg);

dtb_file dtb_read_file(char* file_name)
{
	dtb_file result = {0};

	FILE* file = fopen(file_name, "rb");

	dtb_assert(file);

	fseek(file, 0, SEEK_END);
	size_t file_size = ftell(file);
	rewind(file);

	char* file_contents = (char*)malloc(file_size + 1);
	fread(file_contents, file_size, 1, file);
	fclose(file);

	result.name = file_name;
	result.size = file_size;
	result.contents = file_contents;

	return result;
}

//TODO: add a way to write to a file w/out removing the rest of the file
dtb_file dtb_write_file(char* file_name, char* msg)
{
	dtb_file result = {0};

	FILE* file = fopen(file_name, "w+");
	dtb_assert(file);

	fprintf(file, "%s", msg);

	fseek(file, 0, SEEK_END);
	size_t file_size = ftell(file);
	rewind(file);

	char* file_contents = (char*)malloc(file_size + 1);
	fread(file_contents, file_size, 1, file);
	fclose(file);

	result.name = file_name;
	result.size = file_size;
	result.contents = file_contents;

	return result;
}

#ifndef DTB_NO_MATH
//Math structs / section
typedef union 
{
	struct
	{
		float x, y;
	};

	struct
	{
		float u, v;
	};

	struct
	{
		float width, height;
	};

	float elements[2];

}dtb_vec2;

typedef union
{
	struct
	{
		float x, y, z;
	};

	struct
	{
		float r, g, b;
	};

	float elements[3];

}dtb_vec3;

typedef union
{
	struct
	{
		float x, y, z, w;
	};

	struct
	{
		float r, g, b, a;
	};

	float elements[4];
}dtb_vec4;

typedef union
{
	float elements[4][4];
}dtb_matrix4;

DTB_EXTERN dtb_vec2 dtbVec2();
DTB_EXTERN dtb_vec2 dtbVec2f(float x, float y);
DTB_EXTERN dtb_vec2 dtbVec2i(int x, int y);
DTB_EXTERN dtb_vec3 dtbVec3();
DTB_EXTERN dtb_vec3 dtbVec3f(float x, float y, float z);
DTB_EXTERN dtb_vec3 dtbVec3i(int x, int y, int z);
DTB_EXTERN dtb_vec4 dtbVec4();
DTB_EXTERN dtb_vec4 dtbVec4f(float x, float y, float z, float w);
DTB_EXTERN dtb_vec4 dtbVec4i(int x, int y, int z, int w);

DTB_EXTERN dtb_matrix4 dtbMatrix4();
DTB_EXTERN dtb_matrix4 dtbMatrix4d(float diagonal);

DTB_EXTERN dtb_vec2 dtb_vec2_add(dtb_vec2 left, dtb_vec2 right);
DTB_EXTERN dtb_vec2 dtb_vec2_subtract(dtb_vec2 left, dtb_vec2 right);
DTB_EXTERN dtb_vec2 dtb_vec2_divide(dtb_vec2 left, dtb_vec2 right);
DTB_EXTERN dtb_vec2 dtb_vec2_multiply(dtb_vec2 left, dtb_vec2 right);
DTB_EXTERN bool dtb_vec2_equals(dtb_vec2 left, dtb_vec2 right);

DTB_EXTERN dtb_vec3 dtb_vec3_add(dtb_vec3 left, dtb_vec3 right);
DTB_EXTERN dtb_vec3 dtb_vec3_subtract(dtb_vec3 left, dtb_vec3 right);
DTB_EXTERN dtb_vec3 dtb_vec3_multiply(dtb_vec3 left, dtb_vec3 right);
DTB_EXTERN dtb_vec3 dtb_vec3_divide(dtb_vec3 left, dtb_vec3 right);
DTB_EXTERN bool dtb_vec3_equals(dtb_vec3 left, dtb_vec3 right);

DTB_EXTERN dtb_vec4 dtb_vec4_add(dtb_vec4 left, dtb_vec4 right);
DTB_EXTERN dtb_vec4 dtb_vec4_subtract(dtb_vec4 left, dtb_vec4 right);
DTB_EXTERN dtb_vec4 dtb_vec4_divide(dtb_vec4 left, dtb_vec4 right);
DTB_EXTERN dtb_vec4 dtb_vec4_multiply(dtb_vec4 left, dtb_vec4 right);
DTB_EXTERN bool dtb_vec4_equals(dtb_vec4 left, dtb_vec4 right);

DTB_EXTERN dtb_matrix4 dtb_matrix4_add(dtb_matrix4 left, dtb_matrix4 right);
DTB_EXTERN dtb_matrix4 dtb_matrix4_subtract(dtb_matrix4 left, dtb_matrix4 right);
DTB_EXTERN dtb_matrix4 dtb_matrix4_mutiply(dtb_matrix4 left, dtb_matrix4 right);
DTB_EXTERN dtb_matrix4 dtb_matrix4_mutiplyf(dtb_matrix4 matrix, float scalar);
DTB_EXTERN dtb_matrix4 dtb_matrix4_dividef(dtb_matrix4 matrix, float scalar);
DTB_EXTERN bool dtb_matrix4_equals(dtb_matrix4 left, dtb_matrix4 right);

DTB_EXTERN dtb_matrix4 dtb_ortho(float left, float right, float bottom, float top, float near, float far);
DTB_EXTERN dtb_matrix4 dtb_perspective(float fov, float aspect_ratio, float near, float far);
DTB_EXTERN dtb_matrix4 dtb_translate(dtb_vec3 translation);
DTB_EXTERN dtb_matrix4 dtb_scale(dtb_vec3 scale);

//Formulas
#define DTB_PI 3.14159265359
#define DTB_MIN(a, b) (a) > (b) ? (b) : (a)
#define DTB_MAX(a, b) (a) < (b) ? (b) : (a)
#define DTB_ABS(a) ((a) > 0 ? (a) : -(a))

DTB_EXTERN double dtb_sin(double x);
DTB_EXTERN double dtb_cos(double x);
DTB_EXTERN double dtb_tan(double x);

//Power of fn's
DTB_EXTERN int dtb_powi(int x, unsigned int y);
DTB_EXTERN float dtb_powf(float x, int y);
DTB_EXTERN double dtb_powd(double x, int y);

//Distance formulas for plotting distance
DTB_EXTERN float dtb_distance(float x1, float x2, float y1, float y2);
DTB_EXTERN float dtb_distancev(dtb_vec2 x, dtb_vec2 y);
DTB_EXTERN float dtb_distancei(int x1, int x2, int y1, int y2);

//Pythagorean theorem for triangles
DTB_EXTERN float dtb_pythagorean(float a, float b);

//Determining if a perfect square or not
DTB_EXTERN int dtb_perfect_square(int n);

dtb_vec2 dtbVec2()
{
	dtb_vec2 result = {0};

	return result;
}

dtb_vec2 dtbVec2f(float x, float y)
{
	dtb_vec2 result = {0};

	result.x = x;
	result.y = y;

	return result;
}

dtb_vec2 dtbVec2i(int x, int y)
{
	dtb_vec2 result = {0};

	result.x = (float)x;
	result.y = (float)y;

	return result;
}

dtb_vec3 dtbVec3()
{
	dtb_vec3 result = {0};

	return result;
}

dtb_vec3 dtbVec3f(float x, float y, float z)
{
	dtb_vec3 result = {0};

	result.x = x;
	result.y = y;
	result.z = z;

	return result;
}

dtb_vec3 dtbVec3i(int x, int y, int z)
{
	dtb_vec3 result = {0};

	result.x = (float)x;
	result.y = (float)y;
	result.z = (float)z;

	return result;
}

dtb_vec4 dtbVec4()
{
	dtb_vec4 result = {0};

	return result;
}

dtb_vec4 dtbVec4f(float x, float y, float z, float w)
{
	dtb_vec4 result = {0};

	result.x = x;
	result.y = y;
	result.z = z;
	result.w = w;

	return result;
}

dtb_vec4 dtbVec4i(int x, int y, int z, int w)
{
	dtb_vec4 result = {0};

	result.x = (float)x;
	result.y = (float)y;
	result.z = (float)z;
	result.w = (float)w;

	return result;
}


dtb_vec2 dtb_vec2_add(dtb_vec2 left, dtb_vec2 right)
{
	dtb_vec2 result = {0};

	result.x = left.x + right.x;
	result.y = left.y + right.y;

	return result;
}

dtb_vec2 dtb_vec2_subtract(dtb_vec2 left, dtb_vec2 right)
{
	dtb_vec2 result = {0};

	result.x = left.x - right.x;
	result.y = left.y - right.y;

	return result;
}

dtb_vec2 dtb_vec2_divide(dtb_vec2 left, dtb_vec2 right)
{
	dtb_vec2 result = {0};

	result.x = left.x / right.x;
	result.y = left.y / right.y;

	return result;
}

dtb_vec2 dtb_vec2_multiply(dtb_vec2 left, dtb_vec2 right)
{
	dtb_vec2 result = {0};

	result.x = left.x * right.x;
	result.y = left.y * right.y;

	return result;
}

bool dtb_vec2_equals(dtb_vec2 left, dtb_vec2 right)
{
	if(left.x == right.x && left.y == right.y)
		return true;

	return false;
}

dtb_vec3 dtb_vec3_add(dtb_vec3 left, dtb_vec3 right)
{
	dtb_vec3 result = {0};

	result.x = left.x + right.x;
	result.y = left.y + right.y;
	result.z = left.z + right.z;

	return result;
}

dtb_vec3 dtb_vec3_subtract(dtb_vec3 left, dtb_vec3 right)
{
	dtb_vec3 result = {0};

	result.x = left.x - right.x;
	result.y = left.y - right.y;
	result.z = left.z - right.z;

	return result;
}

dtb_vec3 dtb_vec3_divide(dtb_vec3 left, dtb_vec3 right)
{
	dtb_vec3 result = {0};

	result.x = left.x / right.x;
	result.y = left.y / right.y;
	result.z = left.z / right.z;

	return result;
}

dtb_vec3 dtb_vec3_multiply(dtb_vec3 left, dtb_vec3 right)
{
	dtb_vec3 result = {0};

	result.x = left.x * right.x;
	result.y = left.y * right.y;
	result.z = left.z * right.z;

	return result;
}

bool dtb_vec3_equals(dtb_vec3 left, dtb_vec3 right)
{
	if(left.x == right.x && left.y == right.y && left.z == right.z)
		return true;
	return false;
}

dtb_vec4 dtb_vec4_add(dtb_vec4 left, dtb_vec4 right)
{
	dtb_vec4 result = {0};

	result.x = left.x + right.x;
	result.y = left.y + right.y;
	result.z = left.z + right.z;
	result.w = left.w + right.w;

	return result;
}

dtb_vec4 dtb_vec4_subtract(dtb_vec4 left, dtb_vec4 right)
{
	dtb_vec4 result = {0};

	result.x = left.x - right.x;
	result.y = left.y - right.y;
	result.z = left.z - right.z;
	result.w = left.w - right.w;

	return result;
}

dtb_vec4 dtb_vec4_multiply(dtb_vec4 left, dtb_vec4 right)
{
	dtb_vec4 result = {0};

	result.x = left.x * right.x;
	result.y = left.y * right.y;
	result.z = left.z * right.z;
	result.w = left.w * right.w;

	return result;
}

dtb_vec4 dtb_vec4_divide(dtb_vec4 left, dtb_vec4 right)
{
	dtb_vec4 result = {0};

	result.x = left.x / right.x;
	result.y = left.y / right.y;
	result.z = left.z / right.z;
	result.w = left.w / right.w;

	return result;
}

bool dtb_vec4_equals(dtb_vec4 left, dtb_vec4 right)
{
	if(left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w)
		return true;
	return false;
}

dtb_matrix4 dtbMatrix(void)
{
	dtb_matrix4 result = {0};
	return result;
}


dtb_matrix4 dtbMatrix4d(float diagonal)
{
	dtb_matrix4 result = {0};
	result.elements[0][0] = diagonal;
	result.elements[1][1] = diagonal;
	result.elements[2][2] = diagonal;
	result.elements[3][3] = diagonal;
	return result;
}

dtb_matrix4 dtb_matrix4_add(dtb_matrix4 left, dtb_matrix4 right)
{
	dtb_matrix4 result = {0};

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			result.elements[i][j] = left.elements[i][j] + right.elements[i][j];
		}
	}

	return result;
}

dtb_matrix4 dtb_matrix4_subtract(dtb_matrix4 left, dtb_matrix4 right)
{
	dtb_matrix4 result = {0};

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			result.elements[i][j] = left.elements[i][j] - right.elements[i][j];
		}
	}

	return result;
}

dtb_matrix4 dtb_matrix4_multiply(dtb_matrix4 left, dtb_matrix4 right)
{
	dtb_matrix4 result = {0};

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			float sum = 0;
			for(int k = 0; k < 4; k++)
			{
				sum += left.elements[i][j] * right.elements[i][k];
			}
			result.elements[i][j] = sum;
		}
	}

	return result;
}

dtb_matrix4 dtb_matrix4_multiplyf(dtb_matrix4 matrix, float scalar)
{
	dtb_matrix4 result = {0};

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			result.elements[i][j] = matrix.elements[i][j] * scalar;
		}
	}

	return result;
}

dtb_matrix4 dtb_matrix4_dividef(dtb_matrix4 matrix, float scalar)
{
	dtb_matrix4 result = {0};

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			result.elements[i][j] = matrix.elements[i][j] / scalar;
		}
	}

	return result;
}

bool dtb_matrix4_equals(dtb_matrix4 left, dtb_matrix4 right)
{
	if(left.elements == right.elements)
		return true;

	return false;
}

dtb_matrix4 dtb_ortho(float left, float right, float bottom, float top, float near, float far)
{
	dtb_matrix4 result = dtbMatrix4d(1.0f);
	result.elements[0][0] = 2.0f / (right - left);
	result.elements[1][1] = 2.0f / (top - bottom);
	result.elements[2][2] = 2.0f / (near - far);

	result.elements[3][0] = (left + right) / (left - right);
	result.elements[3][1] = (bottom + top) / (bottom - top);
	result.elements[3][2] = (far+ near) / (near- far);

	return result;
}

dtb_matrix4 dtb_perspective(float fov, float aspect_ratio, float near, float far)
{
	dtb_matrix4 result = dtbMatrix4d(1.0f);
	float tan_theta_over2 = (float)dtb_tan(fov * (DTB_PI / 360.0f));

	result.elements[0][0] = 1.0f / tan_theta_over2;
	result.elements[1][1] = aspect_ratio / tan_theta_over2;
	result.elements[2][3] = -1.0f;
	result.elements[2][2] = (near + far) / (near- far);
	result.elements[3][2] = (2.0f * near * far) / (near - far);
	result.elements[3][3] = 0.0f;
	return result;
}

dtb_matrix4 dtb_translate(dtb_vec3 translation)
{
	dtb_matrix4 result = dtbMatrix4d(1.0f);
	result.elements[3][0] = translation.x;
	result.elements[3][1] = translation.y;
	result.elements[3][2] = translation.z;
	return result;
}

dtb_matrix4 dtb_scale(dtb_vec3 scale)
{
	dtb_matrix4 result = dtbMatrix4d(1.0f);
	result.elements[0][0] = scale.x;
	result.elements[1][1] = scale.y;
	result.elements[2][2] = scale.z;
	return result;
}

#ifdef __cplusplus //operator overloading only available in c++

//Vec2
dtb_vec2 operator+(dtb_vec2 left, dtb_vec2 right)
{
	return dtb_vec2_add(left, right);
}

dtb_vec2 operator-(dtb_vec2 left, dtb_vec2 right)
{
	return dtb_vec2_subtract(left, right);
}

dtb_vec2 operator*(dtb_vec2 left, dtb_vec2 right)
{
	return dtb_vec2_multiply(left, right);
}

dtb_vec2 operator/(dtb_vec2 left, dtb_vec2 right)
{
	return dtb_vec2_divide(left, right);
}

bool operator==(dtb_vec2 left, dtb_vec2 right)
{
	return dtb_vec2_equals(left, right);
}


//Vec3
dtb_vec3 operator+(dtb_vec3 left, dtb_vec3 right)
{
	return dtb_vec3_add(left, right);
}

dtb_vec3 operator-(dtb_vec3 left, dtb_vec3 right)
{
	return dtb_vec3_subtract(left, right);
}

dtb_vec3 operator*(dtb_vec3 left, dtb_vec3 right)
{
	return dtb_vec3_multiply(left, right);
}

dtb_vec3 operator/(dtb_vec3 left, dtb_vec3 right)
{
	return dtb_vec3_divide(left, right);
}

bool operator==(dtb_vec3 left, dtb_vec3 right)
{
	return dtb_vec3_equals(left, right);
}

//Vec4
dtb_vec4 operator+(dtb_vec4 left, dtb_vec4 right)
{
	return dtb_vec4_add(left, right);
}

dtb_vec4 operator-(dtb_vec4 left, dtb_vec4 right)
{
	return dtb_vec4_subtract(left, right);
}

dtb_vec4 operator*(dtb_vec4 left, dtb_vec4 right)
{
	return dtb_vec4_multiply(left, right);
}

dtb_vec4 operator/(dtb_vec4 left, dtb_vec4 right)
{
	return dtb_vec4_divide(left, right);
}

bool operator==(dtb_vec4 left, dtb_vec4 right)
{
	return dtb_vec4_equals(left, right);
}

//Mat4
dtb_matrix4 operator+(dtb_matrix4 left, dtb_matrix4 right)
{
	return dtb_matrix4_add(left, right);
}

dtb_matrix4 operator-(dtb_matrix4 left, dtb_matrix4 right)
{
	return dtb_matrix4_subtract(left, right);
}

dtb_matrix4 operator*(dtb_matrix4 left, dtb_matrix4 right)
{
	return dtb_matrix4_multiply(left, right);
}

dtb_matrix4 operator*(dtb_matrix4 left, float right)
{
	return dtb_matrix4_multiplyf(left, right);
}

dtb_matrix4 operator/(dtb_matrix4 left, float right)
{
	return dtb_matrix4_dividef(left, right);
}

bool operator==(dtb_matrix4 left, dtb_matrix4 right)
{
	return dtb_matrix4_equals(left, right);
}

#endif //operator overloading only available in c++

//Formulas
//Easy Macros
#define DTB_AREA_TRIANGLE(b, h)			    (b * h) / 2
#define DTB_AREA_SQUARE(l, w)			      l * w
#define DTB_PERIMETER_TRIANGLE(a, b, c)		a + b + c
#define DTB_PERIMETER_SQUARE(a)			    a * 4

// NOTE(ALL):
// DISCLAIMER:
// The following code is taken from 
// http://www.netlib.org/fdlibm
// None of this code is my own, minus
// some exceptions. Please give credit
// to the author and not to me for the
// following cosine, sine, and tangent
// code.

#ifdef __LITTLE_ENDIAN
#define __HI(x) *(1+(int*)&x)
#define __LO(x) *(int*)&x
#else
#define __HI(x) *(int*)&x
#define __LO(x) *(1+(int*)&x)
#endif

static double
	two54   =  1.80143985094819840000e+16, /* 0x43500000, 0x00000000 */
	twom54  =  5.55111512312578270212e-17, /* 0x3C900000, 0x00000000 */
	huge   = 1.0e+300,
	tiny   = 1.0e-300;

double dtb_fabs(double x)
{
	__HI(x) &= 0x7fffffff;
	return x;
}

double copysign(double x, double y)
{
	__HI(x) = (__HI(x)&0x7fffffff)|(__HI(y)&0x80000000);
	return x;
}

double scalbn (double x, int n)
{
	int  k,hx,lx;
	hx = __HI(x);
	lx = __LO(x);
	k = (hx&0x7ff00000)>>20;		/* extract exponent */
	if (k==0) 
	{   /* 0 or subnormal x */
		if ((lx|(hx&0x7fffffff))==0) 
			return x; /* +-0 */
		x *= two54; 
		hx = __HI(x);
		k = ((hx&0x7ff00000)>>20) - 54; 
		if (n< -50000) 
			return tiny*x; 	/*underflow*/
	}
	if (k==0x7ff)
		return x+x;		/* NaN or Inf */
	k = k+n; 
	if (k >  0x7fe) 
		return huge*copysign(huge,x); /* overflow  */
	if (k > 0) 				/* normal result */
	{
		__HI(x) = (hx&0x800fffff)|(k<<20);
		return x;
	}
	if (k <= -54)
		if (n > 50000) 	/* in case integer overflow in n+k */
			return huge*copysign(huge,x);	/*overflow*/
		else
			return tiny*copysign(tiny,x); 	/*underflow*/
	k += 54;				/* subnormal result */
	__HI(x) = (hx&0x800fffff)|(k<<20);
	return x*twom54;
}

double floor(double x)
{
	int i0,i1,j0;
	unsigned i,j;
	i0 =  __HI(x);
	i1 =  __LO(x);
	j0 = ((i0>>20)&0x7ff)-0x3ff;
	if(j0<20)
	{
		if(j0<0)
		{
			if(huge+x>0.0)
			{
				if(i0>=0)
				{
					i0=i1=0;
				}

				else if(((i0&0x7fffffff)|i1)!=0)
				{
					i0=0xbff00000;
					i1=0;
				}
			}
		}
		else
		{
			i = (0x000fffff)>>j0;
			if(((i0&i)|i1)==0)
				return x;
			if(huge+x>0.0) 
			{
				if(i0<0)
					i0 += (0x00100000)>>j0;

				i0 &= (~i); i1=0;
			}
		}
	}
	else if (j0>51)
	{
		if(j0==0x400)
			return x+x;
		else
			return x;
	} 
	else
	{
		i = ((unsigned)(0xffffffff))>>(j0-20);
		if((i1&i)==0) 
			return x;
		if(huge+x>0.0)
		{
			if(i0<0)
			{
				if(j0==20)
					i0+=1; 
				else
				{
					j = i1+(1<<(52-j0));
					if(j < i1) i0 +=1 ; 	/* got a carry */
					i1=j;
				}
			}
			i1 &= (~i);
		}
	}

	__HI(x) = i0;
	__LO(x) = i1;

	return x;
}

static int init_jk[] = {2,3,4,6}; 

static double PIo2[] =
{
	1.57079625129699707031e+00, /* 0x3FF921FB, 0x40000000 */
	7.54978941586159635335e-08, /* 0x3E74442D, 0x00000000 */
	5.39030252995776476554e-15, /* 0x3CF84698, 0x80000000 */
	3.28200341580791294123e-22, /* 0x3B78CC51, 0x60000000 */
	1.27065575308067607349e-29, /* 0x39F01B83, 0x80000000 */
	1.22933308981111328932e-36, /* 0x387A2520, 0x40000000 */
	2.73370053816464559624e-44, /* 0x36E38222, 0x80000000 */
	2.16741683877804819444e-51, /* 0x3569F31D, 0x00000000 */
};

static double			
	zero   = 0.0,
	one    = 1.0,
	two24   =  1.67772160000000000000e+07, /* 0x41700000, 0x00000000 */
	twon24  =  5.96046447753906250000e-08; /* 0x3E700000, 0x00000000 */


int __kernel_rem_pio2(double *x, double *y, int e0, int nx, int prec, const int *ipio2) 
{
	int jz,jx,jv,jp,jk,carry,n,iq[20],i,j,k,m,q0,ih;
	double z,fw,f[20],fq[20],q[20];

	/* initialize jk*/
	jk = init_jk[prec];
	jp = jk;

	/* determine jx,jv,q0, note that 3>q0 */
	jx =  nx-1;
	jv = (e0-3)/24; if(jv<0) jv=0;
	q0 =  e0-24*(jv+1);

	/* set up f[0] to f[jx+jk] where f[jx+jk] = ipio2[jv+jk] */
	j = jv-jx; m = jx+jk;
	for(i=0;i<=m;i++,j++)
		f[i] = (j<0)? zero : (double) ipio2[j];

	/* compute q[0],q[1],...q[jk] */
	for (i=0;i<=jk;i++)
	{
		for(j=0,fw=0.0;j<=jx;j++) 
			fw += x[j]*f[jx+i-j]; q[i] = fw;
	}

	jz = jk;
recompute:
	/* distill q[] into iq[] reversingly */
	for(i=0,j=jz,z=q[jz];j>0;i++,j--)
	{
		fw    =  (double)((int)(twon24* z));
		iq[i] =  (int)(z-two24*fw);
		z     =  q[j-1]+fw;
	}

	/* compute n */
	z  = scalbn(z,q0);		/* actual value of z */
	z -= 8.0*floor(z*0.125);		/* trim off integer >= 8 */
	n  = (int) z;
	z -= (double)n;
	ih = 0;
	if(q0>0)
	{	/* need iq[jz-1] to determine n */
		i  = (iq[jz-1]>>(24-q0)); n += i;
		iq[jz-1] -= i<<(24-q0);
		ih = iq[jz-1]>>(23-q0);
	} 
	else if(q0==0) 
		ih = iq[jz-1]>>23;
	else if(z>=0.5) 
		ih=2;

	if(ih>0)
	{	/* q > 0.5 */
		n += 1; carry = 0;
		for(i=0;i<jz ;i++)
		{	/* compute 1-q */
			j = iq[i];
			if(carry==0) 
			{
				if(j!=0) 
				{
					carry = 1; iq[i] = 0x1000000- j;
				}
			}
			else  iq[i] = 0xffffff - j;
		}
		if(q0>0)
		{		/* rare case: chance is 1 in 12 */
			switch(q0) 
			{
			case 1:
				iq[jz-1] &= 0x7fffff; 
				break;
			case 2:
				iq[jz-1] &= 0x3fffff; 
				break;
			}
		}
		if(ih==2) 
		{
			z = one - z;
			if(carry!=0) 
				z -= scalbn(one,q0);
		}
	}

	/* check if recomputation is needed */
	if(z==zero)
	{
		j = 0;
		for (i=jz-1;i>=jk;i--) 
			j |= iq[i];
		if(j==0)
		{ /* need recomputation */
			for(k=1;iq[jk-k]==0;k++);   /* k = no. of terms needed */

			for(i=jz+1;i<=jz+k;i++) 
			{   /* add q[jz+1] to q[jz+k] */
				f[jx+i] = (double) ipio2[jv+i];
				for(j=0,fw=0.0;j<=jx;j++) 
					fw += x[j]*f[jx+i-j];
				q[i] = fw;
			}
			jz += k;
			goto recompute;
		}
	}

	/* chop off zero terms */
	if(z==0.0) {
		jz -= 1; q0 -= 24;
		while(iq[jz]==0) { jz--; q0-=24;}
	} else { /* break z into 24-bit if necessary */
		z = scalbn(z,-q0);
		if(z>=two24) { 
			fw = (double)((int)(twon24*z));
			iq[jz] = (int)(z-two24*fw);
			jz += 1; q0 += 24;
			iq[jz] = (int) fw;
		} else iq[jz] = (int) z ;
	}

	/* convert integer "bit" chunk to floating-point value */
	fw = scalbn(one,q0);
	for(i=jz;i>=0;i--) {
		q[i] = fw*(double)iq[i]; fw*=twon24;
	}

	/* compute PIo2[0,...,jp]*q[jz,...,0] */
	for(i=jz;i>=0;i--) {
		for(fw=0.0,k=0;k<=jp&&k<=jz-i;k++) fw += PIo2[k]*q[i+k];
		fq[jz-i] = fw;
	}

	/* compress fq[] into y[] */
	switch(prec) {
	case 0:
		fw = 0.0;
		for (i=jz;i>=0;i--) fw += fq[i];
		y[0] = (ih==0)? fw: -fw; 
		break;
	case 1:
	case 2:
		fw = 0.0;
		for (i=jz;i>=0;i--) fw += fq[i]; 
		y[0] = (ih==0)? fw: -fw; 
		fw = fq[0]-fw;
		for (i=1;i<=jz;i++) fw += fq[i];
		y[1] = (ih==0)? fw: -fw; 
		break;
	case 3:	/* painful */
		for (i=jz;i>0;i--) {
			fw      = fq[i-1]+fq[i]; 
			fq[i]  += fq[i-1]-fw;
			fq[i-1] = fw;
		}
		for (i=jz;i>1;i--) {
			fw      = fq[i-1]+fq[i]; 
			fq[i]  += fq[i-1]-fw;
			fq[i-1] = fw;
		}
		for (fw=0.0,i=jz;i>=2;i--) fw += fq[i]; 
		if(ih==0) {
			y[0] =  fq[0]; y[1] =  fq[1]; y[2] =  fw;
		} else {
			y[0] = -fq[0]; y[1] = -fq[1]; y[2] = -fw;
		}
	}
	return n&7;
}


static int two_over_pi[] = 
{
	0xA2F983, 0x6E4E44, 0x1529FC, 0x2757D1, 0xF534DD, 0xC0DB62, 
	0x95993C, 0x439041, 0xFE5163, 0xABDEBB, 0xC561B7, 0x246E3A, 
	0x424DD2, 0xE00649, 0x2EEA09, 0xD1921C, 0xFE1DEB, 0x1CB129, 
	0xA73EE8, 0x8235F5, 0x2EBB44, 0x84E99C, 0x7026B4, 0x5F7E41, 
	0x3991D6, 0x398353, 0x39F49C, 0x845F8B, 0xBDF928, 0x3B1FF8, 
	0x97FFDE, 0x05980F, 0xEF2F11, 0x8B5A0A, 0x6D1F6D, 0x367ECF, 
	0x27CB09, 0xB74F46, 0x3F669E, 0x5FEA2D, 0x7527BA, 0xC7EBE5, 
	0xF17B3D, 0x0739F7, 0x8A5292, 0xEA6BFB, 0x5FB11F, 0x8D5D08, 
	0x560330, 0x46FC7B, 0x6BABF0, 0xCFBC20, 0x9AF436, 0x1DA9E3, 
	0x91615E, 0xE61B08, 0x659985, 0x5F14A0, 0x68408D, 0xFFD880, 
	0x4D7327, 0x310606, 0x1556CA, 0x73A8C9, 0x60E27B, 0xC08C6B, 
};

#ifdef __STDC__
static const int npio2_hw[] = {
#else
static int npio2_hw[] = {
#endif
	0x3FF921FB, 0x400921FB, 0x4012D97C, 0x401921FB, 0x401F6A7A, 0x4022D97C,
	0x4025FDBB, 0x402921FB, 0x402C463A, 0x402F6A7A, 0x4031475C, 0x4032D97C,
	0x40346B9C, 0x4035FDBB, 0x40378FDB, 0x403921FB, 0x403AB41B, 0x403C463A,
	0x403DD85A, 0x403F6A7A, 0x40407E4C, 0x4041475C, 0x4042106C, 0x4042D97C,
	0x4043A28C, 0x40446B9C, 0x404534AC, 0x4045FDBB, 0x4046C6CB, 0x40478FDB,
	0x404858EB, 0x404921FB,
};

/*
* invpio2:  53 bits of 2/pi
* pio2_1:   first  33 bit of pi/2
* pio2_1t:  pi/2 - pio2_1
* pio2_2:   second 33 bit of pi/2
* pio2_2t:  pi/2 - (pio2_1+pio2_2)
* pio2_3:   third  33 bit of pi/2
* pio2_3t:  pi/2 - (pio2_1+pio2_2+pio2_3)
*/


static double 
	half =  5.00000000000000000000e-01, /* 0x3FE00000, 0x00000000 */
	invpio2 =  6.36619772367581382433e-01, /* 0x3FE45F30, 0x6DC9C883 */
	pio2_1  =  1.57079632673412561417e+00, /* 0x3FF921FB, 0x54400000 */
	pio2_1t =  6.07710050650619224932e-11, /* 0x3DD0B461, 0x1A626331 */
	pio2_2  =  6.07710050630396597660e-11, /* 0x3DD0B461, 0x1A600000 */
	pio2_2t =  2.02226624879595063154e-21, /* 0x3BA3198A, 0x2E037073 */
	pio2_3  =  2.02226624871116645580e-21, /* 0x3BA3198A, 0x2E000000 */
	pio2_3t =  8.47842766036889956997e-32; /* 0x397B839A, 0x252049C1 */


int __ieee754_rem_pio2(double x, double *y)
{
	double z,w,t,r,fn;
	double tx[3];
	int e0,i,j,nx,n,ix,hx;

	hx = __HI(x);		/* high word of x */
	ix = hx&0x7fffffff;
	if(ix<=0x3fe921fb)   /* |x| ~<= pi/4 , no need for reduction */
	{y[0] = x; y[1] = 0; return 0;}
	if(ix<0x4002d97c) {  /* |x| < 3pi/4, special case with n=+-1 */
		if(hx>0) { 
			z = x - pio2_1;
			if(ix!=0x3ff921fb) { 	/* 33+53 bit pi is good enough */
				y[0] = z - pio2_1t;
				y[1] = (z-y[0])-pio2_1t;
			} else {		/* near pi/2, use 33+33+53 bit pi */
				z -= pio2_2;
				y[0] = z - pio2_2t;
				y[1] = (z-y[0])-pio2_2t;
			}
			return 1;
		} else {	/* negative x */
			z = x + pio2_1;
			if(ix!=0x3ff921fb) { 	/* 33+53 bit pi is good enough */
				y[0] = z + pio2_1t;
				y[1] = (z-y[0])+pio2_1t;
			} else {		/* near pi/2, use 33+33+53 bit pi */
				z += pio2_2;
				y[0] = z + pio2_2t;
				y[1] = (z-y[0])+pio2_2t;
			}
			return -1;
		}
	}
	if(ix<=0x413921fb) { /* |x| ~<= 2^19*(pi/2), medium size */
		t  = dtb_fabs(x);
		n  = (int) (t*invpio2+half);
		fn = (double)n;
		r  = t-fn*pio2_1;
		w  = fn*pio2_1t;	/* 1st round good to 85 bit */
		if(n<32&&ix!=npio2_hw[n-1]) {	
			y[0] = r-w;	/* quick check no cancellation */
		} else {
			j  = ix>>20;
			y[0] = r-w; 
			i = j-(((__HI(y[0]))>>20)&0x7ff);
			if(i>16) {  /* 2nd iteration needed, good to 118 */
				t  = r;
				w  = fn*pio2_2;	
				r  = t-w;
				w  = fn*pio2_2t-((t-r)-w);	
				y[0] = r-w;
				i = j-(((__HI(y[0]))>>20)&0x7ff);
				if(i>49)  {	/* 3rd iteration need, 151 bits acc */
					t  = r;	/* will cover all possible cases */
					w  = fn*pio2_3;	
					r  = t-w;
					w  = fn*pio2_3t-((t-r)-w);	
					y[0] = r-w;
				}
			}
		}
		y[1] = (r-y[0])-w;
		if(hx<0) 	{y[0] = -y[0]; y[1] = -y[1]; return -n;}
		else	 return n;
	}
	/* 
	* all other (large) arguments
	*/
	if(ix>=0x7ff00000) {		/* x is inf or NaN */
		y[0]=y[1]=x-x; return 0;
	}
	/* set z = scalbn(|x|,ilogb(x)-23) */
	__LO(z) = __LO(x);
	e0 	= (ix>>20)-1046;	/* e0 = ilogb(z)-23; */
	__HI(z) = ix - (e0<<20);
	for(i=0;i<2;i++) {
		tx[i] = (double)((int)(z));
		z     = (z-tx[i])*two24;
	}
	tx[2] = z;
	nx = 3;
	while(tx[nx-1]==zero) nx--;	/* skip zero term */
	n  =  __kernel_rem_pio2(tx,y,e0,nx,2,two_over_pi);
	if(hx<0) {y[0] = -y[0]; y[1] = -y[1]; return -n;}
	return n;
}








static const double xxx[] = 
{
	3.33333333333334091986e-01,	/* 3FD55555, 55555563 */
	1.33333333333201242699e-01,	/* 3FC11111, 1110FE7A */
	5.39682539762260521377e-02,	/* 3FABA1BA, 1BB341FE */
	2.18694882948595424599e-02,	/* 3F9664F4, 8406D637 */
	8.86323982359930005737e-03,	/* 3F8226E3, E96E8493 */
	3.59207910759131235356e-03,	/* 3F6D6D22, C9560328 */
	1.45620945432529025516e-03,	/* 3F57DBC8, FEE08315 */
	5.88041240820264096874e-04,	/* 3F4344D8, F2F26501 */
	2.46463134818469906812e-04,	/* 3F3026F7, 1A8D1068 */
	7.81794442939557092300e-05,	/* 3F147E88, A03792A6 */
	7.14072491382608190305e-05,	/* 3F12B80F, 32F0A7E9 */
	-1.85586374855275456654e-05,	/* BEF375CB, DB605373 */
	2.59073051863633712884e-05,	/* 3EFB2A70, 74BF7AD4 */
	1.00000000000000000000e+00,	/* 3FF00000, 00000000 */
	7.85398163397448278999e-01,	/* 3FE921FB, 54442D18 */
	3.06161699786838301793e-17,	/* 3C81A626, 33145C07 */
};

#define	one	xxx[13]
#define	pio4	xxx[14]
#define	pio4lo	xxx[15]
#define	T	xxx

double __kernel_tan(double x, double y, int iy) {
	double z, r, v, w, s;
	int ix, hx;
	hx = __HI(x);		/* high word of x */
	ix = hx & 0x7fffffff;			/* high word of |x| */
	if (ix < 0x3e300000) {			/* x < 2**-28 */
		if ((int) x == 0) {		/* generate inexact */
			if (((ix | __LO(x)) | (iy + 1)) == 0)
				return one / dtb_fabs(x);
			else {
				if (iy == 1)
					return x;
				else {	/* compute -1 / (x+y) carefully */
					double a, t;

					z = w = x + y;
					__LO(z) = 0;
					v = y - (z - x);
					t = a = -one / w;
					__LO(t) = 0;
					s = one + t * z;
					return t + a * (s + t * v);
				}
			}
		}
	}
	if (ix >= 0x3FE59428) {	/* |x| >= 0.6744 */
		if (hx < 0) {
			x = -x;
			y = -y;
		}
		z = pio4 - x;
		w = pio4lo - y;
		x = z + w;
		y = 0.0;
	}
	z = x * x;
	w = z * z;
	/*
	* Break x^5*(T[1]+x^2*T[2]+...) into
	* x^5(T[1]+x^4*T[3]+...+x^20*T[11]) +
	* x^5(x^2*(T[2]+x^4*T[4]+...+x^22*[T12]))
	*/
	r = T[1] + w * (T[3] + w * (T[5] + w * (T[7] + w * (T[9] +
		w * T[11]))));
	v = z * (T[2] + w * (T[4] + w * (T[6] + w * (T[8] + w * (T[10] +
		w * T[12])))));
	s = z * x;
	r = y + z * (s * (r + v) + y);
	r += T[0] * s;
	w = x + r;
	if (ix >= 0x3FE59428) {
		v = (double) iy;
		return (double) (1 - ((hx >> 30) & 2)) *
			(v - 2.0 * (x - (w * w / (w + v) - r)));
	}
	if (iy == 1)
		return w;
	else {
		/*
		* if allow error up to 2 ulp, simply return
		* -1.0 / (x+r) here
		*/
		/* compute -1.0 / (x+r) accurately */
		double a, t;
		z = w;
		__LO(z) = 0;
		v = r - (z - x);	/* z+v = r+x */
		t = a = -1.0 / w;	/* a = -1.0/w */
		__LO(t) = 0;
		s = 1.0 + t * z;
		return t + a * (s + t * v);
	}
}

//Tangent code
double dtb_tan(double x)
{
	double y[2],z=0.0;
	int n, ix;

	/* High word of x. */
	ix = __HI(x);

	/* |x| ~< pi/4 */
	ix &= 0x7fffffff;
	if(ix <= 0x3fe921fb) return __kernel_tan(x,z,1);

	/* tan(Inf or NaN) is NaN */
	else if (ix>=0x7ff00000) return x-x;		/* NaN */

	/* argument reduction needed */
	else {
		n = __ieee754_rem_pio2(x,y);
		return __kernel_tan(y[0],y[1],1-((n&1)<<1)); /*   1 -- n even
													 -1 -- n odd */
	}
}


//Cosine code
double 
	dtb_one = 1.00000000000000000000e+00, /* 0x3FF00000, 0x00000000 */
	C1  =  4.16666666666666019037e-02, /* 0x3FA55555, 0x5555554C */
	C2  = -1.38888888888741095749e-03, /* 0xBF56C16C, 0x16C15177 */
	C3  =  2.48015872894767294178e-05, /* 0x3EFA01A0, 0x19CB1590 */
	C4  = -2.75573143513906633035e-07, /* 0xBE927E4F, 0x809C52AD */
	C5  =  2.08757232129817482790e-09, /* 0x3E21EE9E, 0xBDB4B1C4 */
	C6  = -1.13596475577881948265e-11; /* 0xBDA8FAE9, 0xBE8838D4 */
double __kernel_cos(double x, double y)
{
	double a,hz,z,r,qx;
	int ix;
	ix = __HI(x)&0x7fffffff;	/* ix = |x|'s high word*/
	if(ix<0x3e400000)
	{			/* if x < 2**27 */
		if(((int)x)==0) 
			return dtb_one;		/* generate inexact */
	}

	z  = x*x;
	r  = z*(C1+z*(C2+z*(C3+z*(C4+z*(C5+z*C6)))));
	if(ix < 0x3FD33333) 			/* if |x| < 0.3 */ 
		return dtb_one - (0.5*z - (z*r - x*y));
	else 
	{
		if(ix > 0x3fe90000)
		{		/* x > 0.78125 */
			qx = 0.28125;
		} 
		else 
		{
			__HI(qx) = ix-0x00200000;	/* x/4 */
			__LO(qx) = 0;
		}

		hz = 0.5*z-qx;
		a  = dtb_one-qx;
		return a - (hz - (z*r-x*y));
	}
}

//Sine code
static const double
	S1  = -1.66666666666666324348e-01, /* 0xBFC55555, 0x55555549 */
	S2  =  8.33333333332248946124e-03, /* 0x3F811111, 0x1110F8A6 */
	S3  = -1.98412698298579493134e-04, /* 0xBF2A01A0, 0x19C161D5 */
	S4  =  2.75573137070700676789e-06, /* 0x3EC71DE3, 0x57B1FE7D */
	S5  = -2.50507602534068634195e-08, /* 0xBE5AE5E6, 0x8A2B9CEB */
	S6  =  1.58969099521155010221e-10; /* 0x3DE5D93A, 0x5ACFD57C */
double __kernel_sin(double x, double y, int iy)
{
	double z,r,v;
	int ix;
	ix = __HI(x)&0x7fffffff;
	if(ix<0x3e400000)
	{
		if((int)x==0) 
			return x;
	}

	z =  x*x;
	v =  z*x;
	r =  S2+z*(S3+z*(S4+z*(S5+z*S6)));
	if(iy==0) 
		return x+v*(S1+z*r);
	else
		return x-((z*(half*y-v*r)-y)-v*S1);
}



double dtb_cos(double x)
{
	double y[2],z=0.0;
	int n, ix;

	ix = __HI(x);

	ix &= 0x7fffffff;
	if(ix <= 0x3fe921fb) return __kernel_cos(x,z);

	/* cos(Inf or NaN) is NaN */
	else if (ix>=0x7ff00000) return x-x;

	/* argument reduction needed */
	else {
		n = __ieee754_rem_pio2(x,y);
		switch(n&3) {
		case 0: return  __kernel_cos(y[0],y[1]);
		case 1: return -__kernel_sin(y[0],y[1],1);
		case 2: return -__kernel_cos(y[0],y[1]);
		default:
			return  __kernel_sin(y[0],y[1],1);
		}
	}
}

double dtb_sin(double x)
{
	double y[2],z=0.0;
	int n, ix;

	ix = __HI(x);

	ix &= 0x7fffffff;
	if(ix <= 0x3fe921fb) 
		return __kernel_sin(x,z,0);

	/* sin(Inf or NaN) is NaN */
	else if (ix>=0x7ff00000) 
		return x-x;

	/* argument reduction needed */
	else {
		n = __ieee754_rem_pio2(x,y);
		switch(n&3) {
		case 0: return  __kernel_sin(y[0],y[1],1);
		case 1: return  __kernel_cos(y[0],y[1]);
		case 2: return -__kernel_sin(y[0],y[1],1);
		default:
			return -__kernel_cos(y[0],y[1]);
		}
	}
}

//Triangle math
float dtb_pythagorean(float a, float b)
{
	float a2 = dtb_powf(a, 2);
	float b2 = dtb_powf(b, 2);

	float c2 = a2 + b2;

	return c2;
}

//Square math
int dtb_perfect_square(int n)
{
	int h = n & 0xF;
	if(h > 9)
		return 0;

	if(h != 2 && h != 3 && h !=5 && h != 6 && h != 7 && h != 8)
	{
		int t = 0;
		t = dtb_powi(t, 0.5f);

		return t * t == n;
	}


	return 0;
}

//Power of
int dtb_powi(int x, unsigned int y)
{
	if(y ==0)
	{
		return 1;
	}

	else if((y % 2) == 0)
	{
		return dtb_powi(x, y / 2) * dtb_powi(x, y / 2);
	}

	else
	{
		return x * dtb_powi(x, y / 2) * dtb_powi(x, y / 2);
	}

	return NULL;
}

float dtb_powf(float x, int y)
{
	float temp;

	if(y == 0)
	{
		return  1;
	}

	temp = dtb_powf(x, y / 2);
	if((y % 2) == 0)
	{
		return temp * temp;
	}
	else
	{
		if(y > 0)
		{
			return x * temp * temp;
		}
		else
		{
			return (temp * temp) / x;
		}
	}
}

double dtb_powd(double x, int y)
{
	double temp;
	if(y == 0)
	{
		return 1;
	}

	temp = dtb_powd(x, y / 2);
	if((y % 2) == 0)
	{
		return temp * temp;
	}
	else
	{
		if(y > 0)
		{
			return x * temp * temp;
		}
		else
		{
			return (temp * temp) / x;
		}
	}
}

// Distance formula
float dtb_distance(float x1, float x2, float y1, float y2)
{
	float result = dtb_powf(dtb_powi((x2 - x1) + (y2 - y1), 2), 0.5f);
	return result;
}

float dtb_distancei(int x1, int x2, int y1, int y2)
{
	float result = dtb_powf(dtb_powf((x2 - x1) + (y2 - y1), 2.f), 0.5f);
	return result;
}

float dtb_distancev(dtb_vec2 position1, dtb_vec2 position2)
{
	float result = dtb_powf(dtb_powf((position2.x - position1.x) + (position2.y - position1.y), 2), 0.5f);
	return result;
}
#endif //DTB_NO_MATH

#endif //DTB_IMPLEMENT

#define DTB_INCLUDE_GUARD
#endif //DTB_INCLUDE_GUARD
