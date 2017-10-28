#include "rules.h"

#include <MkCore/MUuidPtr>
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

bool Rules::empty() const
{
  return size() == 0;
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
    ids2.push_back(id2);
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

    index2++;
  }

  Q_UNREACHABLE();
  return -1;
}

void Rules::removeIndex(quintptr index)
{
  auto id2 = id(index);
  removeId(id2);
}

quintptr Rules::size() const
{
  return _settings.childGroups().size();
}

void Rules::removeId(const MUuidPtr &id)
{
  _settings.remove(id.toString());
}