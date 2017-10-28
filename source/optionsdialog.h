#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include "ui_optionsdialog.h"
#include <MkWidgets/MWidgetSettings>

class MFormLayout;

class OptionsDialog : public QDialog
{
  Q_OBJECT

  public:
             OptionsDialog(QWidget *parent = Q_NULLPTR);
    virtual ~OptionsDialog() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  private:
    MWidgetSettings   _widgetSettings;
    Ui::OptionsDialog _ui;

    void addHotkeyEdit   (QFormLayout *formLayout, quintptr index) const;
    void removeHotkeyEdit(MFormLayout *formLayout, quintptr index) const;
    void saveHotkeys     ()                                        const;
    void setupHotkeys    ()                                        const;
    void setupSettings   ();

    virtual void accept() Q_DECL_OVERRIDE;

    private Q_SLOTS:
      void on_desktopCount_valueChanged(int i)     const;
      void on_trayIcon_stateChanged    (int state) const;
};

#endif