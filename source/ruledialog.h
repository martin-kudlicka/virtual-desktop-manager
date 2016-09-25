#ifndef RULEDIALOG_H
#define RULEDIALOG_H

#include "ui_ruledialog.h"

class RuleDialog : public QDialog
{
  public:
             RuleDialog(QWidget *parent = Q_NULLPTR);
    virtual ~RuleDialog() Q_DECL_OVERRIDE;

    private:
      Ui::RuleDialog _ui;
};

#endif