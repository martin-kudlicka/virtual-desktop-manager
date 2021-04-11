#ifndef RULEDIALOG_H
#define RULEDIALOG_H

#include "ui_ruledialog.h"
#include "ruleoptions.h"

class RuleDialog : public MOptionsDialog<Ui::RuleDialog, RuleOptions>
{
  Q_OBJECT

  public:
             RuleDialog(const MUuidPtr &id, QWidget *parent);
             RuleDialog(const QString &process, const QString &windowTitle, const QString &windowClass, QWidget *parent);
             RuleDialog(QWidget *parent);
    virtual ~RuleDialog() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  private:
    virtual void setupSettings() Q_DECL_OVERRIDE;

   private Q_SLOTS:
     void on_name_textChanged(const QString &text) const;
};

#endif