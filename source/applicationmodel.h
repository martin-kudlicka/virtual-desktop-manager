#ifndef APPLICATIONMODEL_H
#define APPLICATIONMODEL_H

#include <QtCore/QAbstractItemModel>

class AppWindows;

class ApplicationModel : public QAbstractItemModel
{
  public:
             ApplicationModel(const AppWindows *appWindows);
    virtual ~ApplicationModel();

  private:
    enum class Column
    {
      DesktopIndex,
      Path,
      FileName,
      Count
    };

    const AppWindows *_appWindows;

    virtual int         columnCount(const QModelIndex &parent = QModelIndex())                            const Q_DECL_OVERRIDE;
    virtual QVariant    data       (const QModelIndex &index, int role = Qt::DisplayRole)                 const Q_DECL_OVERRIDE;
    virtual QVariant    headerData (int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    virtual QModelIndex index      (int row, int column, const QModelIndex &parent = QModelIndex())       const Q_DECL_OVERRIDE;
    virtual QModelIndex parent     (const QModelIndex &index)                                             const Q_DECL_OVERRIDE;
    virtual int         rowCount   (const QModelIndex &parent = QModelIndex())                            const Q_DECL_OVERRIDE;
};

#endif