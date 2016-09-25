#include "widgetsettings.h"

#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QRadioButton>
#include <MkCore/MSettings>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLineEdit>

WidgetSettings::WidgetSettings(MSettings *settings) : _settings(settings)
{
}

void WidgetSettings::load() const
{
  update(false);
}

void WidgetSettings::save() const
{
  update(true);
}

void WidgetSettings::setWidget(const QString &key, QRadioButtonPtrList &&radioGroup, MSettings *settings /* Q_NULLPTR */)
{
  WidgetData widgetData;
  widgetData.radioGroup = qMove(radioGroup);
  widgetData.settings   = settings;
  _widgets.insert(key, qMove(widgetData));
}

void WidgetSettings::setWidget(const QString &key, QWidget *widget, MSettings *settings /* Q_NULLPTR */)
{
  WidgetData widgetData;
  widgetData.widget   = widget;
  widgetData.settings = settings;
  _widgets.insert(key, qMove(widgetData));
}

QSizePolicy::ControlType WidgetSettings::type(const QWidget *widget) const
{
  {
    auto *checkBox = qobject_cast<const QCheckBox *>(widget);
    if (checkBox)
    {
      return QSizePolicy::CheckBox;
    }
  }
  {
    auto *comboBox = qobject_cast<const QComboBox *>(widget);
    if (comboBox)
    {
      return QSizePolicy::ComboBox;
    }
  }
  {
    auto *lineEdit = qobject_cast<const QLineEdit *>(widget);
    if (lineEdit)
    {
      return QSizePolicy::LineEdit;
    }
  }
  {
    auto *spinBox = qobject_cast<const QSpinBox *>(widget);
    if (spinBox)
    {
      return QSizePolicy::SpinBox;
    }
  }

  Q_UNREACHABLE();
  return QSizePolicy::DefaultType;
}

void WidgetSettings::update(bool save) const
{
  for (auto widgetData = _widgets.constBegin(); widgetData != _widgets.constEnd(); widgetData++)
  {
    if (!widgetData->radioGroup.empty())
    {
      updateRadioGroup(save, widgetData.key(), widgetData->radioGroup, widgetData->settings);
    }
    else
    {
      auto widgetType = type(widgetData->widget);
      switch (widgetType)
      {
        case QSizePolicy::CheckBox:
          updateCheckBox(save, widgetData.key(), qobject_cast<QCheckBox *>(widgetData->widget), widgetData->settings);
          break;
        case QSizePolicy::ComboBox:
          updateComboBox(save, widgetData.key(), qobject_cast<QComboBox *>(widgetData->widget), widgetData->settings);
          break;
        case QSizePolicy::LineEdit:
          updateLineEdit(save, widgetData.key(), qobject_cast<QLineEdit *>(widgetData->widget), widgetData->settings);
          break;
        case QSizePolicy::SpinBox:
          updateSpinBox(save, widgetData.key(), qobject_cast<QSpinBox *>(widgetData->widget), widgetData->settings);
          break;
        default:
          Q_UNREACHABLE();
      }
    }
  }
}

void WidgetSettings::updateCheckBox(bool save, const QString &key, QCheckBox *checkBox, MSettings *settings /* Q_NULLPTR */) const
{
  if (!settings)
  {
    settings = _settings;
  }

  if (save)
  {
    settings->setValue(key, checkBox->checkState());
  }
  else
  {
    checkBox->setCheckState(static_cast<Qt::CheckState>(settings->value(key).toUInt()));
  }
}

void WidgetSettings::updateComboBox(bool save, const QString &key, QComboBox *comboBox, MSettings *settings /* Q_NULLPTR */) const
{
  if (!settings)
  {
    settings = _settings;
  }

  if (save)
  {
    settings->setValue(key, comboBox->currentData());
  }
  else
  {
    for (auto index = 0; index < comboBox->count(); index++)
    {
      if (comboBox->itemData(index) == settings->value(key))
      {
        comboBox->setCurrentIndex(index);
        return;
      }
    }
  }
}

void WidgetSettings::updateLineEdit(bool save, const QString &key, QLineEdit *lineEdit, MSettings *settings /* Q_NULLPTR */) const
{
  if (!settings)
  {
    settings = _settings;
  }

  if (save)
  {
    settings->setValue(key, lineEdit->text());
  }
  else
  {
    lineEdit->setText(settings->value(key).toString());
  }
}

void WidgetSettings::updateRadioGroup(bool save, const QString &key, const QRadioButtonPtrList &radioGroup, MSettings *settings /* Q_NULLPTR */) const
{
  if (!settings)
  {
    settings = _settings;
  }

  if (save)
  {
    qintptr index;
    for (index = 0; index < radioGroup.size(); index++)
    {
      if (radioGroup.at(index)->isChecked())
      {
        break;
      }
    }

    settings->setValue(key, index);
  }
  else
  {
    for (auto index = 0; index < radioGroup.size(); index++)
    {
      if (index == settings->value(key).toInt())
      {
        radioGroup.at(index)->setChecked(true);
        break;
      }
    }
  }
}

void WidgetSettings::updateSpinBox(bool save, const QString &key, QSpinBox *spinBox, MSettings *settings /* Q_NULLPTR */) const
{
  if (!settings)
  {
    settings = _settings;
  }

  if (save)
  {
    settings->setValue(key, spinBox->value());
  }
  else
  {
    spinBox->setValue(settings->value(key).toInt());
  }
}

WidgetSettings::WidgetData::WidgetData() : widget(Q_NULLPTR), settings(Q_NULLPTR)
{
}