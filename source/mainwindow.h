#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "appwindows.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
             MainWindow();
    virtual ~MainWindow();

  private:
    AppWindows     _appWindows;
    Ui::MainWindow _ui;

  private slots:
    void on_actionOptions_triggered(bool checked = false);
};

#endif