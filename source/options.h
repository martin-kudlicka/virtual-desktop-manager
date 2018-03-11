#ifndef OPTIONS_H
#define OPTIONS_H

#include <MkCore/MSettings>
#include <MkCore/MLazySingleton>
#include <MkGui/MHotkey>

class Options : public MSettings
{
  public:
    struct Property
    {
      static const QString DesktopCount;
      static const QString MinimizeToTray;
      static const QString TrayIcon;
    };

             Options();
    virtual ~Options() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

    quintptr desktopCount    ()               const;
    MHotkey  desktopHotkey   (quintptr index) const;
    bool     minimizeToTray  ()               const;
    void     setDesktopCount (quintptr count);
    void     setDesktopHotkey(quintptr index, const MHotkey &hotkey);
    bool     trayIcon        ()               const;
};

extern MLazySingleton<Options> gOptions;

#endif