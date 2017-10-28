#ifndef APPLICATIONMODEL_H
#define APPLICATIONMODEL_H

#include <QtCore/QAbstractItemModel>
#include "appwindows.h"

class ApplicationModel : public QAbstractItemModel
{
  public:
             ApplicationModel(const AppInfoList *applications);
    virtual ~ApplicationModel() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

  private:
    enum class Column
    {
      DesktopIndex,
      Path,
      FileName,
      Title,
      Rule,
      Count
    };

    const AppInfoList *_applications;

    virtual int         columnCount(const QModelIndex &parent = QModelIndex())                            const Q_DECL_OVERRIDE;
    virtual QVariant    data       (const QModelIndex &index, int role = Qt::DisplayRole)                 const Q_DECL_OVERRIDE;
    virtual QVariant    headerData (int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    virtual QModelIndex index      (int row, int column, const QModelIndex &parent = QModelIndex())       const Q_DECL_OVERRIDE;
    virtual QModelIndex parent     (const QModelIndex &index)                                             const Q_DECL_OVERRIDE;
    virtual int         rowCount   (const QModelIndex &parent = QModelIndex())                            const Q_DECL_OVERRIDE;
};

#endif