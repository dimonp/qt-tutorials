#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractItemModel>

class TableModel final : public QAbstractTableModel {
    Q_OBJECT

public:
    explicit TableModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    int rowCount(const QModelIndex &index = QModelIndex()) const override;
    int columnCount(const QModelIndex &index = QModelIndex()) const override;
};

#endif // TABLEMODEL_H
