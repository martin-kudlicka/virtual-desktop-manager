#include "mainwindow.h"

#include "optionsdialog.h"

MainWindow::MainWindow() : QMainWindow(), _applicationModel(&_appWindows)
{
  _ui.setupUi(this);

  setupApplicationModel();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupApplicationModel()
{
  _ui.applicationView->setModel(&_applicationModel);

  auto headerView = _ui.applicationView->header();
  headerView->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void MainWindow::on_actionOptions_triggered(bool checked /* false */)
{
  OptionsDialog(this).exec();
}