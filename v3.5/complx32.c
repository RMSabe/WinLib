/*
	These are some definitions to ease application development on Windows systems.
	Version 3.5

	config.h is the macro configuration file, where all macro code settings are applied.
	Settings like text format, target system and so on are set in config.h.

	globldef.h is the global definition file. It defines/undefines macros based on the definitions in config.h file.
	It should be the first #include in all subsequent header and source files.

	Author: Rafael Sabe
	Email: rafaelmsabe@gmail.com

	GitHub Repository: https://github.com/RMSabe/WinLib
*/

#include "complx32.h"

BOOL WINAPI complex32_get_conjugate(const complex32_t *p_input, complex32_t *p_output)
{
	if(p_input == NULL) return FALSE;
	if(p_output == NULL) return FALSE;

	p_output->r = p_input->r;
	p_output->i = -(p_input->i);

	return TRUE;
}

BOOL WINAPI complex32_add(const complex32_t *p_input1, const complex32_t *p_input2, complex32_t *p_output)
{
	if(p_input1 == NULL) return FALSE;
	if(p_input2 == NULL) return FALSE;
	if(p_output == NULL) return FALSE;

	p_output->r = p_input1->r + p_input2->r;
	p_output->i = p_input1->i + p_input2->i;

	return TRUE;
}

BOOL WINAPI complex32_subtract(const complex32_t *p_input1, const complex32_t *p_input2, complex32_t *p_output)
{
	if(p_input1 == NULL) return FALSE;
	if(p_input2 == NULL) return FALSE;
	if(p_output == NULL) return FALSE;

	p_output->r = p_input1->r - p_input2->r;
	p_output->i = p_input1->i - p_input2->i;

	return TRUE;
}

BOOL WINAPI complex32_multiply(const complex32_t *p_input1, const complex32_t *p_input2, complex32_t *p_output)
{
	if(p_input1 == NULL) return FALSE;
	if(p_input2 == NULL) return FALSE;
	if(p_output == NULL) return FALSE;

	p_output->r = p_input1->r*p_input2->r - p_input1->i*p_input2->i;
	p_output->i = p_input1->r*p_input2->i + p_input1->i*p_input2->r;

	return TRUE;
}

BOOL WINAPI complex32_divide(const complex32_t *p_input1, const complex32_t *p_input2, complex32_t *p_output)
{
	complex32_t conjugate;
	complex32_t numerator;
	complex32_t divider;

	if(p_input1 == NULL) return FALSE;
	if(p_input2 == NULL) return FALSE;
	if(p_output == NULL) return FALSE;

	complex32_get_conjugate(p_input2, &conjugate);
	complex32_multiply(p_input2, &conjugate, &divider);

	if(divider.r == 0.0f) return FALSE;

	complex32_multiply(p_input1, &conjugate, &numerator);

	p_output->r = numerator.r/divider.r;
	p_output->i = numerator.i/divider.r;

	return TRUE;
}
