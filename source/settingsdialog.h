#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "ui_settingsdialog.h"

class SettingsDialog : public QDialog
{
	public:
		SettingsDialog(QWidget *parent = Q_NULLPTR);

	private:
		Ui::SettingsDialog _ui;
};

#endif
