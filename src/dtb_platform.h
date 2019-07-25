/* ============================================================================================
* PROJECT:  Dillon's Tool Box Platform Edition
* AUTHOR:   Dillon Williams
* LICENSE:  Do What The Fuck Ever license
* LANGUAGE: C\C++
*
* 
* INFORMATION:
* Window creation and managment code that instantiates a window on windows and
* linux. Below explains important things to remember and how to implement the API
* 
* IMPORTANT
* OpenGL is required to run. Also every call the end user makes should run through an already defined struct call dtb_platform.
* I have named it "platform". So to use in a scenario it would like " int new_width = platform.window_width; "
* 
* Your main compilation file should look similiar to this:
* -------------------------------------------------------------------------------
#include "dtb_platform.h"

int main(int argc, char* argv[])
{
dtb_platform_init("Window Title", 800, 600);

while(platform.running)
{
dtb_platform_update();

//Your calls here

}

return 0;
}
* -------------------------------------------------------------------------------
*
*
*
* Cursor positions are stored in platform.cursorX and platform.cursorY
*
*
*
* To grab key presses do:
* -------------------------------------------------------------------------------

if(dtb_check_key(dtb_key_space))
{
}

* -------------------------------------------------------------------------------
*
*
* ============================================================================================ */


#if !defined(DTB_PLATFORM_H)

#include <stdio.h>
#include <stdlib.h>

#define NOMINMAX
#define NOCOMM
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef near
#undef far

#include <GL/GL.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")

#if !defined(__cplusplus)
typedef char bool;
#define true 1
#define false 0
#define NULL 0
#endif

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef enum
{
	dtb_key_invalid,
	dtb_key_mb_left,
	dtb_key_mb_right,
	dtb_key_mb_middle,
	dtb_key_mwheel_up,
	dtb_key_mwheel_down,
	dtb_key_mb_0,
	dtb_key_mb_1,
	dtb_key_backspace,
	dtb_key_tab,
	dtb_key_enter,
	dtb_key_pause,
	dtb_key_caps_lock,
	dtb_key_space,
	dtb_key_escape,
	dtb_key_left,
	dtb_key_right,
	dtb_key_up,
	dtb_key_down,
	dtb_key_shift,
	dtb_key_left_shift,
	dtb_key_right_shift,
	dtb_key_ctrl,
	dtb_key_left_ctrl,
	dtb_key_right_ctrl,
	
	dtb_key_a,
	dtb_key_b,
	dtb_key_c,
	dtb_key_d,
	dtb_key_e,
	dtb_key_f,
	dtb_key_g,
	dtb_key_h,
	dtb_key_i,
	dtb_key_j,
	dtb_key_k,
	dtb_key_l,
	dtb_key_m,
	dtb_key_n,
	dtb_key_o,
	dtb_key_p,
	dtb_key_q,
	dtb_key_r,
	dtb_key_s,
	dtb_key_t,
	dtb_key_u,
	dtb_key_v,
	dtb_key_w,
	dtb_key_x,
	dtb_key_y,
	dtb_key_z,
	
	dtb_key_0,
	dtb_key_1,
	dtb_key_2,
	dtb_key_3,
	dtb_key_4,
	dtb_key_5,
	dtb_key_6,
	dtb_key_7,
	dtb_key_8,
	dtb_key_9,
	
	dtb_key_F1,
	dtb_key_F2,
	dtb_key_F3,
	dtb_key_F4,
	dtb_key_F5,
	dtb_key_F6,
	dtb_key_F7,
	dtb_key_F8,
	dtb_key_F9,
	dtb_key_F10,
	dtb_key_F11,
	dtb_key_F12,
	dtb_key_F13,
	dtb_key_F14,
	dtb_key_F15,
	dtb_key_F16,
	dtb_key_F17,
	dtb_key_F18,
	dtb_key_F19,
	dtb_key_F20,
	dtb_key_F21,
	dtb_key_F22,
}dtb_key;

typedef enum
{
	dtb_system_event_type_note,
	dtb_system_event_type_key,
	dtb_system_event_type_char,
	dtb_system_event_type_mouse_move,
	dtb_system_event_type_max,
}dtb_system_event_type;

typedef struct
{
	u32 u32_value;
	int i32_value;
	float r32_value;
}dtb_system_event_data;

typedef enum
{
	dtb_key_state_key_down = 1,
	dtb_key_state_alt_key = 2,
	dtb_key_state_ctrl_key = 4,
	dtb_key_state_shift_key = 8,
	dtb_key_state_caps_key = 16,
	dtb_key_state_number_key = 32,
}dtb_key_state;

typedef struct
{
	u32 time;
	dtb_system_event_type type;
	dtb_system_event_data data[4];
	u32 ptr_size;
	unsigned char* ptr_data;	
}dtb_system_event;

#define DTB_MAX_QUEUED_EVENTS 256 //default buffer size
#define DTB_MAX_QUEUED_EVENT_MASK DTB_MAX_QUEUED_EVENTS - 1 //Padding

typedef struct
{
	int number_events;
	dtb_system_event event_queue[DTB_MAX_QUEUED_EVENTS];
	
	int window_width;
	int window_height;
	char* window_title;
	bool running;
	int cursorX;
	int cursorY;
}dtb_platform;

typedef struct
{
	POINT p;
	HWND window;
	HDC dc;
	MSG msg;
}dtb_win32;

dtb_platform platform = {0};
dtb_win32 win32_platform = {0};

void dtb_platform_log_error(char* msg, ...)
{
	const size_t BUFFER_SIZE = 16384;
	char buffer[BUFFER_SIZE];
	va_list args;
	va_start(args, msg);
	vsprintf_s(buffer, BUFFER_SIZE, msg, args);
	printf("ERROR: %s \n", buffer);
	va_end(args);
}

dtb_system_event *dtb_queue_event(dtb_system_event_type type)
{
	dtb_system_event *ev = platform.event_queue + (platform.number_events & DTB_MAX_QUEUED_EVENT_MASK);
	
	if(platform.number_events < DTB_MAX_QUEUED_EVENTS - 1)
	{
		++platform.number_events;
	}
	else
	{
		dtb_platform_log_error("SysEvent Queue overflow");
	}
	ev->type = type;
	ev->ptr_size = 0;
	ev->ptr_data = 0;
	
	return ev;
}

dtb_key dtb_check_key(dtb_key key)
{
	for(int i = 0; i < platform.number_events; i++)
	{
		if(platform.event_queue[i].type == dtb_system_event_type_key)
		{
			if(platform.event_queue[i].data[0].u32_value == key)
			{
				return (dtb_key)dtb_key_state_key_down;
			}
		}
	}
	
	return dtb_key_invalid;
}

#define VK_MWHEEL_UP      0x86
#define VK_MWHEEL_DOWN	  0x87

dtb_key dtb_win32_map_key(int key)
{
	dtb_key result = dtb_key_invalid;
	
	switch(key)
	{
		case VK_LBUTTON:				//0x01
		return dtb_key_mb_left;
		case VK_RBUTTON:				//0x02
		return dtb_key_mb_right;
		case VK_MBUTTON:
		return dtb_key_mb_middle;
		case VK_MWHEEL_UP:
		return dtb_key_mwheel_up;
		case VK_MWHEEL_DOWN:
		return dtb_key_mwheel_down;
		case VK_XBUTTON1:
		return dtb_key_mb_0;
		case VK_XBUTTON2:
		return dtb_key_mb_1;
		case VK_BACK:
		return dtb_key_backspace;
		case VK_TAB:
		return dtb_key_tab;
		case VK_RETURN:
		return dtb_key_enter;
		case VK_SHIFT:
		return dtb_key_shift;
		case VK_CONTROL:
		return dtb_key_ctrl;
		case VK_PAUSE:
		return dtb_key_pause;
		case VK_CAPITAL:
		return dtb_key_caps_lock;
		case VK_SPACE:
		return dtb_key_space;
		case VK_ESCAPE:
		return dtb_key_escape;
		case VK_LEFT:
		return dtb_key_left;
		case VK_RIGHT:
		return dtb_key_right;
		case VK_DOWN:
		return dtb_key_down;
		case VK_UP:
		return dtb_key_up;
		case VK_LSHIFT:
		return dtb_key_left_shift;
		case VK_RSHIFT:
		return dtb_key_right_shift;
		case VK_LCONTROL:
		return dtb_key_left_ctrl;
		case VK_RCONTROL:
		return dtb_key_right_ctrl;
		case 0x30:
		return dtb_key_0;
		case 0x31:
		return dtb_key_1;
		case 0x32:
		return dtb_key_2;
		case 0x33:
		return dtb_key_3;
		case 0x34:
		return dtb_key_4;
		case 0x35:
		return dtb_key_5;
		case 0x36:
		return dtb_key_6;
		case 0x37:
		return dtb_key_7;
		case 0x38:
		return dtb_key_8;
		case 0x39:
		return dtb_key_9;
		
		case 0x41:
		return dtb_key_a;
		case 0x42:
		return dtb_key_b;
		case 0x43:
		return dtb_key_c;
		case 0x44:
		return dtb_key_d;
		case 0x45:
		return dtb_key_e;
		case 0x46:
		return dtb_key_f;
		case 0x47:
		return dtb_key_g;
		case 0x48:
		return dtb_key_h;
		case 0x49:
		return dtb_key_i;
		case 0x4A:
		return dtb_key_j;
		case 0x4B:
		return dtb_key_k;
		case 0x4C:
		return dtb_key_l;
		case 0x4D:
		return dtb_key_m;
		case 0x4E:
		return dtb_key_n;
		case 0x4F:
		return dtb_key_o;
		case 0x50:
		return dtb_key_p;
		case 0x51:
		return dtb_key_q;
		case 0x52:
		return dtb_key_r;
		case 0x53:
		return dtb_key_s;
		case 0x54:
		return dtb_key_t;
		case 0x55:
		return dtb_key_u;
		case 0x56:
		return dtb_key_v;
		case 0x57:
		return dtb_key_w;
		case 0x58:
		return dtb_key_x;
		case 0x59:
		return dtb_key_y;
		case 0x5A:
		return dtb_key_z;
		
		case VK_F1:
		return dtb_key_F1;
		case VK_F2:
		return dtb_key_F2;
		case VK_F3:
		return dtb_key_F3;
		case VK_F4:
		return dtb_key_F4;
		case VK_F5:
		return dtb_key_F5;
		case VK_F6:
		return dtb_key_F6;
		case VK_F7:
		return dtb_key_F7;
		case VK_F8:
		return dtb_key_F8;
		case VK_F9:
		return dtb_key_F9;
		case VK_F10:
		return dtb_key_F10;
		case VK_F11:
		return dtb_key_F11;
		case VK_F12:
		return dtb_key_F12;
		case VK_F13:
		return dtb_key_F13;
		case VK_F14:
		return dtb_key_F14;
		case VK_F15:
		return dtb_key_F15;
		case VK_F16:
		return dtb_key_F16;
		case VK_F17:
		return dtb_key_F17;
		case VK_F18:
		return dtb_key_F18;
		case VK_F19:
		return dtb_key_F19;
		case VK_F20:
		return dtb_key_F20;
		case VK_F21:
		return dtb_key_F21;
		case VK_F22:
		return dtb_key_F22;
		default:
		return result;
	}
}

LRESULT CALLBACK win32_procedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
	HGLRC gl_context = NULL;
	
	switch(message)
	{	
		case WM_CREATE:
		{
			HDC device_context = GetDC(window);
			PIXELFORMATDESCRIPTOR pfd = { 0 };
			pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
			pfd.nVersion = 1;
			pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
			pfd.iPixelType = PFD_TYPE_RGBA;
			pfd.cColorBits = 32;
			pfd.cAlphaBits = 8;
			pfd.iLayerType = PFD_MAIN_PLANE;
			
			int pf_index = ChoosePixelFormat(device_context, &pfd);
			if(pf_index == 0){
				dtb_platform_log_error("Failed to choose a pixel format");
			}
			
			PIXELFORMATDESCRIPTOR suggested_pfd;
			DescribePixelFormat(device_context, pf_index, sizeof(suggested_pfd), &suggested_pfd);
			
			if(!SetPixelFormat(device_context, pf_index, &pfd))
			{
				dtb_platform_log_error("Failed to Set the pixel format for opengl");
			}
			gl_context = wglCreateContext(device_context);
			if(!wglMakeCurrent(device_context, gl_context))
			{
				dtb_platform_log_error("Failed to make the context for opengl current!");
			}
		}break;
		case WM_MOUSEWHEEL:
		{
			float mwheel_delta = GET_WHEEL_DELTA_WPARAM(wparam);
			
			if(mwheel_delta > 0)
			{
				dtb_system_event *e = dtb_queue_event(dtb_system_event_type_key);
				e->data[0].u32_value = (u32)dtb_win32_map_key(VK_MWHEEL_UP);
			}
			else
			{
				dtb_system_event *e = dtb_queue_event(dtb_system_event_type_key);
				e->data[0].u32_value = (u32)dtb_win32_map_key(VK_MWHEEL_DOWN);
			}
		}break;
		case WM_LBUTTONDOWN:
		{
			dtb_system_event *e = dtb_queue_event(dtb_system_event_type_key);
			e->data[0].u32_value = (u32)dtb_win32_map_key(VK_LBUTTON);
		}break;
		case WM_RBUTTONDOWN:
		{
			dtb_system_event *e = dtb_queue_event(dtb_system_event_type_key);
			e->data[0].u32_value = (u32)dtb_win32_map_key(VK_RBUTTON);
		}break;
		case WM_MBUTTONDOWN:
		{
			dtb_system_event *e = dtb_queue_event(dtb_system_event_type_key);
			e->data[0].u32_value = (u32)dtb_win32_map_key(VK_MBUTTON);
		}break;
		case WM_XBUTTONDOWN:
		{
			int x_button = GET_XBUTTON_WPARAM(wparam);
			
			if(x_button == 0x001)
			{
				dtb_system_event *e = dtb_queue_event(dtb_system_event_type_key);
				e->data[0].u32_value = (u32)dtb_win32_map_key(VK_XBUTTON1);
			}
			
			if(x_button == 0x002)
			{
				dtb_system_event *e = dtb_queue_event(dtb_system_event_type_key);
				e->data[0].u32_value = (u32)dtb_win32_map_key(VK_XBUTTON2);
			}
		}break;
		case WM_KEYUP:
		{
			u32 vk_code = (u32)wparam;
			int was_down = ((lparam & (1 << 30)) != 0);
			int is_down = ((lparam & (1 << 31)) == 0);
			
			int alt_key_down = (lparam & (1 << 29)) != 0;
			int ctrl_key_down = GetKeyState(VK_CONTROL) != 0;
			int shift_key_down = GetKeyState(VK_SHIFT) != 0;
			int caps_lock_key_on = GetKeyState(VK_CAPITAL) != 0;
			int num_lock_key_on = GetKeyState(VK_NUMLOCK) != 0;
			
			if(was_down != is_down)
			{
				
			}
			
			if(is_down)
			{
				if(vk_code == VK_F4 && alt_key_down)
				{
					platform.running = false;
					
				}
			}	
			
			dtb_system_event *e = dtb_queue_event(dtb_system_event_type_key);
			e->data[0].u32_value = (u32)dtb_win32_map_key((int)wparam);
			e->data[1].u32_value = is_down;
			
			if(alt_key_down)
			{
				e->data[1].u32_value |= dtb_key_state_alt_key;
			}
			if(ctrl_key_down)
			{
				e->data[1].u32_value |= dtb_key_state_ctrl_key;
			}
			if(shift_key_down)
			{
				e->data[1].u32_value |= dtb_key_state_shift_key;
			}
			if(caps_lock_key_on)
			{
				e->data[1].u32_value |= dtb_key_state_caps_key;
			}
			if(num_lock_key_on)
			{
				e->data[1].u32_value |= dtb_key_state_number_key;
			}
		}break;
		case WM_PAINT:
		{
			PAINTSTRUCT paint;
			HDC deviceContext = BeginPaint(window, &paint);
			EndPaint(window, &paint);
		}break;
		case WM_CHAR:
		{
			dtb_system_event *e = dtb_queue_event(dtb_system_event_type_char);
			e->data[0].u32_value = (u32)wparam;
		}break;
		case WM_CLOSE:
		{
			platform.running = false;
		}break;
		case WM_QUIT:
		{
			platform.running = false;
			wglDeleteContext(gl_context);
		}break;
		case WM_SIZE:
		{
			glViewport(0, 0, LOWORD(lparam), HIWORD(lparam));
			RECT ClientRect;
			GetClientRect(window, &ClientRect);
			int width = ClientRect.right - ClientRect.left;
			int height = ClientRect.bottom - ClientRect.top;
			platform.window_height = height;
			platform.window_width = width;
			
			PostMessage(window, WM_PAINT, 0, 0);
		}break;
		
		default:
		return DefWindowProc(window, message, wparam, lparam);
	}
	
	return DefWindowProc(window, message, wparam, lparam);
}

bool dtb_platform_init(char* title, int width, int height)
{
	platform.window_width = width;
	platform.window_height = height;
	platform.window_title = title;
	
	WNDCLASS wc = {0};
	wc.hInstance = GetModuleHandle(0);
	wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = win32_procedure;
	wc.lpszClassName = platform.window_title;
	RegisterClass(&wc);
	
	win32_platform.window = CreateWindow(wc.lpszClassName, platform.window_title, 
										 WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
										 platform.window_width, platform.window_height,
										 0, 0, wc.hInstance, 0);
	
	if(!win32_platform.window)
	{
		dtb_platform_log_error("Failed to create win32 window");
		return false;
	}
	
	win32_platform.dc = GetDC(win32_platform.window);
	
	ShowWindow(win32_platform.window, SW_SHOW);
	UpdateWindow(win32_platform.window);
	
	platform.cursorX = 0;
	platform.cursorY = 0;
	platform.running = true;
	
	return true;
}

void dtb_platform_update()
{
	win32_platform.dc = GetDC(win32_platform.window);
	platform.number_events = 0;
	if(PeekMessage(&win32_platform.msg, win32_platform.window, 0, 0, PM_REMOVE))
	{
		GetCursorPos(&win32_platform.p);
		ScreenToClient(win32_platform.window, &win32_platform.p);
		platform.cursorX = win32_platform.p.x;
		platform.cursorY = win32_platform.p.y;
		
		TranslateMessage(&win32_platform.msg);
		DispatchMessage(&win32_platform.msg);
	}
	
	SwapBuffers(win32_platform.dc);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


#define DTB_PLATFORM_H
#endif