#include "mainwindow.h"

#include "optionsdialog.h"
#include "options.h"
#include "virtualdesktopmanager.h"

MainWindow::MainWindow() : QMainWindow(), _applicationModel(&_appWindows)
{
  _ui.setupUi(this);

  setupApplicationModel();

  registerHotkeys();

  _trayIcon.setIcon(QIcon(":/resources/mainwindow/mainwindow.png"));

  applySettings();
}

MainWindow::~MainWindow()
{
}

void MainWindow::applySettings()
{
  _trayIcon.setVisible(gOptions->trayIcon());

  registerHotkeys();
}

void MainWindow::registerHotkeys() const
{
  for (auto index = 0; index < gOptions->desktopCount(); index++)
  {
    auto hotkey = gOptions->desktopHotkey(index);
    if (!hotkey.valid())
    {
      continue;
    }

    UINT modifiers = 0;
    if (hotkey.modifiers().testFlag(Qt::ControlModifier))
    {
      modifiers |= MOD_CONTROL;
    }
    if (hotkey.modifiers().testFlag(Qt::AltModifier))
    {
      modifiers |= MOD_ALT;
    }
    if (hotkey.modifiers().testFlag(Qt::ShiftModifier))
    {
      modifiers |= MOD_SHIFT;
    }
    if (hotkey.modifiers().testFlag(Qt::MetaModifier))
    {
      modifiers |= MOD_WIN;
    }

    RegisterHotKey(reinterpret_cast<HWND>(winId()), index, modifiers, hotkey.nativeVirtualKey());
  }
}

void MainWindow::setupApplicationModel()
{
  _ui.applicationView->setModel(&_applicationModel);

  auto headerView = _ui.applicationView->header();
  headerView->setSectionResizeMode(QHeaderView::ResizeToContents);
}

bool MainWindow::event(QEvent *event)
{
  switch (event->type())
  {
    case QEvent::WindowStateChange:
      if (isMinimized() && _trayIcon.isVisible() && gOptions->minimizeToTray())
      {
        setWindowFlags(windowFlags() | Qt::CustomizeWindowHint);
      }
  }

  return QMainWindow::event(event);
}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
  auto msg = static_cast<LPMSG>(message);
  switch (msg->message)
  {
    case WM_HOTKEY:
      auto desktopIndex = msg->wParam;
      gVirtualDesktopManager->switchTo(desktopIndex);
      return true;
  }

  return false;
}

void MainWindow::on_actionOptions_triggered(bool checked /* false */)
{
  auto desktopCountOld = gOptions->desktopCount();

  if (OptionsDialog(this).exec() == QDialog::Rejected)
  {
    return;
  }

  for (auto index = gOptions->desktopCount(); index < desktopCountOld; index++)
  {
    UnregisterHotKey(reinterpret_cast<HWND>(winId()), index);
  }

  applySettings();
}