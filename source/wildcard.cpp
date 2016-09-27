#include "wildcard.h"

#include <QtCore/QRegExp>

Wildcard::Wildcard(QString &&pattern) : _pattern(qMove(pattern))
{
}

bool Wildcard::matches(QString text) const
{
  QRegExp regExp(_pattern, Qt::CaseInsensitive, QRegExp::Wildcard);

  text.replace('\\', "\\\\");
  return regExp.exactMatch(text);
}