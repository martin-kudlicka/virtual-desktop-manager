#ifndef RULES_H
#define RULES_H

#include <MkCore/MLazySingleton>
#include <QtCore/QSettings>
#include <MkCore/MUuidPtr>

class Rules
{
  public:
    static const QString Group;

     Rules();
    ~Rules() Q_DECL_EQ_DEFAULT;

    bool         anyEnabled ()                   const;
    quintptr     count      ()                   const;
    MUuidPtr     id         (quintptr index)     const;
    MUuidPtrList ids        ()                   const;
    quintptr     index      (const MUuidPtr &id) const;
    bool         isEmpty    ()                   const;
    void         removeIndex(quintptr index);

  private:
    QSettings _settings;

    void removeId(const MUuidPtr &id);
};

extern MLazySingleton<Rules> gRules;

#endif