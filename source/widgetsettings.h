#ifndef WIDGETSETTINGS_H
#define WIDGETSETTINGS_H

#include <QtCore/QHash>
#include <QtCore/QString>
#include <QtWidgets/QSizePolicy>

class QCheckBox;
class QComboBox;
class QLineEdit;
class QRadioButton;
class QSpinBox;
class QWidget;
class Settings;

typedef QList<QRadioButton *> QRadioButtonPtrList;

class WidgetSettings
{
  public:
    WidgetSettings(Settings *settings);

    void load     () const;
    void save     () const;
    void setWidget(const QString &key, QRadioButtonPtrList &&radioGroup, Settings *settings = Q_NULLPTR);
    void setWidget(const QString &key, QWidget *widget, Settings *settings = Q_NULLPTR);

  private:
    struct WidgetData
    {
      QRadioButtonPtrList radioGroup;
      QWidget            *widget;
      Settings           *settings;

      WidgetData();
    };

    QHash<QString, WidgetData> _widgets;
    Settings                  *_settings;

    QSizePolicy::ControlType type            (const QWidget *widget)                                                                                const;
    void                     update          (bool save)                                                                                            const;
    void                     updateCheckBox  (bool save, const QString &key, QCheckBox *checkBox, Settings *settings = Q_NULLPTR)                   const;
    void                     updateComboBox  (bool save, const QString &key, QComboBox *comboBox, Settings *settings = Q_NULLPTR)                   const;
    void                     updateLineEdit  (bool save, const QString &key, QLineEdit *lineEdit, Settings *settings = Q_NULLPTR)                   const;
    void                     updateRadioGroup(bool save, const QString &key, const QRadioButtonPtrList &radioGroup, Settings *settings = Q_NULLPTR) const;
    void                     updateSpinBox   (bool save, const QString &key, QSpinBox *spinBox, Settings *settings = Q_NULLPTR)                     const;
};

#endif