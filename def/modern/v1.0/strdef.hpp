/*
	These are some definitions to ease application development on modern Windows systems.

	config.h is the macro configuration file.
	globldef.h is the global definition file. It should be the first #include in all subsequent header and source files.

	Author: Rafael Sabe
	Email: rafaelmsabe@gmail.com
*/

#ifndef STRDEF_HPP
#define STRDEF_HPP

#include "globldef.h"
#include <string>

#ifdef __USE_UTF16
typedef std::wstring __string;
#define __TOSTRING(val) std::to_wstring(val)
#else
typedef std::string __string;
#define __TOSTRING(val) std::to_string(val)
#endif

#endif //STRDEF_HPP
