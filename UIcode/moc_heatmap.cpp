/****************************************************************************
** Meta object code from reading C++ file 'heatmap.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "heatmap.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'heatmap.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HeatMap_t {
    QByteArrayData data[60];
    char stringdata0[940];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HeatMap_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HeatMap_t qt_meta_stringdata_HeatMap = {
    {
QT_MOC_LITERAL(0, 0, 7), // "HeatMap"
QT_MOC_LITERAL(1, 8, 10), // "addSideNav"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 9), // "addHeader"
QT_MOC_LITERAL(4, 30, 14), // "addScaleValues"
QT_MOC_LITERAL(5, 45, 12), // "labelOffsetX"
QT_MOC_LITERAL(6, 58, 12), // "labelOffsetY"
QT_MOC_LITERAL(7, 71, 6), // "minVal"
QT_MOC_LITERAL(8, 78, 6), // "maxVal"
QT_MOC_LITERAL(9, 85, 9), // "scaleName"
QT_MOC_LITERAL(10, 95, 16), // "addTrafficCanvas"
QT_MOC_LITERAL(11, 112, 14), // "getRouterStats"
QT_MOC_LITERAL(12, 127, 23), // "createRouterPacketsData"
QT_MOC_LITERAL(13, 151, 18), // "QList<QList<int> >"
QT_MOC_LITERAL(14, 170, 11), // "packetsData"
QT_MOC_LITERAL(15, 182, 24), // "createHorizontalLinkData"
QT_MOC_LITERAL(16, 207, 8), // "linkData"
QT_MOC_LITERAL(17, 216, 22), // "createVerticalLinkData"
QT_MOC_LITERAL(18, 239, 10), // "findMinMax"
QT_MOC_LITERAL(19, 250, 13), // "QList<double>"
QT_MOC_LITERAL(20, 264, 20), // "colorGeneratorValues"
QT_MOC_LITERAL(21, 285, 23), // "setColorGradientSamples"
QT_MOC_LITERAL(22, 309, 14), // "QList<QString>"
QT_MOC_LITERAL(23, 324, 16), // "colorInterpolate"
QT_MOC_LITERAL(24, 341, 6), // "pBegin"
QT_MOC_LITERAL(25, 348, 4), // "pEnd"
QT_MOC_LITERAL(26, 353, 5), // "pStep"
QT_MOC_LITERAL(27, 359, 4), // "pMax"
QT_MOC_LITERAL(28, 364, 17), // "getPreferredColor"
QT_MOC_LITERAL(29, 382, 4), // "data"
QT_MOC_LITERAL(30, 387, 3), // "min"
QT_MOC_LITERAL(31, 391, 3), // "max"
QT_MOC_LITERAL(32, 395, 17), // "paintRouterMatrix"
QT_MOC_LITERAL(33, 413, 4), // "rows"
QT_MOC_LITERAL(34, 418, 4), // "cols"
QT_MOC_LITERAL(35, 423, 33), // "QList<QList<QMap<QString,int>..."
QT_MOC_LITERAL(36, 457, 16), // "packetInfoMatrix"
QT_MOC_LITERAL(37, 474, 31), // "paintHorizontalSignalPathMatrix"
QT_MOC_LITERAL(38, 506, 13), // "trafficMatrix"
QT_MOC_LITERAL(39, 520, 29), // "paintVerticalSignalPathMatrix"
QT_MOC_LITERAL(40, 550, 11), // "paintRouter"
QT_MOC_LITERAL(41, 562, 7), // "offsets"
QT_MOC_LITERAL(42, 570, 17), // "QMap<QString,int>"
QT_MOC_LITERAL(43, 588, 17), // "routerPacketsInfo"
QT_MOC_LITERAL(44, 606, 25), // "paintHorizontalSignalPath"
QT_MOC_LITERAL(45, 632, 23), // "horizontalSignalTraffic"
QT_MOC_LITERAL(46, 656, 23), // "paintVerticalSignalPath"
QT_MOC_LITERAL(47, 680, 21), // "verticalSignalTraffic"
QT_MOC_LITERAL(48, 702, 16), // "paintRouterUpper"
QT_MOC_LITERAL(49, 719, 12), // "packetsCount"
QT_MOC_LITERAL(50, 732, 16), // "paintRouterLower"
QT_MOC_LITERAL(51, 749, 25), // "paintHorizontalArrowRight"
QT_MOC_LITERAL(52, 775, 12), // "trafficValue"
QT_MOC_LITERAL(53, 788, 24), // "paintHorizontalArrowLeft"
QT_MOC_LITERAL(54, 813, 20), // "paintVerticalArrowUp"
QT_MOC_LITERAL(55, 834, 22), // "paintVerticalArrowDown"
QT_MOC_LITERAL(56, 857, 16), // "on_print_clicked"
QT_MOC_LITERAL(57, 874, 24), // "routerLinksDataArrayInit"
QT_MOC_LITERAL(58, 899, 29), // "submitRouterDataToHeatMapSlot"
QT_MOC_LITERAL(59, 929, 10) // "routerData"

    },
    "HeatMap\0addSideNav\0\0addHeader\0"
    "addScaleValues\0labelOffsetX\0labelOffsetY\0"
    "minVal\0maxVal\0scaleName\0addTrafficCanvas\0"
    "getRouterStats\0createRouterPacketsData\0"
    "QList<QList<int> >\0packetsData\0"
    "createHorizontalLinkData\0linkData\0"
    "createVerticalLinkData\0findMinMax\0"
    "QList<double>\0colorGeneratorValues\0"
    "setColorGradientSamples\0QList<QString>\0"
    "colorInterpolate\0pBegin\0pEnd\0pStep\0"
    "pMax\0getPreferredColor\0data\0min\0max\0"
    "paintRouterMatrix\0rows\0cols\0"
    "QList<QList<QMap<QString,int> > >\0"
    "packetInfoMatrix\0paintHorizontalSignalPathMatrix\0"
    "trafficMatrix\0paintVerticalSignalPathMatrix\0"
    "paintRouter\0offsets\0QMap<QString,int>\0"
    "routerPacketsInfo\0paintHorizontalSignalPath\0"
    "horizontalSignalTraffic\0paintVerticalSignalPath\0"
    "verticalSignalTraffic\0paintRouterUpper\0"
    "packetsCount\0paintRouterLower\0"
    "paintHorizontalArrowRight\0trafficValue\0"
    "paintHorizontalArrowLeft\0paintVerticalArrowUp\0"
    "paintVerticalArrowDown\0on_print_clicked\0"
    "routerLinksDataArrayInit\0"
    "submitRouterDataToHeatMapSlot\0routerData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HeatMap[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      27,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  149,    2, 0x08 /* Private */,
       3,    0,  150,    2, 0x08 /* Private */,
       4,    5,  151,    2, 0x08 /* Private */,
      10,    0,  162,    2, 0x08 /* Private */,
      11,    0,  163,    2, 0x08 /* Private */,
      12,    1,  164,    2, 0x08 /* Private */,
      15,    1,  167,    2, 0x08 /* Private */,
      17,    1,  170,    2, 0x08 /* Private */,
      18,    1,  173,    2, 0x08 /* Private */,
      21,    1,  176,    2, 0x08 /* Private */,
      23,    4,  179,    2, 0x08 /* Private */,
      28,    4,  188,    2, 0x08 /* Private */,
      32,    3,  197,    2, 0x08 /* Private */,
      37,    3,  204,    2, 0x08 /* Private */,
      39,    3,  211,    2, 0x08 /* Private */,
      40,    2,  218,    2, 0x08 /* Private */,
      44,    2,  223,    2, 0x08 /* Private */,
      46,    2,  228,    2, 0x08 /* Private */,
      48,    2,  233,    2, 0x08 /* Private */,
      50,    2,  238,    2, 0x08 /* Private */,
      51,    2,  243,    2, 0x08 /* Private */,
      53,    2,  248,    2, 0x08 /* Private */,
      54,    2,  253,    2, 0x08 /* Private */,
      55,    2,  258,    2, 0x08 /* Private */,
      56,    0,  263,    2, 0x08 /* Private */,
      57,    0,  264,    2, 0x08 /* Private */,
      58,    1,  265,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString,    5,    6,    7,    8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 13,   16,
    QMetaType::Void, 0x80000000 | 13,   16,
    0x80000000 | 19, 0x80000000 | 19,   20,
    0x80000000 | 22, 0x80000000 | 19,   20,
    QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   24,   25,   26,   27,
    QMetaType::Int, QMetaType::Int, QMetaType::Double, QMetaType::Double, 0x80000000 | 19,   29,   30,   31,   20,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 35,   33,   34,   36,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 35,   33,   34,   38,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 35,   33,   34,   38,
    QMetaType::Void, QMetaType::QPoint, 0x80000000 | 42,   41,   43,
    QMetaType::Void, QMetaType::QPoint, 0x80000000 | 42,   41,   45,
    QMetaType::Void, QMetaType::QPoint, 0x80000000 | 42,   41,   47,
    QMetaType::Void, QMetaType::QPoint, QMetaType::Int,   41,   49,
    QMetaType::Void, QMetaType::QPoint, QMetaType::Int,   41,   49,
    QMetaType::Void, QMetaType::QPoint, QMetaType::Int,   41,   52,
    QMetaType::Void, QMetaType::QPoint, QMetaType::Int,   41,   52,
    QMetaType::Void, QMetaType::QPoint, QMetaType::Int,   41,   52,
    QMetaType::Void, QMetaType::QPoint, QMetaType::Int,   41,   52,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,   59,

       0        // eod
};

void HeatMap::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HeatMap *_t = static_cast<HeatMap *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addSideNav(); break;
        case 1: _t->addHeader(); break;
        case 2: _t->addScaleValues((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 3: _t->addTrafficCanvas(); break;
        case 4: _t->getRouterStats(); break;
        case 5: _t->createRouterPacketsData((*reinterpret_cast< QList<QList<int> >(*)>(_a[1]))); break;
        case 6: _t->createHorizontalLinkData((*reinterpret_cast< QList<QList<int> >(*)>(_a[1]))); break;
        case 7: _t->createVerticalLinkData((*reinterpret_cast< QList<QList<int> >(*)>(_a[1]))); break;
        case 8: { QList<double> _r = _t->findMinMax((*reinterpret_cast< QList<double>(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QList<double>*>(_a[0]) = _r; }  break;
        case 9: { QList<QString> _r = _t->setColorGradientSamples((*reinterpret_cast< QList<double>(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QList<QString>*>(_a[0]) = _r; }  break;
        case 10: { int _r = _t->colorInterpolate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 11: { int _r = _t->getPreferredColor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< QList<double>(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 12: _t->paintRouterMatrix((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QList<QList<QMap<QString,int> > >(*)>(_a[3]))); break;
        case 13: _t->paintHorizontalSignalPathMatrix((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QList<QList<QMap<QString,int> > >(*)>(_a[3]))); break;
        case 14: _t->paintVerticalSignalPathMatrix((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QList<QList<QMap<QString,int> > >(*)>(_a[3]))); break;
        case 15: _t->paintRouter((*reinterpret_cast< QPoint(*)>(_a[1])),(*reinterpret_cast< QMap<QString,int>(*)>(_a[2]))); break;
        case 16: _t->paintHorizontalSignalPath((*reinterpret_cast< QPoint(*)>(_a[1])),(*reinterpret_cast< QMap<QString,int>(*)>(_a[2]))); break;
        case 17: _t->paintVerticalSignalPath((*reinterpret_cast< QPoint(*)>(_a[1])),(*reinterpret_cast< QMap<QString,int>(*)>(_a[2]))); break;
        case 18: _t->paintRouterUpper((*reinterpret_cast< QPoint(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 19: _t->paintRouterLower((*reinterpret_cast< QPoint(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 20: _t->paintHorizontalArrowRight((*reinterpret_cast< QPoint(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 21: _t->paintHorizontalArrowLeft((*reinterpret_cast< QPoint(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 22: _t->paintVerticalArrowUp((*reinterpret_cast< QPoint(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 23: _t->paintVerticalArrowDown((*reinterpret_cast< QPoint(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 24: _t->on_print_clicked(); break;
        case 25: _t->routerLinksDataArrayInit(); break;
        case 26: _t->submitRouterDataToHeatMapSlot((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QList<int> > >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QList<int> > >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QList<int> > >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<double> >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<double> >(); break;
            }
            break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 3:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<double> >(); break;
            }
            break;
        }
    }
}

const QMetaObject HeatMap::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_HeatMap.data,
      qt_meta_data_HeatMap,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *HeatMap::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HeatMap::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_HeatMap.stringdata0))
        return static_cast<void*>(const_cast< HeatMap*>(this));
    return QWidget::qt_metacast(_clname);
}

int HeatMap::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 27)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 27;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 27)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 27;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
