#include "ruledialog.h"

#include "options.h"

RuleDialog::RuleDialog(MUuidPtr &&id, QWidget *parent /* Q_NULLPTR */) : QDialog(parent), _options(qMove(id)), _widgetSettings(&_options)
{
  _ui.setupUi(this);

  setupSettings();
  _widgetSettings.load();

  _ui.desktopIndex->setMaximum(gOptions->desktopCount());
}

RuleDialog::RuleDialog(const QString &process, const QString &windowTitle, const QString &windowClass, QWidget *parent /* Q_NULLPTR */) : RuleDialog(MUuidPtr::createUuid(), parent)
{
  _ui.process->setText(process);
  _ui.windowTitle->setText(windowTitle);
  _ui.windowClass->setText(windowClass);
}

RuleDialog::RuleDialog(QWidget *parent /* Q_NULLPTR */) : RuleDialog(MUuidPtr::createUuid(), parent)
{
}

RuleDialog::~RuleDialog()
{
}

const RuleOptions &RuleDialog::options() const
{
  return _options;
}

void RuleDialog::setupSettings()
{
  _widgetSettings.setWidget(RuleOptions::Name,         _ui.name);
  _widgetSettings.setWidget(RuleOptions::Enabled,      _ui.enabled);
  _widgetSettings.setWidget(RuleOptions::Process,      _ui.process);
  _widgetSettings.setWidget(RuleOptions::Title,        _ui.windowTitle);
  _widgetSettings.setWidget(RuleOptions::Class,        _ui.windowClass);
  _widgetSettings.setWidget(RuleOptions::Action,       qMove(QRadioButtonPtrList() << _ui.moveToDesktop << _ui.keepOnOneDesktop << _ui.autoClose));
  _widgetSettings.setWidget(RuleOptions::DesktopIndex, _ui.desktopIndex);
}

void RuleDialog::accept()
{
  _widgetSettings.save();

  QDialog::accept();
}

void RuleDialog::on_name_textChanged(const QString &text) const
{
  _ui.okButton->setEnabled(!text.isEmpty());
}