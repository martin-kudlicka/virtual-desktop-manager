#include "appwindows.h"

#include <MkCore/MGlobal>
#include "virtualdesktopmanager.h"

AppWindows::AppWindows()
{
  enumerate();
}

void AppWindows::enumerate()
{
  EnumWindows(&enumWindowsProc, reinterpret_cast<LPARAM>(this));
}

void AppWindows::enumWindows(HWND window)
{
  if (IsWindowVisible(window))
  {
    AppInfo appInfo;

    GetWindowThreadProcessId(window, &appInfo.process.id);

    appInfo.window.handle = window;

    WCHAR text[Mk::PageSize] = { 0 };
    GetClassName(window, text, _countof(text));
    if (wcslen(text) > 0)
    {
      appInfo.window.className = QString::fromWCharArray(text);
    }

    GetWindowText(window, text, _countof(text));
    if (wcslen(text) == 0)
    {
      return;
    }
    appInfo.window.title = QString::fromWCharArray(text);

    appInfo.window.desktopIndex = gVirtualDesktopManager->index(window);

    _appsInfo.append(qMove(appInfo));
  }
}

BOOL CALLBACK AppWindows::enumWindowsProc(_In_ HWND hwnd, _In_ LPARAM lParam)
{
  auto appWindows = reinterpret_cast<AppWindows *>(lParam);
  appWindows->enumWindows(hwnd);

  return TRUE;
}