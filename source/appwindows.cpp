#include "appwindows.h"

AppWindows::AppWindows()
{
  enumerate();
}

void AppWindows::enumerate()
{
  EnumWindows(&enumWindowsProc, reinterpret_cast<LPARAM>(this));
}

void AppWindows::enumWindows(HWND hwnd)
{
  if (IsWindowVisible(hwnd))
  {
    AppInfo appInfo;

    GetWindowThreadProcessId(hwnd, &appInfo.process.id);

    appInfo.window.handle = hwnd;

    WCHAR text[4096] = { 0 };
    GetClassName(hwnd, text, _countof(text));
    if (wcslen(text) > 0)
    {
      appInfo.window.className = QString::fromWCharArray(text);
    }

    GetWindowText(hwnd, text, _countof(text));
    if (wcslen(text) == 0)
    {
      return;
    }
    appInfo.window.title = QString::fromWCharArray(text);

    _appsInfo.append(qMove(appInfo));
  }
}

BOOL CALLBACK AppWindows::enumWindowsProc(_In_ HWND hwnd, _In_ LPARAM lParam)
{
  auto appWindows = reinterpret_cast<AppWindows *>(lParam);
  appWindows->enumWindows(hwnd);

  return TRUE;
}