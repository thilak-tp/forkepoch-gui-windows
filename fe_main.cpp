#include<windows.h>

int WINAPI CALLBACK WinMain( HINSTANCE h_instance, HINSTANCE h_prev_instance, LPSTR cmd_line, int cmd_show)
{
    const wchar_t class_name[] = L"ForkEPOCH";

    WNDCLASSEX wc = {};
    wc.hbrBackground = CreateSolidBrush(RGB(64, 64, 64));
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = h_instance;
    wc.lpszClassName = class_name;
    wc.lpfnWndProc = wndProc;



    
}