#include <windows.h>
#include <shellapi.h>

#define IDT_TIMER1 0
#define IDC_STATIC_TEXT 1
#define IDC_STATIC_ICON 2
#define IDC_OK_BUTTON 3

int dx = 5, dy = 5;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch (msg)
  {
  case WM_CLOSE:
    DestroyWindow(hwnd);
    break;
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  case WM_CREATE:
  {
    // Create the static text control
    CreateWindowEx(0, "STATIC", "Task failed successfully.", WS_CHILD | WS_VISIBLE | SS_CENTER, 30, 40, 300, 30, hwnd, (HMENU)IDC_STATIC_TEXT, NULL, NULL);

    // Create the static icon control
    HICON hInfoIcon = LoadIcon(NULL, IDI_INFORMATION);
    CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_ICON, 40, 30, 30, 30, hwnd, (HMENU)IDC_STATIC_ICON, NULL, NULL);
    SendMessage(GetDlgItem(hwnd, IDC_STATIC_ICON), STM_SETICON, (WPARAM)hInfoIcon, 0);

    // Create the OK button
    CreateWindowEx(0, "BUTTON", "OK", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 100, 95, 100, 30, hwnd, (HMENU)IDC_OK_BUTTON, NULL, NULL);
  }
  break;
  case WM_COMMAND:
  {
    if (LOWORD(wParam) == IDC_OK_BUTTON)
    {
      DestroyWindow(hwnd);
    }
  }
  break;
  case WM_TIMER:
  {
    RECT rect;
    GetWindowRect(hwnd, &rect);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    HMONITOR hmon = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi = {sizeof(mi)};
    GetMonitorInfo(hmon, &mi);

    RECT desktopRect = mi.rcWork;

    if (rect.left + dx < desktopRect.left || rect.right + dx > desktopRect.right)
      dx = -dx;
    if (rect.top + dy < desktopRect.top || rect.bottom + dy > desktopRect.bottom)
      dy = -dy;

    SetWindowPos(hwnd, HWND_TOP, rect.left + dx, rect.top + dy, width, height, SWP_SHOWWINDOW);
  }
  break;
  default:
    return DefWindowProc(hwnd, msg, wParam, lParam);
  }
  return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  const char CLASS_NAME[] = "FunnyErrorWindow";

  // Parse command line arguments
  int argc;
  LPWSTR *argv = CommandLineToArgvW(GetCommandLineW(), &argc);
  if (argv)
  {
    for (int i = 0; i < argc; i++)
    {
      if (wcscmp(argv[i], L"--speed") == 0 && i + 1 < argc)
      {
        dx = dy = _wtoi(argv[i + 1]);
      }
    }
    LocalFree(argv);
  }

  WNDCLASS wc = {};

  wc.lpfnWndProc = WndProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = CLASS_NAME;
  wc.hIcon = LoadIcon(NULL, IDI_ERROR);

  RegisterClass(&wc);

  HWND hwnd = CreateWindowEx(0, CLASS_NAME, "Error", WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 300, 175, NULL, NULL, hInstance, NULL);

  if (hwnd == NULL)
  {
    return 0;
  }

  ShowWindow(hwnd, nCmdShow);
  UpdateWindow(hwnd);

  SetTimer(hwnd, IDT_TIMER1, 10, (TIMERPROC)NULL);

  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}