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
    virtual ~MainWindow();

  private:
    ApplicationModel _applicationModel;
    AppWindows       _appWindows;
    Ui::MainWindow   _ui;

    void setupApplicationModel();

  private slots:
    void on_actionOptions_triggered(bool checked = false);
};

#endif