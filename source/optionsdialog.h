#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include "ui_optionsdialog.h"
#include "widgetsettings.h"

class OptionsDialog : public QDialog
{
  public:
    OptionsDialog(QWidget *parent = Q_NULLPTR);

  private:
    Ui::OptionsDialog _ui;
    WidgetSettings    _widgetSettings;

    void saveHotkeys  () const;
    void setupHotkeys () const;
    void setupSettings();

    virtual void accept() override;
};

#endif