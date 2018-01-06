#include <windows.h>

#define ID_CHECKBOX_TOGGLEME    1

LRESULT CALLBACK MainWindowProc(HWND hwnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   PWSTR pCmdLine, int nCmdShow)
{

    const LPCTSTR szClassName = TEXT("MainWindow");
    HWND hMainWindow = INVALID_HANDLE_VALUE;

    WNDCLASS wndClsMainWindowClass = {
        .style = 0,
        .lpfnWndProc = MainWindowProc,
        .cbClsExtra = 0,
        .cbWndExtra = 0,
        .hInstance = hInstance,
        .hIcon = NULL,
        .hbrBackground = COLOR_WINDOW,
        .lpszMenuName = NULL,
        .lpszClassName = szClassName
    };

    if (RegisterClass(&wndClsMainWindowClass) == 0) {
        MessageBox(
            NULL,
            TEXT("Could not register class."),
            TEXT("Error"),
            MB_OK | MB_ICONERROR);
        ExitProcess(-1);
    }

    hMainWindow = CreateWindow(
        szClassName,
        TEXT("Toggle my Checkbox (please)"),
        WS_OVERLAPPEDWINDOW | WS_VISIBLE, // style
        CW_USEDEFAULT, // x
        CW_USEDEFAULT, // y
        CW_USEDEFAULT, // width
        CW_USEDEFAULT, // height
        NULL, // parent
        NULL, // menu
        hInstance,
        NULL,
    );

    if (hMainWindow == INVALID_HANDLE_VALUE) {
        MessageBox(
            NULL,
            TEXT("Error"),
            TEXT("Could not create window."),
            MB_OK | MB_ICONERROR
        );
        ExitProcess(-1);
    }

    ShowWindow(hMainWindow, nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK MainWindowProc(HWND hwnd,
                                UINT message,
                                WPARAM wParam,
                                LPARAM lParam) 
{
    
    BOOL checked = FALSE;
    
    switch (message) {
    case WM_CREATE:
        CreateWindow(
            TEXT("BUTTON"),
            TEXT("Install some uselessware on this computer, with a lot of "
                 "annoying advertisements."),
            WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
            20, 20, 600, 35,
            hwnd,
            (HMENU)ID_CHECKBOX_TOGGLEME,
            ((LPCREATESTRUCT)lParam)->hInstance,
            NULL);
            CheckDlgButton(hwnd, ID_CHECKBOX_TOGGLEME, BST_CHECKED);
       
        break;

    case WM_COMMAND:
        checked = IsDlgButtonChecked(hwnd, ID_CHECKBOX_TOGGLEME);
        if (checked) {
            CheckDlgButton(hwnd, ID_CHECKBOX_TOGGLEME, BST_UNCHECKED);
        }
        else {
            CheckDlgButton(hwnd, ID_CHECKBOX_TOGGLEME, BST_CHECKED);
        }
        break;


    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);;
}