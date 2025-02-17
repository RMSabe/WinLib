#include "globldef.h"
#include "cstrdef.h"
#include "console.h"

extern BOOL WINAPI app_init(VOID);
extern VOID WINAPI app_deinit(VOID);

extern VOID WINAPI test_proc(VOID);

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
	INT n_events_remaining = 10;

	console_set_title(TEXT("Console Test 4"));

	while(n_events_remaining >= 0)
	{
		__SPRINTF(textbuf, TEXTBUF_SIZE_CHARS, TEXT("%d 'CTRL' keydown events remaining\r\n"), n_events_remaining);
		console_stdout_write(textbuf);
		Sleep(250);
		if(console_get_specific_key_pressed(VK_CONTROL))
		{
			console_stdout_write(TEXT("'CTRL' Key pressed!!!\r\n"));
			n_events_remaining--;
		}
	}

	console_wait_keypress(NULL);
	console_clear_text();
	return;
}
