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
* The only dependency is OpenGL; OpenGL is forced as the rendering API in dtb_platform. 
* Everything else is hand written by myself or other contributers.
* 
* To Implement in your own code put this in your main source file:
* -------------------------------------------------------------------------------

#define DTB_IMPLEMENT_PLATFORM
#include "dtb_platform.h"

static dtb_platform *gp;

int DTB_INIT(dtb_platform *platform, int argc, char **argv)
{
 gp = platform;
 
 return 0;
}

void DTB_LOOP(float dt)
{

}


* -------------------------------------------------------------------------------
*
*
* To grab key presses do:
* -------------------------------------------------------------------------------

if(dtb_check_key(&platform, dtb_key_space))
{
}

OR

if(dtb_check_key(&platform, dtb_key_space) == dtb_key_state_key_down)
{
}

* -------------------------------------------------------------------------------
*
*
* ============================================================================================ */


#ifndef DTB_PLATFORM_H

#ifdef DTB_IMPLEMENT_PLATFORM

#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
#include <GL/glx.h>
#endif

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef signed char    i8;
typedef signed short   i16;
typedef signed int     i32;

typedef enum
{
    dtb_key_invalid,
    dtb_key_mb_left,
    dtb_key_mb_right,
    dtb_key_mb_middle,
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
    i32 i32_value;
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
}dtb_platform;

//User defines this in main source file
extern int DTB_INIT(dtb_platform *platform, int argc, char **argv);
extern void DTB_LOOP(float dt);

//Defintion of this depends on platform
extern void dtb_platform_log_error(char* msg, ...);

dtb_system_event *dtb_queue_event(dtb_platform *platform, dtb_system_event_type type)
{
    dtb_system_event *ev = platform->event_queue + (platform->number_events & DTB_MAX_QUEUED_EVENT_MASK);
    
    if(platform->number_events < DTB_MAX_QUEUED_EVENTS - 1)
    {
        ++platform->number_events;
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

dtb_key dtb_check_key(dtb_platform* platform, dtb_key key)
{
    for(int i = 0; i < platform->number_events; i++)
    {
        if(platform->event_queue[i].type == dtb_system_event_type_key)
        {
            if(platform->event_queue[i].data[0].u32_value == key)
            {
                return (dtb_key)dtb_key_state_key_down;
            }
        }
    }
    
    return dtb_key_invalid;
}

#ifndef DTB_WINDOW_WIDTH
#define DTB_WINDOW_WIDTH 800
#endif

#ifndef DTB_WINDOW_HEIGHT
#define DTB_WINDOW_HEIGHT 600
#endif

#ifndef DTB_WINDOW_TITLE
#define DTB_WINDOW_TITLE "DTB Window"
#endif

#ifdef __linux__
#include <X11/X.h>
#include <X11/Xlib.h>

uint32_t attributes[] = 
{
    GLX_RGBA,
    GLX_DEPTH_SIZE, 24,
    GLX_DOUBLEBUFFER, None
};

void dtb_platform_log_error(char* msg, ...)
{
    fprintf(stderr, "DTB_ERROR: %s", msg);
    exit(0);
}

typedef struct
{
    Display *display;
    Window window;
    int running;
    XWindowAttributes window_attributes;
}dtb_linux_state;

int main(int argc, char* argv[])
{
    printf("CHECK1\n");
    dtb_platform linux_platform = {0};
    dtb_linux_state state = {0};	
    state.display = XOpenDisplay(0);
    
    printf("CHECK1/2\n");
    if(state.display == 0)
    {
        dtb_log_error("Can't connect to X server\n");
    }
    
    //@TODO: Maybe add this to the structure
    Window root = DefaultRootWindow(state.display); 
    
    XVisualInfo *vi = glXChooseVisual(state.display, 0, attributes);
    if(vi == 0)
    {
        dtb_log_error("No appropriate visual found\n");
    }
    
    Colormap color_map = XCreateColormap(state.display,
                                         root,
                                         vi->visual,
                                         AllocNone);
    
    XSetWindowAttributes window_attributes;
    window_attributes.colormap = color_map;
    window_attributes.event_mask = ExposureMask | KeyPressMask;
    printf("CHECK2\n");
    state.window = XCreateWindow(state.display, root,
                                 0, 0,
                                 DTB_WINDOW_WIDTH, DTB_WINDOW_HEIGHT,
                                 0, vi->depth, InputOutput,
                                 vi->visual, CWColormap | CWEventMask,
                                 &window_attributes);
    
    XMapWindow(state.display, state.window);
    
    XStoreName(state.display, state.window, DTB_WINDOW_TITLE);
    
    GLXContext context = glXCreateContext(state.display, vi, 0, GL_TRUE);
    glXMakeCurrent(state.display, state.window, context);
    
    printf("CHECK3\n");
    if(glewInit() != GLEW_OK)
    {
        dtb_log_error("Failed to init GLEW\n");
    }
    
    glEnable(GL_DEPTH_TEST);
    
    DTB_INIT(&linux_platform, argc, argv);
    
    XEvent event;
    state.running = 1;
    while(state.running == 1)
    {
        XNextEvent(state.display, &event);
        XGetWindowAttributes(state.display, state.window, &state.window_attributes);
        glViewport(0, 0, state.window_attributes.width, state.window_attributes.height);
        
        if(event.type == KeyPress)
        {
            if(event.xkey.keycode == 0x09)
                exit(0);
        }
        
        DTB_LOOP(1.f/60.f);
        glXSwapBuffers(state.display, state.window);
    }
    
    
    return 0;
}


#endif

#ifndef DTB_WIN32_DEFINED
#if defined _WIN32

#define NOMINMAX
#define NOCOMM
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef near
#undef far

#define DTB_WIN32_DEFINED
#endif
#endif

#include <GL/GL.h>

#ifdef DTB_ENABLE_GLEW
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glew32s.lib")
#endif

#pragma comment(lib, "opengl32.lib")

#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")

typedef struct
{
    HWND window;
    int running;
    HGLRC gl_context;
}dtb_win32_state;

void dtb_platform_log_error(char* msg, ...)
{
    const size_t BUFFER_SIZE = 16384;
    char buffer[BUFFER_SIZE];
    va_list args;
    va_start(args, msg);
    vsprintf_s(buffer, BUFFER_SIZE, msg, args);
    printf("ERROR: %s \n", buffer);
    OutputDebugString("ERROR: ");
    OutputDebugString(buffer);
    OutputDebugString("\n");
    va_end(args);
}

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

#ifndef DTB_NO_WIN32_COMMAND_PROMPT
//Main Entry point in win32 for command prompt
int main(int argc, char* argv[])
{
    WinMain(GetModuleHandle(0), 0, 0, SW_SHOW);
    
    return 0;
}
#endif


dtb_win32_state win32_state = {0};
dtb_platform win32_platform = {0};

LRESULT CALLBACK win32_procedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
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
            win32_state.gl_context = wglCreateContext(device_context);
            if(!wglMakeCurrent(device_context, win32_state.gl_context))
            {
                dtb_platform_log_error("Failed to make the context for opengl current!");
            }
            
#ifdef DTB_ENABLE_GLEW
            GLenum gl_res = glewInit();
            if(gl_res != GLEW_OK)
            {
                dtb_platform_log_error("Failed to init GLEW correctly");
            }
#endif
            win32_platform.window_title = DTB_WINDOW_TITLE;
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
                    win32_state.running = 0;
                    
                }
            }	
            
            dtb_system_event *e = dtb_queue_event(&win32_platform, dtb_system_event_type_key);
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
            dtb_system_event *e = dtb_queue_event(&win32_platform, dtb_system_event_type_char);
            e->data[0].u32_value = (u32)wparam;
        }break;
        case WM_CLOSE:
        {
            win32_state.running = -1;
        }break;
        case WM_QUIT:
        {
            win32_state.running = -1;
            wglDeleteContext(win32_state.gl_context);
        }break;
        case WM_SIZE:
        {
            glViewport(0, 0, LOWORD(lparam), HIWORD(lparam));
            RECT ClientRect;
            GetClientRect(window, &ClientRect);
            int width = ClientRect.right - ClientRect.left;
            int height = ClientRect.bottom - ClientRect.top;
            win32_platform.window_height = height;
            win32_platform.window_width = width;
            
            PostMessage(window, WM_PAINT, 0, 0);
        }break;
        
        default:
        return DefWindowProc(window, message, wparam, lparam);
    }
    
    return DefWindowProc(window, message, wparam, lparam);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prev_instance, LPSTR command_line, int command_show)
{
    WNDCLASS wc = {0};
    wc.hInstance = instance;
    wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = win32_procedure;
    wc.lpszClassName = DTB_WINDOW_TITLE;
    RegisterClass(&wc);
    
    win32_state.window = CreateWindow(wc.lpszClassName, DTB_WINDOW_TITLE, 
                                      WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                                      DTB_WINDOW_WIDTH, DTB_WINDOW_HEIGHT,
                                      0, 0, wc.hInstance, 0);
    if(!win32_state.window)
    {
        dtb_platform_log_error("Failed to create win32 window");
        return -1;
    }
    
    HDC dc = GetDC(win32_state.window);
    
    ShowWindow(win32_state.window, SW_SHOW);
    UpdateWindow(win32_state.window);
    
    DTB_INIT(&win32_platform, 1, &command_line);
    
    MSG msg;
    win32_state.running = 1;
    while(win32_state.running == 1)
    {
        win32_platform.number_events = 0;
        if(PeekMessage(&msg, win32_state.window, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        
        SwapBuffers(dc);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        DTB_LOOP(1.f/60.f);
    }
    
    return 0;
}

#endif //DTB_IMPLEMENT_PLATFORM

#define DTB_PLATFORM_H
#endif