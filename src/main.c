#include <windows.h>
#include <shellapi.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include "lang.h"

#define IDT_TIMER1 0
#define IDC_STATIC_TEXT 1
#define IDC_STATIC_ICON 2
#define IDC_OK_BUTTON 3
#define VERSION "1.51 (BUGFIX)"

int dx = 5, dy = 5;
bool funMode = false;
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
    if (funMode)
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
      if (funMode)
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
      if (funMode)
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
  const char CLASS_NAME[] = "FunnyErrorWindow";

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
      else if (wcscmp(argv[i], L"--fun") == 0)
      {
        funMode = true;
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
      else if (wcscmp(argv[i], L"--license") == 0)
      {
        char message[2048];
        sprintf(message, "Creeper76's Software License\n\nCopyright (c) 2024 Creeper76\n\n"
                         "Permission is hereby granted, free of charge, to any person obtaining a copy\n"
                         "of this software and associated documentation files (the \"Software\"), to deal\n"
                         "in the Software without restriction, including without limitation the rights\n"
                         "to use, copy, modify, and distribute the Software for any non-commercial purpose,\n"
                         "subject to the following conditions:\n\n"
                         "You may:\n"
                         "- Use the Software for any non-commercial purpose, where non-commercial purpose means any activity\n"
                         "  or transaction done without an intention to make a profit.\n"
                         "- Copy the Software for your own use or backup.\n"
                         "- Modify the Software to suit your needs or preferences.\n"
                         "- Distribute the Software to others, as long as you comply with the terms of this license.\n\n"
                         "You may not:\n"
                         "- Use the Software for any commercial purpose, where commercial purpose means any activity or\n"
                         "  transaction done with an intention to make a profit.\n"
                         "- Use the Software for any illegal or harmful activities.\n"
                         "- Distribute the Software with a hidden or obfuscated source code.\n"
                         "- Distribute the Software with a modified or changed license.\n"
                         "- Distribute the Software with a charge for the source code.\n\n"
                         "This software is provided \"as is\", without warranty of any kind, express or implied. The author(s)\n"
                         "of the software are not liable for any damages or losses arising from the use of the software.");
        MessageBox(NULL, message, "License", MB_OK);
        return 0;
      }
      else if (wcscmp(argv[i], L"--author") == 0)
      {
        MessageBox(NULL, "Max Reinartz", "Author", MB_OK);
        return 0;
      }
      else if (wcscmp(argv[i], L"--lang") == 0)
      {
        if (i + 1 < argc)
        {
          char userLang[256];
          wcstombs(userLang, argv[i + 1], sizeof(userLang));
          userLang[sizeof(userLang) - 1] = '\0';

          // MessageBoxA(NULL, userLang, "DEBUG", MB_OK);

          initializeLanguage();

          if (isLangCodeValid(userLang) == 0)
          {
            const char *translation = getTranslation(userLang);
            if (translation != NULL)
            {
              wchar_t wideTranslation[256];
              MultiByteToWideChar(CP_UTF8, 0, translation, -1, wideTranslation, sizeof(wideTranslation) / sizeof(wideTranslation[0]));
              wcscpy(textString, wideTranslation);
            }
            else
            {
              MessageBoxA(NULL, "Translation is missing.", "Error", MB_OK);
            }
          }
          else
          {
            char message[256];
            sprintf(message, "Invalid language code. Function returned %s", isLangCodeValid(userLang) == 1 ? "1" : "2");
            MessageBoxA(NULL, message, "Error", MB_OK);
            return 1;
          }
        }
        else
        {
          MessageBoxA(NULL, "Language argument is missing.", "Error", MB_OK);
          return 1;
        }
      }
      else if (wcscmp(argv[i], L"--help") == 0)
      {
        char message[1024];
        sprintf(message, "Usage: [--speed <speed>] [--fun] [--msg <message>] [--version] [--license] [--author] [--lang <language_code>] [--help]\n"
                         "Options:\n"
                         "  --speed <speed>        Set the speed of the window\n"
                         "  --fun                  Enable fun mode\n"
                         "  --msg <message>        Set the message of the window\n"
                         "  --version              Display the version information\n"
                         "  --license              Display the license information\n"
                         "  --author               Display the author\n"
                         "  --lang <language_code> Set the language for the message\n"
                         "  --help                 Display this help message\n");
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