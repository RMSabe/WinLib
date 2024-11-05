/*
	Console utilities for Windows

	These utilities are based on the win32 console API.
	https://learn.microsoft.com/en-us/windows/console/console-functions

	Author: Rafael Sabe
	Email: rafaelmsabe@gmail.com
*/

#include "console.h"

HANDLE _console_stdin = INVALID_HANDLE_VALUE;
HANDLE _console_stdout = INVALID_HANDLE_VALUE;
HANDLE _console_stderr = INVALID_HANDLE_VALUE;

BOOL WINAPI console_init(VOID)
{
	_console_stdin = GetStdHandle(STD_INPUT_HANDLE);
	_console_stdout = GetStdHandle(STD_OUTPUT_HANDLE);
	_console_stderr = GetStdHandle(STD_ERROR_HANDLE);

	if((_console_stdin == INVALID_HANDLE_VALUE) || (_console_stdout == INVALID_HANDLE_VALUE) || (_console_stderr == INVALID_HANDLE_VALUE))
	{
		console_deinit();
		return FALSE;
	}

	_console_set_color(__CONSOLE_COLOR_DEFAULT);
	return TRUE;
}

VOID WINAPI console_deinit(VOID)
{
	_console_set_color(__CONSOLE_COLOR_DEFAULT);

	if(_console_stdin != INVALID_HANDLE_VALUE)
	{
		CloseHandle(_console_stdin);
		_console_stdin = INVALID_HANDLE_VALUE;
	}

	if(_console_stdout != INVALID_HANDLE_VALUE)
	{
		CloseHandle(_console_stdout);
		_console_stdout = INVALID_HANDLE_VALUE;
	}

	if(_console_stderr != INVALID_HANDLE_VALUE)
	{
		CloseHandle(_console_stderr);
		_console_stderr = INVALID_HANDLE_VALUE;
	}

	return;
}

//console.c inside function
BOOL WINAPI _console_read(HANDLE input, TCHAR *buffer, SIZE_T length)
{
	SIZE_T size = length*sizeof(TCHAR);
	DWORD n_read = 0u;

	if(input == INVALID_HANDLE_VALUE) return FALSE;
	if(buffer == NULL) return FALSE;

	if(!ReadConsole(input, buffer, (DWORD) length, &n_read, NULL)) return FALSE;

	buffer[length - 1u] = '\0';
	return TRUE;
}

//console.c inside function
BOOL WINAPI _console_write(HANDLE output, const TCHAR *text)
{
	SIZE_T len = 0u;

	if(output == INVALID_HANDLE_VALUE) return FALSE;
	if(text == NULL) return FALSE;

	while(text[len] != '\0') len++;

	return WriteConsole(output, text, len, NULL, NULL);
}

BOOL WINAPI console_stdin_read(TCHAR *buffer, SIZE_T length)
{
	return _console_read(_console_stdin, buffer, length);
}

BOOL WINAPI console_stdout_write(const TCHAR *text)
{
	return _console_write(_console_stdout, text);
}

BOOL WINAPI console_stderr_write(const TCHAR *text)
{
	return _console_write(_console_stderr, text);
}

BOOL WINAPI _console_set_color(BYTE color)
{
	CONSOLE_SCREEN_BUFFER_INFO stdout_info;
	WORD textAttr = 0u;

	if(_console_stdout == INVALID_HANDLE_VALUE) return FALSE;

	if(!GetConsoleScreenBufferInfo(_console_stdout, &stdout_info)) return FALSE;

	textAttr = stdout_info.wAttributes;
	textAttr &= 0xff00;
	textAttr |= (WORD) color;

	return SetConsoleTextAttribute(_console_stdout, textAttr);
}

INT WINAPI _console_get_color(VOID)
{
	CONSOLE_SCREEN_BUFFER_INFO stdout_info;
	BYTE color = 0u;

	if(_console_stdout == INVALID_HANDLE_VALUE) return -1;

	if(!GetConsoleScreenBufferInfo(_console_stdout, &stdout_info)) return -1;

	color = (stdout_info.wAttributes & 0xff);

	return (INT) color;
}

BOOL WINAPI console_set_foreground_color(BYTE foreground_color)
{
	CONSOLE_SCREEN_BUFFER_INFO stdout_info;
	WORD textAttr = 0u;

	if(_console_stdout == INVALID_HANDLE_VALUE) return FALSE;

	if(!GetConsoleScreenBufferInfo(_console_stdout, &stdout_info)) return FALSE;

	foreground_color &= 0xf;

	textAttr = stdout_info.wAttributes;
	textAttr &= 0xfff0;
	textAttr |= (WORD) foreground_color;

	return SetConsoleTextAttribute(_console_stdout, textAttr);
}

INT WINAPI console_get_foreground_color(VOID)
{
	INT color = _console_get_color();
	if(color < 0) return -1;

	return (color & 0xf);
}

BOOL WINAPI console_set_background_color(BYTE background_color)
{
	CONSOLE_SCREEN_BUFFER_INFO stdout_info;
	WORD textAttr = 0u;

	if(_console_stdout == INVALID_HANDLE_VALUE) return FALSE;

	if(!GetConsoleScreenBufferInfo(_console_stdout, &stdout_info)) return FALSE;

	background_color &= 0xf;
	background_color = (background_color << 4);

	textAttr = stdout_info.wAttributes;
	textAttr &= 0xff0f;
	textAttr |= (WORD) background_color;

	return SetConsoleTextAttribute(_console_stdout, textAttr);
}

INT WINAPI console_get_background_color(VOID)
{
	INT color = _console_get_color();
	if(color < 0) return -1;

	return ((color >> 4) & 0xf);
}

BOOL WINAPI console_get_title(TCHAR *buffer, SIZE_T buffer_length, SIZE_T *p_title_length)
{
	DWORD n_ret = 0u;

	if(buffer == NULL) return FALSE;

	n_ret = GetConsoleTitle(buffer, (DWORD) buffer_length);

	if(n_ret == 0u) return FALSE;

	if(p_title_length != NULL) *p_title_length = (SIZE_T) n_ret;

	if(((SIZE_T) n_ret) < (buffer_length - 1u)) buffer[n_ret] = '\0';
	else buffer[buffer_length - 1u] = '\0';

	return TRUE;
}

BOOL WINAPI console_set_title(const TCHAR *title)
{
	if(title == NULL) return FALSE;

	return SetConsoleTitle(title);
}

BOOL WINAPI console_get_current_dimensions(SHORT *p_width, SHORT *p_height)
{
	CONSOLE_SCREEN_BUFFER_INFO stdout_info;

	if(_console_stdout == INVALID_HANDLE_VALUE) return FALSE;

	if(!GetConsoleScreenBufferInfo(_console_stdout, &stdout_info)) return FALSE;

	if(p_width != NULL) *p_width = stdout_info.dwSize.X;
	if(p_height != NULL) *p_height = stdout_info.dwSize.Y;

	return TRUE;
}

INT WINAPI console_get_current_size_chars(VOID)
{
	SHORT width = 0;
	SHORT height = 0;

	if(!console_get_current_dimensions(&width, &height)) return -1;

	return ((INT) width)*((INT) height);
}

BOOL WINAPI console_get_current_window_dimensions(SHORT *p_width, SHORT *p_height)
{
	CONSOLE_SCREEN_BUFFER_INFO stdout_info;

	if(_console_stdout == INVALID_HANDLE_VALUE) return FALSE;

	if(!GetConsoleScreenBufferInfo(_console_stdout, &stdout_info)) return FALSE;

	if(p_width != NULL) *p_width = stdout_info.dwMaximumWindowSize.X;
	if(p_height != NULL) *p_height = stdout_info.dwMaximumWindowSize.Y;

	return TRUE;
}

INT WINAPI console_get_current_window_size_chars(VOID)
{
	SHORT width = 0;
	SHORT height = 0;

	if(!console_get_current_window_dimensions(&width, &height)) return -1;

	return ((INT) width)*((INT) height);
}

BOOL WINAPI console_get_cursor_position(SHORT *p_xpos, SHORT *p_ypos)
{
	CONSOLE_SCREEN_BUFFER_INFO stdout_info;

	if(_console_stdout == INVALID_HANDLE_VALUE) return FALSE;

	if(!GetConsoleScreenBufferInfo(_console_stdout, &stdout_info)) return FALSE;

	if(p_xpos != NULL) *p_xpos = stdout_info.dwCursorPosition.X;
	if(p_ypos != NULL) *p_ypos = stdout_info.dwCursorPosition.Y;

	return TRUE;
}

BOOL WINAPI console_set_cursor_position(SHORT xpos, SHORT ypos)
{
	COORD pos;
	pos.X = xpos;
	pos.Y = ypos;

	if(_console_stdout == INVALID_HANDLE_VALUE) return FALSE;

	return SetConsoleCursorPosition(_console_stdout, pos);
}

BOOL WINAPI console_fill_screen_chars(TCHAR fill_char, SHORT xstart, SHORT ystart, DWORD length_chars)
{
	DWORD filled = 0u;
	COORD pos;

	pos.X = xstart;
	pos.Y = ystart;

	if(_console_stdout == INVALID_HANDLE_VALUE) return FALSE;

	return FillConsoleOutputCharacter(_console_stdout, fill_char, length_chars, pos, &filled);
}

BOOL WINAPI _console_fill_screen_color(BYTE color, SHORT xstart, SHORT ystart, DWORD length_chars)
{
	CONSOLE_SCREEN_BUFFER_INFO stdout_info;
	DWORD filled = 0u;
	COORD pos;
	WORD textAttr = 0u;

	pos.X = xstart;
	pos.Y = ystart;

	if(_console_stdout == INVALID_HANDLE_VALUE) return FALSE;

	if(!GetConsoleScreenBufferInfo(_console_stdout, &stdout_info)) return FALSE;

	textAttr = stdout_info.wAttributes;
	textAttr &= 0xff00;
	textAttr |= (WORD) color;

	return FillConsoleOutputAttribute(_console_stdout, textAttr, length_chars, pos, &filled);
}

BOOL WINAPI console_fill_screen_color(BYTE foreground, BYTE background, SHORT xstart, SHORT ystart, DWORD length_chars)
{
	foreground &= 0xf;
	background &= 0xf;

	return _console_fill_screen_color(((background << 4) | (foreground)), xstart, ystart, length_chars);
}

BOOL WINAPI console_clear_text(VOID)
{
	if(!console_fill_screen_chars('\0', 0, 0, console_get_current_size_chars())) return FALSE;
	if(!console_set_cursor_position(0, 0)) return FALSE;

	return TRUE;
}

BOOL WINAPI console_clear_screen(VOID)
{
	if(!_console_fill_screen_color(__CONSOLE_COLOR_DEFAULT, 0, 0, console_get_current_size_chars())) return FALSE;
	if(!console_fill_screen_chars('\0', 0, 0, console_get_current_size_chars())) return FALSE;
	if(!console_set_cursor_position(0, 0)) return FALSE;

	return TRUE;
}

//console.c inside function
BOOL WINAPI _console_peek_stdin_record(INPUT_RECORD *p_input_record_struct_array, DWORD array_length, DWORD *p_structswritten)
{
	DWORD events_written = 0u;

	if(_console_stdin == INVALID_HANDLE_VALUE) return FALSE;
	if(p_input_record_struct_array == NULL) return FALSE;

	if(!PeekConsoleInput(_console_stdin, p_input_record_struct_array, array_length, &events_written)) return FALSE;

	if(p_structswritten != NULL) *p_structswritten = events_written;
	return TRUE;
}

//console.c inside function
BOOL WINAPI _console_read_stdin_record(INPUT_RECORD *p_input_record_struct_array, DWORD array_length, DWORD *p_structswritten)
{
	DWORD events_written = 0u;

	if(_console_stdin == INVALID_HANDLE_VALUE) return FALSE;
	if(p_input_record_struct_array == NULL) return FALSE;

	if(!ReadConsoleInput(_console_stdin, p_input_record_struct_array, array_length, &events_written)) return FALSE;

	if(p_structswritten != NULL) *p_structswritten = events_written;
	return TRUE;
}

BOOL WINAPI console_wait_keypress(const TCHAR *text)
{
	KEY_EVENT_RECORD *p_event = NULL;
	INPUT_RECORD input_data;
	DWORD n_events = 0u;
	BOOL loop_stop = FALSE;

	if(_console_stdin == INVALID_HANDLE_VALUE) return FALSE;

	if(text != NULL)
	{
		console_stdout_write(text);
		console_stdout_write(TEXT("\r\n"));
	}

	console_stdout_write(TEXT("Press any key to continue...\r\n"));
	FlushConsoleInputBuffer(_console_stdin);

	do{
		GetNumberOfConsoleInputEvents(_console_stdin, &n_events);

		if(n_events > 0u)
		{
			_console_read_stdin_record(&input_data, 1, NULL);
			if(input_data.EventType == KEY_EVENT)
			{
				p_event = (KEY_EVENT_RECORD*) &input_data.Event;
				if(p_event->bKeyDown)
					loop_stop = TRUE;
			}
		}

		Sleep(1u);

	}while(!loop_stop);

	return TRUE;
}

BOOL WINAPI console_check_keypress(VOID)
{
	KEY_EVENT_RECORD *p_event = NULL;
	INPUT_RECORD *p_input_data = NULL;
	DWORD n_event = 0u;
	DWORD n_events = 0u;
	BOOL key_pressed = FALSE;

	if(_console_stdin == INVALID_HANDLE_VALUE) return FALSE;

	GetNumberOfConsoleInputEvents(_console_stdin, &n_events);
	if(n_events == 0u) return FALSE;

	p_input_data = (INPUT_RECORD*) malloc(n_events*sizeof(INPUT_RECORD));

	_console_read_stdin_record(p_input_data, n_events, NULL);

	for(n_event = 0u; n_event < n_events; n_event++)
	{
		if(p_input_data[n_event].EventType == KEY_EVENT)
		{
			p_event = (KEY_EVENT_RECORD*) &p_input_data[n_event].Event;
			if(p_event->bKeyDown)
			{
				key_pressed = TRUE;
				break;
			}
		}
	}

	if(p_input_data != NULL)
	{
		free(p_input_data);
		p_input_data = NULL;
		p_event = NULL;
	}

	return key_pressed;
}
