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

void Rules::remove(quintptr index)
{
  auto id2 = id(index);
  _settings.remove(id2.toString());
}

quintptr Rules::size() const
{
  return _settings.childGroups().size();
}