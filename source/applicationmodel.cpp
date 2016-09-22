#include "applicationmodel.h"

#include "appwindows.h"
#include <QtCore/QDir>

ApplicationModel::ApplicationModel(const AppWindows *appWindows) : QAbstractItemModel(), _appWindows(appWindows)
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

  auto appInfo = _appWindows->applications()->at(index.row());

  switch (index.column())
  {
    case static_cast<int>(Column::DesktopIndex):
      return appInfo.window.desktopIndex;
    case static_cast<int>(Column::Path):
      return QDir::toNativeSeparators(appInfo.process.fileInfo.path());
    case static_cast<int>(Column::FileName):
      return appInfo.process.fileInfo.completeBaseName();
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
    return _appWindows->applications()->size();
  }
  else
  {
    return 0;
  }
}