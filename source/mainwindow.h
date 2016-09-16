#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <QtWidgets/QMainWindow>
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
		void on_actionSettings_triggered(bool checked = false);
};

#endif