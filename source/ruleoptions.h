#ifndef RULEOPTIONS_H
#define RULEOPTIONS_H

#include <MkCore/MSettings>

class RuleOptions : public MSettings
{
  public:
             RuleOptions(const QUuid &id);
    virtual ~RuleOptions();

    static const QString Action;
    static const QString Class;
    static const QString Enabled;
    static const QString Name;
    static const QString Process;
    static const QString Title;
};

#endif