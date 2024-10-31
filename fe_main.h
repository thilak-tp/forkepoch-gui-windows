
#pragma once
LRESULT WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
void AddMenus(HWND hwnd);
void Screen(HWND screen_handler);
void Buttons(HWND btn_handler);
void Textbox(HWND txtbx_handler);
static wchar_t* CharToWchar(const char* text);