/*
	These are some definitions to ease application development on Windows systems.
	Version 1.1

	config.h is the macro configuration file, where all macro code settings are applied.
	Settings like text format, target system and so on are set in config.h.

	globldef.h is the global definition file. It defines/undefines macros based on the definitions in config.h file.
	It should be the first #include in all subsequent header and source files.

	Author: Rafael Sabe
	Email: rafaelmsabe@gmail.com
*/

#ifndef STRDEF_H
#define STRDEF_H

#include "globldef.h"
#include <stdio.h>

#ifdef __USE_UTF16
#define __SPRINTF(output, size, input, ...) swprintf(output, size, input, ## __VA_ARGS__)
#define __STRTOINT32(str) _wtol(str)
#define __STRTOINT64(str) _wtoi64(str)
#define __STRTODOUBLE(str) _wtof(str)
#else
#define __SPRINTF(output, size, input, ...) snprintf(output, size, input, ## __VA_ARGS__)
#define __STRTOINT32(str) atol(str)
#define __STRTODOUBLE(str) atof(str)
#ifdef __NTWIN
#define __STRTOINT64(str) _atoi64(str)
#endif
#endif

#endif //STRDEF_H
