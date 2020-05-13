/*  ============================================================================================
*  PROJECT:  Dillon's Tool Box Platform Edition
*  AUTHOR:   Dillon Williams
*  LICENSE:  Do What The Fuck Ever license
*  LANGUAGE: C\C++
*
*  INFORMATION:
*  Include this file into your main compilation unit and follow the example as follows:
  *
*  Example on how to implement:
*  ===========================================================================================
*  #include "dtb_platform.h"
*  u32 DTB_INIT(dtbPlatform* platform)
*  {
*      return 0;
*  }
*
*  void DTB_LOOP(dtbPlatform* platform, float deltaTime)
*  {
*  }
*  ===========================================================================================
*
*  This is developed in my free time, constant and consistent updates should not be expected.
*  Feel free to modify this code to your preference.
*
*  ============================================================================================
*/

#if !defined(DTB_PLATFOR_H)

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

#if defined(__cplusplus)
typedef bool b32;
#else
typedef unsigned int b32;
#define true 1
#define false 0
#define NULL 0
#endif

#define DTB_WINDOW_NAME "window"
#define DTB_WINDOW_WIDTH 800
#define DTB_WINDOW_HEIGHT 600

typedef enum
{
    DTB_KEY_A,
    DTB_KEY_B,
    DTB_KEY_C,
    DTB_KEY_D,
    DTB_KEY_E,
    DTB_KEY_F,
    DTB_KEY_G,
    DTB_KEY_H,
    DTB_KEY_I,
    DTB_KEY_J,
    DTB_KEY_K,
    DTB_KEY_L,
    DTB_KEY_M,
    DTB_KEY_N,
    DTB_KEY_O,
    DTB_KEY_P,
    DTB_KEY_Q,
    DTB_KEY_R,
    DTB_KEY_S,
    DTB_KEY_T,
    DTB_KEY_U,
    DTB_KEY_V,
    DTB_KEY_W,
    DTB_KEY_X,
    DTB_KEY_Y,
    DTB_KEY_Z,
    
    DTB_KEY_SPACE,
    
    DTB_KEY_TAB,
    
    DTB_KEY_CAPS_LOCK,
    
    DTB_KEY_LEFT_SHIFT,
    DTB_KEY_RIGHT_SHIFT,
    
    DTB_KEY_LEFT_CTRL,
    DTB_KEY_RIGHT_CTRL,
    
    DTB_KEY_ALT,
    
    DTB_KEY_LEFT_ARROW,
    DTB_KEY_RIGHT_ARROW,
    DTB_KEY_UP_ARROW,
    DTB_KEY_DOWN_ARROW,
    
    DTB_KEY_HOME,
    DTB_KEY_INSERT,
    DTB_KEY_DELETE,
    DTB_KEY_PAGE_UP,
    DTB_KEY_PAGE_DOWN,
    
    DTB_KEY_ESCAPE,
    
    DTB_KEY_BACKSPACE,
    
    DTB_KEY_1,
    DTB_KEY_2,
    DTB_KEY_3,
    DTB_KEY_4,
    DTB_KEY_5,
    DTB_KEY_6,
    DTB_KEY_7,
    DTB_KEY_8,
    DTB_KEY_9,
    DTB_KEY_0,
    
    DTB_KEY_F1,
    DTB_KEY_F2,
    DTB_KEY_F3,
    DTB_KEY_F4,
    DTB_KEY_F5,
    DTB_KEY_F6,
    DTB_KEY_F7,
    DTB_KEY_F8,
    DTB_KEY_F9,
    DTB_KEY_F10,
    DTB_KEY_F11,
    DTB_KEY_F12,
    
    DTB_MOUSE_ONE,
    DTB_MOUSE_TWO,
    
    DTB_MOUSE_SCROLL_UP,
    DTB_MOUSE_SCROLL_DOWN,
    
    DTB_KEY_MAX,
    
}dtb_key_type;

// TODO(Dillon): I don't like having this many structures clogging up the code base
// Maybe look into changing this at a later point, when performance is a bigger issue
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

typedef struct
{
    dtb_key_type type;
    b32 isDown;
    b32 isChanged;
}dtb_key;

typedef struct
{
    dtb_key keys[DTB_KEY_MAX];
    u32 mousePositionX;
    u32 mousePositionY;
}dtb_input;

typedef struct
{
    b32 isRunning;
    int windowWidth;
    int windowHeight;
    dtb_input input;
#ifdef _WIN32
	HWND win32WindowHandle;
	HDC win32DeviceContext;
	UINT win32Message;
	WPARAM win32WParam;
	LPARAM win32LParam;
#endif
}dtbPlatform;

// NOTE(Dillon): User has to define this in main compilation unit
u32 DTB_INIT(dtbPlatform* platform);
void DTB_LOOP(dtbPlatform* platform, float deltaTime);

// TODO(Dillon): Get rid of this, this is terrible, win32 sucks
b32 globalRunning;

// TODO(Dillon): Maybe rename this function later
b32 dtbIsKeyDown(dtbPlatform platform, dtb_key_type type)
{
    return platform.input.keys[type].isDown && platform.input.keys[type].isChanged;
}

#if defined(_WIN32)
#if defined(DTB_PLATFORM_OPENGL)
#include <gl\gl.h>
#include <gl\glu.h>
#pragma comment(lib, "opengl32.lib")
#endif

void win32TranslateVKcodes(dtbPlatform* platform, u32 vkCode)
{
    switch(vkCode)
    {
        // NOTE(Dillon): Function keys
        case VK_F1:
        {
            platform->input.keys[DTB_KEY_F1].isDown = true;
            platform->input.keys[DTB_KEY_F1].isChanged = true;
        }break;
        case VK_F2:
        {
            platform->input.keys[DTB_KEY_F2].isDown = true;
            platform->input.keys[DTB_KEY_F2].isChanged = true;
        }break;
        case VK_F3:
        {
            platform->input.keys[DTB_KEY_F3].isDown = true;
            platform->input.keys[DTB_KEY_F3].isChanged = true;
        }break;
        case VK_F4:
        {
            platform->input.keys[DTB_KEY_F4].isDown = true;
            platform->input.keys[DTB_KEY_F4].isChanged = true;
        }break;
        case VK_F5:
        {
            platform->input.keys[DTB_KEY_F5].isDown = true;
            platform->input.keys[DTB_KEY_F5].isChanged = true;
        }break;
        case VK_F6:
        {
            platform->input.keys[DTB_KEY_F6].isDown = true;
            platform->input.keys[DTB_KEY_F6].isChanged = true;
        }break;
        case VK_F7:
        {
            platform->input.keys[DTB_KEY_F7].isDown = true;
            platform->input.keys[DTB_KEY_F7].isChanged = true;
        }break;
        case VK_F8:
        {
            platform->input.keys[DTB_KEY_F8].isDown = true;
            platform->input.keys[DTB_KEY_F8].isChanged = true;
        }break;
        case VK_F9:
        {
            platform->input.keys[DTB_KEY_F9].isDown = true;
            platform->input.keys[DTB_KEY_F9].isChanged = true;
        }break;
        case VK_F10:
        {
            platform->input.keys[DTB_KEY_F10].isDown = true;
            platform->input.keys[DTB_KEY_F10].isChanged = true;
        }break;
        case VK_F11:
        {
            platform->input.keys[DTB_KEY_F11].isDown = true;
            platform->input.keys[DTB_KEY_F11].isChanged = true;
        }break;
        case VK_F12:
        {
            platform->input.keys[DTB_KEY_F12].isDown = true;
            platform->input.keys[DTB_KEY_F12].isChanged = true;
        }break;
        
        // NOTE(Dillon): Number keys
        case 0x30:
        {
            platform->input.keys[DTB_KEY_0].isDown = true;
            platform->input.keys[DTB_KEY_0].isChanged = true;
        }break;
        case 0x31:
        {
            platform->input.keys[DTB_KEY_1].isDown = true;
            platform->input.keys[DTB_KEY_1].isChanged = true;
        }break;
        case 0x32:
        {
            platform->input.keys[DTB_KEY_2].isDown = true;
            platform->input.keys[DTB_KEY_2].isChanged = true;
        }break;
        case 0x33:
        {
            platform->input.keys[DTB_KEY_3].isDown = true;
            platform->input.keys[DTB_KEY_3].isChanged = true;
        }break;
        case 0x34:
        {
            platform->input.keys[DTB_KEY_4].isDown = true;
            platform->input.keys[DTB_KEY_4].isChanged = true;
        }break;
        case 0x35:
        {
            platform->input.keys[DTB_KEY_5].isDown = true;
            platform->input.keys[DTB_KEY_5].isChanged = true;
        }break;
        case 0x36:
        {
            platform->input.keys[DTB_KEY_6].isDown = true;
            platform->input.keys[DTB_KEY_6].isChanged = true;
        }break;
        case 0x37:
        {
            platform->input.keys[DTB_KEY_7].isDown = true;
            platform->input.keys[DTB_KEY_7].isChanged = true;
        }break;
        case 0x38:
        {
            platform->input.keys[DTB_KEY_8].isDown = true;
            platform->input.keys[DTB_KEY_8].isChanged = true;
        }break;
        case 0x39:
        {
            platform->input.keys[DTB_KEY_9].isDown = true;
            platform->input.keys[DTB_KEY_9].isChanged = true;
        }break;
        
        // NOTE(Dillon): Special keys
        case VK_SPACE:
        {
            platform->input.keys[DTB_KEY_SPACE].isDown = true;
            platform->input.keys[DTB_KEY_SPACE].isChanged = true;
        }break;
        case VK_TAB:
        {
            platform->input.keys[DTB_KEY_TAB].isDown = true;
            platform->input.keys[DTB_KEY_TAB].isChanged = true;
        }break;
        case VK_CAPITAL:
        {
            platform->input.keys[DTB_KEY_CAPS_LOCK].isDown = true;
            platform->input.keys[DTB_KEY_CAPS_LOCK].isChanged = true;
        }break;
        case VK_LSHIFT:
        {
            platform->input.keys[DTB_KEY_LEFT_SHIFT].isDown = true;
            platform->input.keys[DTB_KEY_LEFT_SHIFT].isChanged = true;
        }break;
        case VK_RSHIFT:
        {
            platform->input.keys[DTB_KEY_RIGHT_SHIFT].isDown = true;
            platform->input.keys[DTB_KEY_RIGHT_SHIFT].isChanged = true;
        }break;
        case VK_LCONTROL:
        {
            platform->input.keys[DTB_KEY_LEFT_CTRL].isDown = true;
            platform->input.keys[DTB_KEY_LEFT_CTRL].isChanged = true;
        }break;
        case VK_RCONTROL:
        {
            platform->input.keys[DTB_KEY_RIGHT_CTRL].isDown = true;
            platform->input.keys[DTB_KEY_RIGHT_CTRL].isChanged = true;
        }break;
        case 0x12:
        {
            platform->input.keys[DTB_KEY_ALT].isDown = true;
            platform->input.keys[DTB_KEY_ALT].isChanged = true;
        }break;
        case VK_LEFT:
        {
            platform->input.keys[DTB_KEY_LEFT_ARROW].isDown = true;
            platform->input.keys[DTB_KEY_LEFT_ARROW].isChanged = true;
        }break;
        case VK_RIGHT:
        {
            platform->input.keys[DTB_KEY_RIGHT_ARROW].isDown = true;
            platform->input.keys[DTB_KEY_RIGHT_ARROW].isChanged = true;
        }break;
        case VK_UP:
        {
            platform->input.keys[DTB_KEY_UP_ARROW].isDown = true;
            platform->input.keys[DTB_KEY_UP_ARROW].isChanged = true;
        }break;
        case VK_DOWN:
        {
            platform->input.keys[DTB_KEY_DOWN_ARROW].isDown = true;
            platform->input.keys[DTB_KEY_DOWN_ARROW].isChanged = true;
        }break;
        case VK_HOME:
        {
            platform->input.keys[DTB_KEY_HOME].isDown = true;
            platform->input.keys[DTB_KEY_HOME].isChanged = true;
        }break;
        case VK_INSERT:
        {
            platform->input.keys[DTB_KEY_INSERT].isDown = true;
            platform->input.keys[DTB_KEY_INSERT].isChanged = true;
        }break;
        case VK_DELETE:
        {
            platform->input.keys[DTB_KEY_DELETE].isDown = true;
            platform->input.keys[DTB_KEY_DELETE].isChanged = true;
        }break;
        case VK_PRIOR:
        {
            platform->input.keys[DTB_KEY_PAGE_UP].isDown = true;
            platform->input.keys[DTB_KEY_PAGE_UP].isChanged = true;
        }break;
        case VK_NEXT:
        {
            platform->input.keys[DTB_KEY_PAGE_DOWN].isDown = true;
            platform->input.keys[DTB_KEY_PAGE_DOWN].isChanged = true;
        }break;
        case VK_ESCAPE:
        {
            platform->input.keys[DTB_KEY_ESCAPE].isDown = true;
            platform->input.keys[DTB_KEY_ESCAPE].isChanged = true;
        }break;
        case VK_BACK:
        {
            platform->input.keys[DTB_KEY_BACKSPACE].isDown = true;
            platform->input.keys[DTB_KEY_BACKSPACE].isChanged = true;
        }break;
        
        // NOTE(Dillon): Alphabet
        case 0x41:
        {
            platform->input.keys[DTB_KEY_A].isDown = true;
            platform->input.keys[DTB_KEY_A].isChanged = true;
        }break;
        case 0x42:
        {
            platform->input.keys[DTB_KEY_B].isDown = true;
            platform->input.keys[DTB_KEY_B].isChanged = true;
        }break;
        case 0x43:
        {
            platform->input.keys[DTB_KEY_C].isDown = true;
            platform->input.keys[DTB_KEY_C].isChanged = true;
        }break;
        case 0x44:
        {
            platform->input.keys[DTB_KEY_D].isDown = true;
            platform->input.keys[DTB_KEY_D].isChanged = true;
        }break;
        case 0x45:
        {
            platform->input.keys[DTB_KEY_E].isDown = true;
            platform->input.keys[DTB_KEY_E].isChanged = true;
        }break;
        case 0x46:
        {
            platform->input.keys[DTB_KEY_F].isDown = true;
            platform->input.keys[DTB_KEY_F].isChanged = true;
        }break;
        case 0x47:
        {
            platform->input.keys[DTB_KEY_G].isDown = true;
            platform->input.keys[DTB_KEY_G].isChanged = true;
        }break;
        case 0x48:
        {
            platform->input.keys[DTB_KEY_H].isDown = true;
            platform->input.keys[DTB_KEY_H].isChanged = true;
        }break;
        case 0x49:
        {
            platform->input.keys[DTB_KEY_I].isDown = true;
            platform->input.keys[DTB_KEY_I].isChanged = true;
        }break;
        case 0x4A:
        {
            platform->input.keys[DTB_KEY_J].isDown = true;
            platform->input.keys[DTB_KEY_J].isChanged = true;
        }break;
        case 0x4B:
        {
            platform->input.keys[DTB_KEY_K].isDown = true;
            platform->input.keys[DTB_KEY_K].isChanged = true;
        }break;
        case 0x4C:
        {
            platform->input.keys[DTB_KEY_L].isDown = true;
            platform->input.keys[DTB_KEY_L].isChanged = true;
        }break;
        case 0x4D:
        {
            platform->input.keys[DTB_KEY_M].isDown = true;
            platform->input.keys[DTB_KEY_M].isChanged = true;
        }break;
        case 0x4E:
        {
            platform->input.keys[DTB_KEY_N].isDown = true;
            platform->input.keys[DTB_KEY_N].isChanged = true;
        }break;
        case 0x4F:
        {
            platform->input.keys[DTB_KEY_O].isDown = true;
            platform->input.keys[DTB_KEY_O].isChanged = true;
        }break;
        case 0x50:
        {
            platform->input.keys[DTB_KEY_P].isDown = true;
            platform->input.keys[DTB_KEY_P].isChanged = true;
        }break;
        case 0x51:
        {
            platform->input.keys[DTB_KEY_Q].isDown = true;
            platform->input.keys[DTB_KEY_Q].isChanged = true;
        }break;
        case 0x52:
        {
            platform->input.keys[DTB_KEY_R].isDown = true;
            platform->input.keys[DTB_KEY_R].isChanged = true;
        }break;
        case 0x53:
        {
            platform->input.keys[DTB_KEY_S].isDown = true;
            platform->input.keys[DTB_KEY_S].isChanged = true;
        }break;
        case 0x54:
        {
            platform->input.keys[DTB_KEY_T].isDown = true;
            platform->input.keys[DTB_KEY_T].isChanged = true;
        }break;
        case 0x55:
        {
            platform->input.keys[DTB_KEY_U].isDown = true;
            platform->input.keys[DTB_KEY_U].isChanged = true;
        }break;
        case 0x56:
        {
            platform->input.keys[DTB_KEY_V].isDown = true;
            platform->input.keys[DTB_KEY_V].isChanged = true;
        }break;
        case 0x57:
        {
            platform->input.keys[DTB_KEY_W].isDown = true;
            platform->input.keys[DTB_KEY_W].isChanged = true;
        }break;
        case 0x58:
        {
            platform->input.keys[DTB_KEY_X].isDown = true;
            platform->input.keys[DTB_KEY_X].isChanged = true;
        }break;
        case 0x59:
        {
            platform->input.keys[DTB_KEY_Y].isDown = true;
            platform->input.keys[DTB_KEY_Y].isChanged = true;
        }break;
        case 0x5A:
        {
            platform->input.keys[DTB_KEY_Z].isDown = true;
            platform->input.keys[DTB_KEY_Z].isChanged = true;
        }break;
        
        default:
        {
        }break;
    }
}

#ifdef DTB_PLATFORM_SHOW_CONSOLE
int main(int argc, char* argv[])
{
    WinMain(GetModuleHandle(0),0, *argv, SW_SHOW);
    return 0;
}

#endif

LRESULT CALLBACK win32Callback(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    if(message == WM_CLOSE)
    {
        globalRunning = false;
    }
    
    return DefWindowProc(window, message, wparam, lparam);
}

int WINAPI
WinMain(HINSTANCE instance, HINSTANCE prev_instance, LPSTR command_line, int command_show)
{
    
    WNDCLASS wc = {0};
    
    wc.hInstance = instance;
    wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = win32Callback;
    wc.lpszClassName = DTB_WINDOW_NAME;
    
    if(!RegisterClass(&wc))
    {
        // TODO(Dillon): Error
    }
    dtbPlatform platform;
    platform.win32WindowHandle = CreateWindowA(wc.lpszClassName, wc.lpszClassName,
                                WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                CW_USEDEFAULT, CW_USEDEFAULT,
                                DTB_WINDOW_WIDTH, DTB_WINDOW_HEIGHT,
                                0, 0,
                                wc.hInstance,
                                0);
    
    if(!platform.win32WindowHandle)
    {
        // TODO(Dillon): Error
    }
    
    ShowWindow(platform.win32WindowHandle, SW_SHOW);
    UpdateWindow(platform.win32WindowHandle);
    
    platform.win32DeviceContext = GetDC(platform.win32WindowHandle);
#if defined(DTB_PLATFORM_OPENGL)
    HGLRC glContext;
    PIXELFORMATDESCRIPTOR pfd = { 0 };
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cAlphaBits = 8;
    pfd.iLayerType = PFD_MAIN_PLANE;
    
    int pfIndex = ChoosePixelFormat(platform.win32DeviceContext, &pfd);
    if (pfIndex == 0){
        int x = 10;
    }
    
    PIXELFORMATDESCRIPTOR suggestedPfd;
    DescribePixelFormat(platform.win32DeviceContext, pfIndex, sizeof(suggestedPfd), &suggestedPfd);
    
    if (!SetPixelFormat(platform.win32DeviceContext, pfIndex, &pfd)){
        int x = 10;
    }
    
    glContext = wglCreateContext(platform.win32DeviceContext);
    if (!wglMakeCurrent(platform.win32DeviceContext, glContext)){
        int x = 10;
    }
    
#endif
    

    DTB_INIT(&platform);
    
    MSG msg;
    globalRunning = true;
    platform.isRunning = globalRunning;
    while(platform.isRunning)
    {
        INT64 countsPerSec = 0;
        QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
        
        float secPerCount = 1.0f / (float)countsPerSec;
        
        INT64 prevTime = 0;
        QueryPerformanceCounter((LARGE_INTEGER*)&prevTime);
        
        // NOTE(Dillon): Clear input at the start of each frame
        for(int i = 0; i < DTB_KEY_MAX; i++)
        {
            platform.input.keys[i].isDown = false;
            platform.input.keys[i].isChanged = false;
        }
        
        while(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            if(msg.message == WM_LBUTTONUP)
            {
                platform.input.keys[DTB_MOUSE_ONE].isDown = true;
                platform.input.keys[DTB_MOUSE_ONE].isChanged = true;
            }
            if(msg.message == WM_RBUTTONUP)
            {
                platform.input.keys[DTB_MOUSE_TWO].isDown = true;
                platform.input.keys[DTB_MOUSE_TWO].isChanged = true;
            }
            
            if(msg.message == WM_KEYUP)
            {
                u32 vkCode = msg.wParam;
                win32TranslateVKcodes(&platform, vkCode);
            }
            
            TranslateMessage(&msg);
            DispatchMessage(&msg);

			platform.win32Message = msg.message;
			platform.win32LParam = msg.lParam;
			platform.win32WParam = msg.wParam;
        }
        
        POINT p;
        if(GetCursorPos(&p))
        {
            if(ScreenToClient(platform.win32WindowHandle, &p))
            {
                platform.input.mousePositionX = p.x;
                platform.input.mousePositionY = p.y;
            }
        }
        
        if(globalRunning == false)
        {
            platform.isRunning = false;
        }
        
        
        INT64 currentTime = 0;
        QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
        float deltaTime = (currentTime - prevTime) * secPerCount;
        
        platform.win32DeviceContext = GetDC(platform.win32WindowHandle);
        
        DTB_LOOP(&platform, deltaTime);
        
        SwapBuffers(platform.win32DeviceContext);
    }
    
    return 0;
}
#endif //_WIN32

#define DTB_PLATFORM_H
#endif