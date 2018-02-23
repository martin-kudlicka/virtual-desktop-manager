#include "applicationmodel.h"

#include <QtCore/QDir>

ApplicationModel::ApplicationModel(const AppInfoList *applications) : _applications(applications)
{
}

int ApplicationModel::columnCount(const QModelIndex &parent /* QModelIndex() */) const
{
  return static_cast<int>(Column::Count);
}

QVariant ApplicationModel::data(const QModelIndex &index, int role /* Qt::DisplayRole */) const
{
  if (role != Qt::DisplayRole)
  {
    return QVariant();
  }

  auto appInfo = _applications->at(index.row());

  switch (index.column())
  {
    case Column::DesktopIndex:
      return appInfo.window().desktopIndex + 1;
    case Column::Path:
      return QDir::toNativeSeparators(appInfo.process().fileInfo.path());
    case Column::FileName:
      return appInfo.process().fileInfo.fileName();
    case Column::Title:
      return appInfo.window().title;
    case Column::Rule:
      {
        auto ruleOptions = appInfo.bestRule();
        if (ruleOptions.valid())
        {
          return ruleOptions.name();
        }
      }
      return QVariant();
  }

  Q_UNREACHABLE();
  return QVariant();
}

QVariant ApplicationModel::headerData(int section, Qt::Orientation orientation, int role /* Qt::DisplayRole */) const
{
  if (orientation == Qt::Orientation::Vertical || role != Qt::DisplayRole)
  {
    return QVariant();
  }

  switch (section)
  {
    case Column::DesktopIndex:
      return "#";
    case Column::Path:
      return tr("Path");
    case Column::FileName:
      return tr("Name");
    case Column::Title:
      return tr("Title");
    case Column::Rule:
      return tr("Rule");
  }

  Q_UNREACHABLE();
  return QVariant();
}

QModelIndex ApplicationModel::index(int row, int column, const QModelIndex &parent /* QModelIndex() */) const
{
  return createIndex(row, column);
}

QModelIndex ApplicationModel::parent(const QModelIndex &index) const
{
  return QModelIndex();
}

int ApplicationModel::rowCount(const QModelIndex &parent /* QModelIndex() */) const
{
  if (parent == QModelIndex())
  {
    return _applications->count();
  }
  else
  {
    return 0;
  }
}