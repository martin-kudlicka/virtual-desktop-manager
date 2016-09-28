#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "applicationmodel.h"
#include <QtWidgets/QSystemTrayIcon>
#include "rulemodel.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
             MainWindow();
    virtual ~MainWindow() Q_DECL_OVERRIDE;

  private:
    ApplicationModel _applicationModel;
    AppWindows       _appWindows;
    Ui::MainWindow   _ui;
    RuleModel        _ruleModel;
    QMenu            _desktopIndexMenu;
    QSystemTrayIcon  _trayIcon;

    void applyRule            (const AppInfo &appInfo, const RuleOptions &ruleOptions) const;
    void applySettings        ();
    void registerHotkeys      () const;
    void setupApplicationModel();
    void setupRuleModel       ();

    virtual bool event      (QEvent *event)                                            Q_DECL_OVERRIDE;
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result) Q_DECL_OVERRIDE;

  private Q_SLOTS:
    void on_actionOptions_triggered                        (bool checked = false);
    void on_addRuleButton_clicked                          (bool checked = false);
    void on_applicationView_customContextMenuRequested     (const QPoint &pos);
    void on_applicationView_selectionModel_selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) const;
    void on_applyRuleButton_clicked                        (bool checked = false);
    void on_desktopIndexMenu_triggered                     (QAction *action);
    void on_editRuleButton_clicked                         (bool checked = false);
    void on_refreshApplicationsButton_clicked              (bool checked = false);
    void on_removeRuleButton_clicked                       (bool checked = false);
    void on_ruleView_customContextMenuRequested            (const QPoint &pos)                                                const;
    void on_ruleView_doubleClicked                         (const QModelIndex &index);
    void on_ruleView_selectionModel_selectionChanged       (const QItemSelection &selected, const QItemSelection &deselected) const;
    void on_switchToButton_clicked                         (bool checked = false)                                             const;
    void on_trayIcon_activated                             (QSystemTrayIcon::ActivationReason reason);
};

#endif