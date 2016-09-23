#include "options.h"

#include "virtualdesktopmanager.h"

const QString Group_Desktop = "desktop";
const QString Group_Hotkey  = "hotkey";

const QString Key_Key              = "key";
const QString Key_Modifiers        = "modifiers";
const QString Key_NativeVirtualKey = "nativeVirtualKey";

const QString Options::DesktopCount   = "general/desktopCount";
const QString Options::MinimizeToTray = "general/minimizeToTray";
const QString Options::TrayIcon       = "general/trayIcon";

MLazySingleton<Options> gOptions;

Options::Options()
{
  beginGroup("options");

  addProperty(DesktopCount,   gVirtualDesktopManager->count());
  addProperty(TrayIcon,       Qt::Checked);
  addProperty(MinimizeToTray, Qt::Checked);
}

Options::~Options()
{
  endGroup();
}

quintptr Options::desktopCount() const
{
  return value(DesktopCount).toUInt();
}

MHotkey Options::desktopHotkey(quintptr index) const
{
  auto group = QString("%1/%2/%3/").arg(Group_Hotkey).arg(Group_Desktop).arg(index);

  MHotkey hotkey;
  hotkey.setKey(static_cast<Qt::Key>(value(group + Key_Key).toUInt()));
  hotkey.setModifiers(static_cast<Qt::KeyboardModifiers>(value(group + Key_Modifiers).toUInt()));
  hotkey.setNativeVirtualKey(value(group + Key_NativeVirtualKey).toUInt());

  return hotkey;
}

void Options::setDesktopHotkey(quintptr index, const MHotkey &hotkey)
{
  auto group = QString("%1/%2/%3/").arg(Group_Hotkey).arg(Group_Desktop).arg(index);

  setValue(group + Key_Key,              static_cast<quintptr>(hotkey.key()));
  setValue(group + Key_Modifiers,        static_cast<quintptr>(hotkey.modifiers()));
  setValue(group + Key_NativeVirtualKey, hotkey.nativeVirtualKey());
}

bool Options::trayIcon() const
{
  return value(TrayIcon).toBool();
}