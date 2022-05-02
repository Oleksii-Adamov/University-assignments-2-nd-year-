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

    /// Get data
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /// Edit data
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    /// Add data
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    /// Remove data
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    /// sort m_list (by string representaion in alphabet order)
    void sort();

    /// increment number of done pomodoros by one for given task (from index)
    bool increment_pomodoros(const QModelIndex &index, int role = Qt::EditRole);

    /// returns m_list[i] = m_list[index->row()]
    ToDoListData ToDoListItemData(const QModelIndex &index, int role = Qt::DisplayRole);

    void load_from_file(const QString& file_path);

    void write_to_file(const QString& file_path);

private:
    std::vector<ToDoListData> m_list;
};

#endif // TODOLISTMODEL_H
