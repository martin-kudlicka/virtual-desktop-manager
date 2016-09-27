#ifndef APPWINDOWS_H
#define APPWINDOWS_H

#include "appinfo.h"

class AppWindows
{
  public:
    AppWindows();

    const AppInfoList *applications() const;
          void         refresh     ();

  private:
    AppInfoList _appsInfo;

    void enumerate     ();
    void enumWindows   (HWND window);
    void setProcessInfo(AppInfo::ProcessInfo *processInfo) const;
    void setWindowInfo (AppInfo::WindowInfo *windowInfo)   const;

    static BOOL CALLBACK enumWindowsProc(_In_ HWND hwnd, _In_ LPARAM lParam);
};

#endif