#include "globldef.h"
#include "cstrdef.h"
#include "console.h"

extern BOOL WINAPI app_init(VOID);
extern VOID WINAPI app_deinit(VOID);

extern VOID WINAPI runtime_loop(VOID);

extern VOID WINAPI sum_proc(VOID);
extern VOID WINAPI sub_proc(VOID);
extern VOID WINAPI mult_proc(VOID);
extern VOID WINAPI div_proc(VOID);

INT main(VOID)
{
	if(!app_init())
	{
		app_deinit();
		return 1;
	}

	console_set_title(TEXT("CMD Calculator"));
	runtime_loop();

	app_deinit();
	return 0;
}

BOOL WINAPI app_init(VOID)
{
	p_processheap = GetProcessHeap();
	if(p_processheap == NULL)
	{
		MessageBox(NULL, TEXT("Error: Invalid Process Heap."), TEXT("INIT ERROR"), (MB_ICONSTOP | MB_OK));
		return FALSE;
	}

	if(!console_init())
	{
		MessageBox(NULL, TEXT("Error: Console Init Failed."), TEXT("INIT ERROR"), (MB_ICONSTOP | MB_OK));
		return FALSE;
	}

	return TRUE;
}

VOID WINAPI app_deinit(VOID)
{
	console_deinit();
	return;
}

VOID WINAPI runtime_loop(VOID)
{
	while(TRUE)
	{
		console_clear_text();

		console_stdout_write(TEXT("Choose an Operation:\r\n\r\n"));

		console_stdout_write(TEXT("Enter \"sum\" for sum\r\n"));
		console_stdout_write(TEXT("Enter \"sub\" for subtraction\r\n"));
		console_stdout_write(TEXT("Enter \"mult\" for multiplication\r\n"));
		console_stdout_write(TEXT("Enter \"div\" for division\r\n"));

		console_stdout_write(TEXT("Enter \"quit\" to quit\r\n\r\n"));

		console_stdin_readcmd(textbuf, TEXTBUF_SIZE_CHARS);
		cstr_tolower(textbuf, TEXTBUF_SIZE_CHARS);

		console_clear_text();

		if(cstr_compare(textbuf, TEXT("quit"))) break;
		else if(cstr_compare(textbuf, TEXT("sum"))) sum_proc();
		else if(cstr_compare(textbuf, TEXT("sub"))) sub_proc();
		else if(cstr_compare(textbuf, TEXT("mult"))) mult_proc();
		else if(cstr_compare(textbuf, TEXT("div"))) div_proc();
		else console_wait_keypress(TEXT("Error: invalid command entered\r\n"));
	}

	return;
}

VOID WINAPI sum_proc(VOID)
{
	DOUBLE a = 0.0;
	DOUBLE b = 0.0;
	DOUBLE r = 0.0;

	console_stdout_write(TEXT("Sum \"a + b\"\r\nEnter value of \"a\": "));
	console_stdin_readcmd(textbuf, TEXTBUF_SIZE_CHARS);
	a = __CSTRTODOUBLE(textbuf);

	console_stdout_write(TEXT("Enter value of \"b\": "));
	console_stdin_readcmd(textbuf, TEXTBUF_SIZE_CHARS);
	b = __CSTRTODOUBLE(textbuf);

	r = a + b;

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("\r\nResult: %lf\r\n\r\n"), r);
	console_stdout_write(textbuf);
	console_wait_keypress(NULL);
	return;
}

VOID WINAPI sub_proc(VOID)
{
	DOUBLE a = 0.0;
	DOUBLE b = 0.0;
	DOUBLE r = 0.0;

	console_stdout_write(TEXT("Subtraction \"a - b\"\r\nEnter value of \"a\": "));
	console_stdin_readcmd(textbuf, TEXTBUF_SIZE_CHARS);
	a = __CSTRTODOUBLE(textbuf);

	console_stdout_write(TEXT("Enter value of \"b\": "));
	console_stdin_readcmd(textbuf, TEXTBUF_SIZE_CHARS);
	b = __CSTRTODOUBLE(textbuf);

	r = a - b;

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("\r\nResult: %lf\r\n\r\n"), r);
	console_stdout_write(textbuf);
	console_wait_keypress(NULL);
	return;
}

VOID WINAPI mult_proc(VOID)
{
	DOUBLE a = 0.0;
	DOUBLE b = 0.0;
	DOUBLE r = 0.0;

	console_stdout_write(TEXT("Multiplication \"a * b\"\r\nEnter value of \"a\": "));
	console_stdin_readcmd(textbuf, TEXTBUF_SIZE_CHARS);
	a = __CSTRTODOUBLE(textbuf);

	console_stdout_write(TEXT("Enter value of \"b\": "));
	console_stdin_readcmd(textbuf, TEXTBUF_SIZE_CHARS);
	b = __CSTRTODOUBLE(textbuf);

	r = a*b;

	__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("\r\nResult: %lf\r\n\r\n"), r);
	console_stdout_write(textbuf);
	console_wait_keypress(NULL);
	return;
}

VOID WINAPI div_proc(VOID)
{
	DOUBLE a = 0.0;
	DOUBLE b = 0.0;
	DOUBLE r = 0.0;

	console_stdout_write(TEXT("Division \"a / b\"\r\nEnter value of \"a\": "));
	console_stdin_readcmd(textbuf, TEXTBUF_SIZE_CHARS);
	a = __CSTRTODOUBLE(textbuf);

	console_stdout_write(TEXT("Enter value of \"b\": "));
	console_stdin_readcmd(textbuf, TEXTBUF_SIZE_CHARS);
	b = __CSTRTODOUBLE(textbuf);

	if(b == 0.0) console_stdout_write(TEXT("\r\nResult: No Solution\r\n\r\n"));
	else
	{
		r = a/b;
		__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("\r\nResult: %lf\r\n\r\n"), r);
		console_stdout_write(textbuf);
	}

	console_wait_keypress(NULL);
	return;
}
