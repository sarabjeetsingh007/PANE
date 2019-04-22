/****************************************************************************
** Meta object code from reading C++ file 'setclockdomains.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "setclockdomains.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'setclockdomains.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SetClockDomains_t {
    QByteArrayData data[13];
    char stringdata0[247];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SetClockDomains_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SetClockDomains_t qt_meta_stringdata_SetClockDomains = {
    {
QT_MOC_LITERAL(0, 0, 15), // "SetClockDomains"
QT_MOC_LITERAL(1, 16, 23), // "submitClockDomainSignal"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 28), // "submitClockDomainToGUISignal"
QT_MOC_LITERAL(4, 70, 19), // "on_generate_clicked"
QT_MOC_LITERAL(5, 90, 16), // "on_clear_clicked"
QT_MOC_LITERAL(6, 107, 17), // "on_submit_clicked"
QT_MOC_LITERAL(7, 125, 13), // "isRangeFormat"
QT_MOC_LITERAL(8, 139, 7), // "mString"
QT_MOC_LITERAL(9, 147, 24), // "getListElementsFromRange"
QT_MOC_LITERAL(10, 172, 28), // "on_clockDomainSetGUI_clicked"
QT_MOC_LITERAL(11, 201, 28), // "submitRouterMatrixConfigSlot"
QT_MOC_LITERAL(12, 230, 16) // "routerMatrixData"

    },
    "SetClockDomains\0submitClockDomainSignal\0"
    "\0submitClockDomainToGUISignal\0"
    "on_generate_clicked\0on_clear_clicked\0"
    "on_submit_clicked\0isRangeFormat\0mString\0"
    "getListElementsFromRange\0"
    "on_clockDomainSetGUI_clicked\0"
    "submitRouterMatrixConfigSlot\0"
    "routerMatrixData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SetClockDomains[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       3,    1,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   65,    2, 0x08 /* Private */,
       5,    0,   66,    2, 0x08 /* Private */,
       6,    0,   67,    2, 0x08 /* Private */,
       7,    1,   68,    2, 0x08 /* Private */,
       9,    1,   71,    2, 0x08 /* Private */,
      10,    0,   74,    2, 0x08 /* Private */,
      11,    1,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QStringList,    2,
    QMetaType::Void, QMetaType::QStringList,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QString,    8,
    QMetaType::QString, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,   12,

       0        // eod
};

void SetClockDomains::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SetClockDomains *_t = static_cast<SetClockDomains *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->submitClockDomainSignal((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 1: _t->submitClockDomainToGUISignal((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 2: _t->on_generate_clicked(); break;
        case 3: _t->on_clear_clicked(); break;
        case 4: _t->on_submit_clicked(); break;
        case 5: { bool _r = _t->isRangeFormat((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: { QString _r = _t->getListElementsFromRange((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 7: _t->on_clockDomainSetGUI_clicked(); break;
        case 8: _t->submitRouterMatrixConfigSlot((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SetClockDomains::*_t)(QStringList );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SetClockDomains::submitClockDomainSignal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (SetClockDomains::*_t)(QStringList );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SetClockDomains::submitClockDomainToGUISignal)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject SetClockDomains::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SetClockDomains.data,
      qt_meta_data_SetClockDomains,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SetClockDomains::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SetClockDomains::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SetClockDomains.stringdata0))
        return static_cast<void*>(const_cast< SetClockDomains*>(this));
    return QWidget::qt_metacast(_clname);
}

int SetClockDomains::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void SetClockDomains::submitClockDomainSignal(QStringList _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SetClockDomains::submitClockDomainToGUISignal(QStringList _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
