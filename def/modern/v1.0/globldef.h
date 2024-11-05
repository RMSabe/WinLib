/*
	These are some definitions to ease application development on modern Windows systems.

	config.h is the macro configuration file.
	globldef.h is the global definition file. It should be the first #include in all subsequent header and source files.

	Author: Rafael Sabe
	Email: rafaelmsabe@gmail.com
*/

#ifndef GLOBLDEF_H
#define GLOBLDEF_H

#include "config.h"

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
