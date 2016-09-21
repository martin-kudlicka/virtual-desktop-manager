#include "optionsdialog.h"

#include "options.h"

OptionsDialog::OptionsDialog(QWidget *parent /* Q_NULLPTR */) : QDialog(parent), _widgetSettings(gOptions.data())
{
  _ui.setupUi(this);

  setupSettings();

  _widgetSettings.load();
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