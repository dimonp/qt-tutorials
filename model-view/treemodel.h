#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>

class TreeModel final : public QAbstractItemModel {
    Q_OBJECT

    struct TreeItem {
        TreeItem *parentItem = nullptr;
        QList<TreeItem*> children;
        
        TreeItem(const std::initializer_list<TreeItem*> &children)
        {
            for (auto &child : children) {
                child->parentItem = this;
                this->children.push_back(child);
            }
        }

        ~TreeItem() 
        {
            qDeleteAll(children);
        }
    };

public:
    explicit TreeModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &index = QModelIndex()) const override;
    int columnCount(const QModelIndex &index = QModelIndex()) const override;

private:
    std::unique_ptr<TreeItem> rootItem;
};

#endif // TREEMODEL_H
