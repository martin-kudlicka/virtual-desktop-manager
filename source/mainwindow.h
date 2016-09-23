#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "appwindows.h"
#include "applicationmodel.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
             MainWindow();
    virtual ~MainWindow() Q_DECL_OVERRIDE;

  private:
    ApplicationModel _applicationModel;
    AppWindows       _appWindows;
    Ui::MainWindow   _ui;

    void registerHotkeys      () const;
    void setupApplicationModel();

    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result) Q_DECL_OVERRIDE;

  private slots:
    void on_actionOptions_triggered(bool checked = false);
};

#endif