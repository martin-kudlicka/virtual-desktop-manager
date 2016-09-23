#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include "ui_optionsdialog.h"
#include "widgetsettings.h"

class OptionsDialog : public QDialog
{
  Q_OBJECT

  public:
             OptionsDialog(QWidget *parent = Q_NULLPTR);
    virtual ~OptionsDialog() Q_DECL_OVERRIDE;

  private:
    Ui::OptionsDialog _ui;
    WidgetSettings    _widgetSettings;

    void saveHotkeys  () const;
    void setupHotkeys () const;
    void setupSettings();

    virtual void accept() override;

    private Q_SLOTS:
      void on_trayIcon_stateChanged(int state) const;
};

#endif