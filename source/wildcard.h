#ifndef WILDCARD_H
#define WILDCARD_H

#include <QtCore/QString>

class Wildcard
{
  public:
    Wildcard(QString &&pattern);

    bool matches(QString text) const;

  private:
    QString _pattern;
};

#endif