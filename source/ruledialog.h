#ifndef RULEDIALOG_H
#define RULEDIALOG_H

#include "ui_ruledialog.h"
#include "ruleoptions.h"
#include <MkWidgets/MWidgetSettings>

class RuleDialog : public QDialog
{
  Q_OBJECT

  public:
             RuleDialog(MUuidPtr &&id, QWidget *parent = Q_NULLPTR);
             RuleDialog(QWidget *parent = Q_NULLPTR);
    virtual ~RuleDialog() Q_DECL_OVERRIDE;

    const RuleOptions &options() const;

    private:
      Ui::RuleDialog  _ui;
      RuleOptions     _options;
      MWidgetSettings _widgetSettings;

      void setupSettings();

      virtual void accept() Q_DECL_OVERRIDE;

     private Q_SLOTS:
       void on_name_textChanged(const QString &text) const;
};

#endif