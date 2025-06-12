#include <QAction>
#include <QModelIndex>

#include "treemodel.h"

TreeModel::TreeModel(QObject *parent) : QAbstractItemModel(parent)
{
    // very simple tree structure
    TreeItem *item = new TreeItem({
        new TreeItem { },
        new TreeItem {
            new TreeItem { },
            new TreeItem { 
                new TreeItem { }
            }
        },
        new TreeItem { 
            new TreeItem { }
        }
    });

    rootItem.reset(item);
}

QVariant TreeModel::data(const QModelIndex &index, int role) const 
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    return QString::asprintf("row=%d, col=%d", index.row(), index.column());
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        return QString::asprintf("head=%d", section);
    }

    return QVariant();
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const 
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    const TreeItem *parentItem;
    if (!parent.isValid())
        parentItem = rootItem.get();
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    if (row < 0 || row >= parentItem->children.size()) {
        return QModelIndex();
    } 

    const TreeItem *childItem = parentItem->children.at(row);
    return createIndex(row, column, childItem);
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    const TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    const TreeItem *parentItem = item->parentItem;

    if (parentItem == rootItem.get())
        return QModelIndex();

    const TreeItem *parentOfParentItem = parentItem->parentItem;
    int row = parentOfParentItem->children.indexOf(const_cast<TreeItem*>(parentItem));

    return createIndex(row, 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const 
{
    if (parent.column() > 0)
        return 0;

    const TreeItem *parentItem;
    if (!parent.isValid())
        parentItem = rootItem.get();
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->children.size();
}

int TreeModel::columnCount(const QModelIndex &parent) const 
{
    return 2;
}