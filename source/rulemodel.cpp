#include "rulemodel.h"

#include "rules.h"
#include <QtCore/QUuid>
#include "ruleoptions.h"

RuleModel::RuleModel(const Rules *rules) : QAbstractItemModel(), _rules(rules)
{
}

RuleModel::~RuleModel()
{
}

int RuleModel::columnCount(const QModelIndex &parent /* QModelIndex() */) const
{
  return static_cast<int>(Column::Count);
}

QVariant RuleModel::data(const QModelIndex &index, int role /* Qt::DisplayRole */) const
{
  if (role != Qt::DisplayRole && role != Qt::CheckStateRole)
  {
    return QVariant();
  }

  auto id      = _rules->id(index.row());
  RuleOptions options(id);

  switch (role)
  {
    case Qt::DisplayRole:
      switch (index.column())
      {
        case static_cast<int>(Column::Name):
          return options.name();
        case static_cast<int>(Column::Process) :
          return options.process();
        case static_cast<int>(Column::Title) :
          return options.title();
        case static_cast<int>(Column::Class) :
          return options.className();
        default:
          return QVariant();
      }
    case Qt::CheckStateRole:
      switch (index.column())
      {
        case static_cast<int>(Column::Enabled) :
          return options.enabled();
        default:
          return QVariant();
      }
  }

  Q_UNREACHABLE();
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
    case static_cast<int>(Column::Enabled):
      return "*";
    case static_cast<int>(Column::Name):
      return tr("Name");
    case static_cast<int>(Column::Process):
      return tr("Process");
    case static_cast<int>(Column::Title):
      return tr("Title");
    case static_cast<int>(Column::Class) :
      return tr("Class");
    default:
      Q_UNREACHABLE();
  }

  Q_UNREACHABLE();
  return QVariant();
}

QModelIndex RuleModel::index(int row, int column, const QModelIndex &parent /* QModelIndex() */) const
{
  return createIndex(row, column);
}

QModelIndex RuleModel::parent(const QModelIndex &index) const
{
  return QModelIndex();
}

int RuleModel::rowCount(const QModelIndex &parent /* QModelIndex() */) const
{
  if (parent == QModelIndex())
  {
    return _rules->size();
  }
  else
  {
    return 0;
  }
}