#include "mainwindow.h"
#include <MkWidgets/MApplication>
#include "virtualdesktopmanager.h"

int main(int argc, char *argv[])
{
  MApplication application(argc, argv);

  MainWindow mainWindow;
  mainWindow.show();

  return application.exec();
}