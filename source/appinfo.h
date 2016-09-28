#ifndef APPINFO_H
#define APPINFO_H

#include <qt_windows.h>
#include <QtCore/QList>
#include <QtCore/QFileInfo>
#include "ruleoptions.h"

class AppInfo
{
  public:
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

      WindowInfo();
    };

          RuleOptions  bestRule()                             const;
          RuleOptions  bestRule(const MUuidPtrList &rulesIds) const;
          ProcessInfo &process ();
    const ProcessInfo &process ()                             const;
          WindowInfo  &window  ();
    const WindowInfo  &window  ()                             const;

  private:
    ProcessInfo _process;
    WindowInfo  _window;

    RuleOptions     bestRule     (const RuleOptionsList &rulesOptions) const;
    RuleOptionsList suitableRules(const MUuidPtrList &ruleIds)         const;
};

using AppInfoList = QList<AppInfo>;

#endif