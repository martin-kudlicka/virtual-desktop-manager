#include "ruleoptions.h"

#include "rules.h"

const QString RuleOptions::Action       = "action";
const QString RuleOptions::Class        = "class";
const QString RuleOptions::DesktopIndex = "desktopIndex";
const QString RuleOptions::Enabled      = "enabled";
const QString RuleOptions::Name         = "name";
const QString RuleOptions::Process      = "process";
const QString RuleOptions::Title        = "title";

RuleOptions::RuleOptions(MUuidPtr &&id) : _id(qMove(id))
{
  beginGroup(Rules::Group);
  beginGroup(_id.toString());

  addProperty(Enabled, Qt::Checked);
}

RuleOptions::RuleOptions(const MUuidPtr &id) : RuleOptions(MUuidPtr(id))
{
}

RuleOptions::RuleOptions(const RuleOptions &other) : RuleOptions(MUuidPtr(other._id))
{
}

RuleOptions::ActionType RuleOptions::action() const
{
  return static_cast<ActionType>(value(Action).toUInt());
}

QString RuleOptions::className() const
{
  return value(Class).toString();
}

quintptr RuleOptions::desktopIndex() const
{
  return value(DesktopIndex).toUInt();
}

bool RuleOptions::enabled() const
{
  return value(Enabled).toBool();
}

const MUuidPtr &RuleOptions::id() const
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

bool RuleOptions::valid() const
{
  return !_id.isNull();
}