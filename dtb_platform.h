/*  ============================================================================================
*  PROJECT:  Dillon's Tool Box Platform
*  AUTHOR:   Dillon Williams
*  LICENSE:  GPLv3
*  LANGUAGE: C\C++
*
*  INFORMATION:
*  Include this file into your main compilation unit and follow the example as follows:
*
*  Example on how to implement:
*  ===========================================================================================
*  #include "dtb_platform.h"
*
*  unsigned int dtb_init(dtb_platform* platform)
*  {
*      return 0;
*  }
*
*  void dtb_loop(dtb_platform* platform, float delta_time)
*  {
*  }
*  ===========================================================================================
*
*  This is developed in my free time, constant and consistent updates should not be expected.
*  Feel free to modify this code to your preference as all code in this header file falls
*  under the GLPv3 license. I all I, personally, ask is to please give me credit if you use
*  this library in your code bases.
*
*  ============================================================================================
*/

#if !defined(DTB_PLATFORM_H)

#if !defined(__cplusplus)
typedef unsigned int bool;
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
#include <windows.h>

#include <gl\gl.h>
#include <gl\glu.h>

#pragma comment(lib, "opengl32.lib")

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

#endif //_WIN32

typedef struct
{
    dtb_key_type type;
    bool is_down;
    bool is_changed;
}dtb_key;

typedef struct
{
    dtb_key keys[DTB_KEY_MAX];
    unsigned int mouse_position_x;
    unsigned int mouse_position_y;
}dtb_input;

typedef struct
{
    HWND window_handle;
	HDC device_context;
	UINT message;
	WPARAM wparam;
	LPARAM lparam;
}win32_internals;

typedef struct
{
    bool is_running;
    int window_width;
    int window_height;
    dtb_input input;

    win32_internals win32;
}dtb_platform;

// NOTE(Dillon): User has to define this in main compilation unit

unsigned int dtb_init(dtb_platform* platform);
void dtb_loop(dtb_platform* platform, float delta_time);

// TODO(Dillon): Get rid of this, this is terrible, win32 sucks
bool global_running;

// TODO(Dillon): Maybe rename this function later

#define dtb_key_is_pressed(platform, type) platform->input.keys[type].is_down && platform->input.keys[type].is_changed
#define dtb_key_is_released(platform, type) !platform->input.keys[type].is_down && platform->input.keys[type].is_changed
#define dtb_key_is_down(platform, type) platform->input.keys[type].is_down

#if defined(_WIN32)

void win32_translate_vk_codes(dtb_platform* platform, unsigned int vk_code)
{
    switch(vk_code)
    {
        // NOTE(Dillon): Function keys
        case VK_F1:
        {
            platform->input.keys[DTB_KEY_F1].is_down = true;
            platform->input.keys[DTB_KEY_F1].is_changed = true;
        }break;
        case VK_F2:
        {
            platform->input.keys[DTB_KEY_F2].is_down = true;
            platform->input.keys[DTB_KEY_F2].is_changed = true;
        }break;
        case VK_F3:
        {
            platform->input.keys[DTB_KEY_F3].is_down = true;
            platform->input.keys[DTB_KEY_F3].is_changed = true;
        }break;
        case VK_F4:
        {
            platform->input.keys[DTB_KEY_F4].is_down = true;
            platform->input.keys[DTB_KEY_F4].is_changed = true;
        }break;
        case VK_F5:
        {
            platform->input.keys[DTB_KEY_F5].is_down = true;
            platform->input.keys[DTB_KEY_F5].is_changed = true;
        }break;
        case VK_F6:
        {
            platform->input.keys[DTB_KEY_F6].is_down = true;
            platform->input.keys[DTB_KEY_F6].is_changed = true;
        }break;
        case VK_F7:
        {
            platform->input.keys[DTB_KEY_F7].is_down = true;
            platform->input.keys[DTB_KEY_F7].is_changed = true;
        }break;
        case VK_F8:
        {
            platform->input.keys[DTB_KEY_F8].is_down = true;
            platform->input.keys[DTB_KEY_F8].is_changed = true;
        }break;
        case VK_F9:
        {
            platform->input.keys[DTB_KEY_F9].is_down = true;
            platform->input.keys[DTB_KEY_F9].is_changed = true;
        }break;
        case VK_F10:
        {
            platform->input.keys[DTB_KEY_F10].is_down = true;
            platform->input.keys[DTB_KEY_F10].is_changed = true;
        }break;
        case VK_F11:
        {
            platform->input.keys[DTB_KEY_F11].is_down = true;
            platform->input.keys[DTB_KEY_F11].is_changed = true;
        }break;
        case VK_F12:
        {
            platform->input.keys[DTB_KEY_F12].is_down = true;
            platform->input.keys[DTB_KEY_F12].is_changed = true;
        }break;
        
        // NOTE(Dillon): Number keys
        case 0x30:
        {
            platform->input.keys[DTB_KEY_0].is_down = true;
            platform->input.keys[DTB_KEY_0].is_changed = true;
        }break;
        case 0x31:
        {
            platform->input.keys[DTB_KEY_1].is_down = true;
            platform->input.keys[DTB_KEY_1].is_changed = true;
        }break;
        case 0x32:
        {
            platform->input.keys[DTB_KEY_2].is_down = true;
            platform->input.keys[DTB_KEY_2].is_changed = true;
        }break;
        case 0x33:
        {
            platform->input.keys[DTB_KEY_3].is_down = true;
            platform->input.keys[DTB_KEY_3].is_changed = true;
        }break;
        case 0x34:
        {
            platform->input.keys[DTB_KEY_4].is_down = true;
            platform->input.keys[DTB_KEY_4].is_changed = true;
        }break;
        case 0x35:
        {
            platform->input.keys[DTB_KEY_5].is_down = true;
            platform->input.keys[DTB_KEY_5].is_changed = true;
        }break;
        case 0x36:
        {
            platform->input.keys[DTB_KEY_6].is_down = true;
            platform->input.keys[DTB_KEY_6].is_changed = true;
        }break;
        case 0x37:
        {
            platform->input.keys[DTB_KEY_7].is_down = true;
            platform->input.keys[DTB_KEY_7].is_changed = true;
        }break;
        case 0x38:
        {
            platform->input.keys[DTB_KEY_8].is_down = true;
            platform->input.keys[DTB_KEY_8].is_changed = true;
        }break;
        case 0x39:
        {
            platform->input.keys[DTB_KEY_9].is_down = true;
            platform->input.keys[DTB_KEY_9].is_changed = true;
        }break;
        
        // NOTE(Dillon): Special keys
        case VK_SPACE:
        {
            platform->input.keys[DTB_KEY_SPACE].is_down = true;
            platform->input.keys[DTB_KEY_SPACE].is_changed = true;
        }break;
        case VK_TAB:
        {
            platform->input.keys[DTB_KEY_TAB].is_down = true;
            platform->input.keys[DTB_KEY_TAB].is_changed = true;
        }break;
        case VK_CAPITAL:
        {
            platform->input.keys[DTB_KEY_CAPS_LOCK].is_down = true;
            platform->input.keys[DTB_KEY_CAPS_LOCK].is_changed = true;
        }break;
        case VK_LSHIFT:
        {
            platform->input.keys[DTB_KEY_LEFT_SHIFT].is_down = true;
            platform->input.keys[DTB_KEY_LEFT_SHIFT].is_changed = true;
        }break;
        case VK_RSHIFT:
        {
            platform->input.keys[DTB_KEY_RIGHT_SHIFT].is_down = true;
            platform->input.keys[DTB_KEY_RIGHT_SHIFT].is_changed = true;
        }break;
        case VK_LCONTROL:
        {
            platform->input.keys[DTB_KEY_LEFT_CTRL].is_down = true;
            platform->input.keys[DTB_KEY_LEFT_CTRL].is_changed = true;
        }break;
        case VK_RCONTROL:
        {
            platform->input.keys[DTB_KEY_RIGHT_CTRL].is_down = true;
            platform->input.keys[DTB_KEY_RIGHT_CTRL].is_changed = true;
        }break;
        case 0x12:
        {
            platform->input.keys[DTB_KEY_ALT].is_down = true;
            platform->input.keys[DTB_KEY_ALT].is_changed = true;
        }break;
        case VK_LEFT:
        {
            platform->input.keys[DTB_KEY_LEFT_ARROW].is_down = true;
            platform->input.keys[DTB_KEY_LEFT_ARROW].is_changed = true;
        }break;
        case VK_RIGHT:
        {
            platform->input.keys[DTB_KEY_RIGHT_ARROW].is_down = true;
            platform->input.keys[DTB_KEY_RIGHT_ARROW].is_changed = true;
        }break;
        case VK_UP:
        {
            platform->input.keys[DTB_KEY_UP_ARROW].is_down = true;
            platform->input.keys[DTB_KEY_UP_ARROW].is_changed = true;
        }break;
        case VK_DOWN:
        {
            platform->input.keys[DTB_KEY_DOWN_ARROW].is_down = true;
            platform->input.keys[DTB_KEY_DOWN_ARROW].is_changed = true;
        }break;
        case VK_HOME:
        {
            platform->input.keys[DTB_KEY_HOME].is_down = true;
            platform->input.keys[DTB_KEY_HOME].is_changed = true;
        }break;
        case VK_INSERT:
        {
            platform->input.keys[DTB_KEY_INSERT].is_down = true;
            platform->input.keys[DTB_KEY_INSERT].is_changed = true;
        }break;
        case VK_DELETE:
        {
            platform->input.keys[DTB_KEY_DELETE].is_down = true;
            platform->input.keys[DTB_KEY_DELETE].is_changed = true;
        }break;
        case VK_PRIOR:
        {
            platform->input.keys[DTB_KEY_PAGE_UP].is_down = true;
            platform->input.keys[DTB_KEY_PAGE_UP].is_changed = true;
        }break;
        case VK_NEXT:
        {
            platform->input.keys[DTB_KEY_PAGE_DOWN].is_down = true;
            platform->input.keys[DTB_KEY_PAGE_DOWN].is_changed = true;
        }break;
        case VK_ESCAPE:
        {
            platform->input.keys[DTB_KEY_ESCAPE].is_down = true;
            platform->input.keys[DTB_KEY_ESCAPE].is_changed = true;
        }break;
        case VK_BACK:
        {
            platform->input.keys[DTB_KEY_BACKSPACE].is_down = true;
            platform->input.keys[DTB_KEY_BACKSPACE].is_changed = true;
        }break;
        
        // NOTE(Dillon): Alphabet
        case 0x41:
        {
            platform->input.keys[DTB_KEY_A].is_down = true;
            platform->input.keys[DTB_KEY_A].is_changed = true;
        }break;
        case 0x42:
        {
            platform->input.keys[DTB_KEY_B].is_down = true;
            platform->input.keys[DTB_KEY_B].is_changed = true;
        }break;
        case 0x43:
        {
            platform->input.keys[DTB_KEY_C].is_down = true;
            platform->input.keys[DTB_KEY_C].is_changed = true;
        }break;
        case 0x44:
        {
            platform->input.keys[DTB_KEY_D].is_down = true;
            platform->input.keys[DTB_KEY_D].is_changed = true;
        }break;
        case 0x45:
        {
            platform->input.keys[DTB_KEY_E].is_down = true;
            platform->input.keys[DTB_KEY_E].is_changed = true;
        }break;
        case 0x46:
        {
            platform->input.keys[DTB_KEY_F].is_down = true;
            platform->input.keys[DTB_KEY_F].is_changed = true;
        }break;
        case 0x47:
        {
            platform->input.keys[DTB_KEY_G].is_down = true;
            platform->input.keys[DTB_KEY_G].is_changed = true;
        }break;
        case 0x48:
        {
            platform->input.keys[DTB_KEY_H].is_down = true;
            platform->input.keys[DTB_KEY_H].is_changed = true;
        }break;
        case 0x49:
        {
            platform->input.keys[DTB_KEY_I].is_down = true;
            platform->input.keys[DTB_KEY_I].is_changed = true;
        }break;
        case 0x4A:
        {
            platform->input.keys[DTB_KEY_J].is_down = true;
            platform->input.keys[DTB_KEY_J].is_changed = true;
        }break;
        case 0x4B:
        {
            platform->input.keys[DTB_KEY_K].is_down = true;
            platform->input.keys[DTB_KEY_K].is_changed = true;
        }break;
        case 0x4C:
        {
            platform->input.keys[DTB_KEY_L].is_down = true;
            platform->input.keys[DTB_KEY_L].is_changed = true;
        }break;
        case 0x4D:
        {
            platform->input.keys[DTB_KEY_M].is_down = true;
            platform->input.keys[DTB_KEY_M].is_changed = true;
        }break;
        case 0x4E:
        {
            platform->input.keys[DTB_KEY_N].is_down = true;
            platform->input.keys[DTB_KEY_N].is_changed = true;
        }break;
        case 0x4F:
        {
            platform->input.keys[DTB_KEY_O].is_down = true;
            platform->input.keys[DTB_KEY_O].is_changed = true;
        }break;
        case 0x50:
        {
            platform->input.keys[DTB_KEY_P].is_down = true;
            platform->input.keys[DTB_KEY_P].is_changed = true;
        }break;
        case 0x51:
        {
            platform->input.keys[DTB_KEY_Q].is_down = true;
            platform->input.keys[DTB_KEY_Q].is_changed = true;
        }break;
        case 0x52:
        {
            platform->input.keys[DTB_KEY_R].is_down = true;
            platform->input.keys[DTB_KEY_R].is_changed = true;
        }break;
        case 0x53:
        {
            platform->input.keys[DTB_KEY_S].is_down = true;
            platform->input.keys[DTB_KEY_S].is_changed = true;
        }break;
        case 0x54:
        {
            platform->input.keys[DTB_KEY_T].is_down = true;
            platform->input.keys[DTB_KEY_T].is_changed = true;
        }break;
        case 0x55:
        {
            platform->input.keys[DTB_KEY_U].is_down = true;
            platform->input.keys[DTB_KEY_U].is_changed = true;
        }break;
        case 0x56:
        {
            platform->input.keys[DTB_KEY_V].is_down = true;
            platform->input.keys[DTB_KEY_V].is_changed = true;
        }break;
        case 0x57:
        {
            platform->input.keys[DTB_KEY_W].is_down = true;
            platform->input.keys[DTB_KEY_W].is_changed = true;
        }break;
        case 0x58:
        {
            platform->input.keys[DTB_KEY_X].is_down = true;
            platform->input.keys[DTB_KEY_X].is_changed = true;
        }break;
        case 0x59:
        {
            platform->input.keys[DTB_KEY_Y].is_down = true;
            platform->input.keys[DTB_KEY_Y].is_changed = true;
        }break;
        case 0x5A:
        {
            platform->input.keys[DTB_KEY_Z].is_down = true;
            platform->input.keys[DTB_KEY_Z].is_changed = true;
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
        global_running = false;
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
    
    dtb_platform platform;
    platform.win32.window_handle = CreateWindowA(wc.lpszClassName, wc.lpszClassName,
                                               WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                               CW_USEDEFAULT, CW_USEDEFAULT,
                                               DTB_WINDOW_WIDTH, DTB_WINDOW_HEIGHT,
                                               0, 0,
                                               wc.hInstance,
                                               0);
    
    if(!platform.win32.window_handle)
    {
        // TODO(Dillon): Error
    }
    
    ShowWindow(platform.win32.window_handle, SW_SHOW);
    UpdateWindow(platform.win32.window_handle);
    
    platform.win32.device_context = GetDC(platform.win32.window_handle);

    HGLRC glContext;
    PIXELFORMATDESCRIPTOR pfd = { 0 };
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cAlphaBits = 8;
    pfd.iLayerType = PFD_MAIN_PLANE;
    
    int pfIndex = ChoosePixelFormat(platform.win32.device_context, &pfd);
    if (pfIndex == 0){
        int x = 10;
    }
    
    PIXELFORMATDESCRIPTOR suggestedPfd;
    DescribePixelFormat(platform.win32.device_context, pfIndex, sizeof(suggestedPfd), &suggestedPfd);
    
    if (!SetPixelFormat(platform.win32.device_context, pfIndex, &pfd)){
        int x = 10;
    }
    
    glContext = wglCreateContext(platform.win32.device_context);
    if (!wglMakeCurrent(platform.win32.device_context, glContext)){
        int x = 10;
    }
    
#endif
    
    
    dtb_init(&platform);
    
    MSG msg;
    global_running = true;
    platform.is_running = global_running;
    while(platform.is_running)
    {
        INT64 countsPerSec = 0;
        QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
        
        float secPerCount = 1.0f / (float)countsPerSec;
        
        INT64 prevTime = 0;
        QueryPerformanceCounter((LARGE_INTEGER*)&prevTime);
        
        // NOTE(Dillon): Clear input at the start of each frame
        for(int i = 0; i < DTB_KEY_MAX; i++)
        {
            platform.input.keys[i].is_changed = false;
        }
        
        while(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            if(msg.message == WM_LBUTTONUP)
            {
                platform.input.keys[DTB_MOUSE_ONE].is_down = true;
                platform.input.keys[DTB_MOUSE_ONE].is_changed = true;
            }
            if(msg.message == WM_RBUTTONUP)
            {
                platform.input.keys[DTB_MOUSE_TWO].is_down = true;
                platform.input.keys[DTB_MOUSE_TWO].is_changed = true;
            }
            
            if(msg.message == WM_KEYUP)
            {
                unsigned int vkCode = msg.wParam;
                win32_translate_vk_codes(&platform, vkCode);
            }
        
            TranslateMessage(&msg);
            DispatchMessage(&msg);
		
        	platform.win32.message = msg.message;
			platform.win32.lparam = msg.lParam;
			platform.win32.wparam = msg.wParam;

        }
        
        POINT p;
        if(GetCursorPos(&p))
        {
            if(ScreenToClient(platform.win32.window_handle, &p))
            {
                platform.input.mouse_position_x = p.x;
                platform.input.mouse_position_y = p.y;
            }
        }
        
        if(global_running== false)
        {
            platform.is_running = false;
        }
        
        
        INT64 currentTime = 0;
        QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
        float deltaTime = (currentTime - prevTime) * secPerCount;
        
        platform.win32.device_context = GetDC(platform.win32.window_handle);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        dtb_loop(&platform, deltaTime);
        
        SwapBuffers(platform.win32.device_context);
    }
    
    return 0;
}

#endif //DTB_PLATFORM_H