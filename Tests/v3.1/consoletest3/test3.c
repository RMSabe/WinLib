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
	const BYTE BACKGROUND_COLOR = CONSOLE_COLOR_RED;
	const BYTE BORDER_BACKGROUND_COLOR = CONSOLE_COLOR_BLUE;
	const BYTE BORDER_FOREGROUND_COLOR = CONSOLE_COLOR_WHITE;
	const BYTE TEXT_BACKGROUND_COLOR = CONSOLE_COLOR_BLACK;
	const BYTE TEXT_FOREGROUND_COLOR = CONSOLE_COLOR_GREEN;

	SHORT width = 0;
	SHORT height = 0;
	SHORT center_x = 0;
	SHORT center_y = 0;

	console_set_title(TEXT("Console Test 3"));
	console_clear_text();

	console_get_current_window_dimensions(&width, &height);
	center_x = width/2;
	center_y = height/2;

	console_fill_screen_color(0, BACKGROUND_COLOR, 0, 0, console_get_current_size_chars());

	console_fill_screen_color(BORDER_FOREGROUND_COLOR, BORDER_BACKGROUND_COLOR, 0, (center_y - 5), width);
	console_fill_screen_color(BORDER_FOREGROUND_COLOR, BORDER_BACKGROUND_COLOR, 0, (center_y - 4), width);
	console_fill_screen_color(BORDER_FOREGROUND_COLOR, BORDER_BACKGROUND_COLOR, 0, (center_y - 3), 2);
	console_fill_screen_color(BORDER_FOREGROUND_COLOR, BORDER_BACKGROUND_COLOR, 0, (center_y - 2), 2);
	console_fill_screen_color(BORDER_FOREGROUND_COLOR, BORDER_BACKGROUND_COLOR, (width - 2), (center_y - 3), 2);
	console_fill_screen_color(BORDER_FOREGROUND_COLOR, BORDER_BACKGROUND_COLOR, (width - 2), (center_y - 2), 2);
	console_fill_screen_color(BORDER_FOREGROUND_COLOR, BORDER_BACKGROUND_COLOR, 0, (center_y - 1), 2);
	console_fill_screen_color(BORDER_FOREGROUND_COLOR, BORDER_BACKGROUND_COLOR, 0, center_y, 2);
	console_fill_screen_color(BORDER_FOREGROUND_COLOR, BORDER_BACKGROUND_COLOR, (width - 2), (center_y - 1), 2);
	console_fill_screen_color(BORDER_FOREGROUND_COLOR, BORDER_BACKGROUND_COLOR, (width - 2), center_y, 2);
	console_fill_screen_color(BORDER_FOREGROUND_COLOR, BORDER_BACKGROUND_COLOR, 0, (center_y + 1), 2);
	console_fill_screen_color(BORDER_FOREGROUND_COLOR, BORDER_BACKGROUND_COLOR, 0, (center_y + 2), 2);
	console_fill_screen_color(BORDER_FOREGROUND_COLOR, BORDER_BACKGROUND_COLOR, (width - 2), (center_y + 1), 2);
	console_fill_screen_color(BORDER_FOREGROUND_COLOR, BORDER_BACKGROUND_COLOR, (width - 2), (center_y + 2), 2);
	console_fill_screen_color(BORDER_FOREGROUND_COLOR, BORDER_BACKGROUND_COLOR, 0, (center_y + 3), 2);
	console_fill_screen_color(BORDER_FOREGROUND_COLOR, BORDER_BACKGROUND_COLOR, 0, (center_y + 4), 2);
	console_fill_screen_color(BORDER_FOREGROUND_COLOR, BORDER_BACKGROUND_COLOR, (width - 2), (center_y + 3), 2);
	console_fill_screen_color(BORDER_FOREGROUND_COLOR, BORDER_BACKGROUND_COLOR, (width - 2), (center_y + 4), 2);
	console_fill_screen_color(BORDER_FOREGROUND_COLOR, BORDER_BACKGROUND_COLOR, 0, (center_y + 5), width);
	console_fill_screen_color(BORDER_FOREGROUND_COLOR, BORDER_BACKGROUND_COLOR, 0, (center_y + 6), width);

	console_fill_screen_chars((TCHAR) '@', 0, (center_y - 5), width);
	console_fill_screen_chars((TCHAR) '@', 0, (center_y - 4), width);
	console_fill_screen_chars((TCHAR) '@', 0, (center_y - 3), 2);
	console_fill_screen_chars((TCHAR) '@', 0, (center_y - 2), 2);
	console_fill_screen_chars((TCHAR) '@', (width - 2), (center_y - 3), 2);
	console_fill_screen_chars((TCHAR) '@', (width - 2), (center_y - 2), 2);
	console_fill_screen_chars((TCHAR) '@', 0, (center_y - 1), 2);
	console_fill_screen_chars((TCHAR) '@', 0, center_y, 2);
	console_fill_screen_chars((TCHAR) '@', (width - 2), (center_y - 1), 2);
	console_fill_screen_chars((TCHAR) '@', (width - 2), center_y, 2);
	console_fill_screen_chars((TCHAR) '@', 0, (center_y + 1), 2);
	console_fill_screen_chars((TCHAR) '@', 0, (center_y + 2), 2);
	console_fill_screen_chars((TCHAR) '@', (width - 2), (center_y + 1), 2);
	console_fill_screen_chars((TCHAR) '@', (width - 2), (center_y + 2), 2);
	console_fill_screen_chars((TCHAR) '@', 0, (center_y + 3), 2);
	console_fill_screen_chars((TCHAR) '@', 0, (center_y + 4), 2);
	console_fill_screen_chars((TCHAR) '@', (width - 2), (center_y + 3), 2);
	console_fill_screen_chars((TCHAR) '@', (width - 2), (center_y + 4), 2);
	console_fill_screen_chars((TCHAR) '@', 0, (center_y + 5), width);
	console_fill_screen_chars((TCHAR) '@', 0, (center_y + 6), width);

	console_fill_screen_color(TEXT_FOREGROUND_COLOR, TEXT_BACKGROUND_COLOR, 4, (center_y - 1), (width - 8));
	console_fill_screen_color(TEXT_FOREGROUND_COLOR, TEXT_BACKGROUND_COLOR, 4, center_y, (width - 8));
	console_fill_screen_color(TEXT_FOREGROUND_COLOR, TEXT_BACKGROUND_COLOR, 4, (center_y + 1), (width - 8));
	console_fill_screen_color(TEXT_FOREGROUND_COLOR, TEXT_BACKGROUND_COLOR, 4, (center_y + 2), (width - 8));

	console_set_foreground_color(TEXT_FOREGROUND_COLOR);
	console_set_background_color(TEXT_BACKGROUND_COLOR);

	console_set_cursor_position(4, (center_y - 1));
	console_stdout_write(TEXT("This is line 00"));
	console_set_cursor_position(4, center_y);
	console_stdout_write(TEXT("This is line 01"));
	console_set_cursor_position(4, (center_y + 1));
	console_stdout_write(TEXT("This is line 02"));
	console_set_cursor_position(4, (center_y + 2));
	console_stdout_write(TEXT("This is line 03"));

	Sleep(16384);

	console_clear_text();
	console_wait_keypress(NULL);
	return;
}
