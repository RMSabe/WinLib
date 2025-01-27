#include "globldef.h"
#include "cstrdef.h"
#include "console.h"

#include "strdef.hpp"

__string tstr = TEXT("");

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

	console_set_title(TEXT("CMD Calc"));

	runtime_loop();

	app_deinit();
	return 0;
}

BOOL WINAPI app_init(VOID)
{
	p_processheap = GetProcessHeap();
	if(p_processheap == nullptr)
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

		console_stdout_write(TEXT("Choose an Operation\r\n\r\n"));
		console_stdout_write(TEXT("Enter \"sum\" for sum\r\n"));
		console_stdout_write(TEXT("Enter \"sub\" for subtraction\r\n"));
		console_stdout_write(TEXT("Enter \"mult\" for multiplication\r\n"));
		console_stdout_write(TEXT("Enter \"div\" for division\r\n"));
		console_stdout_write(TEXT("\r\nEnter \"quit\" to quit\r\n"));

		console_stdin_readcmd(textbuf, TEXTBUF_SIZE_CHARS);
		tstr = textbuf;
		tstr = cppstr_tolower(tstr);

		if(!tstr.compare(TEXT("quit"))) break;
		else if(!tstr.compare(TEXT("sum"))) sum_proc();
		else if(!tstr.compare(TEXT("sub"))) sub_proc();
		else if(!tstr.compare(TEXT("mult"))) mult_proc();
		else if(!tstr.compare(TEXT("div"))) div_proc();
		else console_wait_keypress(TEXT("Invalid command entered\r\n"));
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
	tstr = textbuf;

	try
	{
		a = std::stod(tstr);
	}
	catch(...)
	{
		console_wait_keypress(TEXT("\r\nInvalid value entered\r\n"));
		return;
	}

	console_stdout_write(TEXT("Enter value of \"b\": "));
	console_stdin_readcmd(textbuf, TEXTBUF_SIZE_CHARS);
	tstr = textbuf;

	try
	{
		b = std::stod(tstr);
	}
	catch(...)
	{
		console_wait_keypress(TEXT("\r\nInvalid value entered\r\n"));
		return;
	}

	r = a + b;

	tstr = TEXT("\r\nResult: ") + __TOSTRING(r);
	console_stdout_write(tstr.c_str());
	console_wait_keypress(TEXT("\r\n\r\n"));
	return;
}

VOID WINAPI sub_proc(VOID)
{
	DOUBLE a = 0.0;
	DOUBLE b = 0.0;
	DOUBLE r = 0.0;

	console_stdout_write(TEXT("Subtraction \"a - b\"\r\nEnter value of \"a\": "));
	console_stdin_readcmd(textbuf, TEXTBUF_SIZE_CHARS);
	tstr = textbuf;

	try
	{
		a = std::stod(tstr);
	}
	catch(...)
	{
		console_wait_keypress(TEXT("\r\nInvalid value entered\r\n"));
		return;
	}

	console_stdout_write(TEXT("Enter value of \"b\": "));
	console_stdin_readcmd(textbuf, TEXTBUF_SIZE_CHARS);
	tstr = textbuf;

	try
	{
		b = std::stod(tstr);
	}
	catch(...)
	{
		console_wait_keypress(TEXT("\r\nInvalid value entered\r\n"));
		return;
	}

	r = a - b;

	tstr = TEXT("\r\nResult: ") + __TOSTRING(r);
	console_stdout_write(tstr.c_str());
	console_wait_keypress(TEXT("\r\n\r\n"));
	return;
}

VOID WINAPI mult_proc(VOID)
{
	DOUBLE a = 0.0;
	DOUBLE b = 0.0;
	DOUBLE r = 0.0;

	console_stdout_write(TEXT("Multiplication \"a * b\"\r\nEnter value of \"a\": "));
	console_stdin_readcmd(textbuf, TEXTBUF_SIZE_CHARS);
	tstr = textbuf;

	try
	{
		a = std::stod(tstr);
	}
	catch(...)
	{
		console_wait_keypress(TEXT("\r\nInvalid value entered\r\n"));
		return;
	}

	console_stdout_write(TEXT("Enter value of \"b\": "));
	console_stdin_readcmd(textbuf, TEXTBUF_SIZE_CHARS);
	tstr = textbuf;

	try
	{
		b = std::stod(tstr);
	}
	catch(...)
	{
		console_wait_keypress(TEXT("\r\nInvalid value entered\r\n"));
		return;
	}

	r = a*b;

	tstr = TEXT("\r\nResult: ") + __TOSTRING(r);
	console_stdout_write(tstr.c_str());
	console_wait_keypress(TEXT("\r\n\r\n"));
	return;
}

VOID WINAPI div_proc(VOID)
{
	DOUBLE a = 0.0;
	DOUBLE b = 0.0;
	DOUBLE r = 0.0;

	console_stdout_write(TEXT("Division \"a / b\"\r\nEnter value of \"a\": "));
	console_stdin_readcmd(textbuf, TEXTBUF_SIZE_CHARS);
	tstr = textbuf;

	try
	{
		a = std::stod(tstr);
	}
	catch(...)
	{
		console_wait_keypress(TEXT("\r\nInvalid value entered\r\n"));
		return;
	}

	console_stdout_write(TEXT("Enter value of \"b\": "));
	console_stdin_readcmd(textbuf, TEXTBUF_SIZE_CHARS);
	tstr = textbuf;

	try
	{
		b = std::stod(tstr);
	}
	catch(...)
	{
		console_wait_keypress(TEXT("\r\nInvalid value entered\r\n"));
		return;
	}

	if(b == 0.0) console_stdout_write(TEXT("\r\nResult: No solution"));
	else
	{
		r = a/b;
		tstr = TEXT("\r\nResult: ") + __TOSTRING(r);
		console_stdout_write(tstr.c_str());
	}

	console_wait_keypress(TEXT("\r\n\r\n"));
	return;
}
