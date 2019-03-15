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

//Standard libs
#include <stdio.h>
#include <stdlib.h>

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

//Regular types
typedef char unsigned uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

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
inline size_t dtb_strlen(const char *s)
{
	size_t sz = 0;
	while(*s++ != '\0')
	{
		++sz;
	}
	return sz;
}

inline size_t dtb_strnlen(const char *s, size_t max_len)
{
	size_t i;
	for(i = 0; (i < max_len) && s[i]; ++i);
	return i;
}

inline char *dtb_strcpy(char *s, const char *ct)
{
	size_t n = dtb_strlen(ct);
	char *saver = (char*)malloc(n + 1);
	saver = s;
	while(n--)
		*saver++ = *ct++;
	
	*saver = '\0';
	
	return s;
}

inline char *dtb_strncpy(char *s, const char *ct, size_t n) 
{
	char *saver = (char*)malloc(n + 1);
	saver = s;
	while(n--)
		*saver++ = *ct++;
	
	*saver = '\0';
	
	return s;
}

inline int dtb_strcmp(const char* s, const char *t)
{
	while(*s != '\0' && *t != '\0' && *s == *t)
	{
		s++;
		t++;
	}
	
	return (*s - *t);
}

inline int dtb_strncmp(const char *s, const char *t, size_t n) 
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
inline void dtb_memcpy(void *src, void *dest)
{
	int n = sizeof(src);
	
	char *p_src = (char *)src;
	char *p_dest = (char *)dest;
	
	for (int i = 0; i < n; i++) 
	{
		p_dest[i] = p_src[i];
	}
	
}

inline void dtb_memncpy(void *src, void *dest, size_t n) 
{
	char *p_src = (char *)src;
	char *p_dest = (char *)dest;
	
	for (size_t i = 0; i < n; i++)
	{
		p_dest[i] = p_src[i];
	}
}

// TODO(dillon): Make sure this works in pure C
inline void dtb_memmove(void *src, void *dest)
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

inline void dtb_memnmove(void *src, void *dest, size_t n)
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
#define dtb_array_count(array) sizeof(array) / array[0]

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

//File management
typedef struct
{
	char* name;
	char* contents;
	size_t size;
}dtb_file;


inline dtb_file dtb_read_file(char* file_name)
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
inline dtb_file dtb_write_file(char* file_name, char* msg)
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

#define DTB_INCLUDE_GUARD
#endif //DTB_INCLUDE_GUARD
