#include "mainwindow.h"

#include "rules.h"
#include "optionsdialog.h"
#include "options.h"
#include "virtualdesktopmanager.h"
#include "ruledialog.h"
#include <QtCore/QDir>

MainWindow::MainWindow() : QMainWindow(), _applicationModel(_appWindows.applications())
{
  _ui.setupUi(this);

  setupApplicationModel();
  setupRuleModel();

  registerHotkeys();

  _trayIcon.setIcon(QIcon(":/resources/mainwindow/mainwindow.png"));

  applySettings();

  connect(_ui.applicationView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::on_applicationView_selectionModel_selectionChanged);
  connect(_ui.ruleView->selectionModel(),        &QItemSelectionModel::selectionChanged, this, &MainWindow::on_ruleView_selectionModel_selectionChanged);
  connect(&_trayIcon,                            &QSystemTrayIcon::activated,            this, &MainWindow::on_trayIcon_activated);
}

MainWindow::~MainWindow()
{
}

void MainWindow::applyRule(const AppInfo &appInfo, const RuleOptions &ruleOptions) const
{
  if (!ruleOptions.valid())
  {
    return;
  }

  switch (ruleOptions.action())
  {
    case RuleOptions::ActionType::MoveToDesktop:
      gVirtualDesktopManager->moveWindowTo(appInfo.window().handle, ruleOptions.desktopIndex() - 1);
      break;
    case RuleOptions::ActionType::KeepOnDesktop:
      // TODO
    case RuleOptions::ActionType::AutoClose:
      // TODO
      ;
    default:
      Q_UNREACHABLE();
  }
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
  }

  applySettings();
}

void MainWindow::on_addRuleButton_clicked(bool checked /* false */)
{
  RuleDialog ruleDialog(this);
  if (ruleDialog.exec() == QDialog::Rejected)
  {
    return;
  }

  auto row = gRules->index(ruleDialog.options().id());
  _ruleModel.insertRow(row);
}

void MainWindow::on_applicationView_customContextMenuRequested(const QPoint &pos)
{
  auto selected = _ui.applicationView->selectionModel()->selectedRows();

  QMenu contextMenu;

  auto switchTo = contextMenu.addAction(tr("Switch to"), this, &MainWindow::on_switchToButton_clicked);
  switchTo->setEnabled(selected.size() == 1);

  static const auto Property_MoveToDesktopAction = "MoveToDesktop";

  {
    auto moveToMenu = contextMenu.addMenu(tr("Move to desktop"));
    moveToMenu->setEnabled(!selected.empty() && gVirtualDesktopManager->count() > 1);
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

  auto createRule = contextMenu.addAction(tr("Create rule"));
  createRule->setEnabled(selected.size() == 1);

  contextMenu.addSeparator();

  contextMenu.addAction(tr("Refresh"), this, &MainWindow::on_refreshApplicationsButton_clicked);

  auto action = contextMenu.exec(_ui.applicationView->mapToGlobal(pos));
  if (!action)
  {
    return;
  }
  if (action == createRule)
  {
    auto appInfo = &_appWindows.applications()->at(selected.first().row());
    RuleDialog ruleDialog(QDir::toNativeSeparators(appInfo->process().fileInfo.filePath()), appInfo->window().title, appInfo->window().className, this);
    if (ruleDialog.exec() == QDialog::Accepted)
    {
      auto row = gRules->index(ruleDialog.options().id());
      _ruleModel.insertRow(row);
    }
  }
  else if (action->property(Property_MoveToDesktopAction).toBool())
  {
    for (const auto &index : selected)
    {
      auto appInfo = &_appWindows.applications()->at(index.row());
      gVirtualDesktopManager->moveWindowTo(appInfo->window().handle, action->data().toUInt());

      on_refreshApplicationsButton_clicked();
    }
  }
}

void MainWindow::on_applicationView_selectionModel_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) const
{
  _ui.switchToButton->setEnabled(_ui.applicationView->selectionModel()->selectedRows().size() == 1);
}

void MainWindow::on_applyRuleButton_clicked(bool checked /* false */)
{
  MUuidPtrList ruleIds;
  auto selected = _ui.ruleView->selectionModel()->selectedRows();
  for (const auto &index : selected)
  {
    ruleIds.append(index.internalId());
  }

  _appWindows.refresh();

  for (const auto &appWindow : *_appWindows.applications())
  {
    auto ruleOptions = appWindow.bestRule(ruleIds);
    applyRule(appWindow, ruleOptions);
  }

  _ui.applicationView->reset();
}

void MainWindow::on_editRuleButton_clicked(bool checked /* false */)
{
  auto selected = _ui.ruleView->selectionModel()->selectedIndexes();
  auto id       = selected.first().internalId();

  if (RuleDialog(qMove(id)).exec() == QDialog::Rejected)
  {
    return;
  }

  emit _ruleModel.dataChanged(selected.first(), selected.last());
}

void MainWindow::on_refreshApplicationsButton_clicked(bool checked /* false */)
{
  _appWindows.refresh();
  _ui.applicationView->reset();
}

void MainWindow::on_removeRuleButton_clicked(bool checked /* false */)
{
  forever
  {
    auto selected = _ui.ruleView->selectionModel()->selectedRows();
    if (selected.empty())
    {
      break;
    }

    _ruleModel.removeRow(selected.first().row());
  }
}

void MainWindow::on_ruleView_customContextMenuRequested(const QPoint &pos) const
{
  auto selected = _ui.ruleView->selectionModel()->selectedRows();

  QMenu contextMenu;

  auto addRule = contextMenu.addAction(tr("Add"), this, &MainWindow::on_addRuleButton_clicked);

  auto editRule = contextMenu.addAction(tr("Edit"), this, &MainWindow::on_editRuleButton_clicked);
  editRule->setEnabled(selected.size() == 1);

  auto removeRule = contextMenu.addAction(tr("Remove"), this, &MainWindow::on_removeRuleButton_clicked);
  removeRule->setEnabled(!selected.empty());

  contextMenu.addSeparator();

  auto applyRule2 = contextMenu.addAction(tr("Apply"), this, &MainWindow::on_applyRuleButton_clicked);
  applyRule2->setEnabled(!selected.empty());

  contextMenu.exec(_ui.ruleView->mapToGlobal(pos));
}

void MainWindow::on_ruleView_doubleClicked(const QModelIndex &index)
{
  on_editRuleButton_clicked();
}

void MainWindow::on_ruleView_selectionModel_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) const
{
  _ui.editRuleButton->setEnabled(_ui.ruleView->selectionModel()->selectedRows().size() == 1);
  _ui.removeRuleButton->setEnabled(!_ui.ruleView->selectionModel()->selectedRows().empty());
  _ui.applyRuleButton->setEnabled(!_ui.ruleView->selectionModel()->selectedRows().empty());
}

void MainWindow::on_switchToButton_clicked(bool checked /* false */) const
{
  auto selected = _ui.applicationView->selectionModel()->selectedRows();
  auto appInfo  = &_appWindows.applications()->at(selected.first().row());

  SetForegroundWindow(appInfo->window().handle);
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