#include <windows.h>

#define MAX_BUF     255


BOOL CALLBACK TargetWindowEnumChildProc(HWND hwnd, LPARAM lParam);

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PWSTR pCmdLine,
    int nCmdShow)
{
    HWND hTargetWindow = FindWindow(
        NULL,
        TEXT("Toggle my Checkbox (please)"));

    if (hTargetWindow == NULL) {
        MessageBox(
            NULL,
            TEXT("Could not find the target window. "
                 "Maybe you should launch it?"),
            TEXT("OooOops!"),
            MB_OK | MB_ICONWARNING
        );
        ExitProcess(-1);
    }

    EnumChildWindows(
        hTargetWindow,
        TargetWindowEnumChildProc,
        0);

    return 0;
}

BOOL CALLBACK TargetWindowEnumChildProc(HWND hwnd, LPARAM lParam) {
    CHAR cClassName[MAX_BUF] = {'\0'}; // Hope this is enough...
    LONG lWindowStyle = 0;

    GetClassName(hwnd, cClassName, MAX_BUF - 1);

    if (strcmp(cClassName, "Button") == 0) {
        // It's a match! Check that it is a checkbox

        lWindowStyle = GetWindowLong(hwnd, GWL_STYLE);

        if (lWindowStyle & BS_CHECKBOX) {
            // It is a checkbox: uncheck it. :D
            SendMessage(
                hwnd,
                BM_SETCHECK,
                BST_UNCHECKED,
                0);

            MessageBox(
                NULL,
                TEXT("I have unchecked this unwanted damn checkbox!"),
                TEXT("Rock'n'roll!"),
                MB_OK | MB_ICONINFORMATION
            );
        }
    }

    return TRUE;
}
