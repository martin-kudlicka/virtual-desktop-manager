#include "pch.h"
#include "ruledialog.h"

#include "options.h"

RuleDialog::RuleDialog(const MUuidPtr &id, QWidget *parent) : MOptionsDialog(id, parent)
{
  _ui.desktopIndex->setMaximum(gOptions->desktopCount());
}

RuleDialog::RuleDialog(const QString &process, const QString &windowTitle, const QString &windowClass, QWidget *parent) : RuleDialog(MUuidPtr::createUuid(), parent)
{
  _ui.process->setText(process);
  _ui.windowTitle->setText(windowTitle);
  _ui.windowClass->setText(windowClass);
}

RuleDialog::RuleDialog(QWidget *parent) : RuleDialog(MUuidPtr::createUuid(), parent)
{
}

void RuleDialog::setupSettings()
{
  _widgetSettings.setWidget(RuleOptions::Property::Name,         _ui.name);
  _widgetSettings.setWidget(RuleOptions::Property::Enabled,      _ui.enabled);
  _widgetSettings.setWidget(RuleOptions::Property::Process,      _ui.process);
  _widgetSettings.setWidget(RuleOptions::Property::Title,        _ui.windowTitle);
  _widgetSettings.setWidget(RuleOptions::Property::Class,        _ui.windowClass);
  _widgetSettings.setWidget(RuleOptions::Property::Action,       QRadioButtonPtrList() << _ui.moveToDesktop << _ui.keepOnOneDesktop << _ui.autoClose);
  _widgetSettings.setWidget(RuleOptions::Property::DesktopIndex, _ui.desktopIndex);

  MOptionsDialog::setupSettings();
}

void RuleDialog::on_name_textChanged(const QString &text) const
{
  _ui.okButton->setEnabled(!text.isEmpty());
}