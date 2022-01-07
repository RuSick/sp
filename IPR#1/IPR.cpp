// IPR1.cpp /95350040 - 4 draft : Defines the entry point for the application.
//

#include "framework.h"
#include "IPR.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
WCHAR buffer[MAX_LOADSTRING];
WCHAR buffer1[MAX_LOADSTRING];
HWND listbox1, listbox2, edit1;
int num, number;
int indexes[MAX_LOADSTRING];

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_IPR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_IPR));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_IPR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_IPR);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
   CreateWindowEx(NULL, L"STATIC", L"Edit:", WS_VISIBLE | WS_CHILD, 810, 10, 150, 20, hWnd, NULL, hInstance, NULL);
   CreateWindowEx(NULL, L"BUTTON", L"Add", WS_VISIBLE | WS_CHILD | WS_BORDER, 5, 5, 100, 20, hWnd, (HMENU)1001, hInstance, NULL);
   CreateWindowEx(NULL, L"BUTTON", L"Clear", WS_VISIBLE | WS_CHILD | WS_BORDER, 115, 5, 100, 20, hWnd, (HMENU)1002, hInstance, NULL);
   CreateWindowEx(NULL, L"BUTTON", L"ToRight", WS_VISIBLE | WS_CHILD | WS_BORDER, 225, 5, 100, 20, hWnd, (HMENU)1003, hInstance, NULL);
   CreateWindowEx(NULL, L"BUTTON", L"Delete", WS_VISIBLE | WS_CHILD | WS_BORDER, 335, 5, 100, 20, hWnd, (HMENU)1004, hInstance, NULL);
   listbox1 = CreateWindowEx(NULL, L"LISTBOX", L"lstbox1", WS_VISIBLE | WS_CHILD | WS_BORDER | LBS_EXTENDEDSEL | LBS_STANDARD, 10, 40, 200, 200, hWnd, NULL, hInstance, NULL);
   listbox2 = CreateWindowEx(NULL, L"LISTBOX", L"lstbox2", WS_VISIBLE | WS_CHILD | WS_BORDER | LBS_EXTENDEDSEL | LBS_STANDARD, 310, 40, 200, 200, hWnd, NULL, hInstance, NULL);
   edit1 = CreateWindowEx(NULL, L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, 610, 40, 150, 20, hWnd, NULL, hInstance, NULL);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case 1001://add
                if (SendMessage(edit1, WM_GETTEXT, sizeof(buffer), (LPARAM)buffer))
                {
                    number = SendMessage(listbox1, LB_GETCOUNT, 0, 0);
                    if (number)	
                        for (int i = 0; i < number; i++)
                        {
                            SendMessage(listbox1, LB_GETTEXT, i, (LPARAM)buffer1);
                            if (wcscmp(buffer, buffer1) == 0)
                                break;
                            else if (i == number - 1)
                            {
                                SendMessage(listbox1, LB_INSERTSTRING, 0, (LPARAM)buffer);
                                break;
                            }
                        }
                    else
                        SendMessage(listbox1, LB_INSERTSTRING, 0, (LPARAM)buffer);
                }
                break;
            case 1002://clear
                SendMessage(listbox1, LB_RESETCONTENT, 0, 0);
                SendMessage(listbox2, LB_RESETCONTENT, 0, 0);
                break;
            case 1003://to right
                if (SendMessage(listbox1, LB_GETSELITEMS, sizeof(indexes), (LPARAM)indexes))
                {
                    SendMessage(listbox1, LB_GETTEXT, indexes[0], (LPARAM)buffer);
                    number = SendMessage(listbox2, LB_GETCOUNT, 0, 0);
                    if (number)
                        for (int i = 0; i < number; i++)
                        {
                            SendMessage(listbox2, LB_GETTEXT, i, (LPARAM)buffer1);
                            if (wcscmp(buffer, buffer1) == 0)
                                break;
                            else if (i == number - 1)
                            {
                                SendMessage(listbox2, LB_INSERTSTRING, 0, (LPARAM)buffer);
                                break;
                            }
                        }
                    else
                        SendMessage(listbox2, LB_INSERTSTRING, 0, (LPARAM)buffer);
                }
                break;
            case 1004://delete
                if (num = SendMessage(listbox1, LB_GETSELITEMS, sizeof(indexes), (LPARAM)indexes))
                    while (num)
                        SendMessage(listbox1, LB_DELETESTRING, indexes[--num], 0);
                if (num = SendMessage(listbox2, LB_GETSELITEMS, sizeof(indexes), (LPARAM)indexes))
                    while (num)
                        SendMessage(listbox2, LB_DELETESTRING, indexes[--num], 0);
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
