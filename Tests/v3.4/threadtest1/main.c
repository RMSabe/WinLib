/*Test thread_wait()*/

#include "globldef.h"
#include "cstrdef.h"
#include "console.h"
#include "thread.h"

HANDLE p_testthread = NULL;

extern BOOL WINAPI app_init(VOID);
extern VOID WINAPI app_deinit(VOID);

extern __declspec(noreturn) VOID WINAPI app_exit(UINT exit_code, const TCHAR *exit_msg);
extern INT WINAPI debug_msgbox(const TCHAR *text, UINT type);

extern BOOL WINAPI test_proc(VOID);
extern DWORD WINAPI testthread_proc(VOID *p_args);

INT main(VOID)
{
	if(!app_init()) goto _l_main_error;

	if(!test_proc())
	{
		console_wait_keypress(TEXT("Test Proc Failed.\r\n"));
		goto _l_main_error;
	}

	console_wait_keypress(TEXT("Test Proc Successful.\r\n"));

	app_deinit();
	return 0;

_l_main_error:
	app_deinit();
	return 1;
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
	if(p_testthread != NULL) thread_stop(&p_testthread, 0u);
	console_deinit();
	return;
}

__declspec(noreturn) VOID WINAPI app_exit(UINT exit_code, const TCHAR *exit_msg)
{
	if(exit_msg != NULL) MessageBox(NULL, exit_msg, TEXT("PROCESS EXIT CALLED"), (MB_ICONSTOP | MB_OK));

	app_deinit();
	ExitProcess(exit_code);

	while(TRUE) Sleep(1u); /*Not really necessary, but just to be safe.*/
}

INT WINAPI debug_msgbox(const TCHAR *text, UINT type)
{
	return MessageBox(NULL, text, TEXT("DEBUG"), type);
}

BOOL WINAPI test_proc(VOID)
{
	p_testthread = thread_create_default(&testthread_proc, NULL, NULL);
	if(p_testthread == NULL)
	{
		debug_msgbox(TEXT("Thread Create Failed"), (MB_ICONEXCLAMATION | MB_OK));
		return FALSE;
	}

	return thread_wait(&p_testthread);
}

DWORD WINAPI testthread_proc(VOID *p_args)
{
	const DWORD LOOP_DELAYTIME_MS = 400u;
	const BYTE STOP_VAL = 16u;
	BYTE value = 0u;

	while(value < STOP_VAL)
	{
		__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("%u\r\n"), value);
		console_stdout_write(textbuf);
		Sleep(LOOP_DELAYTIME_MS);
		value++;
	}

	return 0u;
}
