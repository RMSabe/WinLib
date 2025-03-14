#include "globldef.h"
#include "cstrdef.h"
#include "console.h"

extern BOOL WINAPI app_init(VOID);
extern VOID WINAPI app_deinit(VOID);

extern VOID WINAPI test_round(VOID);
extern VOID WINAPI test_floor(VOID);
extern VOID WINAPI test_ceil(VOID);
extern VOID WINAPI test_ispower2(VOID);
extern VOID WINAPI test_getsizetmsb(VOID);

INT main(VOID)
{
	if(!app_init())
	{
		app_deinit();
		return 1;
	}

	test_getsizetmsb();
	test_ispower2();

	console_wait_keypress(NULL);
	console_clear_text();

	test_round();
	console_wait_keypress(NULL);
	console_clear_text();

	test_floor();
	console_wait_keypress(NULL);
	console_clear_text();

	test_ceil();

	console_wait_keypress(NULL);
	app_deinit();
	return 0;
}

BOOL WINAPI app_init(VOID)
{
	p_processheap = GetProcessHeap();
	if(p_processheap == NULL)
	{
		__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("Error: Invalid Process Heap."));
		goto _l_app_init_error;
	}

	if(!console_init())
	{
		__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("Error: Console Init Failed."));
		goto _l_app_init_error;
	}

	return TRUE;

	_l_app_init_error:
	MessageBox(NULL, textbuf, TEXT("INIT ERROR"), (MB_ICONSTOP | MB_OK));
	return FALSE;
}

VOID WINAPI app_deinit(VOID)
{
	console_deinit();
	return;
}

VOID WINAPI test_round(VOID)
{
	SIZE_T s_in = 0u;
	SIZE_T s_out = 0u;

	console_stdout_write(TEXT("Test Round:\r\n\r\n"));

	s_out = _get_closest_power2_round(s_in);

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("Input: 0x%p | Output: 0x%p\r\n"), (VOID*) s_in, (VOID*) s_out);
	console_stdout_write(textbuf);

	s_in = _get_sizet_msb_value();
	s_out = _get_closest_power2_round(s_in);

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("Input: 0x%p | Output: 0x%p\r\n"), (VOID*) s_in, (VOID*) s_out);
	console_stdout_write(textbuf);

	s_in = 0x8000;
	s_out = _get_closest_power2_round(s_in);

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("Input: 0x%p | Output: 0x%p\r\n"), (VOID*) s_in, (VOID*) s_out);
	console_stdout_write(textbuf);

	s_in = _get_sizet_msb_value();
	s_in |= 0x3f201c;
	s_out = _get_closest_power2_round(s_in);

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("Input: 0x%p | Output: 0x%p\r\n"), (VOID*) s_in, (VOID*) s_out);
	console_stdout_write(textbuf);

	s_in = 0u;
	s_in = ~s_in;
	s_in -= 0x3f201c;
	s_out = _get_closest_power2_round(s_in);

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("Input: 0x%p | Output: 0x%p\r\n"), (VOID*) s_in, (VOID*) s_out);
	console_stdout_write(textbuf);

	s_in = _get_sizet_msb_value();
	s_in -= 0x3f201c;
	s_out = _get_closest_power2_round(s_in);

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("Input: 0x%p | Output: 0x%p\r\n"), (VOID*) s_in, (VOID*) s_out);
	console_stdout_write(textbuf);

	s_in = 0x3f201c;
	s_out = _get_closest_power2_round(s_in);

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("Input: 0x%p | Output: 0x%p\r\n"), (VOID*) s_in, (VOID*) s_out);
	console_stdout_write(textbuf);

	s_in = 0x25201c;
	s_out = _get_closest_power2_round(s_in);

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("Input: 0x%p | Output: 0x%p\r\n"), (VOID*) s_in, (VOID*) s_out);
	console_stdout_write(textbuf);

	console_stdout_write(TEXT("\r\n"));
	return;
}

VOID WINAPI test_floor(VOID)
{
	SIZE_T s_in = 0u;
	SIZE_T s_out = 0u;

	console_stdout_write(TEXT("Test Floor:\r\n\r\n"));

	s_out = _get_closest_power2_floor(s_in);

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("Input: 0x%p | Output: 0x%p\r\n"), (VOID*) s_in, (VOID*) s_out);
	console_stdout_write(textbuf);

	s_in = _get_sizet_msb_value();
	s_out = _get_closest_power2_floor(s_in);

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("Input: 0x%p | Output: 0x%p\r\n"), (VOID*) s_in, (VOID*) s_out);
	console_stdout_write(textbuf);

	s_in |= 0x3f201c;
	s_out = _get_closest_power2_floor(s_in);

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("Input: 0x%p | Output: 0x%p\r\n"), (VOID*) s_in, (VOID*) s_out);
	console_stdout_write(textbuf);

	s_in = _get_sizet_msb_value();
	s_in -= 0x3f201c;
	s_out = _get_closest_power2_floor(s_in);

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("Input: 0x%p | Output: 0x%p\r\n"), (VOID*) s_in, (VOID*) s_out);
	console_stdout_write(textbuf);

	s_in = 0x8000;
	s_out = _get_closest_power2_floor(s_in);

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("Input: 0x%p | Output: 0x%p\r\n"), (VOID*) s_in, (VOID*) s_out);
	console_stdout_write(textbuf);

	s_in = 0x3f201c;
	s_out = _get_closest_power2_floor(s_in);

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("Input: 0x%p | Output: 0x%p\r\n"), (VOID*) s_in, (VOID*) s_out);
	console_stdout_write(textbuf);

	console_stdout_write(TEXT("\r\n"));
	return;
}

VOID WINAPI test_ceil(VOID)
{
	SIZE_T s_in = 0u;
	SIZE_T s_out = 0u;

	console_stdout_write(TEXT("Test Ceil:\r\n\r\n"));

	s_out = _get_closest_power2_ceil(s_in);

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("Input: 0x%p | Output: 0x%p\r\n"), (VOID*) s_in, (VOID*) s_out);
	console_stdout_write(textbuf);

	s_in = _get_sizet_msb_value();
	s_out = _get_closest_power2_ceil(s_in);

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("Input: 0x%p | Output: 0x%p\r\n"), (VOID*) s_in, (VOID*) s_out);
	console_stdout_write(textbuf);

	s_in |= 0x3f201c;
	s_out = _get_closest_power2_ceil(s_in);

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("Input: 0x%p | Output: 0x%p\r\n"), (VOID*) s_in, (VOID*) s_out);
	console_stdout_write(textbuf);

	s_in = _get_sizet_msb_value();
	s_in -= 0x3f201c;
	s_out = _get_closest_power2_ceil(s_in);

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("Input: 0x%p | Output: 0x%p\r\n"), (VOID*) s_in, (VOID*) s_out);
	console_stdout_write(textbuf);

	s_in = 0x8000;
	s_out = _get_closest_power2_ceil(s_in);

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("Input: 0x%p | Output: 0x%p\r\n"), (VOID*) s_in, (VOID*) s_out);
	console_stdout_write(textbuf);

	s_in = 0x3f201c;
	s_out = _get_closest_power2_ceil(s_in);

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("Input: 0x%p | Output: 0x%p\r\n"), (VOID*) s_in, (VOID*) s_out);
	console_stdout_write(textbuf);

	console_stdout_write(TEXT("\r\n"));
	return;
}

VOID WINAPI test_ispower2(VOID)
{
	SIZE_T s_in = 0u;
	BOOL b_out = FALSE;

	console_stdout_write(TEXT("Test is_power2()\r\n\r\n"));

	s_in = 0u;
	b_out = _is_power2(s_in);

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("Input: 0x%p | Output: %d\r\n"), (VOID*) s_in, b_out);
	console_stdout_write(textbuf);

	s_in = 1u;
	b_out = _is_power2(s_in);

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("Input: 0x%p | Output: %d\r\n"), (VOID*) s_in, b_out);
	console_stdout_write(textbuf);

	s_in = 2u;
	b_out = _is_power2(s_in);

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("Input: 0x%p | Output: %d\r\n"), (VOID*) s_in, b_out);
	console_stdout_write(textbuf);

	s_in = 3u;
	b_out = _is_power2(s_in);

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("Input: 0x%p | Output: %d\r\n"), (VOID*) s_in, b_out);
	console_stdout_write(textbuf);

	s_in = 4u;
	b_out = _is_power2(s_in);

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("Input: 0x%p | Output: %d\r\n"), (VOID*) s_in, b_out);
	console_stdout_write(textbuf);

	s_in = 0x80000;
	b_out = _is_power2(s_in);

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("Input: 0x%p | Output: %d\r\n"), (VOID*) s_in, b_out);
	console_stdout_write(textbuf);

	s_in = 0x83fc6;
	b_out = _is_power2(s_in);

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("Input: 0x%p | Output: %d\r\n"), (VOID*) s_in, b_out);
	console_stdout_write(textbuf);

	s_in = _get_sizet_msb_value();
	b_out = _is_power2(s_in);

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("Input: 0x%p | Output: %d\r\n"), (VOID*) s_in, b_out);
	console_stdout_write(textbuf);

	s_in = (_get_sizet_msb_value() + 0x83fc6);
	b_out = _is_power2(s_in);

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("Input: 0x%p | Output: %d\r\n"), (VOID*) s_in, b_out);
	console_stdout_write(textbuf);

	s_in = (_get_sizet_msb_value() >> 1);
	b_out = _is_power2(s_in);

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("Input: 0x%p | Output: %d\r\n"), (VOID*) s_in, b_out);
	console_stdout_write(textbuf);

	s_in = (_get_sizet_msb_value() - 0x83fc6);
	b_out = _is_power2(s_in);

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("Input: 0x%p | Output: %d\r\n"), (VOID*) s_in, b_out);
	console_stdout_write(textbuf);

	console_stdout_write(TEXT("\r\n"));
	return;
}

VOID WINAPI test_getsizetmsb(VOID)
{
	console_stdout_write(TEXT("Test SIZE_T msb value()\r\n\r\n"));

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("_get_sizet_msb_value() returned: 0x%p\r\n"), (VOID*) _get_sizet_msb_value());
	console_stdout_write(textbuf);

	console_stdout_write(TEXT("\r\n"));
	return;
}
