#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mxnote.h"

#include <QStringListModel>
#include <QVector>
#include <QSharedPointer>


class MXNote : public QMainWindow
{
    Q_OBJECT

public:
    MXNote(QWidget *parent = Q_NULLPTR);
    ~MXNote();

signals:
    void sig_help();

public slots:
    void slot_hotkey_show();
    void slot_hotkey_exit();

    void slot_help();
    
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

protected:
    void load();
    void load_note();
    void save();
    void save_note(bool toCache);

    void create_note();

    void open_note();

    void rename_note();

    void delete_note();

protected slots:
    void slot_list_entered(const QModelIndex &index);
    void slot_title_changed(const QString &title);

private:
    Ui::MXNoteClass ui;

    QStringListModel*       m_list_model;

private:
    bool m_onHelp = false;

    QString                 m_current_note_title;
    QString                 m_current_note_name;

    QStringList             m_note_list;

    struct Note
    {
        QString title;
        QString name;
        QString data;
    };
    typedef QSharedPointer<Note> NotePtr;
    QVector<NotePtr>        m_all_note;
};
