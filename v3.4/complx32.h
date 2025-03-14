/*
	These are some definitions to ease application development on Windows systems.
	Version 3.4

	config.h is the macro configuration file, where all macro code settings are applied.
	Settings like text format, target system and so on are set in config.h.

	globldef.h is the global definition file. It defines/undefines macros based on the definitions in config.h file.
	It should be the first #include in all subsequent header and source files.

	Author: Rafael Sabe
	Email: rafaelmsabe@gmail.com

	GitHub Repository: https://github.com/RMSabe/WinLib
*/

/* Basic Math Operations with complex numbers (32bit floating point). 
Functions return TRUE if successful, FALSE otherwise. Divide also returns FALSE if divider equals 0*/

#ifndef COMPLX32_H
#define COMPLX32_H

#include "globldef.h"

struct _complex32 {
	FLOAT r;
	FLOAT i;
};

typedef struct _complex32 complex32_t;

extern BOOL WINAPI complex32_get_conjugate(const complex32_t *p_input, complex32_t *p_output);
extern BOOL WINAPI complex32_add(const complex32_t *p_input1, const complex32_t *p_input2, complex32_t *p_output);
extern BOOL WINAPI complex32_subtract(const complex32_t *p_input1, const complex32_t *p_input2, complex32_t *p_output);
extern BOOL WINAPI complex32_multiply(const complex32_t *p_input1, const complex32_t *p_input2, complex32_t *p_output);
extern BOOL WINAPI complex32_divide(const complex32_t *p_input1, const complex32_t *p_input2, complex32_t *p_output);

#endif /*COMPLX32_H*/
