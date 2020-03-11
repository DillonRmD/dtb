#if !defined(DTB_PLATFOR_H)

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef float r32;
typedef double r64;

#if defined(__cplusplus)
typedef bool b32;
#else
typedef unsigned char b32;
#define true 1
#define false 0
#define NULL 0
#endif

#define DTB_WINDOW_NAME "window"
#define DTB_WINDOW_WIDTH 800
#define DTB_WINDOW_HEIGHT 600

typedef struct 
{
    b32 isRunning;
    
}dtb_platform;

#if defined(_WIN32)
#include <windows.h>

LRESULT CALLBACK win32_callback(HWND window, UINT message, WPARAM wparam, LPARAM lparam){
    return DefWindowProc(window, message, wparam, lparam);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prev_instance, LPSTR command_line, int command_show){
    WNDCLASS wc = {0};
    
    wc.hInstance = instance;
    wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = win32_callback;
    wc.lpszClassName = DTB_WINDOW_NAME;
    
    if(!RegisterClass(&wc)){
        // TODO(Dillon): Error
    }
    
     HWND window = CreateWindowA(wc.lpszClassName, wc.lpszClassName,
                       WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                       CW_USEDEFAULT, CW_USEDEFAULT,
                       DTB_WINDOW_WIDTH, DTB_WINDOW_HEIGHT,
                       0, 0,
                       wc.hInstance,
                       0);
    
    if(!window){
        // TODO(Dillon): Error
    }
    
    ShowWindow(window, SW_SHOW);
    UpdateWindow(window);
    
    dtb_platform platform;
    DTB_INIT();
    
    MSG msg;
    platform.isRunning = true;
    while(platform.isRunning == true){
        while(PeekMessage(&msg, 0, 0, 0, PM_REMOVE)){
            switch(msg.message){
                case WM_CLOSE:{
                    platform.isRunning = false;
                }break;
                default:{
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }break;
            }
        }
        
        
        
        // TODO(Dillon): Actually add delta time to this later
        DTB_LOOP(1.f / 60.f);
    }
    
    return 0;
}
#endif //_WIN32

#define DTB_PLATFORM_H
#endif