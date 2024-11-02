#include <windows.h>
#include <shellapi.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>

#define IDT_TIMER1 0
#define IDC_STATIC_TEXT 1
#define IDC_STATIC_ICON 2
#define IDC_OK_BUTTON 3
#define VERSION "1.6"

int dx = 5, dy = 5;
bool rainbow = false;
wchar_t textString[] = L"Task failed successfully.";

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  static HBRUSH hBrush = NULL;

  switch (msg)
  {
  case WM_CLOSE:
    DestroyWindow(hwnd);
    break;
  case WM_DESTROY:
  {
    if (hBrush != NULL)
    {
      DeleteObject(hBrush);
    }

    KillTimer(hwnd, IDT_TIMER1);

    PostQuitMessage(0);
  }
  break;
  case WM_CREATE:
  {
    CreateWindowExW(0, L"STATIC", textString, WS_CHILD | WS_VISIBLE | SS_CENTER, 30, 40, 300, 30, hwnd, (HMENU)IDC_STATIC_TEXT, NULL, NULL);

    HICON hInfoIcon = LoadIcon(NULL, IDI_INFORMATION);
    CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_ICON, 40, 30, 30, 30, hwnd, (HMENU)IDC_STATIC_ICON, NULL, NULL);
    SendMessage(GetDlgItem(hwnd, IDC_STATIC_ICON), STM_SETICON, (WPARAM)hInfoIcon, 0);

    CreateWindowEx(0, "BUTTON", "OK", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 100, 95, 100, 30, hwnd, (HMENU)IDC_OK_BUTTON, NULL, NULL);

    SetTimer(hwnd, IDT_TIMER1, 10, NULL);
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
  case WM_CTLCOLORSTATIC:
  {
    HDC hdcStatic = (HDC)wParam;
    SetBkMode(hdcStatic, TRANSPARENT);
    if (rainbow)
      return (LRESULT)GetStockObject(NULL_BRUSH);
    else
      return (LRESULT)GetStockObject(WHITE_BRUSH);
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
    {
      dx = -dx;
      if (rainbow)
      {
        if (hBrush != NULL)
        {
          DeleteObject(hBrush);
        }
        hBrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
        SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)hBrush);
        InvalidateRect(hwnd, NULL, TRUE);
      }
    }
    if (rect.top + dy < desktopRect.top || rect.bottom + dy > desktopRect.bottom)
    {
      dy = -dy;
      if (rainbow)
      {
        if (hBrush != NULL)
        {
          DeleteObject(hBrush);
        }
        hBrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
        SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)hBrush);
        InvalidateRect(hwnd, NULL, TRUE);
      }
    }

    SetWindowPos(hwnd, HWND_TOP, rect.left + dx, rect.top + dy, width, height, SWP_SHOWWINDOW);
  }
  break;
  default:
    return DefWindowProc(hwnd, msg, wParam, lParam);
  }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  const char CLASS_NAME[] = "BouncyErrorWindow";

  int speed = 5;

  int argc;
  LPWSTR *argv = CommandLineToArgvW(GetCommandLineW(), &argc);
  if (argv)
  {
    for (int i = 0; i < argc; i++)
    {
      if (wcscmp(argv[i], L"--speed") == 0 && i + 1 < argc)
      {
        speed = _wtoi(argv[i + 1]);
      }
      else if (wcscmp(argv[i], L"--rainbow") == 0)
      {
        rainbow = true;
      }
      else if (wcscmp(argv[i], L"--msg") == 0)
      {
        textString[0] = '\0';
        for (int j = i + 1; j < argc; j++)
        {
          char temp[256];
          wcstombs(temp, argv[j], sizeof(temp));

          for (int k = 0; temp[k] != '\0'; k++)
          {
            if (temp[k] == '\\' && temp[k + 1] == 'n')
            {
              if (k > 0 && temp[k - 1] == ' ')
              {
                memmove(&temp[k - 1], &temp[k], strlen(temp) - k);
              }

              temp[k] = '\n';
              memmove(&temp[k + 1], &temp[k + 2], strlen(temp) - k - 1);
            }
          }

          wchar_t wideTemp[256];
          MultiByteToWideChar(CP_UTF8, 0, temp, -1, wideTemp, 256);
          wcscat(textString, wideTemp);
          if (j < argc - 1)
          {
            wcscat(textString, L" ");
          }
        }
        break;
      }
      else if (wcscmp(argv[i], L"--version") == 0)
      {
        char message[256];
        sprintf(message, "BouncyError v%s", VERSION);
        MessageBox(NULL, message, "Version", MB_OK);
        return 0;
      }
      else if (wcscmp(argv[i], L"--author") == 0)
      {
        MessageBox(NULL, "Max Reinartz", "Author", MB_OK);
        return 0;
      }
      else if (wcscmp(argv[i], L"--help") == 0)
      {
        char message[1024];
        sprintf(message, "Usage: [--speed <speed>] [--fun] [--msg <message>] [--version] [--license] [--author] [--lang <language_code>] [--help]\n"
                         "Options:\n"
                         "  --speed <speed>         Set the speed of the window\n"
                         "  --rainbow               Enable Rainbow mode\n"
                         "  --msg <message>         Set the message of the window\n"
                         "  --version               Display the version information\n"
                         "  --author                Display the author\n"
                         "  --help                  Display this help message\n");
        MessageBox(NULL, message, "Help", MB_OK);
        return 0;
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

  srand(time(NULL));
  RECT workArea;
  SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0);

  int screenWidth = workArea.right - workArea.left - 300;
  int screenHeight = workArea.bottom - workArea.top - 175;

  int startX = workArea.left + rand() % screenWidth;
  int startY = workArea.top + rand() % screenHeight;

  dx = (rand() % 2 == 0) ? speed : -speed;
  dy = (rand() % 2 == 0) ? speed : -speed;

  HWND hwnd = CreateWindowEx(0, CLASS_NAME, "Error", WS_CAPTION | WS_SYSMENU, startX, startY, 300, 175, NULL, NULL, hInstance, NULL);

  if (hwnd == NULL)
  {
    return 0;
  }

  ShowWindow(hwnd, nCmdShow);
  UpdateWindow(hwnd);

  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}