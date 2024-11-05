/*
	These are some definitions to ease application development on legacy Windows systems.

	config.h is the macro configuration file.
	globldef.h is the global definition file. It should be the first #include in all subsequent header and source files.

	Author: Rafael Sabe
	Email: rafaelmsabe@gmail.com
*/

#ifndef GLOBLDEF_H
#define GLOBLDEF_H

#include "config.h"

#ifdef __DOSWIN
#ifdef __NTWIN
#error "__DOSWIN and __NTWIN must not be defined simultaneously"
#endif
#endif

#ifndef __DOSWIN
#ifndef __NTWIN
#define __NTWIN
#endif
#endif

#ifdef __DOSWIN
#ifdef __USE_UTF16
#error "DOS based Windows does not support UNICODE UTF-16 text format"
#endif
#ifdef __FILE64
#error "DOS based Windows does not support 64 bit file size"
#endif
#endif

#ifdef __USE_UTF16
#ifndef UNICODE
#define UNICODE
#endif
#else
#ifdef UNICODE
#undef UNICODE
#endif
#endif

#include <windows.h>

#endif //GLOBLDEF_H
