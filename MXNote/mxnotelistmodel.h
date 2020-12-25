#ifndef MXNOTELISTMODEL_H
#define MXNOTELISTMODEL_H

#include <QAbstractItemModel>

class MXNoteListModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit MXNoteListModel(QObject *parent = 0);

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

#endif // MXNOTELISTMODEL_H
