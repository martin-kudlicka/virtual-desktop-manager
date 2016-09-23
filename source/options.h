#ifndef OPTIONS_H
#define OPTIONS_H

#include "settings.h"
#include <MkCore/MLazySingleton>
#include <MkGui/MHotkey>

class Options : public Settings
{
  public:
             Options();
    virtual ~Options();

    static const QString DesktopCount;

    quintptr desktopCount    ()               const;
    MHotkey  desktopHotkey   (quintptr index) const;
    void     setDesktopHotkey(quintptr index, const MHotkey &hotkey);
};

extern MLazySingleton<Options> gOptions;

#endif