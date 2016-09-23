#include "optionsdialog.h"

#include "options.h"
#include <MkWidgets/MHotkeyLineEdit>

OptionsDialog::OptionsDialog(QWidget *parent /* Q_NULLPTR */) : QDialog(parent), _widgetSettings(gOptions.data())
{
  _ui.setupUi(this);

  setupSettings();
  _widgetSettings.load();

  setupHotkeys();
}

void OptionsDialog::saveHotkeys() const
{
  auto formLayout = qobject_cast<QFormLayout *>(_ui.hotkeysContents->layout());

  for (auto index = 0; index < formLayout->rowCount(); index++)
  {
    auto layoutItem = formLayout->itemAt(index, QFormLayout::FieldRole);
    auto hotkeyEdit = qobject_cast<MHotkeyLineEdit *>(layoutItem->widget());

    gOptions->setDesktopHotkey(index, hotkeyEdit->hotkey());
  }
}

void OptionsDialog::setupHotkeys() const
{
  auto formLayout = qobject_cast<QFormLayout *>(_ui.hotkeysContents->layout());

  for (auto index = 0; index < _ui.desktopCount->value(); index++)
  {
    auto desktopHotkey = gOptions->desktopHotkey(index);

    auto hotkeyEdit = new MHotkeyLineEdit(_ui.hotkeysContents);
    hotkeyEdit->setHotkey(desktopHotkey);

    formLayout->addRow(QString("Desktop %1").arg(index), hotkeyEdit);
  }
}

void OptionsDialog::setupSettings()
{
  _widgetSettings.setWidget(Options::DesktopCount, _ui.desktopCount);
}

void OptionsDialog::accept()
{
  saveHotkeys();
  _widgetSettings.save();

  QDialog::accept();
}