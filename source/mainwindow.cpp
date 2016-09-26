#include "mainwindow.h"

#include "optionsdialog.h"
#include "options.h"
#include "virtualdesktopmanager.h"
#include "ruledialog.h"
#include <QtCore/QUuid>

MainWindow::MainWindow() : QMainWindow(), _applicationModel(_appWindows.applications()), _ruleModel(&_rules)
{
  _ui.setupUi(this);

  setupApplicationModel();
  setupRuleModel();

  registerHotkeys();

  _trayIcon.setIcon(QIcon(":/resources/mainwindow/mainwindow.png"));

  applySettings();

  connect(_ui.ruleView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::on_ruleView_selectionModel_selectionChanged);
  connect(&_trayIcon,                     &QSystemTrayIcon::activated,            this, &MainWindow::on_trayIcon_activated);
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

void MainWindow::setupRuleModel()
{
  _ui.ruleView->setModel(&_ruleModel);

  auto headerView = _ui.ruleView->header();
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

void MainWindow::on_addRuleButton_clicked(bool checked /* false */)
{
  if (RuleDialog().exec() == QDialog::Rejected)
  {
    return;
  }

  _ui.ruleView->reset();
}

void MainWindow::on_applicationView_customContextMenuRequested(const QPoint &pos)
{
  auto selections = _ui.applicationView->selectionModel()->selectedRows();

  QMenu contextMenu;

  auto switchTo = contextMenu.addAction(tr("Switch to"));
  switchTo->setEnabled(selections.size() == 1);

  static const auto Property_MoveToDesktopAction = "MoveToDesktop";

  {
    auto moveToMenu = contextMenu.addMenu(tr("Move to desktop"));
    moveToMenu->setEnabled(!selections.empty() && gVirtualDesktopManager->count() > 1);
    if (moveToMenu->isEnabled())
    {
      for (auto index = 0; index < gVirtualDesktopManager->count(); index++)
      {
        auto moveTo = moveToMenu->addAction(QString::number(index + 1));
        moveTo->setProperty(Property_MoveToDesktopAction, true);
        moveTo->setData(index);
      }
    }
  }

  contextMenu.addSeparator();

  contextMenu.addAction(tr("Refresh"), this, &MainWindow::on_refreshApplicationsButton_clicked);

  auto action = contextMenu.exec(_ui.applicationView->mapToGlobal(pos));
  if (!action)
  {
    return;
  }
  if (action == switchTo)
  {
    auto appInfo = &_appWindows.applications()->at(selections.first().row());
    SetForegroundWindow(appInfo->window.handle);
  }
  else if (action->property(Property_MoveToDesktopAction).toBool())
  {
    for (const auto &index : selections)
    {
      auto appInfo = &_appWindows.applications()->at(index.row());
      gVirtualDesktopManager->moveWindowTo(appInfo->window.handle, action->data().toUInt());

      on_refreshApplicationsButton_clicked();
    }
  }
}

void MainWindow::on_deleteRuleButton_clicked(bool checked /* false */)
{
  auto selected = _ui.ruleView->selectionModel()->selectedRows();
  for (const auto &index : selected)
  {
    _rules.remove(index.row());
  }

  _ui.ruleView->reset();
}

void MainWindow::on_editRuleButton_clicked(bool checked /* false */)
{
  auto index = _ui.ruleView->selectionModel()->currentIndex().row();
  auto id    = _rules.id(index);

  if (RuleDialog(id).exec() == QDialog::Rejected)
  {
    return;
  }

  _ui.ruleView->reset();
}

void MainWindow::on_refreshApplicationsButton_clicked(bool checked /* false */)
{
  _appWindows.refresh();
  _ui.applicationView->reset();
}

void MainWindow::on_ruleView_selectionModel_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) const
{
  _ui.editRuleButton->setEnabled(_ui.ruleView->selectionModel()->selectedRows().size() == 1);
  _ui.deleteRuleButton->setEnabled(!_ui.ruleView->selectionModel()->selectedRows().empty());
}

void MainWindow::on_trayIcon_activated(QSystemTrayIcon::ActivationReason reason)
{
  switch (reason)
  {
    case QSystemTrayIcon::DoubleClick:
      if (isMinimized())
      {
        setWindowFlags(windowFlags() & ~Qt::CustomizeWindowHint);
        showNormal();
        activateWindow();
      }
  }
}