#ifndef RULEMODEL_H
#define RULEMODEL_H

#include <QtCore/QAbstractItemModel>

class MUuidPtr;
class Rules;

class RuleModel : public QAbstractItemModel
{
  public:
             RuleModel(const Rules *rules);
    virtual ~RuleModel() Q_DECL_OVERRIDE;

  private:
    enum class Column
    {
      Enabled,
      Name,
      Process,
      Title,
      Class,
      Count
    };

    const Rules *_rules;

    virtual int         columnCount(const QModelIndex &parent = QModelIndex())                            const Q_DECL_OVERRIDE;
    virtual QVariant    data       (const QModelIndex &index, int role = Qt::DisplayRole)                 const Q_DECL_OVERRIDE;
    virtual QVariant    headerData (int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    virtual QModelIndex index      (int row, int column, const QModelIndex &parent = QModelIndex())       const Q_DECL_OVERRIDE;
    virtual bool        insertRows (int row, int count, const QModelIndex &parent = QModelIndex())              Q_DECL_OVERRIDE;
    virtual QModelIndex parent     (const QModelIndex &index)                                             const Q_DECL_OVERRIDE;
    virtual bool        removeRows (int row, int count, const QModelIndex &parent = QModelIndex())              Q_DECL_OVERRIDE;
    virtual int         rowCount   (const QModelIndex &parent = QModelIndex())                            const Q_DECL_OVERRIDE;
};

#endif