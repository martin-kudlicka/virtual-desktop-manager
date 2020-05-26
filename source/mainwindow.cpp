#include "pch.h"
#include "mainwindow.h"

#include "rules.h"
#include "optionsdialog.h"
#include "options.h"
#include "virtualdesktopmanager.h"
#include "ruledialog.h"

MainWindow::MainWindow() : _applicationModel(_appWindows.applications()), _desktopIndexMenu(tr("Move to desktop"))
{
  _ui.setupUi(this);

  setupApplicationModel();
  setupRuleModel();

  _trayIcon.setIcon(MIcon::applicationIcon());
  _ui.moveToDesktopButton->setMenu(&_desktopIndexMenu);

  connect(&_desktopIndexMenu,                    &QMenu::triggered,                      this, &MainWindow::on_desktopIndexMenu_triggered);
  connect(&_trayIcon,                            &QSystemTrayIcon::activated,            this, &MainWindow::on_trayIcon_activated);
  connect(_ui.applicationView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::on_applicationView_selectionModel_selectionChanged);
  connect(_ui.ruleView->selectionModel(),        &QItemSelectionModel::selectionChanged, this, &MainWindow::on_ruleView_selectionModel_selectionChanged);

  registerHotkeys();
  applySettings();

  _vdmHookClient.setRulesEnabled(gRules->anyEnabled());
}

void MainWindow::applyRule(const AppInfo &appInfo, const RuleOptions &ruleOptions) const
{
  if (!ruleOptions.valid())
  {
    return;
  }

  switch (ruleOptions.action())
  {
    case RuleOptions::Action::MoveToDesktop:
      gVirtualDesktopManager->moveWindowTo(appInfo.window().handle, ruleOptions.desktopIndex() - 1);
      break;
    case RuleOptions::Action::KeepOnDesktop:
      // apply only when window created
      break;
    case RuleOptions::Action::AutoClose:
      PostMessage(appInfo.window().handle, WM_CLOSE, 0, 0);
      break;
    default:
      Q_UNREACHABLE();
  }
}

void MainWindow::applySettings()
{
  _desktopIndexMenu.clear();
  for (decltype(gVirtualDesktopManager->count()) index = 0; index < gVirtualDesktopManager->count(); ++index)
  {
    auto moveTo = _desktopIndexMenu.addAction(QString::number(index + 1));
    moveTo->setData(index);
  }

  _trayIcon.setVisible(gOptions->trayIcon());

  registerHotkeys();
}

void MainWindow::registerHotkeys() const
{
  for (decltype(gOptions->desktopCount()) index = 0; index < gOptions->desktopCount(); ++index)
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
  Q_UNUSED(eventType);
  Q_UNUSED(result);

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

void MainWindow::on_actionAbout_triggered(bool checked /* false */)
{
  Q_UNUSED(checked);

  MAboutBox(this).exec();
}

void MainWindow::on_actionOptions_triggered(bool checked /* false */)
{
  Q_UNUSED(checked);

  {
    auto desktopCountOld = gOptions->desktopCount();

    if (OptionsDialog(this).exec() == QDialog::Rejected)
    {
      return;
    }

    for (auto index = gOptions->desktopCount(); index < desktopCountOld; ++index)
    {
      UnregisterHotKey(reinterpret_cast<HWND>(winId()), index);
    }
  }

  applySettings();
}

void MainWindow::on_actionSendFeedback_triggered(bool checked /* false */) const
{
  Q_UNUSED(checked);

  MFeedback::createEmailForm();
}

void MainWindow::on_addRuleButton_clicked(bool checked /* false */)
{
  Q_UNUSED(checked);

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
  switchTo->setEnabled(selected.count() == 1);

  contextMenu.addMenu(&_desktopIndexMenu);
  _desktopIndexMenu.setEnabled(!selected.isEmpty() && gVirtualDesktopManager->count() > 1);

  contextMenu.addSeparator();

  auto createRule = contextMenu.addAction(tr("Create rule..."), this, &MainWindow::on_createRuleButton_clicked);
  createRule->setEnabled(selected.count() == 1);

  contextMenu.addSeparator();

  contextMenu.addAction(tr("Refresh"), this, &MainWindow::on_refreshApplicationsButton_clicked);

  contextMenu.exec(_ui.applicationView->mapToGlobal(pos));
}

void MainWindow::on_applicationView_selectionModel_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) const
{
  Q_UNUSED(selected);
  Q_UNUSED(deselected);

  auto selectedRows = _ui.applicationView->selectionModel()->selectedRows();

  _ui.switchToButton->setEnabled(selectedRows.count() == 1);
  _ui.moveToDesktopButton->setEnabled(!selectedRows.isEmpty() && gVirtualDesktopManager->count() > 1);
  _ui.createRuleButton->setEnabled(selectedRows.count() == 1);
}

void MainWindow::on_applyRuleButton_clicked(bool checked /* false */)
{
  Q_UNUSED(checked);

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

  _ui.refreshApplicationsButton->click();
}

void MainWindow::on_createRuleButton_clicked(bool checked /* false */)
{
  Q_UNUSED(checked);

  auto selected = _ui.applicationView->selectionModel()->selectedRows();
  auto appInfo  = &_appWindows.applications()->at(selected.constFirst().row());

  RuleDialog ruleDialog(QDir::toNativeSeparators(appInfo->process().fileInfo.filePath()), appInfo->window().title, appInfo->window().className, this);
  if (ruleDialog.exec() == QDialog::Accepted)
  {
    auto row = gRules->index(ruleDialog.options().id());
    _ruleModel.insertRow(row);
  }
}

void MainWindow::on_desktopIndexMenu_triggered(QAction *action)
{
  auto selected = _ui.applicationView->selectionModel()->selectedRows();

  for (const auto &index : selected)
  {
    auto appInfo = &_appWindows.applications()->at(index.row());
    gVirtualDesktopManager->moveWindowTo(appInfo->window().handle, action->data().toUInt());
  }

  _ui.refreshApplicationsButton->click();
}

void MainWindow::on_editRuleButton_clicked(bool checked /* false */)
{
  Q_UNUSED(checked);

  auto selected = _ui.ruleView->selectionModel()->selectedIndexes();
  auto id       = selected.constFirst().internalId();

  if (RuleDialog(id, this).exec() == QDialog::Rejected)
  {
    return;
  }

  emit _ruleModel.dataChanged(selected.constFirst(), selected.constLast());
  _vdmHookClient.setRulesEnabled(gRules->anyEnabled());
}

void MainWindow::on_refreshApplicationsButton_clicked(bool checked /* false */)
{
  Q_UNUSED(checked);

  _appWindows.refresh();
  _ui.applicationView->reset();
}

void MainWindow::on_removeRuleButton_clicked(bool checked /* false */)
{
  Q_UNUSED(checked);

  forever
  {
    auto selected = _ui.ruleView->selectionModel()->selectedRows();
    if (selected.isEmpty())
    {
      break;
    }

    _ruleModel.removeRow(selected.constFirst().row());
  }
}

void MainWindow::on_ruleView_customContextMenuRequested(const QPoint &pos) const
{
  auto selected = _ui.ruleView->selectionModel()->selectedRows();

  QMenu contextMenu;

  contextMenu.addAction(tr("Add"), this, &MainWindow::on_addRuleButton_clicked);

  auto editRule = contextMenu.addAction(tr("Edit"), this, &MainWindow::on_editRuleButton_clicked);
  editRule->setEnabled(selected.count() == 1);

  auto removeRule = contextMenu.addAction(tr("Remove"), this, &MainWindow::on_removeRuleButton_clicked);
  removeRule->setEnabled(!selected.isEmpty());

  contextMenu.addSeparator();

  auto applyRule2 = contextMenu.addAction(tr("Apply"), this, &MainWindow::on_applyRuleButton_clicked);
  applyRule2->setEnabled(!selected.isEmpty());

  contextMenu.exec(_ui.ruleView->mapToGlobal(pos));
}

void MainWindow::on_ruleView_doubleClicked(const QModelIndex &index)
{
  Q_UNUSED(index);

  _ui.editRuleButton->click();
}

void MainWindow::on_ruleView_selectionModel_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) const
{
  Q_UNUSED(selected);
  Q_UNUSED(deselected);

  auto selectedRows = _ui.ruleView->selectionModel()->selectedRows();

  _ui.editRuleButton->setEnabled(selectedRows.count() == 1);
  _ui.removeRuleButton->setEnabled(!selectedRows.isEmpty());
  _ui.applyRuleButton->setEnabled(!selectedRows.isEmpty());
}

void MainWindow::on_switchToButton_clicked(bool checked /* false */) const
{
  Q_UNUSED(checked);

  auto selected = _ui.applicationView->selectionModel()->selectedRows();
  auto appInfo  = &_appWindows.applications()->at(selected.constFirst().row());

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