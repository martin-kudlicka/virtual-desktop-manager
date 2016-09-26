#include "ruleoptions.h"

#include <QtCore/QUuid>

const QString RuleOptions::Action  = "action";
const QString RuleOptions::Class   = "class";
const QString RuleOptions::Enabled = "enabled";
const QString RuleOptions::Name    = "name";
const QString RuleOptions::Process = "process";
const QString RuleOptions::Title   = "title";

RuleOptions::RuleOptions(const QUuid &id)
{
  beginGroup("rules");
  beginGroup(id.toString());

  addProperty(Enabled, Qt::Checked);
}

RuleOptions::~RuleOptions()
{
  endGroup();
  endGroup();
}