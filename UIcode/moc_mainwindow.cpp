/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[325];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 22), // "on_setIPconfig_clicked"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 16), // "on_build_clicked"
QT_MOC_LITERAL(4, 52, 14), // "on_run_clicked"
QT_MOC_LITERAL(5, 67, 27), // "on_browseConfigFile_clicked"
QT_MOC_LITERAL(6, 95, 26), // "on_setClockDomains_clicked"
QT_MOC_LITERAL(7, 122, 35), // "on_clockDomainConfig_manual_t..."
QT_MOC_LITERAL(8, 158, 7), // "checked"
QT_MOC_LITERAL(9, 166, 27), // "setDefaultClockDomainConfig"
QT_MOC_LITERAL(10, 194, 20), // "setConfigParamLinked"
QT_MOC_LITERAL(11, 215, 22), // "QMap<QString,QString>*"
QT_MOC_LITERAL(12, 238, 10), // "configData"
QT_MOC_LITERAL(13, 249, 4), // "bar1"
QT_MOC_LITERAL(14, 254, 6), // "mySlot"
QT_MOC_LITERAL(15, 261, 4), // "arg1"
QT_MOC_LITERAL(16, 266, 16), // "submitIpConfSlot"
QT_MOC_LITERAL(17, 283, 25), // "submitClockDomainDataSlot"
QT_MOC_LITERAL(18, 309, 15) // "clockDomainData"

    },
    "MainWindow\0on_setIPconfig_clicked\0\0"
    "on_build_clicked\0on_run_clicked\0"
    "on_browseConfigFile_clicked\0"
    "on_setClockDomains_clicked\0"
    "on_clockDomainConfig_manual_toggled\0"
    "checked\0setDefaultClockDomainConfig\0"
    "setConfigParamLinked\0QMap<QString,QString>*\0"
    "configData\0bar1\0mySlot\0arg1\0"
    "submitIpConfSlot\0submitClockDomainDataSlot\0"
    "clockDomainData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    1,   79,    2, 0x08 /* Private */,
       9,    0,   82,    2, 0x08 /* Private */,
      10,    1,   83,    2, 0x0a /* Public */,
      13,    0,   86,    2, 0x0a /* Public */,
      14,    1,   87,    2, 0x0a /* Public */,
      16,    1,   90,    2, 0x0a /* Public */,
      17,    1,   93,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,   15,
    QMetaType::Void, QMetaType::QStringList,   12,
    QMetaType::Void, QMetaType::QStringList,   18,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_setIPconfig_clicked(); break;
        case 1: _t->on_build_clicked(); break;
        case 2: _t->on_run_clicked(); break;
        case 3: _t->on_browseConfigFile_clicked(); break;
        case 4: _t->on_setClockDomains_clicked(); break;
        case 5: _t->on_clockDomainConfig_manual_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->setDefaultClockDomainConfig(); break;
        case 7: _t->setConfigParamLinked((*reinterpret_cast< QMap<QString,QString>*(*)>(_a[1]))); break;
        case 8: _t->bar1(); break;
        case 9: _t->mySlot((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 10: _t->submitIpConfSlot((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 11: _t->submitClockDomainDataSlot((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
