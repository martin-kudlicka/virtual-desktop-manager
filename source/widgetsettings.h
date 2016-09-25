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
class MSettings;

using QRadioButtonPtrList = QList<QRadioButton *>;

class WidgetSettings
{
  public:
    WidgetSettings(MSettings *settings);

    void load     () const;
    void save     () const;
    void setWidget(const QString &key, QRadioButtonPtrList &&radioGroup, MSettings *settings = Q_NULLPTR);
    void setWidget(const QString &key, QWidget *widget, MSettings *settings = Q_NULLPTR);

  private:
    struct WidgetData
    {
      QRadioButtonPtrList radioGroup;
      QWidget            *widget;
      MSettings          *settings;

      WidgetData();
    };

    QHash<QString, WidgetData> _widgets;
    MSettings                 *_settings;

    QSizePolicy::ControlType type            (const QWidget *widget)                                                                                 const;
    void                     update          (bool save)                                                                                             const;
    void                     updateCheckBox  (bool save, const QString &key, QCheckBox *checkBox, MSettings *settings = Q_NULLPTR)                   const;
    void                     updateComboBox  (bool save, const QString &key, QComboBox *comboBox, MSettings *settings = Q_NULLPTR)                   const;
    void                     updateLineEdit  (bool save, const QString &key, QLineEdit *lineEdit, MSettings *settings = Q_NULLPTR)                   const;
    void                     updateRadioGroup(bool save, const QString &key, const QRadioButtonPtrList &radioGroup, MSettings *settings = Q_NULLPTR) const;
    void                     updateSpinBox   (bool save, const QString &key, QSpinBox *spinBox, MSettings *settings = Q_NULLPTR)                     const;
};

#endif