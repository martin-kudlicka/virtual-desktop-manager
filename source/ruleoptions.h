#ifndef RULEOPTIONS_H
#define RULEOPTIONS_H

#include <MkCore/MSettings>
#include <MkCore/MUuidPtr>

class RuleOptions : public MSettings
{
  public:
    static const QString Action;
    static const QString Class;
    static const QString Enabled;
    static const QString Name;
    static const QString Process;
    static const QString Title;

             RuleOptions(MUuidPtr &&id);
    virtual ~RuleOptions() Q_DECL_OVERRIDE;

          QString   className() const;
          bool      enabled  () const;
    const MUuidPtr &id       () const;
          QString   name     () const;
          QString   process  () const;
          QString   title    () const;

  private:
    MUuidPtr _id;
};

#endif