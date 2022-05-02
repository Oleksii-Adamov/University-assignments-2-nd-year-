#ifndef TODOLISTMODEL_H
#define TODOLISTMODEL_H

#include <QAbstractListModel>
#include "todolistdata.h"

class ToDoListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ToDoListModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    void sort();

    bool increment_pomodoros(const QModelIndex &index, int role = Qt::EditRole);

    ToDoListData ToDoListItemData(const QModelIndex &index, int role = Qt::DisplayRole);

private:
    std::vector<ToDoListData> m_list;
};

#endif // TODOLISTMODEL_H
