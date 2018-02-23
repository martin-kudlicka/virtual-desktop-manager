#include "ruleoptions.h"

#include "rules.h"

const QString RuleOptions::Property::Action       = "action";
const QString RuleOptions::Property::Class        = "class";
const QString RuleOptions::Property::DesktopIndex = "desktopIndex";
const QString RuleOptions::Property::Enabled      = "enabled";
const QString RuleOptions::Property::Name         = "name";
const QString RuleOptions::Property::Process      = "process";
const QString RuleOptions::Property::Title        = "title";

RuleOptions::RuleOptions(const MUuidPtr &id) : _id(id)
{
  beginGroup(Rules::Group);
  beginGroup(_id.toString());

  addProperty(Property::Enabled, Qt::Checked);
}

RuleOptions::RuleOptions(const RuleOptions &other) : RuleOptions(MUuidPtr(other._id))
{
}

RuleOptions::Action RuleOptions::action() const
{
  return static_cast<Action>(value(Property::Action).toUInt());
}

QString RuleOptions::className() const
{
  return value(Property::Class).toString();
}

quintptr RuleOptions::desktopIndex() const
{
  return value(Property::DesktopIndex).toUInt();
}

bool RuleOptions::enabled() const
{
  return value(Property::Enabled).toBool();
}

const MUuidPtr &RuleOptions::id() const
{
  return _id;
}

QString RuleOptions::name() const
{
  return value(Property::Name).toString();
}

QString RuleOptions::process() const
{
  return value(Property::Process).toString();
}

QString RuleOptions::title() const
{
  return value(Property::Title).toString();
}

bool RuleOptions::valid() const
{
  return !_id.isNull();
}