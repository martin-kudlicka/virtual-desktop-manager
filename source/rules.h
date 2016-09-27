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

    bool     empty      ()                   const;
    MUuidPtr id         (quintptr index)     const;
    quintptr index      (const MUuidPtr &id) const;
    void     removeId   (const MUuidPtr &id);
    void     removeIndex(quintptr index);
    quintptr size       ()                   const;

  private:
    QSettings _settings;
};

#endif