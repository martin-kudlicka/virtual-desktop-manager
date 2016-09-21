#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include "ui_settingsdialog.h"
#include "widgetsettings.h"

class OptionsDialog : public QDialog
{
  public:
    OptionsDialog(QWidget *parent = Q_NULLPTR);

  private:
    Ui::SettingsDialog _ui;
    WidgetSettings     _widgetSettings;

    void setupSettings();

    virtual void accept() override;
};

#endif