#include "rules.h"

#include <QtCore/QUuid>

const QString Rules::Group = "rules";

Rules::Rules()
{
  _settings.beginGroup(Group);
}

Rules::~Rules()
{
  _settings.endGroup();
}

QUuid Rules::id(quintptr index) const
{
  return _settings.childGroups().at(index);
}

quintptr Rules::index(const QUuid &id) const
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

void Rules::remove(quintptr index)
{
  auto id2 = id(index);
  remove(id2);
}

void Rules::remove(const QUuid &id)
{
  _settings.remove(id.toString());
}

quintptr Rules::size() const
{
  return _settings.childGroups().size();
}