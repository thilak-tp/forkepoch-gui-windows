// This is a Win32API based Windows GUI application written in C++ that converts EPOCH time to regular human readable timestamps

// Existing header files
#include<windows.h>
#include<tchar.h>

// User defined header files
#include "fe_main.h"
#include"app_defs.h"
#include "resource.h"

// Global variable declarations
bool epoch_1980 = false;
HWND textbox;
HMENU h_menu;
wchar_t tb_input[100];


// Execution of the program starts from the WinMain function
int WINAPI CALLBACK WinMain( _In_ HINSTANCE h_instance, _In_opt_ HINSTANCE h_prev_instance, _In_ LPSTR cmd_line, _In_ int cmd_show)
{
    // We define a class name, this would be used for the window name and so on afterwards.
    const wchar_t class_name[] = L"ForkEPOCH - EPOCH Time Convertor";

    //We populate the window class with appropriate data as per the basic characteristics that we need for our main window.
    WNDCLASSEX wc = {};

    //This sets the background color of the window
    wc.hbrBackground = CreateSolidBrush(RGB(64, 64, 64));
    // This sets the cursor type in the window, you can change IDC arrow to any other predefined cursor style to change according to your needs
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    // Handle to the instance that contains the window procedure for the class
    wc.hInstance = h_instance;
    // It specifies the window class name
    wc.lpszClassName = class_name;
    // Pointer to the window procedure function  that interprets the window msgs
    wc.lpfnWndProc = WndProc;
    // Specifies the class size, set to size of WNDCLASSEX
    wc.cbSize = sizeof(WNDCLASSEX);
    // This specifies the style of windows, CS_HREDRAW and CS_VREDRAW redraws the window if the user changes the window dimensions
    wc.style = CS_HREDRAW | CS_VREDRAW;
    // Can be used to load the icon for the application
    wc.hIcon = LoadIcon(wc.hInstance, MAKEINTRESOURCE(IDI_ICON2));
    wc.lpszMenuName = NULL;

    // The above class is resigtered
    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, _T("Window Class Registration Failed"), _T("Error"), NULL);
        return FAILURE;
    }
    // This creates the actual visible window.
    HWND hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, class_name, class_name, WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 400, 300, NULL, NULL, h_instance, NULL);
    if (!hwnd)
    {
        MessageBox(NULL, _T("WIndows Creation Failed"), _T("Error"), NULL);
        return FAILURE;
    }

    ShowWindow(hwnd, cmd_show);
    UpdateWindow(hwnd);


    //Message loop to handle messages that windows sends
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return SUCCESS;

    
}


// A window procedure function catches messages from the windows so that we can handle these messages appropriately
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {
    case WM_COMMAND:
    {
        switch (wparam)
        {
        case MENU_ABOUT: 
            MessageBeep(MB_OK);
            MessageBoxW(hwnd, L"     ForkEPOCH V1.0     \n     2024 (c) Forktail",L"About", NULL);
        }

    
    }
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_CREATE:
        AddMenus(hwnd);
        break;

    default:
        return DefWindowProc(hwnd, msg, wparam, lparam);
    }
    return 0;
}

void AddMenus(HWND hwnd)
{
    h_menu = CreateMenu();
    AppendMenuW(h_menu, MF_STRING, MENU_ABOUT ,L"About");
    SetMenu(hwnd, h_menu);
}