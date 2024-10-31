// This is a Win32API based Windows GUI application written in C++ that converts EPOCH time to regular human readable timestamps

// Existing header files
#include<windows.h>
#include<tchar.h>

// Used for Combobox 
#include<CommCtrl.h>

// User defined header files
#include "fe_main.h"
#include"app_defs.h"
#include "resource.h"
#include "time_conv.h"

// Global variable declarations
bool epoch_1980 = false;
HWND textbox, screen1, screen2, convert, clear, quit, static_op_def_text, combo_box;
HMENU h_menu;
wchar_t tb_input[100] = L" ";
wchar_t * op_string1 = NULL;
wchar_t * op_string2 = NULL;
char timestamp_op[100], IST_time[100], UTC_time[100];



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

        switch (HIWORD(wparam))
        {
        case CBN_SELCHANGE:
        {
            int item_index = SendMessage((HWND)lparam, CB_GETCURSEL, 0, 0);
            TCHAR list_item[50];
            SendMessage((HWND)lparam, CB_GETLBTEXT, item_index, (LPARAM)list_item);

            if (!_wcsicmp(list_item, _T("EPOCH 1980")))
                epoch_1980 = true;
            else
                epoch_1980 = false;
        }
        break;

        default: break;
        }

        switch (wparam)
        {
        case MENU_ABOUT:
        {
            MessageBeep(MB_OK);
            MessageBoxW(hwnd, L"     ForkEPOCH V1.0     \n     2024 (c) Forktail", L"About", NULL);
        }
        break;

        case BTN_CONVERT:
        {
            //Read the input from the textbox typed by the user
            int text_returend = GetWindowText(textbox, tb_input, 20);
            // Converting the EPOCH input given by user into a time format
            time_t tm = _wtoi(tb_input);
            if (epoch_1980 == true)
                EPOCH1970ToNormal(&tm, timestamp_op, UTC_time, IST_time);
            else
                EPOCH1970ToNormal(&tm, timestamp_op, UTC_time, IST_time);

            op_string1 = CharToWchar(UTC_time);
            op_string2 = CharToWchar(IST_time);
        }break;

        case BTN_CLR:
        {
            wchar_t clear[] = L" ";
            op_string1 = clear;
            op_string2 = clear;
            SetWindowText(textbox, op_string1);
            SetWindowText(screen1, op_string1);
            SetWindowText(screen2, op_string1);
        } break;

        case BTN_QUIT:
        {

        }break;


        }break;


        /*case BTN_QUIT:
        {
            PostQuitMessage(0);
            break;
        }*/


    }



    case WM_CREATE:
    {
        AddMenus(hwnd);
        Buttons(hwnd);
        Screen(hwnd);
        Textbox(hwnd);
        break;
    }

    default:
        return DefWindowProc(hwnd, msg, wparam, lparam);
    }
    
    return 0;
}
// A function that does all display screen / output procedures
void Screen(HWND screen_handler)
{
    screen1 = CreateWindowEx(0,L"EDIT", op_string1, WS_CHILDWINDOW | WS_VISIBLE | WS_BORDER | SS_LEFT, 5, 25, 370, 50, screen_handler, NULL, NULL, NULL);
    screen2 = CreateWindowEx(0, L"EDIT", op_string2, WS_CHILDWINDOW | WS_VISIBLE | WS_BORDER | SS_LEFT, 5, 75, 370, 50, screen_handler, NULL, NULL, NULL);

}

//A function to display buttons on the window
void Buttons(HWND btn_handler)
{
    convert = CreateWindowEx(0, L"BUTTON", L"Convert", WS_CHILD | WS_VISIBLE | WS_BORDER, 5, 190, 250, 40, btn_handler, (HMENU)3, NULL, NULL);
    
    clear = CreateWindowEx(0, L"BUTTON", L"Clear", WS_CHILD | WS_VISIBLE | WS_BORDER, 265, 190, 50, 40, btn_handler, (HMENU)4, NULL, NULL);

    quit = CreateWindowEx(0, L"BUTTON", L"Quit", WS_CHILD | WS_VISIBLE | WS_BORDER, 320, 190, 50, 40, btn_handler, (HMENU)7, NULL, NULL);

}

// A function to add the textboxes required
void Textbox(HWND txtbx_handler)
{
    // To display the header for the Output format
    static_op_def_text = CreateWindow(L"STATIC", L"O/P: Day YYYY-MM-DD HH:MM:SS DD/MM/YYYY HH:MM:SS Zone", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_LEFT, 5, 5, 370, 20, txtbx_handler, NULL, NULL, NULL);
    // Creating a font attribute to give ot he above static text
    HFONT h_font = CreateFont(15, 0 , 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE,ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PALETTE | FF_SWISS, L"Arial");
    // Attach the font to the above static text
    SendMessage(static_op_def_text, WM_SETFONT, WPARAM(h_font), TRUE);
    
    // This text box is the input textbox in which the user will insert the input EPOCH time.
    textbox = CreateWindow(L"EDIT", tb_input, WS_VISIBLE| WS_CHILD| WS_BORDER, 120, 140, 250, 25, txtbx_handler, NULL, NULL, NULL);
    SendMessage(textbox, WM_SETFONT, WPARAM(h_font), TRUE);

    int k = 0;
    // To create a selecton combo box
    combo_box = CreateWindow(WC_COMBOBOX, TEXT(" "), CBS_DROPDOWN | WS_VISIBLE | WS_CHILD, 5, 140, 110, 60, txtbx_handler, (HMENU)IDC_COMBOBOX_TEXT,(HINSTANCE) GetWindowLong(txtbx_handler, GWL_INSTANCE),NULL );
    SendMessage(combo_box, WM_SETFONT, WPARAM(h_font), TRUE);
    
    //To assign selectable values
    TCHAR time_formats[3][12] = { TEXT("EPOCH 1970"), TEXT("EPOCH 1980")};

    //A string for storing the selection
    TCHAR selected_format[16];
    memset(&selected_format,0, sizeof(selected_format));
    for (k = 0; k < 2; k++)
    {
        wcscpy_s(selected_format, sizeof(selected_format)/sizeof(TCHAR), (TCHAR*) time_formats[k]);
        //Sending a message CB_ADDSTRING to tell the window to add the string.
        SendMessage(combo_box,(UINT) CB_ADDSTRING,(WPARAM) 0, (LPARAM) selected_format);
    }
    SendMessage(combo_box, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);

    
}


// A fuction that adds menus to the main window
void AddMenus(HWND hwnd)
{
    h_menu = CreateMenu();
    AppendMenuW(h_menu, MF_STRING, MENU_ABOUT ,L"About");
    SetMenu(hwnd, h_menu);
}

static wchar_t* CharToWchar(const char* text)
{
    const size_t size = strlen(text) + 1;
    wchar_t* w_text = new wchar_t[size];
    mbstowcs(w_text, text, size);
    return w_text;
}