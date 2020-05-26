#include "pch.h"

#include "mainwindow.h"

int main(int argc, char *argv[])
{
  MApplication application(argc, argv);

  mAnalytics->setId("UA-115441303-3");

  MainWindow mainWindow;
  mainWindow.show();

  return application.exec();
}