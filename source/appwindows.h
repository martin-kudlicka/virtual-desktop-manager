#ifndef APPWINDOWS_H
#define APPWINDOWS_H

#include <qt_windows.h>
#include <QtCore/QList>
#include <QtCore/QFileInfo>

class AppWindows
{
  public:
    AppWindows();

  private:
    /*struct WindowInfo;
    using WindowInfoList = QList<WindowInfo>;*/

    struct ProcessInfo
    {
      DWORD     id;
      QFileInfo fileInfo;
    };
    struct WindowInfo
    {
      HWND           handle;
      QString        className;
      QString        title;
      quintptr       desktopIndex;
      //WindowInfoList childs;
    };
    struct AppInfo
    {
      ProcessInfo process;
      WindowInfo  window;
    };

    using AppInfoList = QList<AppInfo>;

    AppInfoList _appsInfo;

    void enumerate  ();
    void enumWindows(HWND window);

    static BOOL CALLBACK enumWindowsProc(_In_ HWND hwnd, _In_ LPARAM lParam);
};

#endif