#include "settings.h"

#include "property.h"

Settings::Settings() : QSettings()
{
}

Settings::~Settings()
{
}

void Settings::addProperty(const QString &key, QVariant &&defaultValue)
{
  _properties.insert(key, Property(key, qMove(defaultValue)));
}

void Settings::addProperty(QString &&key, QVariant &&defaultValue)
{
  _properties.insert(key, Property(qMove(key), qMove(defaultValue)));
}

QVariant Settings::value(const QString &key) const
{
  const auto defaultValue = _properties.value(key).defaultValue();
  return QSettings::value(key, defaultValue);
}