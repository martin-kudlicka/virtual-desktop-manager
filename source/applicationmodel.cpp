#include "pch.h"
#include "applicationmodel.h"

ApplicationModel::ApplicationModel(const AppInfoList *applications) : _applications(applications)
{
}

int ApplicationModel::columnCount(const QModelIndex &parent /* QModelIndex() */) const
{
  Q_UNUSED(parent);

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
  Q_UNUSED(parent);

  return createIndex(row, column);
}

QModelIndex ApplicationModel::parent(const QModelIndex &index) const
{
  Q_UNUSED(index);

  return QModelIndex();
}

int ApplicationModel::rowCount(const QModelIndex &parent /* QModelIndex() */) const
{
  if (parent.isValid())
  {
    return 0;
  }
  else
  {
    return _applications->count();
  }
}