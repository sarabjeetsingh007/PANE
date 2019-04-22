/****************************************************************************
** Meta object code from reading C++ file 'setclockdomaingui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "setclockdomaingui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'setclockdomaingui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SetClockDomainGUI_t {
    QByteArrayData data[13];
    char stringdata0[232];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SetClockDomainGUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SetClockDomainGUI_t qt_meta_stringdata_SetClockDomainGUI = {
    {
QT_MOC_LITERAL(0, 0, 17), // "SetClockDomainGUI"
QT_MOC_LITERAL(1, 18, 23), // "submitClockDomainSignal"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 18), // "routersButtonGroup"
QT_MOC_LITERAL(4, 62, 16), // "QAbstractButton*"
QT_MOC_LITERAL(5, 79, 7), // "mButton"
QT_MOC_LITERAL(6, 87, 18), // "createRouterMatrix"
QT_MOC_LITERAL(7, 106, 21), // "createClockDomainList"
QT_MOC_LITERAL(8, 128, 21), // "clockDomainOnSelected"
QT_MOC_LITERAL(9, 150, 16), // "routerOnSelected"
QT_MOC_LITERAL(10, 167, 17), // "on_submit_clicked"
QT_MOC_LITERAL(11, 185, 30), // "submitClockDomainDataToGUISlot"
QT_MOC_LITERAL(12, 216, 15) // "clockDomainData"

    },
    "SetClockDomainGUI\0submitClockDomainSignal\0"
    "\0routersButtonGroup\0QAbstractButton*\0"
    "mButton\0createRouterMatrix\0"
    "createClockDomainList\0clockDomainOnSelected\0"
    "routerOnSelected\0on_submit_clicked\0"
    "submitClockDomainDataToGUISlot\0"
    "clockDomainData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SetClockDomainGUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   57,    2, 0x08 /* Private */,
       6,    0,   60,    2, 0x08 /* Private */,
       7,    0,   61,    2, 0x08 /* Private */,
       8,    1,   62,    2, 0x08 /* Private */,
       9,    1,   65,    2, 0x08 /* Private */,
      10,    0,   68,    2, 0x08 /* Private */,
      11,    1,   69,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QStringList,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,   12,

       0        // eod
};

void SetClockDomainGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SetClockDomainGUI *_t = static_cast<SetClockDomainGUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->submitClockDomainSignal((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 1: _t->routersButtonGroup((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 2: _t->createRouterMatrix(); break;
        case 3: _t->createClockDomainList(); break;
        case 4: _t->clockDomainOnSelected((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 5: _t->routerOnSelected((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 6: _t->on_submit_clicked(); break;
        case 7: _t->submitClockDomainDataToGUISlot((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractButton* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractButton* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractButton* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SetClockDomainGUI::*_t)(QStringList );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SetClockDomainGUI::submitClockDomainSignal)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject SetClockDomainGUI::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SetClockDomainGUI.data,
      qt_meta_data_SetClockDomainGUI,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SetClockDomainGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SetClockDomainGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SetClockDomainGUI.stringdata0))
        return static_cast<void*>(const_cast< SetClockDomainGUI*>(this));
    return QWidget::qt_metacast(_clname);
}

int SetClockDomainGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void SetClockDomainGUI::submitClockDomainSignal(QStringList _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
