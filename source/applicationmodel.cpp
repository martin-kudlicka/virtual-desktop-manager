#include "applicationmodel.h"

#include <QtCore/QDir>

ApplicationModel::ApplicationModel(const AppWindows::AppInfoList *applications) : QAbstractItemModel(), _applications(applications)
{
}

ApplicationModel::~ApplicationModel()
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
    case static_cast<int>(Column::DesktopIndex):
      return appInfo.window.desktopIndex + 1;
    case static_cast<int>(Column::Path):
      return QDir::toNativeSeparators(appInfo.process.fileInfo.path());
    case static_cast<int>(Column::FileName):
      return appInfo.process.fileInfo.completeBaseName();
    case static_cast<int>(Column::Title) :
      return appInfo.window.title;
    default:
      Q_UNREACHABLE();
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
    case static_cast<int>(Column::DesktopIndex):
      return tr("#");
    case static_cast<int>(Column::Path):
      return tr("Path");
    case static_cast<int>(Column::FileName):
      return tr("Name");
    case static_cast<int>(Column::Title) :
      return tr("Title");
    default:
      Q_UNREACHABLE();
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
    return _applications->size();
  }
  else
  {
    return 0;
  }
}