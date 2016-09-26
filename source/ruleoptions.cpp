#include "ruleoptions.h"

#include "rules.h"

const QString RuleOptions::Action  = "action";
const QString RuleOptions::Class   = "class";
const QString RuleOptions::Enabled = "enabled";
const QString RuleOptions::Name    = "name";
const QString RuleOptions::Process = "process";
const QString RuleOptions::Title   = "title";

RuleOptions::RuleOptions(QUuid &&id) : _id(id)
{
  beginGroup(Rules::Group);
  beginGroup(_id.toString());

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

const QUuid &RuleOptions::id() const
{
  return _id;
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