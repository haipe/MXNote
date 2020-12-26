﻿#include "mxnote.h"
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QScreen>
#include <QKeyEvent>
#include <QStringListModel>
#include <QStandardPaths>

#include <QDir>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include <QDateTime>

#include "mx-common.h"


MXNote::MXNote(QWidget *parent)
    : QMainWindow(parent)
{
    QString folder = APP_DATA_FOLDER + "/";
    QDir().mkpath(folder + "note/");

    ui.setupUi(this);

    this->setWindowFlags(Qt::Sheet);

    QObject::connect(this, SIGNAL(sig_help()), this, SLOT(slot_help()), Qt::QueuedConnection);

    installEventFilter(this);

    load();
    m_list_model = new QStringListModel(m_note_list);
    ui.listView->setModel(m_list_model);

    bool needCreate = (m_note_list.isEmpty());
    if(needCreate)
        create_note();

    load_note();

    if(!needCreate)
    {
        QModelIndex qindex = m_list_model->index(0);   //默认选中 0
        ui.listView->setCurrentIndex(qindex);
    }

    ui.listView->setVisible(false);

    QObject::connect(ui.listView,SIGNAL(pressed(const QModelIndex &)),this,SLOT(slot_list_entered(const QModelIndex &)));
    QObject::connect(ui.listView,SIGNAL(windowTitleChanged(const QString &)),this,SLOT(slot_title_changed(const QString &)));
}

MXNote::~MXNote()
{
    qDebug() << "~MXNote";
}

void MXNote::slot_hotkey_show()
{
    //
    QPoint coursePoint = QCursor::pos();//获取当前光标的位置
    coursePoint.setX(coursePoint.x() + 2);
    coursePoint.setY(coursePoint.y() + 2);

    QRect selfRc = geometry();

    QScreen* sc = QGuiApplication::primaryScreen();
    if (sc)
    {
        QRect rc = sc->availableGeometry();
        if (coursePoint.x() > (rc.right() - selfRc.width()))
            coursePoint.setX(coursePoint.x() - selfRc.width());

        if (coursePoint.y() > (rc.bottom() - selfRc.height()))
            coursePoint.setY(coursePoint.y() - selfRc.height());
    }

    move(coursePoint);
    show();
    this->activateWindow();

    setFocus();
    if(ui.textEdit->isVisible())
        ui.textEdit->setFocus();
    else if(ui.listView->isVisible())
        ui.listView->setFocus();
}

void MXNote::slot_hotkey_exit()
{
    qDebug() << "slot_hotkey_exit ";

    save_note(false);
    save();

    qApp->quit();
}

void MXNote::slot_help()
{
    qDebug() << "slot_help";
    QString ss;
    ss += "Wellcome to MXNote.\n\n";
    ss += "Ctrl + Sift + S: Show MXNote.\n";
    ss += "Ctrl + Sift + Q: Quit MXNote.\n";

    QMessageBox::information(this, QStringLiteral("MXNote"), ss);
    m_onHelp = false;
}

bool MXNote::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == this)
    {
        //qDebug() << "eventFilter " << event->type() << ", o " << obj;
        if (event->type() == QEvent::WindowDeactivate)
        {
            //切换焦点时消失
            if (!m_onHelp)
            {
                if(ui.textEdit->isVisible())
                    save_note(true);

                hide();
            }
        }
        else if (event->type() == QEvent::WhatsThis)
        {
            m_onHelp = true;
            emit sig_help();
        }
        else if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *e = static_cast<QKeyEvent*>(event);
            //qDebug() << "eventFilter " << e->key() << ", o " << e;
            if (e->key() == Qt::Key_W && (e->modifiers() & Qt::ControlModifier))
            {
                //close to list
                save_note(false);

                ui.textEdit->clear();

                ui.listView->setVisible(true);
                ui.listView->setFocus();

                ui.textEdit->setVisible(false);
            }
            else if (e->key() == Qt::Key_S && (e->modifiers() & Qt::ControlModifier))
            {
                //save
                save_note(false);
            }
            else if (e->key() == Qt::Key_N && (e->modifiers() & Qt::ControlModifier))
            {
                //new
                save_note(false);

                create_note();
                load_note();
            }
            else if (e->key() == Qt::Key_L && (e->modifiers() & Qt::ControlModifier))
            {
                //show list
                bool willVisible = !ui.listView->isVisible() || !ui.textEdit->isVisible();
                ui.listView->setVisible(willVisible);
                if(willVisible)
                    ui.listView->setFocus();
                else
                    ui.textEdit->setFocus();
            }
            else if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)
            {
                qDebug() << "enter";
                //selected
                if(ui.listView->isVisible())
                {
                    if(ui.textEdit->isVisible())
                        save_note(false);

                    open_note();

                    ui.listView->setVisible(false);
                    ui.textEdit->setVisible(true);
                    ui.textEdit->setFocus();
                }
            }
            else if (e->key() == Qt::Key_D && (e->modifiers() & Qt::ControlModifier))
            {
                if(ui.listView->isVisible())
                {
                    //dmp clone
                }
                else
                {
                    //delete
                }
            }
            else if (e->key() == Qt::Key_Delete)
            {
                //delete
                if(ui.listView->isVisible())
                {
                }
            }
        }
    }

    return QWidget::eventFilter(obj, event);
}

void MXNote::load()
{
    qDebug() << "app:" << QCoreApplication::applicationDirPath();

    QString folder = APP_DATA_FOLDER + "/";

    QFile file(folder + "note.json");
    if(file.exists() && file.open(QFile::ReadOnly))
    {
        QString all = file.readAll();
        qDebug() << all;
        QJsonParseError jsonError;
        QJsonDocument doucment = QJsonDocument::fromJson(all.toUtf8(), &jsonError);  // 转化为 JSON 文档
        if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
        {
            if (doucment.isArray())
            {
                const QJsonArray& array = doucment.array();
                int nSize = array.size();
                for (int i = 0; i < nSize; ++i)
                {
                    QJsonObject object = array.at(i).toObject();
                    if (object.contains("Title") && object.contains("Name"))
                    {
                        QJsonValue title = object.value("Title");
                        QJsonValue name = object.value("Name");
                        if (name.isString() && title.isString())
                        {
                            NotePtr note(new Note);
                            note->title = title.toString();
                            note->name = name.toString();
                            m_note_list.append(note->title);
                            m_all_note.push_back(note);
                        }
                    }
                }
            }
        }
    }

    if(!m_note_list.isEmpty())
    {
        m_current_note_title = m_note_list.first();
        m_current_note_name = m_all_note.first()->name;
    }
}

void MXNote::load_note()
{
    QString folder = APP_DATA_FOLDER + "/";
    QString noteFolder = folder + "note/";

    if(!m_current_note_name.isEmpty())
    {
        QString data;
        QFile cacheFile(noteFolder + m_current_note_name + ".cache");
        if (cacheFile.exists())
        {
            //使用缓存的
            cacheFile.open(QFile::ReadOnly);
            data = QString::fromUtf8(cacheFile.readAll());
        }
        else
        {
            QFile file(noteFolder + m_current_note_name + ".note");
            file.open(QFile::ReadOnly);
            data = QString::fromUtf8(file.readAll());
            file.close();
        }

        cacheFile.close();
        ui.textEdit->clear();
        ui.textEdit->setPlainText(data);
    }
}

void MXNote::save()
{
    QString folder = APP_DATA_FOLDER + "/";

    // 构建 JSON 数组
    QJsonArray jsonArray;
    int index =0;
    for(QStringList::iterator it = m_note_list.begin(); it != m_note_list.end() ; index ++, it++)
    {
        if(index >= m_all_note.count())
            break;

        QString title = *it;

        NotePtr note = m_all_note[index];
        if(!note || note->name.isEmpty())
            continue;

        QJsonObject json;
        json.insert("Title", note->title);
        json.insert("Name", note->name);

        jsonArray.append(json);
    }

    // 构建 JSON 文档
    QJsonDocument document;
    document.setArray(jsonArray);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);

    QFile file(folder + "note.json");
    if(file.exists())
    {
        file.remove();
        file.close();
    }

    file.open(QFile::WriteOnly);
    file.write(byteArray);
    file.close();

    QString strJson(byteArray);
    qDebug() << strJson;
}

void MXNote::save_note(bool toCache)
{
    bool isClosedStatus = !ui.textEdit->isVisible();//关闭状态

    //qDebug() << "MXNote::save_note " << toCache << ", note:" << m_current_note_name << ",status:" << isClosedStatus;
    QString folder = APP_DATA_FOLDER + "/";
    QString noteFolder = folder + "note/";
    if (toCache)
    {
        QString fileName(noteFolder + m_current_note_name + ".cache");
        QFile file(fileName);
        if (file.exists())
        {
            file.remove();
            file.close();
        }

        QString cache = ui.textEdit->toPlainText();
        file.open(QFile::WriteOnly);

        QTextStream streamFileOut(&file);
        streamFileOut.setCodec("UTF-8");
        streamFileOut << cache;
        streamFileOut.flush();

        streamFileOut.setGenerateByteOrderMark(true);

        file.close();
    }
    else
    {
        QFile cacheFile(noteFolder + m_current_note_name + ".cache");
        if(isClosedStatus)
        {
            //改名
            QFile file(noteFolder + m_current_note_name + ".note");
            if(file.exists())
                file.remove();
            file.close();

            cacheFile.rename(noteFolder + m_current_note_name + ".note");
        }
        else
        {
            if (cacheFile.exists())
                cacheFile.remove();

            cacheFile.close();

            QFile file(noteFolder + m_current_note_name + ".note");
            QString cache = ui.textEdit->toPlainText();

            file.open(QFile::WriteOnly);

            QTextStream streamFileOut(&file);
            streamFileOut.setCodec("UTF-8");
            streamFileOut << cache;
            streamFileOut.flush();

            streamFileOut.setGenerateByteOrderMark(true);

            file.close();
        }
    }
}

void MXNote::create_note()
{
    NotePtr note(new Note);

    QDateTime now = QDateTime::currentDateTime();
    note->title = "note " + now.toString("hh:mm:ss");

    int newIndex = m_list_model->rowCount();
    m_list_model->insertRow(newIndex);
    QModelIndex insertIndex = m_list_model->index(newIndex);
    m_list_model->setData(insertIndex,note->title);
    note->name = now.toString("yyyy-MM-dd-hh-mm-ss");
    //note->name = QString("%1").arg(QDateTime::currentMSecsSinceEpoch());
    m_note_list.push_back(note->title);
    m_all_note.push_back(note);

    m_current_note_title= note->title;
    m_current_note_name = note->name;

    ui.textEdit->clear();

    save_note(true);

    ui.listView->setCurrentIndex(insertIndex);
}

void MXNote::open_note()
{
    QString folder = APP_DATA_FOLDER + "/";
    QString noteFolder = folder + "note/";

    int row = ui.listView->currentIndex().row();
    if(row >= m_all_note.count())
        return;

    m_current_note_title = m_all_note[row]->title;
    m_current_note_name = m_all_note[row]->name;

    load_note();
}

void MXNote::rename_note()
{
    int row = ui.listView->currentIndex().row();
    if(row >= m_all_note.count())
        return;

    QModelIndex index = m_list_model->index(row);
    QString title = m_list_model->data(index).toString();
    qDebug() << "new name:" << title << ", old:" << m_current_note_title;
}

void MXNote::delete_note()
{
    int row = ui.listView->currentIndex().row();
    if(row >= m_all_note.count())
        return;


}

void MXNote::slot_list_entered(const QModelIndex &index)
{
    qDebug() << index;
}

void MXNote::slot_title_changed(const QString &title)
{
    qDebug() << title;

}
