#include "ruledialog.h"

#include <QtCore/QUuid>

RuleDialog::RuleDialog(const QUuid &id, QWidget *parent /* Q_NULLPTR */) : QDialog(parent), _options(id), _widgetSettings(&_options)
{
  _ui.setupUi(this);

  setupSettings();
  _widgetSettings.load();
}

RuleDialog::RuleDialog(QWidget *parent /* Q_NULLPTR */) : RuleDialog(QUuid::createUuid(), parent)
{
}

RuleDialog::~RuleDialog()
{
}

void RuleDialog::setupSettings()
{
  _widgetSettings.setWidget(RuleOptions::Name,    _ui.name);
  _widgetSettings.setWidget(RuleOptions::Enabled, _ui.enabled);
  _widgetSettings.setWidget(RuleOptions::Process, _ui.process);
  _widgetSettings.setWidget(RuleOptions::Title,   _ui.windowTitle);
  _widgetSettings.setWidget(RuleOptions::Class,   _ui.windowClass);
  _widgetSettings.setWidget(RuleOptions::Action,  qMove(QRadioButtonPtrList() << _ui.moveToDesktop << _ui.keepOnOneDesktop << _ui.autoClose));
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