#include "todolistmodel.h"

ToDoListModel::ToDoListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int ToDoListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_list.size();
}

QVariant ToDoListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || std::size_t(index.row()) >= m_list.size())
        return QVariant();
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return QVariant(m_list[std::size_t(index.row())].ToQString());
    return QVariant();
}

bool ToDoListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole && data(index, role) != value) {
        m_list[std::size_t(index.row())] = value.value<ToDoListData>();
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags ToDoListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool ToDoListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    m_list.insert(m_list.begin() + row, count, ToDoListData());
    endInsertRows();
    return true;
}

bool ToDoListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    m_list.erase(m_list.begin() + row, m_list.begin() + row + count);
    endRemoveRows();
    return true;
}

