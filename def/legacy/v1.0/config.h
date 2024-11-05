/*
	These are some definitions to ease application development on legacy Windows systems.

	config.h is the macro configuration file.
	globldef.h is the global definition file. It should be the first #include in all subsequent header and source files.

	Author: Rafael Sabe
	Email: rafaelmsabe@gmail.com
*/

#ifndef CONFIG_H
#define CONFIG_H

//======================================================================================
//Target Platform Definition
//define __DOSWIN to target a DOS based Windows system
//define __NTWIN to target a NT based Windows system
//if neither is defined, __NTWIN will be defined by default

//#define __DOSWIN
//#define __NTWIN

//======================================================================================
//Text Definition
//Define __USE_UTF16 to use UNICODE UTF-16 text format (NT based Windows Only)
//If not defined, ANSI UTF-8 text format will be used

//#define __USE_UTF16

//======================================================================================
//File Size Definition
//Define __FILE64 to use 64 bit file size and positioning (NT based Windows Only)
//If not defined, 32 bit file size and positioning will be used

//#define __FILE64

//======================================================================================

#endif //CONFIG_H
