#include "mainwindow.h"

#include "optionsdialog.h"

MainWindow::MainWindow() : QMainWindow()
{
  _ui.setupUi(this);
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_actionOptions_triggered(bool checked /* false */)
{
  OptionsDialog(this).exec();
}