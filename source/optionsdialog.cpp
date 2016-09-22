#include "optionsdialog.h"

#include "options.h"
#include <QtWidgets/QKeySequenceEdit>

OptionsDialog::OptionsDialog(QWidget *parent /* Q_NULLPTR */) : QDialog(parent), _widgetSettings(gOptions.data())
{
  _ui.setupUi(this);

  setupSettings();

  _widgetSettings.load();

  setupHotkeys();
}

void OptionsDialog::setupHotkeys() const
{
  auto formLayout = qobject_cast<QFormLayout *>(_ui.hotkeysContents->layout());

  for (auto index = 0; index < _ui.desktopCount->value(); index++)
  {
    auto hotkeyEdit = new QKeySequenceEdit(_ui.hotkeysContents);

    formLayout->addRow(QString("Desktop %1").arg(index), hotkeyEdit);
  }
}

void OptionsDialog::setupSettings()
{
  _widgetSettings.setWidget(Options::DesktopCount, _ui.desktopCount);
}

void OptionsDialog::accept()
{
  _widgetSettings.save();

  QDialog::accept();
}