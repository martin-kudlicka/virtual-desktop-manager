#include "mainwindow.h"

#include "settingsdialog.h"

MainWindow::MainWindow() : QMainWindow()
{
	_ui.setupUi(this);
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_actionSettings_triggered(bool checked /* false */)
{
	SettingsDialog(this).exec();
}