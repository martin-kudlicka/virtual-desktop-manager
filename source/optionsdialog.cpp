#include "optionsdialog.h"

#include "options.h"
#include <MkWidgets/MHotkeyLineEdit>
#include <MkWidgets/MFormLayout>
#include "virtualdesktopmanager.h"

OptionsDialog::OptionsDialog(QWidget *parent) : QDialog(parent), _widgetSettings(gOptions.data())
{
  _ui.setupUi(this);

  gOptions->setDesktopCount(gVirtualDesktopManager->count());

  _ui.desktopCountLabel->hide();
  _ui.desktopCount->hide();

  setupSettings();

  _ui.trayIcon->setCheckState(_ui.trayIcon->checkState());

  setupHotkeys();
}

void OptionsDialog::addHotkeyEdit(QFormLayout *formLayout, quintptr index) const
{
  auto desktopHotkey = gOptions->desktopHotkey(index);

  auto hotkeyEdit = new MHotkeyLineEdit(_ui.hotkeysContents);
  hotkeyEdit->setHotkey(desktopHotkey);

  formLayout->addRow(QString("Desktop %1").arg(index + 1), hotkeyEdit);
}

void OptionsDialog::removeHotkeyEdit(MFormLayout *formLayout, quintptr index) const
{
  formLayout->removeRow(index);
}

void OptionsDialog::saveHotkeys() const
{
  auto formLayout = static_cast<MFormLayout *>(_ui.hotkeysContents->layout());

  for (auto row = 0; row < formLayout->rowCount(); ++row)
  {
    auto layoutItem = formLayout->itemAt(row, QFormLayout::FieldRole);
    auto hotkeyEdit = qobject_cast<MHotkeyLineEdit *>(layoutItem->widget());

    gOptions->setDesktopHotkey(row, hotkeyEdit->hotkey());
  }
}

void OptionsDialog::setupHotkeys() const
{
  auto formLayout = qobject_cast<QFormLayout *>(_ui.hotkeysContents->layout());

  for (auto index = 0; index < _ui.desktopCount->value(); ++index)
  {
    addHotkeyEdit(formLayout, index);
  }
}

void OptionsDialog::setupSettings()
{
  _widgetSettings.setWidget(Options::DesktopCount,   _ui.desktopCount);
  _widgetSettings.setWidget(Options::TrayIcon,       _ui.trayIcon);
  _widgetSettings.setWidget(Options::MinimizeToTray, _ui.minimizeToTray);

  _widgetSettings.load();
}

void OptionsDialog::accept()
{
  saveHotkeys();
  _widgetSettings.save();

  QDialog::accept();
}

void OptionsDialog::on_desktopCount_valueChanged(int i) const
{
  auto formLayout = static_cast<MFormLayout *>(_ui.hotkeysContents->layout());
  if (formLayout->rowCount() == 0)
  {
    return;
  }

  while (i != formLayout->rowCount())
  {
    if (i < formLayout->rowCount())
    {
      removeHotkeyEdit(formLayout, formLayout->rowCount() - 1);
    }
    else
    {
      addHotkeyEdit(formLayout, formLayout->rowCount());
    }
  }
}

void OptionsDialog::on_trayIcon_stateChanged(int state) const
{
  _ui.minimizeToTray->setEnabled(state == Qt::Checked);
}