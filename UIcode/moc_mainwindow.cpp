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
    QByteArrayData data[22];
    char stringdata0[411];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 30), // "submitRouterMatrixConfigSignal"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 31), // "submitRouterDataToHeatMapSignal"
QT_MOC_LITERAL(4, 75, 22), // "on_setIPconfig_clicked"
QT_MOC_LITERAL(5, 98, 16), // "on_build_clicked"
QT_MOC_LITERAL(6, 115, 14), // "on_run_clicked"
QT_MOC_LITERAL(7, 130, 27), // "on_browseConfigFile_clicked"
QT_MOC_LITERAL(8, 158, 26), // "on_setClockDomains_clicked"
QT_MOC_LITERAL(9, 185, 35), // "on_clockDomainConfig_manual_t..."
QT_MOC_LITERAL(10, 221, 7), // "checked"
QT_MOC_LITERAL(11, 229, 27), // "setDefaultClockDomainConfig"
QT_MOC_LITERAL(12, 257, 22), // "on_viewHeatMap_clicked"
QT_MOC_LITERAL(13, 280, 20), // "setConfigParamLinked"
QT_MOC_LITERAL(14, 301, 22), // "QMap<QString,QString>*"
QT_MOC_LITERAL(15, 324, 10), // "configData"
QT_MOC_LITERAL(16, 335, 4), // "bar1"
QT_MOC_LITERAL(17, 340, 6), // "mySlot"
QT_MOC_LITERAL(18, 347, 4), // "arg1"
QT_MOC_LITERAL(19, 352, 16), // "submitIpConfSlot"
QT_MOC_LITERAL(20, 369, 25), // "submitClockDomainDataSlot"
QT_MOC_LITERAL(21, 395, 15) // "clockDomainData"

    },
    "MainWindow\0submitRouterMatrixConfigSignal\0"
    "\0submitRouterDataToHeatMapSignal\0"
    "on_setIPconfig_clicked\0on_build_clicked\0"
    "on_run_clicked\0on_browseConfigFile_clicked\0"
    "on_setClockDomains_clicked\0"
    "on_clockDomainConfig_manual_toggled\0"
    "checked\0setDefaultClockDomainConfig\0"
    "on_viewHeatMap_clicked\0setConfigParamLinked\0"
    "QMap<QString,QString>*\0configData\0"
    "bar1\0mySlot\0arg1\0submitIpConfSlot\0"
    "submitClockDomainDataSlot\0clockDomainData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,
       3,    1,   92,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   95,    2, 0x08 /* Private */,
       5,    0,   96,    2, 0x08 /* Private */,
       6,    0,   97,    2, 0x08 /* Private */,
       7,    0,   98,    2, 0x08 /* Private */,
       8,    0,   99,    2, 0x08 /* Private */,
       9,    1,  100,    2, 0x08 /* Private */,
      11,    0,  103,    2, 0x08 /* Private */,
      12,    0,  104,    2, 0x08 /* Private */,
      13,    1,  105,    2, 0x0a /* Public */,
      16,    0,  108,    2, 0x0a /* Public */,
      17,    1,  109,    2, 0x0a /* Public */,
      19,    1,  112,    2, 0x0a /* Public */,
      20,    1,  115,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QStringList,    2,
    QMetaType::Void, QMetaType::QStringList,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,   18,
    QMetaType::Void, QMetaType::QStringList,   15,
    QMetaType::Void, QMetaType::QStringList,   21,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->submitRouterMatrixConfigSignal((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 1: _t->submitRouterDataToHeatMapSignal((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 2: _t->on_setIPconfig_clicked(); break;
        case 3: _t->on_build_clicked(); break;
        case 4: _t->on_run_clicked(); break;
        case 5: _t->on_browseConfigFile_clicked(); break;
        case 6: _t->on_setClockDomains_clicked(); break;
        case 7: _t->on_clockDomainConfig_manual_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->setDefaultClockDomainConfig(); break;
        case 9: _t->on_viewHeatMap_clicked(); break;
        case 10: _t->setConfigParamLinked((*reinterpret_cast< QMap<QString,QString>*(*)>(_a[1]))); break;
        case 11: _t->bar1(); break;
        case 12: _t->mySlot((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 13: _t->submitIpConfSlot((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 14: _t->submitClockDomainDataSlot((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(QStringList );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::submitRouterMatrixConfigSignal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(QStringList );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::submitRouterDataToHeatMapSignal)) {
                *result = 1;
                return;
            }
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
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::submitRouterMatrixConfigSignal(QStringList _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::submitRouterDataToHeatMapSignal(QStringList _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
