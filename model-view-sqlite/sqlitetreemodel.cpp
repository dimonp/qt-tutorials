#include <QModelIndex>
#include <QIcon>

#include "sqlitetreemodel.h"
#include <sqlite3.h>

SqliteTreeModel::SqliteTreeModel(QObject *parent) 
    : QAbstractItemModel(parent)
{
    populateModel();

    schemaObjects = {
        { TABLE,    {":/icon/table.png",    &SqliteTreeModel::loadObjects, &SqliteTreeModel::loadDetails, COLUMN}},
        { INDEX,    {":/icon/index.png",    &SqliteTreeModel::loadObjects, &SqliteTreeModel::loadDetails}},
        { VIEW,     {":/icon/view.png",     &SqliteTreeModel::loadObjects, &SqliteTreeModel::loadDetails, COLUMN}},
        { TRIGGER,  {":/icon/trigger.png",  &SqliteTreeModel::loadObjects, &SqliteTreeModel::loadDetails}},
        { COLUMN,   {":/icon/column.png",   &SqliteTreeModel::loadColumns, &SqliteTreeModel::loadDetails}}
    };
}

SqliteTreeModel::~SqliteTreeModel()
{
    close();
}

bool SqliteTreeModel::open(const QString &dbFileName) 
{
    if (dbFileName.isEmpty()) {
        return false;
    }

    close();

    int rc = sqlite3_open(dbFileName.toStdString().c_str(), &db);
    if (rc != SQLITE_OK) {
        return false;
    } else {
        populateModel();
    }

    return true;
}

void SqliteTreeModel::close() 
{
    sqlite3_close(db);
    db = nullptr;
}

void SqliteTreeModel::populateModel() 
{    
    TreeItem *root = new TreeItem("root", UNDEFINED, {
        new TreeItem("table", TABLE),
        new TreeItem("index", INDEX),
        new TreeItem("view", VIEW),
        new TreeItem("trigger", TRIGGER)
    });

    beginResetModel();
    rootItem.reset(root);
    endResetModel();
}

QList<QString> SqliteTreeModel::loadObjects(const QString &relationType)
{
    const char *sql = "SELECT name FROM sqlite_master WHERE type='%1'";
    return doQuery(QString(sql).arg(relationType).toStdString().c_str(), 0);
}

QList<QString> SqliteTreeModel::loadColumns(const QString &tableName) 
{
    const char *sql = "PRAGMA table_info('%1')";
    return doQuery(QString(sql).arg(tableName).toStdString().c_str(), 1);
}

QString SqliteTreeModel::loadDetails(const QString &relationType, const QString &name)
{
    const char *sql = "SELECT sql FROM sqlite_master WHERE type='%1' and name='%2'";
    auto result =  doQuery(QString(sql).arg(relationType, name).toStdString().c_str(), 0);
    return result.isEmpty() ? "" : result.first();
}


QList<QString> SqliteTreeModel::doQuery(const char *sql, int column) {
    if (this->db != nullptr) {
        sqlite3_stmt *stmt;

        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            return QList<QString>();
        }

        QList<QString> result;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            result.push_back(QString(reinterpret_cast<const char*>(sqlite3_column_text(stmt, column))));
        }

        sqlite3_finalize(stmt);
        return result;
    }
    return QList<QString>();
}

QVariant SqliteTreeModel::data(const QModelIndex &index, int role) const 
{
    if (!index.isValid())
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    if (role == Qt::DisplayRole) {
        int childCount = item->children.size();
        return item->title + ( childCount > 0 ? QString(" (%2)").arg(childCount) : QString() );
    } else if (role == Qt::DecorationRole && schemaObjects.contains(item->type)) {
        const SchemaObjectInfo &info = schemaObjects[item->type];
        return QIcon(info.iconName);
    }

    return QVariant();
}

QVariant SqliteTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        return "schema";
    }

    return QVariant();
}

Qt::ItemFlags SqliteTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}

QModelIndex SqliteTreeModel::index(int row, int column, const QModelIndex &parent) const 
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

QModelIndex SqliteTreeModel::parent(const QModelIndex &index) const
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

int SqliteTreeModel::rowCount(const QModelIndex &parent) const 
{
	if (!parent.isValid()) {
		return rootItem->children.size();
	}

    TreeItem *parentItem = static_cast<TreeItem*>(parent.internalPointer());
	return parentItem->children.size();
}

int SqliteTreeModel::columnCount(const QModelIndex &parent) const 
{
    return 1;
}

bool SqliteTreeModel::hasChildren(const QModelIndex &parent) const
{
    TreeItem *parentItem = static_cast<TreeItem*>(parent.internalPointer());

    if (parentItem != nullptr && parentItem->type != UNDEFINED) {
        return parentItem->children.size() > 0 || parentItem->hasMoreChildren;
    }

	return QAbstractItemModel::hasChildren(parent);
}

bool SqliteTreeModel::canFetchMore(const QModelIndex &parent) const
{
	if (!parent.isValid()) {
		return false;
	}

    TreeItem *parentItem = static_cast<TreeItem*>(parent.internalPointer());
    if (parentItem != nullptr) {
        return parentItem->hasMoreChildren;
    }

    return false;
}

void SqliteTreeModel::fetchMore(const QModelIndex &parent)
{
    TreeItem *parentItem = static_cast<TreeItem*>(parent.internalPointer());
    if (parentItem == nullptr) {
        parentItem = rootItem.get();
    }

    if (schemaObjects.contains(parentItem->type)) {
        const SchemaObjectInfo &info = schemaObjects[parentItem->type];

        QList<QString> loadedItems = info.expandCallback(this, parentItem->title);

        beginInsertRows(parent, 0, loadedItems.size() - 1);
        for(const QString &item : loadedItems) {
            parentItem->appendChild(new TreeItem(item, info.childType));
        }
        endInsertRows();

        parentItem->hasMoreChildren = false;
    }
}

QString SqliteTreeModel::getDetails(const QModelIndex &index) 
{
    if (!index.isValid())
        return "";

    const TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    const TreeItem *parentItem = item->parentItem;

    if (parentItem == rootItem.get()) 
        return "";

    SchemaObjectInfo &info = schemaObjects[parentItem->type];

    return info.detailsCallback(this, parentItem->title, item->title);
}