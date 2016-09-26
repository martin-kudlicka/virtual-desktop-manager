#ifndef RULEOPTIONS_H
#define RULEOPTIONS_H

#include <MkCore/MSettings>
#include <QtCore/QUuid>

class RuleOptions : public MSettings
{
  public:
    static const QString Action;
    static const QString Class;
    static const QString Enabled;
    static const QString Name;
    static const QString Process;
    static const QString Title;

             RuleOptions(QUuid &&id);
    virtual ~RuleOptions() Q_DECL_OVERRIDE;

          QString className() const;
          bool    enabled  () const;
    const QUuid  &id       () const;
          QString name     () const;
          QString process  () const;
          QString title    () const;

  private:
    QUuid _id;
};

#endif