#include "mxnotelistmodel.h"

MXNoteListModel::MXNoteListModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QModelIndex MXNoteListModel::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex MXNoteListModel::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int MXNoteListModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int MXNoteListModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant MXNoteListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
