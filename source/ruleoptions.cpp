#include "ruleoptions.h"

#include <QtCore/QUuid>
#include "rules.h"

const QString RuleOptions::Action  = "action";
const QString RuleOptions::Class   = "class";
const QString RuleOptions::Enabled = "enabled";
const QString RuleOptions::Name    = "name";
const QString RuleOptions::Process = "process";
const QString RuleOptions::Title   = "title";

RuleOptions::RuleOptions(const QUuid &id)
{
  beginGroup(Rules::Group);
  beginGroup(id.toString());

  addProperty(Enabled, Qt::Checked);
}

RuleOptions::~RuleOptions()
{
  endGroup();
  endGroup();
}

QString RuleOptions::className() const
{
  return value(Class).toString();
}

bool RuleOptions::enabled() const
{
  return value(Enabled).toBool();
}

QString RuleOptions::name() const
{
  return value(Name).toString();
}

QString RuleOptions::process() const
{
  return value(Process).toString();
}

QString RuleOptions::title() const
{
  return value(Title).toString();
}