#include "mainwindow.h"
#include <QtWidgets/QApplication>

#include "virtualdesktopmanager.h"

int main(int argc, char *argv[])
{
  QApplication application(argc, argv);
  application.setOrganizationName("MartinK");
  application.setApplicationName("Virtual Desktop Manager");

  MainWindow mainWindow;
  mainWindow.show();

  auto error = application.exec();

  gVirtualDesktopManager.reset();

  return error;
}