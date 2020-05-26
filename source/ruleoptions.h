#ifndef RULEOPTIONS_H
#define RULEOPTIONS_H

class RuleOptions : public MSettings
{
  public:
    enum class Action
    {
      MoveToDesktop,
      KeepOnDesktop,
      AutoClose
    };

    struct Property
    {
      static const QString Action;
      static const QString Class;
      static const QString DesktopIndex;
      static const QString Enabled;
      static const QString Name;
      static const QString Process;
      static const QString Title;
    };

             RuleOptions() Q_DECL_EQ_DEFAULT;
             RuleOptions(const MUuidPtr &id);
             RuleOptions(const RuleOptions &other);
    virtual ~RuleOptions() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

          Action    action      () const;
          QString   className   () const;
          quintptr  desktopIndex() const;
          bool      enabled     () const;
    const MUuidPtr &id          () const;
          QString   name        () const;
          QString   process     () const;
          QString   title       () const;
          bool      valid       () const;

  private:
    MUuidPtr _id;
};

using RuleOptionsList = QList<RuleOptions>;

#endif