#ifndef PROPERTY_H
#define PROPERTY_H

#include <QtCore/QString>
#include <QtCore/QVariant>

class Property
{
  public:
    Property();
    Property(const QString &name, QVariant &&defaultValue);
    Property(QString &&name, QVariant &&defaultValue);

    const QVariant &defaultValue() const;

  private:
    QString  _name;
    QVariant _defaultValue;
};

#endif