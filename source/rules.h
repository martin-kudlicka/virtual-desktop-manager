#ifndef RULES_H
#define RULES_H

#include <QtCore/QSettings>
#include <MkCore/MUuidPtr>

class Rules
{
  public:
    static const QString Group;

     Rules();
    ~Rules();

    MUuidPtr id    (quintptr index)     const;
    quintptr index (const MUuidPtr &id) const;
    void     remove(quintptr index);
    void     remove(const MUuidPtr &id);
    quintptr size  ()                   const;

  private:
    QSettings _settings;
};

#endif