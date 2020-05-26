#include "pch.h"
#include "rulemodel.h"

#include "rules.h"
#include "ruleoptions.h"

int RuleModel::columnCount(const QModelIndex &parent /* QModelIndex() */) const
{
  Q_UNUSED(parent);

  return static_cast<int>(Column::Count);
}

QVariant RuleModel::data(const QModelIndex &index, int role /* Qt::DisplayRole */) const
{
  if (role != Qt::DisplayRole && role != Qt::CheckStateRole)
  {
    return QVariant();
  }

  RuleOptions options(index.internalId());

  switch (role)
  {
    case Qt::DisplayRole:
      switch (index.column())
      {
        case Column::Name:
          return options.name();
        case Column::Process:
          return options.process();
        case Column::Title:
          return options.title();
        case Column::Class:
          return options.className();
      }
      break;
    case Qt::CheckStateRole:
      switch (index.column())
      {
        case Column::Enabled:
          return options.enabled();
      }
  }

  return QVariant();
}

QVariant RuleModel::headerData(int section, Qt::Orientation orientation, int role /* Qt::DisplayRole */) const
{
  if (orientation == Qt::Orientation::Vertical || role != Qt::DisplayRole)
  {
    return QVariant();
  }

  switch (section)
  {
    case Column::Enabled:
      return "*";
    case Column::Name:
      return tr("Name");
    case Column::Process:
      return tr("Process");
    case Column::Title:
      return tr("Title");
    case Column::Class:
      return tr("Class");
  }

  Q_UNREACHABLE();
  return QVariant();
}

QModelIndex RuleModel::index(int row, int column, const QModelIndex &parent /* QModelIndex() */) const
{
  Q_UNUSED(parent);

  if (gRules->isEmpty())
  {
    return createIndex(row, column);
  }

  return createIndex(row, column, gRules->id(row));
}

bool RuleModel::insertRows(int row, int count, const QModelIndex &parent /* QModelIndex() */)
{
  beginInsertRows(parent, row, row + count - 1);
  // already added
  endInsertRows();

  return true;
}

QModelIndex RuleModel::parent(const QModelIndex &index) const
{
  Q_UNUSED(index);

  return QModelIndex();
}

bool RuleModel::removeRows(int row, int count, const QModelIndex &parent /* QModelIndex() */)
{
  beginRemoveRows(parent, row, row + count - 1);

  gRules->removeIndex(row);

  endRemoveRows();

  return true;
}

int RuleModel::rowCount(const QModelIndex &parent /* QModelIndex() */) const
{
  if (parent.isValid())
  {
    return 0;
  }
  else
  {
    return gRules->count();
  }
}