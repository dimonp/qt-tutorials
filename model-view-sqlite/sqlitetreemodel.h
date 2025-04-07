#ifndef SQLITE_TREEMODEL_H
#define SQLITE_TREEMODEL_H

#include <QAbstractItemModel>

struct sqlite3;

class SqliteTreeModel final : public QAbstractItemModel {
    Q_OBJECT

    struct TreeItem;
    using LoadCallback = std::function<QList<QString>(SqliteTreeModel*, const QString &name)>;

    enum SchemaObjectType {
        UNDEFINED = -1,
        TABLE,
        INDEX,
        VIEW,
        TRIGGER,
        COLUMN
    };

    struct SchemaObjectInfo {
        QString iconName;
        LoadCallback expandCallback;
        SchemaObjectType childType = UNDEFINED;
    };

    struct TreeItem {
        QString title;
        TreeItem *parentItem = nullptr;
        QList<TreeItem*> children;
        bool hasMoreChildren;
        SchemaObjectType type;

        TreeItem(const QString &title, SchemaObjectType type, const std::initializer_list<TreeItem*> &children)
            : title(title), hasMoreChildren(false), type(type)
        {
            appendChildren(children.begin(), children.end());
        }

        TreeItem(const QString &title, SchemaObjectType type)
            : title(title), hasMoreChildren(true),  type(type)
        {
        }

        void appendChildren(const std::initializer_list<TreeItem*> &children) 
        {
            appendChildren(children.begin(), children.end());
        }

        template <typename Iterator>
        void appendChildren(Iterator begin, Iterator end) 
        {
            for (auto it = begin; it < end; ++it) {
                appendChild(*it);
            }
        }

        void appendChild(TreeItem *child) {
            child->parentItem = this;
            this->children.push_back(child);
        }

        void clearChildren() 
        {
            qDeleteAll(children);
            children.clear();
        }

        ~TreeItem() 
        {
            clearChildren();
        }
    };

public:
    explicit SqliteTreeModel(QObject *parent = nullptr);
    ~SqliteTreeModel() override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &index = QModelIndex()) const override;
    int columnCount(const QModelIndex &index = QModelIndex()) const override;

    bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;
    bool canFetchMore(const QModelIndex &parent) const override;
    void fetchMore(const QModelIndex &parent) override;

    bool open(const QString &dbName);
    void close();
    void populateModel();

private:
    QList<QString> loadObjects(const QString &relationType);
    QList<QString> loadColumns(const QString &tableName);

    QList<QString> doQuery(const char *sql, int column);



    sqlite3* db = nullptr;
    std::unique_ptr<TreeItem> rootItem;
    QHash<SchemaObjectType, SchemaObjectInfo> schemaObjects;
};

#endif // SQLITE_TREEMODEL_H
