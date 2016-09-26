#ifndef RULES_H
#define RULES_H

#include <QtCore/QSettings>

class Rules
{
  public:
    static const QString Group;

     Rules();
    ~Rules();

    QUuid    id  (quintptr index) const;
    quintptr size()               const;

  private:
    QSettings _settings;
};

#endif