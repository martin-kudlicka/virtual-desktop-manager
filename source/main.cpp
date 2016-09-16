#include "mainwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication application(argc, argv);
	application.setOrganizationName("MartinK");
	application.setApplicationName("Virtual Desktop Manager");

	MainWindow mainWindow;
	mainWindow.show();

	return application.exec();
}