#ifndef SETTINGS_H
#define SETTINGS_H

#include <QtCore/QSettings>

class Property;

class Settings : public QSettings
{
  public:
    QVariant value(const QString &key) const;

  protected:
             Settings();
    virtual ~Settings();

    void addProperty(const QString &key, QVariant &&defaultValue);
    void addProperty(QString &&key, QVariant &&defaultValue);

  private:
    QHash<QString, Property> _properties;
};

#endif