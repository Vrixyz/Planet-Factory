/****************************************************************************
** Meta object code from reading C++ file 'PlanetCompoBox.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Generateur_new/PlanetCompoBox.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PlanetCompoBox.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PlanetCompoBox_t {
    QByteArrayData data[18];
    char stringdata[284];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_PlanetCompoBox_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_PlanetCompoBox_t qt_meta_stringdata_PlanetCompoBox = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 15),
QT_MOC_LITERAL(2, 31, 0),
QT_MOC_LITERAL(3, 32, 18),
QT_MOC_LITERAL(4, 51, 20),
QT_MOC_LITERAL(5, 72, 20),
QT_MOC_LITERAL(6, 93, 17),
QT_MOC_LITERAL(7, 111, 17),
QT_MOC_LITERAL(8, 129, 17),
QT_MOC_LITERAL(9, 147, 22),
QT_MOC_LITERAL(10, 170, 22),
QT_MOC_LITERAL(11, 193, 13),
QT_MOC_LITERAL(12, 207, 13),
QT_MOC_LITERAL(13, 221, 13),
QT_MOC_LITERAL(14, 235, 13),
QT_MOC_LITERAL(15, 249, 13),
QT_MOC_LITERAL(16, 263, 9),
QT_MOC_LITERAL(17, 273, 9)
    },
    "PlanetCompoBox\0checkPercentPla\0\0"
    "changePercentCompo\0componentPlaSelected\0"
    "componentSysSelected\0windowSysEdiCompo\0"
    "windowSysAddCompo\0windowPlaAddCompo\0"
    "windowSysCloseAndClean\0windowPlaCloseAndClean\0"
    "addCompoToSys\0ediCompoToSys\0delCompoToSys\0"
    "addCompoToPla\0delCompoToPla\0setColor1\0"
    "setColor2\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlanetCompoBox[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x0a,
       3,    1,   95,    2, 0x0a,
       4,    0,   98,    2, 0x0a,
       5,    0,   99,    2, 0x0a,
       6,    0,  100,    2, 0x0a,
       7,    0,  101,    2, 0x0a,
       8,    0,  102,    2, 0x0a,
       9,    0,  103,    2, 0x0a,
      10,    0,  104,    2, 0x0a,
      11,    0,  105,    2, 0x0a,
      12,    0,  106,    2, 0x0a,
      13,    0,  107,    2, 0x0a,
      14,    0,  108,    2, 0x0a,
      15,    1,  109,    2, 0x0a,
      16,    0,  112,    2, 0x0a,
      17,    0,  113,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PlanetCompoBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PlanetCompoBox *_t = static_cast<PlanetCompoBox *>(_o);
        switch (_id) {
        case 0: _t->checkPercentPla(); break;
        case 1: _t->changePercentCompo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->componentPlaSelected(); break;
        case 3: _t->componentSysSelected(); break;
        case 4: _t->windowSysEdiCompo(); break;
        case 5: _t->windowSysAddCompo(); break;
        case 6: _t->windowPlaAddCompo(); break;
        case 7: _t->windowSysCloseAndClean(); break;
        case 8: _t->windowPlaCloseAndClean(); break;
        case 9: _t->addCompoToSys(); break;
        case 10: _t->ediCompoToSys(); break;
        case 11: _t->delCompoToSys(); break;
        case 12: _t->addCompoToPla(); break;
        case 13: _t->delCompoToPla((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->setColor1(); break;
        case 15: _t->setColor2(); break;
        default: ;
        }
    }
}

const QMetaObject PlanetCompoBox::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PlanetCompoBox.data,
      qt_meta_data_PlanetCompoBox,  qt_static_metacall, 0, 0}
};


const QMetaObject *PlanetCompoBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlanetCompoBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PlanetCompoBox.stringdata))
        return static_cast<void*>(const_cast< PlanetCompoBox*>(this));
    return QWidget::qt_metacast(_clname);
}

int PlanetCompoBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
