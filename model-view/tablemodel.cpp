#include <QAction>
#include <QModelIndex>

#include "tablemodel.h"

TableModel::TableModel(QObject *parent) : QAbstractTableModel(parent) {}

QVariant TableModel::data(const QModelIndex &index, int role) const 
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    return QString::asprintf("row=%d, col=%d", index.row(), index.column());
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        return QString::asprintf("head=%d", section);

    }

    return QVariant();
}

int TableModel::rowCount(const QModelIndex &parent) const 
{
    return 4;
}

int TableModel::columnCount(const QModelIndex &parent) const 
{
    return 3;
}