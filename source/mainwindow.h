#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
             MainWindow();
    virtual ~MainWindow();

  private:
    Ui::MainWindow _ui;

  private slots:
    void on_actionOptions_triggered(bool checked = false);
};

#endif