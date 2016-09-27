#include "appwindows.h"

#include <MkCore/MkGlobal>
#include "virtualdesktopmanager.h"
#include <MkCore/MProcessHandle>

AppWindows::AppWindows()
{
  enumerate();
}

const AppInfoList *AppWindows::applications() const
{
  return &_appsInfo;
}

void AppWindows::refresh()
{
  _appsInfo.clear();
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

    GetWindowThreadProcessId(window, &appInfo.process().id);
    setProcessInfo(&appInfo.process());

    appInfo.window().handle = window;
    setWindowInfo(&appInfo.window());

    if (appInfo.window().title.isEmpty() || appInfo.window().desktopIndex == VirtualDesktopManager::InvalidDesktop)
    {
      return;
    }

    _appsInfo.append(qMove(appInfo));
  }
}

void AppWindows::setProcessInfo(AppInfo::ProcessInfo *processInfo) const
{
  auto process = MProcessHandle(processInfo->id, PROCESS_QUERY_LIMITED_INFORMATION);
  if (!process.valid())
  {
    return;
  }

  WCHAR filePath[Mk::PageSize] = { 0 };
  DWORD filePathSize           = _countof(filePath);
  auto ok = QueryFullProcessImageName(process, 0, filePath, &filePathSize);
  if (ok)
  {
    processInfo->fileInfo.setFile(QString::fromWCharArray(filePath));
  }
}

void AppWindows::setWindowInfo(AppInfo::WindowInfo *windowInfo) const
{
  {
    WCHAR text[Mk::PageSize] = { 0 };
    auto chars               = GetClassName(windowInfo->handle, text, _countof(text));
    if (chars > 0)
    {
      windowInfo->className = QString::fromWCharArray(text);
    }

    chars = GetWindowText(windowInfo->handle, text, _countof(text));
    if (chars == 0)
    {
      return;
    }
    windowInfo->title = QString::fromWCharArray(text);
  }

  windowInfo->desktopIndex = gVirtualDesktopManager->index(windowInfo->handle);
}

BOOL CALLBACK AppWindows::enumWindowsProc(_In_ HWND hwnd, _In_ LPARAM lParam)
{
  auto appWindows = reinterpret_cast<AppWindows *>(lParam);
  appWindows->enumWindows(hwnd);

  return TRUE;
}