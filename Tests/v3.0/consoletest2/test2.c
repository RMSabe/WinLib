#include "globldef.h"
#include "strdef.h"
#include "console.h"

extern BOOL WINAPI app_init(VOID);
extern VOID WINAPI app_deinit(VOID);

extern VOID WINAPI test_proc(VOID);
extern VOID WINAPI keyevent_eventhandler(KEY_EVENT_RECORD *p_eventrecord);

INT main(VOID)
{
	if(!app_init())
	{
		app_deinit();
		return 1;
	}

	test_proc();

	app_deinit();
	return 0;
}

BOOL WINAPI app_init(VOID)
{
	p_processheap = GetProcessHeap();
	if(p_processheap == NULL)
	{
		MessageBox(NULL, TEXT("Error: Invalid Process Heap"), TEXT("INIT ERROR"), (MB_ICONSTOP | MB_OK));
		return FALSE;
	}

	if(!console_init())
	{
		MessageBox(NULL, TEXT("Error: Console Init Failed"), TEXT("INIT ERROR"), (MB_ICONSTOP | MB_OK));
		return FALSE;
	}

	return TRUE;
}

VOID WINAPI app_deinit(VOID)
{
	console_deinit();
	return;
}

VOID WINAPI test_proc(VOID)
{
	INT n = 0;

	console_set_title(TEXT("Console Test 2"));
	console_set_input_event_handlers(&keyevent_eventhandler, NULL, NULL);

	for(n = 0; n < 100; n++)
	{
		console_manage_input_events();
		Sleep(100u);
	}

	console_wait_keypress(NULL);
	console_clear_text();
	return;
}

VOID WINAPI keyevent_eventhandler(KEY_EVENT_RECORD *p_eventrecord)
{
	console_stdout_write(TEXT("Key event detected\r\n"));
	return;
}