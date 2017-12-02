#include "options.h"

#include "virtualdesktopmanager.h"

namespace {
  const auto Group_Desktop = "desktops";
  const auto Group_Hotkey  = "hotkeys";

  const auto Key_Key              = "key";
  const auto Key_Modifiers        = "modifiers";
  const auto Key_NativeVirtualKey = "nativeVirtualKey";
}

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

bool Options::minimizeToTray() const
{
  return value(MinimizeToTray).toBool();
}

void Options::setDesktopCount(quintptr count)
{
  setValue(DesktopCount, count);
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