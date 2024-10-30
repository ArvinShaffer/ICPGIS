#ifndef ICPPLATFORM_HPP
#define ICPPLATFORM_HPP

#define ICP_PLATFORM_WIN32   1
#define ICP_PLATFORM_LINUX   2
#define ICP_PLATFORM_APPLE   3
#define ICP_PLATFORM_ANDROID 4
#define ICP_PATH_LENGTH 1024
#define ICP_CALL __stdcall

#define ICP_PLATFORM ICP_PLATFORM_WIN32

#if ICP_PLATFORM == ICP_PLATFORM_WIN32
#include<stdio.h>
#include<stdlib.h>
#include<wchar.h>
#include<tchar.h>
#include<windows.h>
#include<GL/glew.h>
#include<gl/gl.h>
#include<gl/glu.h>

#ifdef ICPGIS_EXPORTS
#define ICPGIS_API __declspec(dllexport)
#else
#define ICPGIS_API __declspec(dllimport)
#endif

#define HDISPLAY HDC
#define HWINDOW  HWND
#define HLIBRARY HMODULE
#define INSTANCE HINSTANCE

typedef const char* STRING;

#elif ICP_PLATFORM = ICP_PLATFORM_LINUX || ICP_PLATFORM_ANDROID
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<wchar.h>
#include<X11/X.h>
#include<X11/Xlib.h>
#include<GL/glew.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>
#include<dlfcn.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<sys/time.h>

#ifdef ICPGIS_EXPORTS
#define ICPGIS_API
#else
#define ICPGIS_API
#define HDISPLAY void*
#define HWINDOW  void*
#define HLIBRARY void*

#endif

#endif

#endif // ICPPLATFORM_HPP
