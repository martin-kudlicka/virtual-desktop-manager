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
    bool         empty      ()                   const;
    MUuidPtr     id         (quintptr index)     const;
    MUuidPtrList ids        ()                   const;
    quintptr     index      (const MUuidPtr &id) const;
    void         removeIndex(quintptr index);
    quintptr     size       ()                   const;

  private:
    QSettings _settings;

    void removeId(const MUuidPtr &id);
};

extern MLazySingleton<Rules> gRules;

#endif