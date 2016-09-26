#include "rules.h"

#include <MkCore/MUuidPtr>

const QString Rules::Group = "rules";

Rules::Rules()
{
  _settings.beginGroup(Group);
}

Rules::~Rules()
{
  _settings.endGroup();
}

MUuidPtr Rules::id(quintptr index) const
{
  return _settings.childGroups().at(index);
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

void Rules::removeId(const MUuidPtr &id)
{
  _settings.remove(id.toString());
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