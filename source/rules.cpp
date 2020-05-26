#include "pch.h"
#include "rules.h"

#include "ruleoptions.h"

const QString Rules::Group = "rules";

MLazySingleton<Rules> gRules;

Rules::Rules()
{
  _settings.beginGroup(Group);
}

bool Rules::anyEnabled() const
{
  for (const auto &id2 : ids())
  {
    RuleOptions ruleOptions(id2);
    if (ruleOptions.enabled())
    {
      return true;
    }
  }

  return false;
}

quintptr Rules::count() const
{
  return _settings.childGroups().count();
}

MUuidPtr Rules::id(quintptr index) const
{
  return _settings.childGroups().at(index);
}

MUuidPtrList Rules::ids() const
{
  MUuidPtrList ids2;

  for (const auto &id2 : _settings.childGroups())
  {
    ids2.append(id2);
  }

  return ids2;
}

quintptr Rules::index(const MUuidPtr &id) const
{
  quintptr index2 = 0;

  for (const auto &id2 : _settings.childGroups())
  {
    if (id2 == id.toString())
    {
      return index2;
    }

    ++index2;
  }

  Q_UNREACHABLE();
  return std::numeric_limits<quintptr>::max();
}

bool Rules::isEmpty() const
{
  return count() == 0;
}

void Rules::removeIndex(quintptr index)
{
  auto id2 = id(index);
  removeId(id2);
}

void Rules::removeId(const MUuidPtr &id)
{
  _settings.remove(id.toString());
}