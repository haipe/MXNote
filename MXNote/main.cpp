#include "mxnote.h"
#include <QtWidgets/QApplication>
#include <QSharedMemory>
#include <QMessageBox>
#include <QHotkey>

#define START_BACKGROUND

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MXNote w;

#if !defined(_DEBUG)
    QSharedMemory shared("MXNote_memory");
    if (shared.attach())//共享内存被占用则直接返回
    {
        w.slot_help();
        return 0;
    }

    shared.create(1);
#endif
        
    QHotkey* startKey = new QHotkey(QKeySequence(Qt::ShiftModifier | Qt::ControlModifier | Qt::Key_S), true, &w);

    QObject::connect(startKey, &QHotkey::activated, &w, &MXNote::slot_hotkey_show);

    QHotkey* endKey = new QHotkey(QKeySequence(Qt::ShiftModifier | Qt::ControlModifier | Qt::Key_Q), true, &w);

    QObject::connect(endKey, &QHotkey::activated, &w, &MXNote::slot_hotkey_exit);

    w.show();

    return a.exec();
}
