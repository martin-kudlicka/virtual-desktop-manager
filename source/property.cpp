#include "property.h"

Property::Property()
{
}

Property::Property(const QString &name, QVariant &&defaultValue) : _name(name), _defaultValue(qMove(defaultValue))
{
}

Property::Property(QString &&name, QVariant &&defaultValue) : _name(qMove(name)), _defaultValue(qMove(defaultValue))
{
}

const QVariant &Property::defaultValue() const
{
  return _defaultValue;
}